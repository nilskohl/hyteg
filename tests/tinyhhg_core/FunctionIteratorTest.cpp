#include "core/Environment.h"
#include "core/debug/CheckFunctions.h"
#include "core/DataTypes.h"

#include "tinyhhg_core/FunctionIterator.hpp"
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"
#include "tinyhhg_core/p2functionspace/P2Function.hpp"

using walberla::uint_t;

namespace hhg {

static void testFunctionIterator( const std::string & meshFileName, const uint_t & level )
{
  auto storage = PrimitiveStorage::createFromGmshFile( meshFileName );

  P1Function     < int > nVertex( "nVertex", storage, level, level );
  EdgeDoFFunction< int > nEdge  ( "nEdge",   storage, level, level );

  nVertex.enumerate( level );
  nEdge.enumerate( level );

  auto storageInfo = storage->getGlobalInfo();
  WALBERLA_LOG_INFO_ON_ROOT( storageInfo );

  std::set< uint_t > testEnumerateSet;
  uint_t numGlobalDoFs;
  uint_t numLocalDoFs;

  WALBERLA_LOG_INFO_ON_ROOT( "--- Testing VertexDoFSpace ---" );
  WALBERLA_MPI_BARRIER();

  numGlobalDoFs = numberOfGlobalDoFs< P1FunctionTag >( *storage, level );
  numLocalDoFs  = numberOfLocalDoFs< P1FunctionTag >( *storage, level );

  WALBERLA_LOG_INFO_ON_ROOT( "global dofs: " << numGlobalDoFs );
  WALBERLA_LOG_INFO( "local dofs: " << numLocalDoFs );

  for ( const auto & dof : FunctionIterator< P1Function< int > >( nVertex, level ) )
  {
    WALBERLA_CHECK( dof.isVertexDoF() )
    WALBERLA_LOG_INFO( dof );
    WALBERLA_CHECK_EQUAL( testEnumerateSet.count( dof.value() ), 0 );
    testEnumerateSet.insert( dof.value() );
  }
  WALBERLA_CHECK_EQUAL( testEnumerateSet.size(), numLocalDoFs );

  testEnumerateSet.clear();

  WALBERLA_MPI_BARRIER();
  WALBERLA_LOG_INFO_ON_ROOT( "--- Testing EdgeDoFSpace ---" );
  WALBERLA_MPI_BARRIER();

  numGlobalDoFs = numberOfGlobalDoFs< EdgeDoFFunctionTag >( *storage, level );
  numLocalDoFs  = numberOfLocalDoFs< EdgeDoFFunctionTag >( *storage, level );

  WALBERLA_LOG_INFO_ON_ROOT( "global dofs: " << numGlobalDoFs );
  WALBERLA_LOG_INFO( "local dofs: " << numLocalDoFs );

  for ( const auto & dof : FunctionIterator< EdgeDoFFunction< int > >( nEdge, level ) )
  {
    WALBERLA_CHECK( dof.isEdgeDoF() )
    WALBERLA_LOG_INFO( dof );
    WALBERLA_CHECK_EQUAL( testEnumerateSet.count( dof.value() ), 0 );
    testEnumerateSet.insert( dof.value() );
  }
  WALBERLA_CHECK_EQUAL( testEnumerateSet.size(), numLocalDoFs );

}

} // namespace hhg


int main( int argc, char* argv[] )
{
  walberla::Environment walberlaEnv(argc, argv);
  walberla::MPIManager::instance()->useWorldComm();
  hhg::testFunctionIterator( "../../data/meshes/annulus_coarse.msh", 2 );
  hhg::testFunctionIterator( "../../data/meshes/annulus_coarse.msh", 3 );
  hhg::testFunctionIterator( "../../data/meshes/3D/cube_24el.msh", 2 );
  hhg::testFunctionIterator( "../../data/meshes/3D/cube_24el.msh", 3 );

  return EXIT_SUCCESS;
}
