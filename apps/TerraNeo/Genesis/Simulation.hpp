/*
 * Copyright (c) 2024 Eugenio D'Ascoli.
 *
 * This file is part of HyTeG
 * (see https://i10git.cs.fau.de/hyteg/hyteg).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "hyteg/solvers/solvertemplates/StokesSolverTemplates.hpp"

#include "Convection.hpp"
#include "terraneo/dataimport/ParameterIO.hpp"

////////////////////////
//   Initialisation   //
////////////////////////

#include "ModelInit.hpp"
#include "SimulationIO.hpp"

namespace terraneo {

/////////////////////////
//   Simulation Step   //
/////////////////////////

void ConvectionSimulation::step()
{
   // _output->write( TN.domainParameters.maxLevel, 0 );

   // solveStokes();

   // _output->write( TN.domainParameters.maxLevel, 1 );

   // return;

   if ( TN.simulationParameters.timeStep == 0 )
   {
      //set up logging
      WALBERLA_ROOT_SECTION()
      {
         walberla::logging::Logging::instance()->includeLoggingToFile( TN.outputParameters.outputDirectory + "/" +
                                                                       TN.outputParameters.outputBaseName + ".out" );
      }

      // setupStokesRHS();
      if ( TN.outputParameters.ADIOS2StartFromCheckpoint )
      {
         checkpointImporter->restoreFunction( *temperature );
         solveStokes();
         dataOutput();
      }
      else
      {
         dataOutput();
         solveStokes();
      }
      ++TN.simulationParameters.timeStep;
      stokesLHSPrev->assign( { real_c( 1 ) }, { *stokesLHS }, TN.domainParameters.maxLevel, All );
   } //end timestep0 stokes

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "-------- Time step: " << TN.simulationParameters.timeStep << " --------" );

   real_t vMax =
       velocityMaxMagnitude( stokesLHS->uvw(), *scalarTmp, *velocityMagnitudeSquared, TN.domainParameters.maxLevel, All );

   TN.simulationParameters.dtPrev = TN.simulationParameters.dt;

   if ( TN.simulationParameters.fixedTimestep )
   {
      TN.simulationParameters.dt = TN.simulationParameters.dtConstant;
   }

   else
   {
      TN.simulationParameters.dt = ( TN.simulationParameters.cflMax / vMax ) * TN.simulationParameters.hMin;
   }

   TN.simulationParameters.modelTime += TN.simulationParameters.dt;

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT(
       "Step size: " << ( TN.simulationParameters.dt * TN.physicalParameters.mantleThickness ) /
                            ( TN.physicalParameters.characteristicVelocity * TN.simulationParameters.plateVelocityScaling *
                              TN.simulationParameters.secondsPerMyr )
                     << " Ma" );
   WALBERLA_LOG_INFO_ON_ROOT( "Velocity max magnitude: " << vMax << " " );

   if ( TN.simulationParameters.simulationType == "CirculationModel" )
   {
      //update current and previous age
      TN.simulationParameters.agePrev = TN.simulationParameters.ageMa;
      TN.simulationParameters.ageMa -= ( TN.simulationParameters.dt * TN.physicalParameters.mantleThickness ) /
                                       ( TN.physicalParameters.characteristicVelocity *
                                         TN.simulationParameters.plateVelocityScaling * TN.simulationParameters.secondsPerMyr );

      //if the time goes below finalAge Ma we return from current step and finish the circulation model in main
      if ( TN.simulationParameters.ageMa <= TN.simulationParameters.finalAge )
      {
         return;
      }
      WALBERLA_LOG_INFO_ON_ROOT( "Model age: " << TN.simulationParameters.ageMa << " Ma" )
   }

   TN.simulationParameters.modelRunTimeMa =
       ( TN.simulationParameters.modelTime * TN.physicalParameters.mantleThickness ) /
       ( TN.physicalParameters.characteristicVelocity * TN.simulationParameters.plateVelocityScaling *
         TN.simulationParameters.secondsPerMyr );

   WALBERLA_LOG_INFO_ON_ROOT( "Model runtime: " << TN.simulationParameters.modelRunTimeMa << " Ma" )

   //######################################################//
   //                  ENERGY EQUATION                     //
   //######################################################//

   /*############ EXTRAPOLATE FIELDS FOR RHS ############*/

   if ( TN.simulationParameters.timeStep > 1 )
   {
      stokesLHSExtrapolated->assign(
          {
              real_c( 1 ) + TN.simulationParameters.dt / TN.simulationParameters.dtPrev,
              -TN.simulationParameters.dt / TN.simulationParameters.dtPrev,
          },
          { *stokesLHS, *stokesLHSPrev },
          TN.domainParameters.maxLevel,
          All );

      temperatureExtrapolated->assign(
          {
              real_c( 1 ) + TN.simulationParameters.dt / TN.simulationParameters.dtPrev,
              -TN.simulationParameters.dt / TN.simulationParameters.dtPrev,
          },
          { *temperature, *temperaturePrev },
          TN.domainParameters.maxLevel,
          All );
   }
   else
   {
      stokesLHSExtrapolated->assign( { real_c( 1 ) }, { *stokesLHS }, TN.domainParameters.maxLevel, All );
      temperatureExtrapolated->assign( { real_c( 1 ) }, { *temperature }, TN.domainParameters.maxLevel, All );
   }

   if ( TN.simulationParameters.simulationType == "CirculationModel" )
   {
      updatePlateVelocities( *stokesLHSExtrapolated );
   }

   /*############ ADVECTION STEP ############*/

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "-----------------------------" );
   WALBERLA_LOG_INFO_ON_ROOT( "------- Advection Step ------" );
   WALBERLA_LOG_INFO_ON_ROOT( "-----------------------------" );
   WALBERLA_LOG_INFO_ON_ROOT( "" );

   transportOperator->step( *temperature,
                            stokesLHS->uvw(),
                            stokesLHSPrev->uvw(),
                            TN.domainParameters.maxLevel,
                            All,
                            TN.simulationParameters.dt,
                            1,
                            true );

   // Reset temperature on boundary to initial values

   temperaturePrev->assign( { real_c( 1 ) }, { *temperature }, TN.domainParameters.maxLevel, All );

   for ( uint_t l = TN.domainParameters.minLevel; l <= TN.domainParameters.maxLevel; l++ )
   {
      if ( TN.initialisationParameters.temperatureNoise )
      {
         temperature->interpolate(
             temperatureWhiteNoise( *temperatureInitParams, *temperatureReferenceFct, TN.initialisationParameters.noiseFactor ),
             l,
             DirichletBoundary );
      }
      else
      {
         temperature->interpolate( temperatureSPH( *temperatureInitParams,
                                                   *temperatureReferenceFct,
                                                   TN.initialisationParameters.tempInit,
                                                   TN.initialisationParameters.deg,
                                                   TN.initialisationParameters.ord,
                                                   TN.initialisationParameters.lmax,
                                                   TN.initialisationParameters.lmin,
                                                   TN.initialisationParameters.superposition,
                                                   TN.initialisationParameters.buoyancyFactor,
                                                   TN.physicalParameters.initialTemperatureSteepness ),
                                   l,
                                   DirichletBoundary );
      }
   }

   /*############ ENERGY STEP ############*/

   // setupEnergyRHS();

   solveEnergy();

   //######################################################//
   //                  STOKES EQUATIONS                    //
   //######################################################//

   // update velocity field storing the velocity field of the Prev timestep
   stokesLHSPrev->assign( { real_c( 1 ) }, { *stokesLHS }, TN.domainParameters.maxLevel, All );

   if ( TN.simulationParameters.simulationType == "CirculationModel" )
   {
      //update plate velocity boundary condition prior to stokes solve
      //update if >=1Myr has passed since Prev update
      if ( ( ( TN.simulationParameters.plateAge - TN.simulationParameters.ageMa ) >= real_c( 1 ) ) )
      {
         WALBERLA_LOG_INFO_ON_ROOT( "" );
         WALBERLA_LOG_INFO_ON_ROOT( "Update plates" );

         //save the age of the current update (rounded to 1Myr intervals)
         TN.simulationParameters.plateAge = std::round( TN.simulationParameters.ageMa );
         updatePlateVelocities( *stokesLHS );
      }

      WALBERLA_LOG_INFO_ON_ROOT( "Plage age: " << TN.simulationParameters.plateAge << " Ma" )
   }

   //update ref temp vector based on new temperature field
   TN.physicalParameters.temperatureProfile = temperatureProfiles->mean;

   solveStokes();

   //######################################################//
   //                  DUMP OUTPUT                         //
   //######################################################//

   if ( TN.outputParameters.outputMyr && ( ( TN.simulationParameters.modelRunTimeMa - TN.outputParameters.prevOutputTime ) >=
                                           real_c( TN.outputParameters.outputIntervalMyr ) ) )
   {
      dataOutput();
   }

   if ( !TN.outputParameters.outputMyr )
   {
      dataOutput();
   }

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "Finished step: " << TN.simulationParameters.timeStep );
   ++TN.simulationParameters.timeStep;
}

