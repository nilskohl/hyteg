#include "core/Environment.h"
#include "core/logging/Logging.h"
#include "core/timing/Timer.h"
#include "core/math/Random.h"

#include "tinyhhg_core/p2functionspace/P2Function.hpp"
#include "tinyhhg_core/p2functionspace/P2ConstantOperator.hpp"
#include "tinyhhg_core/solvers/CGSolver.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/Visualization.hpp"
#include "tinyhhg_core/p1functionspace/generated/p1_tet_diffusion.h"
#include "tinyhhg_core/VTKWriter.hpp"

using walberla::real_t;
using walberla::real_c;
using walberla::uint_c;
using walberla::uint_t;

using namespace hhg;

void testLaplace3D( const std::string & meshFile, const uint_t & level )
{
  // Tests (on multiple meshes) if the 3D Laplace operator has the following properties:
  // 1. laplace(u) = 0, if u = const.
  // 2. laplace(u) = 0, if u linear

  const bool   writeVTK   = true;
  const real_t errorLimit = 5.1e-13;

  uint_t timestep = 0;

  const auto meshInfo = MeshInfo::fromGmshFile( meshFile );
  SetupPrimitiveStorage setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
  setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
  const auto storage = std::make_shared< PrimitiveStorage >( setupStorage );

  WALBERLA_CHECK( storage->hasGlobalCells() );

  if ( writeVTK )
    writeDomainPartitioningVTK( storage, "../../output", "P1LaplaceOperatorTest3D_partitioning" );

  P2ConstantLaplaceOperator laplaceOperator3D( storage, level, level );

  // Although the apply test should be sufficient we check here again explicitly that the sum
  // of the stencil weights at every inner point of the mesh is equal to zero.
  // This is equivalent to checking that the row wise sums are equal to zero in the stiffness matrix.

  ////////////////
  // Macro-face //
  ////////////////

  for ( const auto & faceIt : storage->getFaces() )
  {
    auto face = faceIt.second;
    // skip faces at boundary
    if ( face->getNumNeighborCells() < 2 )
      continue;

    // At vertices
    auto vertexToVertexStencilSize = face->getData( laplaceOperator3D.getVertexToVertexOpr().getFaceStencilID() )->getSize( level );
    auto vertexToVertexStencilArray = face->getData( laplaceOperator3D.getVertexToVertexOpr().getFaceStencilID() )->getPointer( level );

    real_t sumAtVertex = real_c(0);
    for ( uint_t i = 0; i < vertexToVertexStencilSize; i++ )
    {
      sumAtVertex += vertexToVertexStencilArray[i];
    }

    auto edgeToVertexStencilMap = face->getData( laplaceOperator3D.getEdgeToVertexOpr().getFaceStencil3DID() )->getData( level );
    for ( uint_t neighborCellId = 0; neighborCellId < 2; neighborCellId++ )
      for ( auto leafOrientation : edgeToVertexStencilMap.at(neighborCellId) )
        for ( auto direction : leafOrientation.second )
        {
          WALBERLA_LOG_DEVEL_ON_ROOT( "Adding (edge -> vertex) " << direction.second )
          sumAtVertex += direction.second;
        }


    WALBERLA_LOG_DEVEL_ON_ROOT( "Face stencil sum = " << sumAtVertex );
    WALBERLA_CHECK_FLOAT_EQUAL( sumAtVertex, 0.0 );

    // At edges
    // For now we add all three types of edges to check that row sum == 0 (since 0 + 0 + 0 == 0 ;) )
    // This is however not sufficient to be really sure that the row sum for the individual edge types are zero.
    real_t sumAtAllEdgeTypes = real_c(0);

    auto vertexToEdgeStencilMap = face->getData( laplaceOperator3D.getVertexToEdgeOpr().getFaceStencil3DID() )->getData( level );
    for ( uint_t neighborCellId = 0; neighborCellId < 2; neighborCellId++ )
      for ( auto centerOrientation : vertexToEdgeStencilMap.at(neighborCellId) )
        for ( auto direction : centerOrientation.second )
        {
          WALBERLA_LOG_DEVEL_ON_ROOT( "Adding (vertex -> edge)" << direction.second )
          sumAtAllEdgeTypes += direction.second;
        }

    auto edgeToEdgeStencilMap = face->getData( laplaceOperator3D.getEdgeToEdgeOpr().getFaceStencil3DID() )->getData( level );
    for ( uint_t neighborCellId = 0; neighborCellId < 2; neighborCellId++ )
      for ( auto centerOrientation : edgeToEdgeStencilMap.at(neighborCellId) )
        for ( auto leafOrientation : centerOrientation.second )
          for ( auto direction : leafOrientation.second )
          {
            WALBERLA_LOG_DEVEL_ON_ROOT( "Adding (edge -> edge)" << direction.second )
            sumAtAllEdgeTypes += direction.second;
          }
    WALBERLA_LOG_DEVEL_ON_ROOT( "Face stencil sum = " << sumAtAllEdgeTypes );
    WALBERLA_CHECK_FLOAT_EQUAL( sumAtAllEdgeTypes, 0.0 );
  }


  std::function< real_t( const hhg::Point3D& ) > zero = []( const hhg::Point3D & ) -> real_t
  {
      return 0.0;
  };

  std::function< real_t( const hhg::Point3D& ) > one = []( const hhg::Point3D & ) -> real_t
  {
      return 1.0;
  };

  std::function< real_t( const hhg::Point3D& ) > linearInX = []( const hhg::Point3D & p ) -> real_t
  {
      return real_c(42) * p[0];
  };

  std::function< real_t( const hhg::Point3D& ) > linearInXY = []( const hhg::Point3D & p ) -> real_t
  {
      return p[0] + p[1];
  };

  std::function< real_t( const hhg::Point3D& ) > linearInXYZ = []( const hhg::Point3D & p ) -> real_t
  {
      return real_c(42) * p[0] + p[1] + real_c(1337) * p[2];
  };

  hhg::P2Function< real_t > u          ( "u",           storage, level, level );
  hhg::P2Function< real_t > resultExact( "u_exact",     storage, level, level );
  hhg::P2Function< real_t > result     ( "result",      storage, level, level );
  hhg::P2Function< real_t > err        ( "err",         storage, level, level );
  hhg::P2Function< real_t > oneFunction( "oneFunction", storage, level, level );

  oneFunction.interpolate( one, level, DoFType::All );
  const real_t numPoints  = oneFunction.dotGlobal( oneFunction, level, DoFType::Inner );

  VTKOutput vtkOutput("../../output", "P1LaplaceOperatorTest3D", storage);
  vtkOutput.add( &u );
  vtkOutput.add( &result );
  vtkOutput.add( &resultExact );
  vtkOutput.add( &err );

  auto testLaplaceResult = [&]( std::function< real_t( const hhg::Point3D& ) > uFunction,
                                std::function< real_t( const hhg::Point3D& ) > resultExactFunction ) -> real_t
  {
      u.interpolate( uFunction, level, DoFType::All );
      result.interpolate( resultExactFunction, level, DoFType::DirichletBoundary );
      resultExact.interpolate( resultExactFunction, level, DoFType::All );
      err.interpolate( zero, level, DoFType::All );

      laplaceOperator3D.apply( u, result, level, DoFType::Inner );

      err.assign( { 1.0, -1.0 }, { &result, &resultExact }, level, DoFType::All );
      const real_t discrL2Err = std::sqrt( err.dotGlobal( err, level, DoFType::Inner ) / numPoints );

      if ( writeVTK )
      {
        vtkOutput.write( level, timestep++ );
      }

      return discrL2Err;
  };

  // 1. u = const
  // ------------
  //   a) u = 0
  const real_t errorUZero = testLaplaceResult( zero, zero );
  WALBERLA_LOG_INFO_ON_ROOT( "u = 0: L2 error: " << errorUZero );
  WALBERLA_CHECK_LESS( errorUZero, errorLimit );

  //   b) u = 1
  const real_t errorUOne  = testLaplaceResult( one, zero );
  WALBERLA_LOG_INFO_ON_ROOT( "u = 1: L2 error: " << errorUOne );
  WALBERLA_CHECK_LESS( errorUOne, errorLimit );

  // 2. u linear
  // -----------
  //   a) u linear in x
  const real_t errorULinearInX   = testLaplaceResult( linearInX, zero );
  WALBERLA_LOG_INFO_ON_ROOT( "u linear in x: L2 error: " << errorULinearInX );
  WALBERLA_CHECK_LESS( errorULinearInX, errorLimit );

  //   b) u linear in x and y
  const real_t errorULinearInXY   = testLaplaceResult( linearInXY, zero );
  WALBERLA_LOG_INFO_ON_ROOT( "u linear in x and y: L2 error: " << errorULinearInXY );
  WALBERLA_CHECK_LESS( errorULinearInXY, errorLimit );

  //   c) u linear in x, y and z
  const real_t errorULinearInXYZ = testLaplaceResult( linearInXYZ, zero );
  WALBERLA_LOG_INFO_ON_ROOT( "u linear in x, y and z: L2 error: " << errorULinearInXYZ );
  WALBERLA_CHECK_LESS( errorULinearInXYZ, errorLimit );

}

int main( int argc, char* argv[] )
{
  walberla::Environment walberlaEnv( argc, argv );
  walberla::MPIManager::instance()->useWorldComm();

#if 0
  testLaplace3D( "../../data/meshes/3D/tet_1el.msh", 2 );
#endif

  testLaplace3D( "../../data/meshes/3D/tet_1el.msh", 3 );
  testLaplace3D( "../../data/meshes/3D/tet_1el.msh", 4 );
  testLaplace3D( "../../data/meshes/3D/tet_tilted_1el.msh", 3 );
  testLaplace3D( "../../data/meshes/3D/tet_tilted_1el.msh", 4 );

#if 0
  testLaplace3D( "../../data/meshes/3D/pyramid_2el.msh", 2 );
#endif
  testLaplace3D( "../../data/meshes/3D/pyramid_2el.msh", 3 );
  testLaplace3D( "../../data/meshes/3D/pyramid_2el.msh", 4 );
#if 0
  testLaplace3D( "../../data/meshes/3D/pyramid_4el.msh", 3 );
  testLaplace3D( "../../data/meshes/3D/pyramid_tilted_4el.msh", 3 );
  testLaplace3D( "../../data/meshes/3D/regular_octahedron_8el.msh", 3 );
#endif
  return 0;
}
