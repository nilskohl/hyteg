/*
 * Copyright (c) 2017-2020 Nils Kohl.
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

#include "Helpers.hpp"

namespace hyteg {
namespace tme_benchmarks {

using walberla::int_c;

#if 0
static std::string getDateTimeID()
{
   std::vector< char > cTimeString( 64 );
   WALBERLA_ROOT_SECTION()
   {
      std::time_t t;
      std::time( &t );
      std::strftime( cTimeString.data(), 64, "%F_%H-%M-%S", std::localtime( &t ) );
   }

   walberla::mpi::broadcastObject( cTimeString );

   std::string timeString( cTimeString.data() );
   return timeString;
}
#endif

void writeDataHeader()
{
   WALBERLA_LOG_INFO_ON_ROOT(
       " iteration | iteration type | FMG level | L2 error velocity | L2 residual velocity | L2 error pressure | L2 residual pressure " );
   WALBERLA_LOG_INFO_ON_ROOT(
       "-----------+----------------+-----------+-------------------+----------------------+-------------------+----------------------" );
}

// iterationType: I: initial
//                V: v-cycle
//                F: FMG
void writeDataRow( uint_t                                      iteration,
                   std::string                                 iterationType,
                   uint_t                                      fmgLevel,
                   real_t                                      errorL2Velocity,
                   real_t                                      residualL2Velocity,
                   real_t                                      errorL2Pressure,
                   real_t                                      residualL2Pressure,
                   walberla::sqlite::SQLiteDB&                 db,
                   std::map< std::string, walberla::int64_t >& sqlIntegerProperties,
                   std::map< std::string, double >&            sqlRealProperties,
                   std::map< std::string, std::string >&       sqlStringProperties )
{
   std::string fmgLevelString = "-";
   if ( iterationType == "F" )
   {
      fmgLevelString = walberla::format( "%9d", fmgLevel );
   }

   sqlStringProperties["iteration_type"]     = iterationType;
   sqlIntegerProperties["fmg_level"]         = int_c( fmgLevel );
   sqlRealProperties["error_l2_velocity"]    = errorL2Velocity;
   sqlRealProperties["residual_l2_velocity"] = residualL2Velocity;
   sqlRealProperties["error_l2_pressure"]    = errorL2Pressure;
   sqlRealProperties["residual_l2_pressure"] = residualL2Pressure;

   WALBERLA_ROOT_SECTION()
   {
      db.storeRun( sqlIntegerProperties, sqlStringProperties, sqlRealProperties );
      sqlRealProperties.clear();
      sqlIntegerProperties.clear();
      sqlStringProperties.clear();
   }

   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %9d | %14s | %9s | %17.5e | %20.5e | %17.5e | %20.5e ",
                                                iteration,
                                                iterationType.c_str(),
                                                fmgLevelString.c_str(),
                                                errorL2Velocity,
                                                residualL2Velocity,
                                                errorL2Pressure,
                                                residualL2Pressure ) );
}

template < template < typename > class StokesFunction,
           typename StokesOperator,
           typename VelocityMassOperator,
           typename PressureMassOperator,
           typename Restriction,
           typename Prolongation,
           typename FMGProlongation >
void solveImplementation( const MeshInfo&                                         meshInfo,
                          bool                                                    hasAnalyticalSolution,
                          const std::function< real_t( const hyteg::Point3D& ) >& solutionU,
                          const std::function< real_t( const hyteg::Point3D& ) >& solutionV,
                          const std::function< real_t( const hyteg::Point3D& ) >& solutionW,
                          const std::function< real_t( const hyteg::Point3D& ) >& solutionP,
                          const std::function< real_t( const hyteg::Point3D& ) >& rhsU,
                          const std::function< real_t( const hyteg::Point3D& ) >& rhsV,
                          const std::function< real_t( const hyteg::Point3D& ) >& rhsW,
                          uint_t                                                  minLevel,
                          uint_t                                                  maxLevel,
                          MultigridSettings                                       multigridSettings,
                          SmootherSettings                                        smootherSettings,
                          CoarseGridSettings                                      coarseGridSettings,
                          bool                                                    projectPressure,
                          bool                                                    projectPressurefterRestriction,
                          bool                                                    calculateDiscretizationError,
                          uint_t                                                  errorCalculationLevelIncrement,
                          bool                                                    vtk,
                          const std::string&                                      benchmarkName,
                          bool                                                    verbose,
                          std::string                                             dbFile )
{

   auto setupStorage = std::make_shared< SetupPrimitiveStorage >(
       meshInfo, walberla::uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   setupStorage->setMeshBoundaryFlagsOnBoundary( 1, 0, true );

   auto storage = std::make_shared< PrimitiveStorage >( *setupStorage );

   if ( vtk )
   {
      writeDomainPartitioningVTK( storage, "vtk/", benchmarkName + "_domain" );
   }

   auto timer = storage->getTimingTree();
   timer->start( "Total" );
   timer->start( "Setup" );

   const uint_t unknowns   = numberOfGlobalDoFs< P2FunctionTag >( *storage, maxLevel );
   const real_t hMin       = MeshQuality::getMinimalEdgeLength( storage, maxLevel );
   const real_t hMax       = MeshQuality::getMaximalEdgeLength( storage, maxLevel );
   const auto   errorLevel = maxLevel + errorCalculationLevelIncrement;

   WALBERLA_LOG_INFO_ON_ROOT( "Benchmark name: " << benchmarkName )
   WALBERLA_LOG_INFO_ON_ROOT( " - space discretization: " )
   WALBERLA_LOG_INFO_ON_ROOT( "   + elements:                                     " << ( std::is_same< typename StokesFunction< real_t >::Tag, P2P1TaylorHoodFunctionTag >::value ? "P2-P1" : "P1-P1" ) );
   WALBERLA_LOG_INFO_ON_ROOT( "   + dimensions:                                   " << ( storage->hasGlobalCells() ? "3" : "2" ) )
   WALBERLA_LOG_INFO_ON_ROOT( "   + min level:                                    " << minLevel )
   WALBERLA_LOG_INFO_ON_ROOT( "   + max level:                                    " << maxLevel )
   WALBERLA_LOG_INFO_ON_ROOT( "   + unknowns (== particles), including boundary:  " << unknowns )
   WALBERLA_LOG_INFO_ON_ROOT( "   + h_min:                                        " << hMin )
   WALBERLA_LOG_INFO_ON_ROOT( "   + h_max:                                        " << hMax )
   WALBERLA_LOG_INFO_ON_ROOT( " - multigrid settings: " )
   WALBERLA_LOG_INFO_ON_ROOT( "   + pre smooth:                                   " << multigridSettings.preSmooth )
   WALBERLA_LOG_INFO_ON_ROOT( "   + post smooth:                                  " << multigridSettings.postSmooth )
   WALBERLA_LOG_INFO_ON_ROOT( "   + inc smooth:                                   " << multigridSettings.incSmooth )
   WALBERLA_LOG_INFO_ON_ROOT( "   + num cycles:                                   " << multigridSettings.numCycles )
   WALBERLA_LOG_INFO_ON_ROOT( "   + FMG inner iterations:                         " << multigridSettings.fmgInnerIterations )
   WALBERLA_LOG_INFO_ON_ROOT( " - smoother settings: " )
   WALBERLA_LOG_INFO_ON_ROOT( "   + num GS velocity:                              " << smootherSettings.numGSVelocity )
   WALBERLA_LOG_INFO_ON_ROOT( "   + symmetric velocity:                           " << smootherSettings.symmGSVelocity )
   WALBERLA_LOG_INFO_ON_ROOT(
       "   + omega estimation:                             " << ( smootherSettings.estimateOmega ? "yes" : "no" ) )
   if ( smootherSettings.estimateOmega )
   {
      WALBERLA_LOG_INFO_ON_ROOT(
          "   + omega estimation level:                       " << smootherSettings.omegaEstimationIterations )
      WALBERLA_LOG_INFO_ON_ROOT(
          "   + omega estimation iterations:                  " << smootherSettings.omegaEstimationIterations )
   }
   else
   {
      WALBERLA_LOG_INFO_ON_ROOT( "   + fixed omega:                                  " << smootherSettings.omega )
   }
   WALBERLA_LOG_INFO_ON_ROOT( " - coarse grid settings: " )
   WALBERLA_LOG_INFO_ON_ROOT( "   + coarse grid solver:                           " << coarseGridSettings.solverType )
   WALBERLA_LOG_INFO_ON_ROOT(
       "   + absolute residual tolerance:                  " << coarseGridSettings.absoluteResidualTolerance )
   WALBERLA_LOG_INFO_ON_ROOT( "   + max iterations:                               " << coarseGridSettings.maxIterations )
   WALBERLA_LOG_INFO_ON_ROOT( " - app settings: " )
   WALBERLA_LOG_INFO_ON_ROOT( "   + error interpolation level:                    " << errorLevel )
   WALBERLA_LOG_INFO_ON_ROOT( "   + VTK:                                          " << ( vtk ? "yes" : "no" ) )
   WALBERLA_LOG_INFO_ON_ROOT( "   + verbose:                                      " << verbose )
   WALBERLA_LOG_INFO_ON_ROOT( "   + database file:                                " << dbFile )
   WALBERLA_LOG_INFO_ON_ROOT( "" )

   walberla::sqlite::SQLiteDB                 db( dbFile );
   std::map< std::string, walberla::int64_t > sqlIntegerProperties;
   std::map< std::string, double >            sqlRealProperties;
   std::map< std::string, std::string >       sqlStringProperties;

   uint_t iteration                  = 0;
   sqlIntegerProperties["iteration"] = int_c( iteration );

   sqlIntegerProperties["min_level"]            = int_c( minLevel );
   sqlIntegerProperties["max_level"]            = int_c( maxLevel );
   sqlIntegerProperties["unknowns"]             = int_c( unknowns );
   sqlRealProperties["h_min"]                   = hMin;
   sqlRealProperties["h_max"]                   = hMax;
   sqlIntegerProperties["num_macro_cells"]      = int_c( setupStorage->getNumberOfCells() );
   sqlIntegerProperties["num_macro_faces"]      = int_c( setupStorage->getNumberOfFaces() );
   sqlIntegerProperties["num_macro_edges"]      = int_c( setupStorage->getNumberOfEdges() );
   sqlIntegerProperties["num_macro_vertices"]   = int_c( setupStorage->getNumberOfVertices() );
   sqlIntegerProperties["num_macro_primitives"] = int_c( setupStorage->getNumberOfPrimitives() );

   sqlIntegerProperties["num_cycles"]           = int_c( multigridSettings.numCycles );
   sqlIntegerProperties["pre_smooth"]           = int_c( multigridSettings.preSmooth );
   sqlIntegerProperties["post_smooth"]          = int_c( multigridSettings.postSmooth );
   sqlIntegerProperties["inc_smooth"]           = int_c( multigridSettings.incSmooth );
   sqlIntegerProperties["fmg_inner_iterations"] = int_c( multigridSettings.fmgInnerIterations );

   sqlRealProperties["omega"]                          = smootherSettings.omega;
   sqlIntegerProperties["omega_estimation_iterations"] = int_c( smootherSettings.omegaEstimationIterations );
   sqlIntegerProperties["omega_estimation_level"]      = int_c( smootherSettings.omegaEstimationLevel );
   sqlIntegerProperties["estimate_omega"]              = int_c( smootherSettings.estimateOmega );
   sqlIntegerProperties["symm_gs_velocity"]            = int_c( smootherSettings.symmGSVelocity );
   sqlIntegerProperties["num_gs_velocity"]             = int_c( smootherSettings.numGSVelocity );

   sqlIntegerProperties["coarse_grid_solver_type"]              = int_c( coarseGridSettings.solverType );
   sqlIntegerProperties["coarse_grid_max_iterations"]           = int_c( coarseGridSettings.maxIterations );
   sqlRealProperties["coarse_grid_absolute_residual_tolerance"] = coarseGridSettings.absoluteResidualTolerance;

   sqlIntegerProperties["error_calculation_level_increment"] = int_c( errorCalculationLevelIncrement );

   const auto errorFlag = Inner | NeumannBoundary | FreeslipBoundary;

   StokesFunction< real_t > u( "u", storage, minLevel, errorLevel );
   StokesFunction< real_t > f( "f", storage, minLevel, errorLevel );
   StokesFunction< real_t > r( "r", storage, minLevel, errorLevel );
   StokesFunction< real_t > err( "error", storage, minLevel, errorLevel );
   StokesFunction< real_t > tmp( "tmp", storage, minLevel, errorLevel );
   StokesFunction< real_t > tmpFMG( "tmpFMG", storage, minLevel, errorLevel );
   StokesFunction< real_t > exact( "exact", storage, minLevel, errorLevel );

   StokesOperator       A( storage, minLevel, errorLevel );
   VelocityMassOperator MVelocity( storage, minLevel, errorLevel );
   PressureMassOperator MPressure( storage, minLevel, errorLevel );

   for ( uint_t level = minLevel; level <= errorLevel; level++ )
   {
      exact.u.interpolate( solutionU, level, All );
      exact.v.interpolate( solutionV, level, All );
      exact.w.interpolate( solutionW, level, All );
      exact.p.interpolate( solutionP, level, All );

      vertexdof::projectMean( exact.p, level );

      u.u.interpolate( solutionU, level, DirichletBoundary );
      u.v.interpolate( solutionV, level, DirichletBoundary );
      u.w.interpolate( solutionW, level, DirichletBoundary );

      tmp.u.interpolate( rhsU, level, All );
      tmp.v.interpolate( rhsV, level, All );
      tmp.w.interpolate( rhsW, level, All );

      MVelocity.apply( tmp.u, f.u, level, All );
      MVelocity.apply( tmp.v, f.v, level, All );
      MVelocity.apply( tmp.w, f.w, level, All );
   }

   auto prolongationOperator = std::make_shared< Prolongation >();
   auto restrictionOperator  = std::make_shared< Restriction >( projectPressurefterRestriction );

   std::shared_ptr< Solver< typename StokesOperator::VelocityOperator_T > > scalarSmoother;
   if ( smootherSettings.symmGSVelocity )
   {
      scalarSmoother = std::make_shared< SymmetricSORSmoother< typename StokesOperator::VelocityOperator_T > >( 1.0 );
   }
   else
   {
      scalarSmoother = std::make_shared< SORSmoother< typename StokesOperator::VelocityOperator_T > >( 1.0 );
   }

   auto uzawaVelocityPreconditioner =
       std::make_shared< StokesVelocityBlockBlockDiagonalPreconditioner< StokesOperator > >( storage, scalarSmoother );

   auto smoother = std::make_shared< UzawaSmoother< StokesOperator > >( storage,
                                                                        uzawaVelocityPreconditioner,
                                                                        minLevel,
                                                                        maxLevel,
                                                                        smootherSettings.omega,
                                                                        Inner | NeumannBoundary,
                                                                        smootherSettings.numGSVelocity );

   if ( smootherSettings.estimateOmega )
   {
      WALBERLA_LOG_INFO_ON_ROOT( "" );
      WALBERLA_LOG_INFO_ON_ROOT( "Estimating omega (" << smootherSettings.omegaEstimationIterations
                                                      << " power iterations on level " << smootherSettings.omegaEstimationLevel
                                                      << ") ..." );
      const auto estimatedOmega = estimateUzawaRelaxationParameter( storage,
                                                                    uzawaVelocityPreconditioner,
                                                                    smootherSettings.omegaEstimationLevel,
                                                                    smootherSettings.omegaEstimationIterations,
                                                                    smootherSettings.numGSVelocity );
      smoother->setRelaxationParameter( estimatedOmega );
      WALBERLA_LOG_INFO_ON_ROOT( "Setting omega to estimate: " << estimatedOmega );
      WALBERLA_LOG_INFO_ON_ROOT( "" );
      sqlRealProperties["sor_relax"] = estimatedOmega;
   }

   // coarse grid solver type:
   // 0: MUMPS                          (PETSc)
   // 1: block preconditioned MINRES    (PETSc)

   std::shared_ptr< Solver< StokesOperator > > coarseGridSolverInternal;

   if ( coarseGridSettings.solverType == 0 )
   {
      auto petscSolverInternalTmp = std::make_shared< PETScLUSolver< StokesOperator > >( storage, minLevel );

      coarseGridSolverInternal = petscSolverInternalTmp;
   }
   else if ( coarseGridSettings.solverType == 1 )
   {
      auto petscSolverInternalTmp = std::make_shared< PETScBlockPreconditionedStokesSolver< StokesOperator > >(
          storage, minLevel, coarseGridSettings.absoluteResidualTolerance, coarseGridSettings.maxIterations, 1 );
      petscSolverInternalTmp->setVerbose( true );
      coarseGridSolverInternal = petscSolverInternalTmp;
   }

   auto coarseGridSolver = std::make_shared< TimedSolver< StokesOperator > >( coarseGridSolverInternal );

   auto multigridSolver = std::make_shared< GeometricMultigridSolver< StokesOperator > >( storage,
                                                                                          smoother,
                                                                                          coarseGridSolver,
                                                                                          restrictionOperator,
                                                                                          prolongationOperator,
                                                                                          minLevel,
                                                                                          maxLevel,
                                                                                          multigridSettings.preSmooth,
                                                                                          multigridSettings.postSmooth,
                                                                                          multigridSettings.incSmooth,
                                                                                          CycleType::VCYCLE );

   auto fmgProlongation = std::make_shared< FMGProlongation >();

   auto postCycle = [&]( uint_t currentLevel ) {

      if ( projectPressure )
      {
         vertexdof::projectMean( u.p, currentLevel );
      }

      for ( uint_t l = minLevel; l <= errorLevel; l++ )
      {
         tmpFMG.interpolate( 0, l, All );
      }

      tmpFMG.assign( {1.0}, {u}, currentLevel, All );

      const auto fmgErrorLevel = currentLevel + errorCalculationLevelIncrement;
      for ( uint_t prolongationSourceLevel = currentLevel; prolongationSourceLevel < fmgErrorLevel; prolongationSourceLevel++ )
      {
         prolongationOperator->prolongate( tmpFMG, prolongationSourceLevel, All );
      }

      residual( tmpFMG, f, A, tmp, currentLevel, errorFlag, r );
      error( tmpFMG, exact, fmgErrorLevel, errorFlag, err );

      auto errorL2VelocityFMG    = normL2Velocity( err, MVelocity, tmp, fmgErrorLevel, errorFlag );
      auto residualL2VelocityFMG = normL2Velocity( r, MVelocity, tmp, currentLevel, errorFlag );

      auto errorL2PressureFMG    = normL2Scalar( err.p, MPressure, tmp.p, fmgErrorLevel, errorFlag );
      auto residualL2PressureFMG = normL2Scalar( r.p, MPressure, tmp.p, currentLevel, errorFlag );

      writeDataRow( iteration,
                    "F",
                    currentLevel,
                    errorL2VelocityFMG,
                    residualL2VelocityFMG,
                    errorL2PressureFMG,
                    residualL2PressureFMG,
                    db,
                    sqlIntegerProperties,
                    sqlRealProperties,
                    sqlStringProperties );
      iteration++;
   };

   FullMultigridSolver< StokesOperator > fullMultigridSolver(
       storage, multigridSolver, fmgProlongation, minLevel, maxLevel, multigridSettings.fmgInnerIterations, postCycle );

   for ( uint_t prolongationSourceLevel = maxLevel; prolongationSourceLevel < errorLevel; prolongationSourceLevel++ )
   {
      prolongationOperator->prolongate( u, prolongationSourceLevel, All );
   }

   residual( u, f, A, tmp, maxLevel, errorFlag, r );
   error( u, exact, errorLevel, errorFlag, err );

   auto errorL2Velocity    = normL2Velocity( err, MVelocity, tmp, errorLevel, errorFlag );
   auto residualL2Velocity = normL2Velocity( r, MVelocity, tmp, maxLevel, errorFlag );
   auto errorL2Pressure    = normL2Scalar( err.p, MPressure, tmp.p, errorLevel, errorFlag );
   auto residualL2Pressure = normL2Scalar( r.p, MPressure, tmp.p, maxLevel, errorFlag );

   writeDataHeader();
   writeDataRow( iteration,
                 "I",
                 0,
                 errorL2Velocity,
                 residualL2Velocity,
                 errorL2Pressure,
                 residualL2Pressure,
                 db,
                 sqlIntegerProperties,
                 sqlRealProperties,
                 sqlStringProperties );
   iteration++;

   VTKOutput vtkOutput( "vtk", "TME", storage );
   vtkOutput.add( u );
   vtkOutput.add( f );
   vtkOutput.add( err );
   vtkOutput.add( exact );

   if ( vtk )
   {
      vtkOutput.write( maxLevel, 0 );
   }

   if ( multigridSettings.fmgInnerIterations > 0 )
   {
      fullMultigridSolver.solve( A, u, f, maxLevel );
   }
   else
   {
      multigridSolver->solve( A, u, f, maxLevel );

      if ( projectPressure )
      {
         vertexdof::projectMean( u.p, maxLevel );
      }

      for ( uint_t prolongationSourceLevel = maxLevel; prolongationSourceLevel < errorLevel; prolongationSourceLevel++ )
      {
         prolongationOperator->prolongate( u, prolongationSourceLevel, All );
      }

      residual( u, f, A, tmp, maxLevel, errorFlag, r );
      error( u, exact, errorLevel, errorFlag, err );

      errorL2Velocity    = normL2Velocity( err, MVelocity, tmp, errorLevel, errorFlag );
      residualL2Velocity = normL2Velocity( r, MVelocity, tmp, maxLevel, errorFlag );
      errorL2Pressure    = normL2Scalar( err.p, MPressure, tmp.p, errorLevel, errorFlag );
      residualL2Pressure = normL2Scalar( r.p, MPressure, tmp.p, maxLevel, errorFlag );

      writeDataRow( iteration,
                    "V",
                    0,
                    errorL2Velocity,
                    residualL2Velocity,
                    errorL2Pressure,
                    residualL2Pressure,
                    db,
                    sqlIntegerProperties,
                    sqlRealProperties,
                    sqlStringProperties );
      iteration++;
   }

   for ( uint_t i = 1; i < multigridSettings.numCycles; i++ )
   {
      multigridSolver->solve( A, u, f, maxLevel );

      if ( projectPressure )
      {
         vertexdof::projectMean( u.p, maxLevel );
      }

      for ( uint_t prolongationSourceLevel = maxLevel; prolongationSourceLevel < errorLevel; prolongationSourceLevel++ )
      {
         prolongationOperator->prolongate( u, prolongationSourceLevel, All );
      }

      residual( u, f, A, tmp, maxLevel, errorFlag, r );
      error( u, exact, errorLevel, errorFlag, err );

      errorL2Velocity    = normL2Velocity( err, MVelocity, tmp, errorLevel, errorFlag );
      residualL2Velocity = normL2Velocity( r, MVelocity, tmp, maxLevel, errorFlag );
      errorL2Pressure    = normL2Scalar( err.p, MPressure, tmp.p, errorLevel, errorFlag );
      residualL2Pressure = normL2Scalar( r.p, MPressure, tmp.p, maxLevel, errorFlag );

      writeDataRow( iteration,
                    "V",
                    0,
                    errorL2Velocity,
                    residualL2Velocity,
                    errorL2Pressure,
                    residualL2Pressure,
                    db,
                    sqlIntegerProperties,
                    sqlRealProperties,
                    sqlStringProperties );
      iteration++;
   }

   if ( vtk )
   {
      vtkOutput.write( maxLevel, 1 );
   }
}

void solve( const MeshInfo&                                         meshInfo,
            Discretization                                          discretization,
            bool                                                    hasAnalyticalSolution,
            const std::function< real_t( const hyteg::Point3D& ) >& solutionU,
            const std::function< real_t( const hyteg::Point3D& ) >& solutionV,
            const std::function< real_t( const hyteg::Point3D& ) >& solutionW,
            const std::function< real_t( const hyteg::Point3D& ) >& solutionP,
            const std::function< real_t( const hyteg::Point3D& ) >& rhsU,
            const std::function< real_t( const hyteg::Point3D& ) >& rhsV,
            const std::function< real_t( const hyteg::Point3D& ) >& rhsW,
            uint_t                                                  minLevel,
            uint_t                                                  maxLevel,
            MultigridSettings                                       multigridSettings,
            SmootherSettings                                        smootherSettings,
            CoarseGridSettings                                      coarseGridSettings,
            bool                                                    projectPressure,
            bool                                                    projectPressurefterRestriction,
            bool                                                    calculateDiscretizationError,
            uint_t                                                  normCalculationLevelIncrement,
            bool                                                    vtk,
            const std::string&                                      benchmarkName,
            bool                                                    verbose,
            std::string                                             dbFile )
{
   if ( discretization == Discretization::P2_P1 )
   {
      solveImplementation< P2P1TaylorHoodFunction,
                           P2P1TaylorHoodStokesOperator,
                           P2ConstantMassOperator,
                           P1ConstantMassOperator,
                           P2P1StokesToP2P1StokesRestriction,
                           P2P1StokesToP2P1StokesProlongation,
                           P2P1StokesToP2P1StokesProlongation >( meshInfo,
                                                                 hasAnalyticalSolution,
                                                                 solutionU,
                                                                 solutionV,
                                                                 solutionW,
                                                                 solutionP,
                                                                 rhsU,
                                                                 rhsV,
                                                                 rhsW,
                                                                 minLevel,
                                                                 maxLevel,
                                                                 multigridSettings,
                                                                 smootherSettings,
                                                                 coarseGridSettings,
                                                                 projectPressure,
                                                                 projectPressurefterRestriction,
                                                                 calculateDiscretizationError,
                                                                 normCalculationLevelIncrement,
                                                                 vtk,
                                                                 benchmarkName,
                                                                 verbose,
                                                                 dbFile );
   }
   else
   {
      solveImplementation< P1StokesFunction,
          P1StokesOperator,
          P1ConstantMassOperator,
          P1ConstantMassOperator,
          P1P1StokesToP1P1StokesRestriction,
          P1P1StokesToP1P1StokesProlongation,
          P1P1StokesToP1P1StokesProlongation >( meshInfo,
                                                hasAnalyticalSolution,
                                                solutionU,
                                                solutionV,
                                                solutionW,
                                                solutionP,
                                                rhsU,
                                                rhsV,
                                                rhsW,
                                                minLevel,
                                                maxLevel,
                                                multigridSettings,
                                                smootherSettings,
                                                coarseGridSettings,
                                                projectPressure,
                                                projectPressurefterRestriction,
                                                calculateDiscretizationError,
                                                normCalculationLevelIncrement,
                                                vtk,
                                                benchmarkName,
                                                verbose,
                                                dbFile );
   }
}

} // namespace tme_benchmarks
} // namespace hyteg