void ConvectionSimulation::solveEnergy()
{
   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "------------------------------" );
   WALBERLA_LOG_INFO_ON_ROOT( "------- Energy Solve ------" );
   WALBERLA_LOG_INFO_ON_ROOT( "------------------------------" );
   WALBERLA_LOG_INFO_ON_ROOT( "" );

   transportOperatorTALA->setTimestep( TN.simulationParameters.dt );

   std::function< real_t( const Point3D&, const std::vector< real_t >& ) > shearHeatingCoeffCalc =
       [=]( const Point3D&, const std::vector< real_t >& density ) {
          return TN.physicalParameters.dissipationNumber * TN.physicalParameters.pecletNumber /
                 ( TN.physicalParameters.rayleighNumber * density[0] );
       };

   std::function< real_t( const Point3D& ) > internalHeatingCoeffCalc = [=]( const Point3D& ) {
      real_t intHeatingFactor = 1.0;
      return TN.physicalParameters.hNumber * intHeatingFactor;
   };

   adiabaticTermCoeff->interpolate( TN.physicalParameters.dissipationNumber, TN.domainParameters.maxLevel, All );
   shearHeatingTermCoeff->interpolate( shearHeatingCoeffCalc, { *densityFE }, TN.domainParameters.maxLevel, All );
   surfTempCoeff->interpolate( TN.physicalParameters.surfaceTemp /
                                   ( TN.physicalParameters.cmbTemp - TN.physicalParameters.surfaceTemp ),
                               TN.domainParameters.maxLevel,
                               All );
   constEnergyCoeff->interpolate( internalHeatingCoeffCalc, TN.domainParameters.maxLevel, All );

   // Assemble RHS
   transportOperatorTALA->applyRHS( *energyRHSWeak, TN.domainParameters.maxLevel, All );

   // Solve
   transportSolverTALA->solve( *transportOperatorTALA, *temperature, *energyRHSWeak, TN.domainParameters.maxLevel );

   transportOperatorTALA->incrementTimestep();
}

