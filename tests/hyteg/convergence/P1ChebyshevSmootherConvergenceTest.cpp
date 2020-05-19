#include <cmath>

#include "core/DataTypes.h"
#include "core/Environment.h"
#include "core/math/Constants.h"
#include "core/mpi/MPIManager.h"

#include "hyteg/dataexport/VTKOutput.hpp"
#include "hyteg/elementwiseoperators/P1ElementwiseOperator.hpp"
#include "hyteg/gridtransferoperators/P1toP1LinearProlongation.hpp"
#include "hyteg/gridtransferoperators/P1toP1LinearRestriction.hpp"
#include "hyteg/p1functionspace/P1ConstantOperator.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"
#include "hyteg/primitivestorage/PrimitiveStorage.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/solvers/CGSolver.hpp"
#include "hyteg/solvers/ChebyshevSmoother.hpp"
#include "hyteg/solvers/GeometricMultigridSolver.hpp"

using walberla::real_t;
using walberla::uint_c;
using walberla::uint_t;
using walberla::math::pi;

using namespace hyteg;

void setupDiagonal( const uint_t& minLevel, const uint_t& maxLevel, P1ElementwiseLaplaceOperator& laplaceOperator )
{
   for ( uint_t level = minLevel; level <= maxLevel; level += 1 )
   {
      laplaceOperator.computeDiagonalOperatorValues( level, true );
   }
}

int main( int argc, char** argv )
{
   walberla::Environment env( argc, argv );
   walberla::mpi::MPIManager::instance()->useWorldComm();

   const uint_t minLevel         = 2;
   const uint_t maxLevel         = 5;
   const uint_t max_outer_iter   = 4;
   const uint_t max_coarse_iter  = 1000;
   const real_t coarse_tolerance = 1e-16;
   const uint_t smoothingSteps   = 2;

   MeshInfo meshInfo = MeshInfo::meshRectangle( Point2D( {-1, -1} ), Point2D( {1., 1.} ), MeshInfo::CRISSCROSS, 2, 2 );
   SetupPrimitiveStorage setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
   std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );

   const auto analytic_solution = []( const hyteg::Point3D& p ) -> real_t {
      return std::sin( 2 * pi * p[0] ) * std::cos( 3 * pi * p[1] );
   };

   const auto rhs = []( const hyteg::Point3D& p ) {
      return ( 4 + 9 ) * pi * pi * std::sin( 2 * pi * p[0] ) * std::cos( 3 * pi * p[1] );
   };

   P1ElementwiseLaplaceOperator laplaceOperator( storage, minLevel, maxLevel );
   setupDiagonal( minLevel, maxLevel, laplaceOperator );

   P1Function< real_t > eigenvector( "eigenvector", storage, minLevel, maxLevel );
   P1Function< real_t > tmp( "tmp", storage, minLevel, maxLevel );
   eigenvector.interpolate( analytic_solution, minLevel, DirichletBoundary );
   const auto spectralRadius = chebyshev::estimateRadius( laplaceOperator, minLevel, 100, storage, eigenvector, tmp );

   const std::array< real_t, 5 > expectedResiduals{0.00799318, 0.000244743, 4.86337e-05, 1.53384e-05, 6.00188e-06};

   for ( uint_t order = 1; order < 6; order += 1 )
   {
      P1Function< real_t > residual( "residual", storage, minLevel, maxLevel );
      P1Function< real_t > rightHandSide( "rightHandSide", storage, minLevel, maxLevel );
      P1Function< real_t > function( "function", storage, minLevel, maxLevel );
      P1Function< real_t > laplaceTimesFunction( "laplaceTimesFunction", storage, minLevel, maxLevel );

      auto smoother = std::make_shared< ChebyshevSmoother< P1ElementwiseLaplaceOperator > >( storage, minLevel, maxLevel );
      smoother->setupCoefficients( order, spectralRadius );

      auto coarseGridSolver = std::make_shared< CGSolver< P1ElementwiseLaplaceOperator > >(
          storage, minLevel, minLevel, max_coarse_iter, coarse_tolerance );
      auto restrictionOperator  = std::make_shared< P1toP1LinearRestriction >();
      auto prolongationOperator = std::make_shared< P1toP1LinearProlongation >();

      auto multiGridSolver = GeometricMultigridSolver< P1ElementwiseLaplaceOperator >( storage,
                                                                                       smoother,
                                                                                       coarseGridSolver,
                                                                                       restrictionOperator,
                                                                                       prolongationOperator,
                                                                                       minLevel,
                                                                                       maxLevel,
                                                                                       smoothingSteps,
                                                                                       smoothingSteps );

      // bcs
      function.interpolate( analytic_solution, maxLevel, DirichletBoundary );

      // rhs
      P1ConstantMassOperator massOperator( storage, minLevel, maxLevel );
      residual.interpolate( rhs, maxLevel, DoFType::All );
      massOperator.apply( residual, rightHandSide, maxLevel, DoFType::All, UpdateType::Replace );

      for ( uint_t i = 0; i < max_outer_iter; ++i )
         multiGridSolver.solve( laplaceOperator, function, rightHandSide, maxLevel );

      laplaceOperator.apply( function, laplaceTimesFunction, maxLevel, Inner );
      residual.assign( {1.0, -1.0}, {rightHandSide, laplaceTimesFunction}, maxLevel, Inner );
      const auto residualValue = std::sqrt( residual.dotGlobal( residual, maxLevel, Inner ) );

      // the calculated residuals should up to 10% match the expected residual.
      const auto expectedResidualValue = expectedResiduals[order - 1];
      WALBERLA_CHECK_LESS(
          0.9 * expectedResidualValue, residualValue, "residual for chebyshev smoother of order " << order << " has changed " );
      WALBERLA_CHECK_GREATER(
          1.1 * expectedResidualValue, residualValue, "residual for chebyshev smoother of order " << order << " has changed " );
   }

   return EXIT_SUCCESS;
}