void ConvectionSimulation::setupStokesRHS()
{
   for ( uint_t l = TN.domainParameters.minLevel; l <= TN.domainParameters.maxLevel; l++ )
   {
      // std::function to calculate temperature difference between temperature and reference/background temperature

      ////////////////////
      //    Momentum    //
      ////////////////////

      temperatureDev->assign( { 1.0, -1.0 }, { *temperature, *temperatureReference }, l, All );

      // Multiply with mass matrix (of velocity space -- P2) to get the weak form

      P2MassOperator->apply( *temperatureDev, stokesRHS->uvw()[0], l, All );
      P2MassOperator->apply( *temperatureDev, stokesRHS->uvw()[1], l, All );
      P2MassOperator->apply( *temperatureDev, stokesRHS->uvw()[2], l, All );

      // Multiply current RHS with rho and non-dimensionalised numbers
      std::function< real_t( const Point3D&, const std::vector< real_t >& ) > momentumFactors =
          [&]( const Point3D& x, const std::vector< real_t >& deltaT ) {
             return ( -( TN.physicalParameters.rayleighNumber / TN.physicalParameters.pecletNumber ) * densityFunction( x ) *
                      deltaT[0] );
          };

      // Interpolate functions to RHS
      stokesRHS->uvw()[0].interpolate( momentumFactors, { stokesRHS->uvw()[0] }, l, All );
      stokesRHS->uvw()[1].interpolate( momentumFactors, { stokesRHS->uvw()[1] }, l, All );
      stokesRHS->uvw()[2].interpolate( momentumFactors, { stokesRHS->uvw()[2] }, l, All );

      // multply with outward normal (for gravity)
      stokesRHS->uvw().multElementwise( { stokesRHS->uvw(), *inwardNormal }, l );

      /////////////////
      //    Mass    //
      ////////////////

      // Provide the option to run incompressible simulations for test or educational purposes
      if ( TN.simulationParameters.compressible )
      {
         frozenVelocityRHSX->apply( stokesLHS->uvw().component( 0U ), stokesRHS->p(), l, All, Replace );
         frozenVelocityRHSY->apply( stokesLHS->uvw().component( 1U ), stokesRHS->p(), l, All, Add );
         frozenVelocityRHSZ->apply( stokesLHS->uvw().component( 2U ), stokesRHS->p(), l, All, Add );

         stokesRHS->p().assign( { -1.0 }, { stokesRHS->p() }, l, All );
      }
      else
      {
         stokesRHS->p().interpolate( real_c( 0 ), l, All );
      }
   }
}

// void ConvectionSimulation::setupEnergyRHS()
// {
//    std::function< real_t( const Point3D&, const std::vector< real_t >& ) > EnergyRHS =
//        [&]( const Point3D& x, const std::vector< real_t >& fields ) {
//           // Currently the internal heating function is a scalar (hNumber)
//           real_t retVal = real_c( 1 ) * TN.physicalParameters.hNumber; //internal heating term

//           if ( TN.simulationParameters.compressible )
//           {
//              //add adiabatic heating term
//              retVal += TN.physicalParameters.dissipationNumber *
//                        ( fields[0] * fields[3] + fields[1] * fields[4] + fields[2] * fields[5] ) * //this part is u dot g
//                        ( fields[6] + ( TN.physicalParameters.surfaceTemp /
//                                        ( TN.physicalParameters.cmbTemp - TN.physicalParameters.surfaceTemp ) ) );
//           }

//           if ( TN.simulationParameters.shearHeating )
//           {
//              WALBERLA_UNUSED( x );
//              //add shear heating term
//              WALBERLA_LOG_INFO_ON_ROOT( "No shear-heating available currently -> on my ToDo list!" );
//              // For the shear-heating term update grad U is necessary which is currently not applicable
//              // using the new solvers -> Fix this!
//           }
//           return retVal;
//        };
//    for ( uint_t l = TN.domainParameters.minLevel; l <= TN.domainParameters.maxLevel; l++ )
//    {
//       energyRHS->interpolate( EnergyRHS,
//                               { stokesLHS->uvw()[0],  //fields[0]
//                                 stokesLHS->uvw()[1],  //fields[1]
//                                 stokesLHS->uvw()[2],  //fields[2]
//                                 ( *inwardNormal )[0], //fields[3]
//                                 ( *inwardNormal )[1], //fields[4]
//                                 ( *inwardNormal )[2], //fields[5]
//                                 *temperature },       //fields[6]
//                               l,
//                               All );
//       // derive weak formulation of the right hand side
//       P2MassOperator->apply( *energyRHS, *energyRHSWeak, l, All );
//    }
// }

void ConvectionSimulation::solveStokes()
{
   if ( TN.simulationParameters.tempDependentViscosity )
   {
      updateRefViscosity();
   }

   if ( TN.simulationParameters.tempDependentViscosity && TN.simulationParameters.resetSolver &&
        ( TN.simulationParameters.timeStep != 0 ) &&
        ( TN.simulationParameters.timeStep % TN.simulationParameters.resetSolverFrequency == 0 ) )
   {
      WALBERLA_LOG_INFO_ON_ROOT( "---------------------------------------------" );
      WALBERLA_LOG_INFO_ON_ROOT( "------ Resetting Solvers and Operators ------" );
      WALBERLA_LOG_INFO_ON_ROOT( "---------------------------------------------" );

      std::function< real_t( const Point3D& ) > zeros = []( const Point3D& ) { return real_c( 0 ); };

      for ( uint_t l = TN.domainParameters.minLevel; l <= TN.domainParameters.maxLevel; ++l )
      {
         //save current velocity in temorary, as U and F must be altered for solver setup
         stokesTmp->assign( { real_c( 1 ) }, { *stokesLHS }, l, All );
         stokesRHS->interpolate( { zeros, zeros, zeros }, l, All );
      }

      // for temperature dependent viscosity the spectral radius might change after several solving
      // iterations -> resetting solvers and operators

      setupSolversAndOperators();

      //after setup, reset velocity to values stored in temporary
      for ( uint_t l = TN.domainParameters.minLevel; l <= TN.domainParameters.maxLevel; ++l )
      {
         stokesLHS->assign( { real_c( 1 ) }, { *stokesTmp }, l, All );
      }

      WALBERLA_LOG_INFO_ON_ROOT( "-------------------------------------------------------" );
      WALBERLA_LOG_INFO_ON_ROOT( "------ Resetting Solvers and Operators: Finished ------" );
      WALBERLA_LOG_INFO_ON_ROOT( "-------------------------------------------------------" );
   }

   setupStokesRHS();

   if ( TN.simulationParameters.timeStep == 0 )
   {
      WALBERLA_LOG_INFO_ON_ROOT( "----------------------------------" );
      WALBERLA_LOG_INFO_ON_ROOT( "------ Initial Stokes solve ------" );
      WALBERLA_LOG_INFO_ON_ROOT( "----------------------------------" );
   }
   else
   {
      WALBERLA_LOG_INFO_ON_ROOT( "--------------------------" );
      WALBERLA_LOG_INFO_ON_ROOT( "------ Stokes solve ------" );
      WALBERLA_LOG_INFO_ON_ROOT( "--------------------------" );
   }

   walberla::WcTimer localTimer;
   real_t            stokesResidual = calculateStokesResidual( TN.domainParameters.maxLevel );

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "Stokes residual (initial): " << stokesResidual );
   WALBERLA_LOG_INFO_ON_ROOT( "" );

   if ( stokesResidual > TN.solverParameters.stokesKillTolerance && ( TN.simulationParameters.timeStep != 0 ) )
   {
      WALBERLA_ABORT( "Residual " << stokesResidual << " exceeds tolerance of " << TN.solverParameters.stokesKillTolerance
                                  << ". ABORTING SIMULATION. " );
   }

   localTimer.start();
   storage->getTimingTree()->start( "Stokes Solve" );
   projectionOperator->project( *stokesRHS, TN.domainParameters.maxLevel, FreeslipBoundary );
   stokesSolverFS->solve( *stokesOperatorFS, *stokesLHS, *stokesRHS, TN.domainParameters.maxLevel );
   // stokesSolver->solve( *stokesOperator, *stokesLHS, *stokesRHS, TN.domainParameters.maxLevel );
   storage->getTimingTree()->stop( "Stokes Solve" );
   localTimer.end();

   real_t timeStokes = localTimer.last();
   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "Stokes time [s]: " << timeStokes );

   stokesResidual = calculateStokesResidual( TN.domainParameters.maxLevel );

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "Stokes residual (final): " << stokesResidual );
}

real_t ConvectionSimulation::calculateStokesResidual( uint_t level )
{
   stokesOperator->apply( *stokesLHS, *stokesTmp, level, Inner | NeumannBoundary | FreeslipBoundary );
   stokesTmp->assign(
       { real_c( 1 ), real_c( -1 ) }, { *stokesTmp, *stokesRHS }, level, Inner | NeumannBoundary | FreeslipBoundary );
   return std::sqrt( stokesTmp->dotGlobal( *stokesTmp, level, Inner | NeumannBoundary | FreeslipBoundary ) );
}

////////////////////////
// Public functions  //
///////////////////////

const SimulationParameters& ConvectionSimulation::getSimulationParams()
{
   return TN.simulationParameters;
}

real_t ConvectionSimulation::viscosityFunction( const Point3D& x, real_t Temperature )
{
   real_t radius = std::sqrt( x[0] * x[0] + x[1] * x[1] + x[2] * x[2] );
   real_t retVal = 1.0;

   // If a viscosity profile is provided, use it, otherwise use the constant viscosity

   if ( TN.simulationParameters.haveViscosityProfile )
   {
      // retVal = TN.physicalParameters.viscosityProfile;
      WALBERLA_ABORT( "Viscosity profiles are not yet supported" );
   }
   else
   {
      retVal = TN.physicalParameters.viscosity;
   }
   //scale background viscosity by temperature- and depth-dependent factors
   //depth-dependent factor counteracts the decrease in viscosity due to increasing temperature with depth
   if ( TN.simulationParameters.tempDependentViscosity )
   {
      switch ( TN.simulationParameters.tempDependentViscosityType )
      {
      //Frank–Kamenetskii type 1
      case 0: {
         retVal *= std::exp( -TN.physicalParameters.activationEnergy * ( Temperature ) +
                             TN.physicalParameters.depthViscosityFactor * ( TN.domainParameters.rMax - radius ) /
                                 ( TN.domainParameters.rMax - TN.domainParameters.rMin ) );
         break;
      }
      //Frank–Kamenetskii type 2
      case 1: {
         retVal *= std::exp( TN.physicalParameters.activationEnergy * ( real_c( 0.5 ) - Temperature ) +
                             TN.physicalParameters.depthViscosityFactor * ( TN.domainParameters.rMax - radius ) /
                                 ( TN.domainParameters.rMax - TN.domainParameters.rMin ) );
         break;
      }

      //with respect to mean
      case 2: {
         uint_t shell = static_cast< uint_t >(
             std::round( real_c( TN.simulationParameters.numLayers ) *
                         ( ( radius - TN.domainParameters.rMin ) / ( TN.domainParameters.rMax - TN.domainParameters.rMin ) ) ) );

         retVal *= std::exp( -TN.physicalParameters.activationEnergy *
                             ( Temperature - TN.physicalParameters.temperatureProfile.at( shell ) ) );

         break;
      }
      //Arrhenius type
      case 3: {
         retVal *= std::exp( TN.physicalParameters.activationEnergy *
                                 ( ( real_c( 1 ) / ( Temperature + real_c( 0.5 ) ) ) - real_c( 1 ) ) +
                             TN.physicalParameters.depthViscosityFactor * ( TN.domainParameters.rMax - radius ) /
                                 ( TN.domainParameters.rMax - TN.domainParameters.rMin ) );

         break;
      }
      //Frank–Kamenetskii type 1
      default: {
         retVal *= std::exp( -TN.physicalParameters.activationEnergy * ( Temperature ) +
                             TN.physicalParameters.depthViscosityFactor * ( TN.domainParameters.rMax - radius ) /
                                 ( TN.domainParameters.rMax - TN.domainParameters.rMin ) );
         break;
      }
      }

      //impose min viscosity
      if ( retVal < TN.physicalParameters.viscosityLowerBound )
      {
         retVal = TN.physicalParameters.viscosityLowerBound;
      }

      //impose max viscosity
      if ( retVal > TN.physicalParameters.viscosityUpperBound )
      {
         retVal = TN.physicalParameters.viscosityUpperBound;
      }
   }

   retVal /= TN.physicalParameters.referenceViscosity;

   return retVal;
}

real_t ConvectionSimulation::densityFunction( const Point3D& x )
{
   auto   radius = std::sqrt( x[0] * x[0] + x[1] * x[1] + x[2] * x[2] );
   real_t retVal;

   //implement adiabatic compression, determined by dissipation number and gruneisen parameter
   real_t rho = TN.physicalParameters.surfaceDensity *
                std::exp( TN.physicalParameters.dissipationNumber * ( TN.domainParameters.rMax - radius ) /
                          TN.physicalParameters.grueneisenParameter );

   retVal = rho / TN.physicalParameters.referenceDensity;

   return retVal;
}

real_t ConvectionSimulation::diffPreFactorFunction( const Point3D& x )
{
   return ( real_c( 1.0 ) * TN.physicalParameters.thermalDiffusivity ) /
          ( densityFunction( x ) * TN.physicalParameters.pecletNumber * TN.physicalParameters.specificHeatCapacity );
}

void ConvectionSimulation::updatePlateVelocities( StokesFunction& )
{
   // CURRENTLY NOT IMPLEMENTED -> ORACLE STUFF NOT WORKING

   //    //needed for capture below
   //    uint_t coordIdx = 0;

   //    //function to return plate velocities, copied and adapted from PlateVelocityDemo.cpp.
   //    std::function< real_t( const Point3D& ) > Velocity = [this, &coordIdx]( const Point3D& x ) {
   //       terraneo::vec3D coords{ x[0], x[1], x[2] };
   //       //get velocity at current plate age (intervals of 1Ma)
   //       terraneo::vec3D velocity = TN.oracle->getPointVelocity(
   //           coords,
   //           TN.simulationParameters.plateAge,
   //           terraneo::plates::LinearDistanceSmoother{ real_c( 1 ) / TN.simulationParameters.plateSmoothingDistance },
   //           terraneo::plates::DefaultPlateNotFoundHandler{} );

   //       return velocity[int_c( coordIdx )] /
   //              ( TN.physicalParameters.characteristicVelocity *
   //                TN.simulationParameters.plateVelocityScaling ); //non-dimensionalise by dividing by characteristic velocity
   //    };

   //    for ( uint_t l = TN.domainParameters.minLevel; l <= TN.domainParameters.maxLevel; ++l )
   //    {
   //       for ( coordIdx = 0; coordIdx < 3; ++coordIdx )
   //       {
   //          //interpolate current plate velocities at the surface
   //          U.uvw()[coordIdx].interpolate( Velocity, l, idSurface );

   //          //just used for setting up stokesLHSPrev in the initialisation
   //          if ( TN.simulationParameters.timeStep == 0 )
   //          {
   //             stokesLHSPrev->uvw()[coordIdx].interpolate( Velocity, l, idSurface );
   //          }
   //       }
   //    }
   WALBERLA_LOG_INFO_ON_ROOT( "No plates moving, Earth has no tectonics." );
}

void ConvectionSimulation::updateRefViscosity()
{
   std::function< real_t( const Point3D&, const std::vector< real_t >& ) > viscosityInt =
       [&]( const Point3D& x, const std::vector< real_t >& Temperature ) { return viscosityFunction( x, Temperature[0] ); };

   auto viscosityIntInv = [&]( const Point3D& x, const std::vector< real_t >& Temperature ) {
      return ( 1.0 / ( viscosityFunction( x, Temperature[0] ) ) );
   };
   for ( uint_t l = TN.domainParameters.minLevel; l <= TN.domainParameters.maxLevel; l++ )
   {
      viscosityFE->interpolate( viscosityInt, { *temperature }, l, All );
      viscosityFEInv->interpolate( viscosityIntInv, { *temperature }, l, All );
   }

   real_t minRefViscosity = viscosityFE->getMinValue( TN.domainParameters.maxLevel ) * TN.physicalParameters.referenceViscosity;

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "New reference (min) viscosity: " << minRefViscosity );

   real_t maxViscosity = viscosityFE->getMaxValue( TN.domainParameters.maxLevel ) * TN.physicalParameters.referenceViscosity;

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "Max viscosity: " << maxViscosity );
}
void ConvectionSimulation::normalFunc( const Point3D& p, Point3D& n )
{
   real_t radius = p.norm();
   if ( std::abs( radius - TN.domainParameters.rMax ) < std::abs( radius - TN.domainParameters.rMin ) )
   {
      n = Point3D( { p[0] / radius, p[1] / radius, p[2] / radius } );
   }
   else
   {
      n = Point3D( { -p[0] / radius, -p[1] / radius, -p[2] / radius } );
   }
}

//returns a reference adiabat relevant for the Earth, commonly implemented in TALA
real_t ConvectionSimulation::referenceTemperatureFunction( const Point3D& x )
{
   auto radius = std::sqrt( x[0] * x[0] + x[1] * x[1] + x[2] * x[2] );

   if ( ( radius - TN.domainParameters.rMin ) < real_c( 1e-10 ) )
   {
      return TN.physicalParameters.cmbTemp / ( TN.physicalParameters.cmbTemp - TN.physicalParameters.surfaceTemp );
   }
   else if ( ( TN.domainParameters.rMax - radius ) < real_c( 1e-10 ) )
   {
      return TN.physicalParameters.surfaceTemp / ( TN.physicalParameters.cmbTemp - TN.physicalParameters.surfaceTemp );
   }

   real_t temp = TN.physicalParameters.adiabatSurfaceTemp *
                 std::exp( ( TN.physicalParameters.dissipationNumber * ( TN.domainParameters.rMax - radius ) ) );

   real_t retVal = temp / ( TN.physicalParameters.cmbTemp - TN.physicalParameters.surfaceTemp );

   return retVal;
}

} // namespace terraneo