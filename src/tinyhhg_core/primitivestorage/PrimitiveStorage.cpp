
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"

#include "core/debug/CheckFunctions.h"
#include "core/debug/Debug.h"
#include "core/logging/Logging.h"
#include "core/mpi/OpenMPBufferSystem.h"
#include "tinyhhg_core/primitivedata/PrimitiveDataID.hpp"
#include "tinyhhg_core/primitives/Primitive.hpp"
#include "tinyhhg_core/primitives/vertex.hpp"
#include "tinyhhg_core/primitives/edge.hpp"
#include "tinyhhg_core/primitives/face.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"

#include <algorithm>
#include <map>
#include <vector>

namespace hhg {

using walberla::uint_t;

PrimitiveStorage::PrimitiveStorage( const SetupPrimitiveStorage & setupStorage ) :
  primitiveDataHandlers_( 0 )
{
  for ( auto it = setupStorage.beginVertices(); it != setupStorage.endVertices(); it++  )
  {
    if ( uint_c( walberla::mpi::MPIManager::instance()->rank() ) == setupStorage.getTargetRank( it->first ) )
    {
      vertices_[ it->first ] = std::make_shared< Vertex >( *it->second );
    }
  }

  for ( auto it = setupStorage.beginEdges(); it != setupStorage.endEdges(); it++ )
  {
    if ( uint_c( walberla::mpi::MPIManager::instance()->rank() )  == setupStorage.getTargetRank( it->first ) )
    {
      edges_[ it->first ] = std::make_shared< Edge >( *it->second );
    }
  }

  for ( auto it = setupStorage.beginFaces(); it != setupStorage.endFaces(); it++ )
  {
    if ( uint_c( walberla::mpi::MPIManager::instance()->rank() )  == setupStorage.getTargetRank( it->first ) )
    {
      faces_[ it->first ] = std::make_shared< Face >( *it->second );
    }
  }

  // Neighborhood

  for ( const auto & it : vertices_ )
  {
    auto vertex = it.second;

    for ( const auto & neighborVertexID : vertex->neighborVertices() )
    {
      const Vertex * neighborVertex = setupStorage.getVertex( neighborVertexID );
      if ( !vertexExistsLocally( neighborVertexID ) && !vertexExistsInNeighborhood( neighborVertexID ) )
      {
        neighborVertices_[ neighborVertexID.getID() ] = std::make_shared< Vertex >( *neighborVertex );
        neighborRanks_[ neighborVertexID.getID() ] = setupStorage.getTargetRank( neighborVertexID.getID() );
      }
    }

    for ( const auto & neighborEdgeID : vertex->neighborEdges() )
    {
      const Edge * neighborEdge = setupStorage.getEdge( neighborEdgeID );
      if ( !edgeExistsLocally( neighborEdgeID ) && !edgeExistsInNeighborhood( neighborEdgeID ) )
      {
        neighborEdges_[ neighborEdgeID.getID() ] = std::make_shared< Edge >( *neighborEdge );
        neighborRanks_[ neighborEdgeID.getID() ] = setupStorage.getTargetRank( neighborEdgeID.getID() );
      }
    }

    for ( const auto & neighborFaceID : vertex->neighborFaces() )
    {
      const Face * neighborFace = setupStorage.getFace( neighborFaceID );
      if ( !faceExistsLocally( neighborFaceID ) && !faceExistsInNeighborhood( neighborFaceID ) )
      {
        neighborFaces_[ neighborFaceID.getID() ] = std::make_shared< Face >( *neighborFace );
        neighborRanks_[ neighborFaceID.getID() ] = setupStorage.getTargetRank( neighborFaceID.getID() );
      }
    }
  }

  for ( const auto & it : edges_ )
  {
    auto edge = it.second;

    for ( const auto & neighborVertexID : edge->neighborVertices() )
    {
      const Vertex * neighborVertex = setupStorage.getVertex( neighborVertexID );
      if ( !vertexExistsLocally( neighborVertexID ) && !vertexExistsInNeighborhood( neighborVertexID ) )
      {
        neighborVertices_[ neighborVertexID.getID() ] = std::make_shared< Vertex >( *neighborVertex );
        neighborRanks_[ neighborVertexID.getID() ] = setupStorage.getTargetRank( neighborVertexID.getID() );
      }
    }

    for ( const auto & neighborEdgeID : edge->neighborEdges() )
    {
      const Edge * neighborEdge = setupStorage.getEdge( neighborEdgeID );
      if ( !edgeExistsLocally( neighborEdgeID ) && !edgeExistsInNeighborhood( neighborEdgeID ) )
      {
        neighborEdges_[ neighborEdgeID.getID() ] = std::make_shared< Edge >( *neighborEdge );
        neighborRanks_[ neighborEdgeID.getID() ] = setupStorage.getTargetRank( neighborEdgeID.getID() );
      }
    }

    for ( const auto & neighborFaceID : edge->neighborFaces() )
    {
      const Face * neighborFace = setupStorage.getFace( neighborFaceID );
      if ( !faceExistsLocally( neighborFaceID ) && !faceExistsInNeighborhood( neighborFaceID ) )
      {
        neighborFaces_[ neighborFaceID.getID() ] = std::make_shared< Face >( *neighborFace );
        neighborRanks_[ neighborFaceID.getID() ] = setupStorage.getTargetRank( neighborFaceID.getID() );
      }
    }
  }

  for ( const auto & it : faces_ )
  {
    auto face = it.second;

    for ( const auto & neighborVertexID : face->neighborVertices() )
    {
      const Vertex * neighborVertex = setupStorage.getVertex( neighborVertexID );
      if ( !vertexExistsLocally( neighborVertexID ) && !vertexExistsInNeighborhood( neighborVertexID ) )
      {
        neighborVertices_[ neighborVertexID.getID() ] = std::make_shared< Vertex >( *neighborVertex );
        neighborRanks_[ neighborVertexID.getID() ] = setupStorage.getTargetRank( neighborVertexID.getID() );
      }
    }

    for ( const auto & neighborEdgeID : face->neighborEdges() )
    {
      const Edge * neighborEdge = setupStorage.getEdge( neighborEdgeID );
      if ( !edgeExistsLocally( neighborEdgeID ) && !edgeExistsInNeighborhood( neighborEdgeID ) )
      {
        neighborEdges_[ neighborEdgeID.getID() ] = std::make_shared< Edge >( *neighborEdge );
        neighborRanks_[ neighborEdgeID.getID() ] = setupStorage.getTargetRank( neighborEdgeID.getID() );
      }
    }

    for ( const auto & neighborFaceID : face->neighborFaces() )
    {
      const Face * neighborFace = setupStorage.getFace( neighborFaceID );
      if ( !faceExistsLocally( neighborFaceID ) && !faceExistsInNeighborhood( neighborFaceID ) )
      {
        neighborFaces_[ neighborFaceID.getID() ] = std::make_shared< Face >( *neighborFace );
        neighborRanks_[ neighborFaceID.getID() ] = setupStorage.getTargetRank( neighborFaceID.getID() );
      }
    }
  }


#ifndef NDEBUG
  checkConsistency();
#endif
}



void PrimitiveStorage::getPrimitives( PrimitiveMap & primitiveMap ) const
{
  primitiveMap.clear();

  primitiveMap.insert( beginVertices(), endVertices() );
  primitiveMap.insert( beginEdges(), endEdges() );
  primitiveMap.insert( beginFaces(), endFaces() );

  WALBERLA_ASSERT_EQUAL( primitiveMap.size(), vertices_.size() + edges_.size() + faces_.size() );
}


const Primitive* PrimitiveStorage::getPrimitive( const PrimitiveID & id ) const
{
  if ( vertexExistsLocally( id ) || vertexExistsInNeighborhood( id ) ) return getVertex( id );
  if (   edgeExistsLocally( id ) ||   edgeExistsInNeighborhood( id ) ) return   getEdge( id );
  if (   faceExistsLocally( id ) ||   faceExistsInNeighborhood( id ) ) return   getFace( id );
  return nullptr;
}

Primitive* PrimitiveStorage::getPrimitive( const PrimitiveID & id )
{
  if ( vertexExistsLocally( id ) || vertexExistsInNeighborhood( id ) ) return getVertex( id );
  if (   edgeExistsLocally( id ) ||   edgeExistsInNeighborhood( id ) ) return   getEdge( id );
  if (   faceExistsLocally( id ) ||   faceExistsInNeighborhood( id ) ) return   getFace( id );
  return nullptr;
}

const Vertex* PrimitiveStorage::getVertex( const PrimitiveID & id ) const
{
  if ( vertexExistsLocally( id ) )
  {
    return vertices_.at( id.getID() ).get();
  }
  else if ( vertexExistsInNeighborhood( id ) )
  {
    return neighborVertices_.at( id.getID() ).get();
  }
  else
  {
    return nullptr;
  }
}

Vertex* PrimitiveStorage::getVertex( const PrimitiveID & id )
{
  if ( vertexExistsLocally( id ) )
  {
    return vertices_[ id.getID() ].get();
  }
  else if ( vertexExistsInNeighborhood( id ) )
  {
    return neighborVertices_[ id.getID() ].get();
  }
  else
  {
    return nullptr;
  }
}

const Edge* PrimitiveStorage::getEdge( const PrimitiveID & id ) const
{
  if ( edgeExistsLocally( id ) )
  {
    return edges_.at( id.getID() ).get();
  }
  else if ( edgeExistsInNeighborhood( id ) )
  {
    return neighborEdges_.at( id.getID() ).get();
  }
  else
  {
    return nullptr;
  }
}

Edge* PrimitiveStorage::getEdge( const PrimitiveID & id )
{
  if ( edgeExistsLocally( id ) )
  {
    return edges_[ id.getID() ].get();
  }
  else if ( edgeExistsInNeighborhood( id ) )
  {
    return neighborEdges_[ id.getID() ].get();
  }
  else
  {
    return nullptr;
  }
}

const Face* PrimitiveStorage::getFace( const PrimitiveID & id ) const
{
  if ( faceExistsLocally( id ) )
  {
    return faces_.at( id.getID() ).get();
  }
  else if ( faceExistsInNeighborhood( id ) )
  {
    return neighborFaces_.at( id.getID() ).get();
  }
  else
  {
    return nullptr;
  }
}

Face* PrimitiveStorage::getFace( const PrimitiveID & id )
{
  if ( faceExistsLocally( id ) )
  {
    return faces_[ id.getID() ].get();
  }
  else if ( faceExistsInNeighborhood( id ) )
  {
    return neighborFaces_[ id.getID() ].get();
  }
  else
  {
    return nullptr;
  }
}

void PrimitiveStorage::getPrimitiveIDs ( std::vector< PrimitiveID > & primitiveIDs ) const
{
  primitiveIDs.clear();

  std::vector< PrimitiveID > someIDs;

  getVertexIDs( someIDs );
  primitiveIDs.insert( primitiveIDs.end(), someIDs.begin(), someIDs.end() );

  getEdgeIDs( someIDs );
  primitiveIDs.insert( primitiveIDs.end(), someIDs.begin(), someIDs.end() );

  getFaceIDs( someIDs );
  primitiveIDs.insert( primitiveIDs.end(), someIDs.begin(), someIDs.end() );
}

void PrimitiveStorage::getVertexIDs ( std::vector< PrimitiveID > & vertexIDs ) const
{
  vertexIDs.clear();
  for ( auto const & it : vertices_ )
  {
    vertexIDs.push_back( it.first );
  }
}

void PrimitiveStorage::getEdgeIDs ( std::vector< PrimitiveID > & edgeIDs ) const
{
  edgeIDs.clear();
  for ( auto const & it : edges_ )
  {
    edgeIDs.push_back( it.first );
  }
}

void PrimitiveStorage::getFaceIDs ( std::vector< PrimitiveID > & faceIDs ) const
{
  faceIDs.clear();
  for ( auto const & it : faces_ )
  {
    faceIDs.push_back( it.first );
  }
}

uint_t PrimitiveStorage::getPrimitiveRank ( const PrimitiveID & id ) const
{
  WALBERLA_ASSERT( primitiveExistsLocally( id ) || primitiveExistsInNeighborhood( id ) );
  if ( primitiveExistsLocally( id ) )
  {
    return uint_c( walberla::mpi::MPIManager::instance()->rank() );
  }
  else
  {
    return getNeighborPrimitiveRank( id );
  }
}

void PrimitiveStorage::migratePrimitives( const std::map< PrimitiveID::IDType, uint_t > & primitivesToMigrate )
{
  uint_t rank         = uint_c( walberla::mpi::MPIManager::instance()->rank() );
  uint_t numProcesses = uint_c( walberla::mpi::MPIManager::instance()->numProcesses() );

  walberla::mpi::OpenMPBufferSystem bufferSystem( walberla::mpi::MPIManager::instance()->comm() );

  ///////////////////////////////////
  // Serialization and sender side //
  ///////////////////////////////////

  std::map< uint_t, std::vector< std::function< void( SendBuffer & ) > > > sendingFunctions;

  for ( const auto & primitiveToMigrate : primitivesToMigrate )
  {
    PrimitiveID primitiveID = primitiveToMigrate.first;
    uint_t      targetRank  = primitiveToMigrate.second;

    WALBERLA_CHECK( primitiveExistsLocally( primitiveID ), "Cannot migrate non-locally-existent primitives." );
    WALBERLA_CHECK_LESS( targetRank, numProcesses );

    if ( targetRank == rank )
    {
      // we do not want to send already local primitives
      continue;
    }

    // Serialize primitives:
    // Create one serialization callback per primitive that shall be serialized.
    // for all primitives to be migrated:
    // - true (signals that this is no empty message)
    // - primitive type (Vertex, Edge, ...)
    // - primitive (contains neighborhood IDs and metadata like coordinates etc.)
    // - primitive data
    //   - data that was added to all primitives
    //   - data that was added to the type of primitive
    // - for all neighbors:
    //   - neighbor type
    //   - neighbor primitive
    auto sendingFunction = [ = ]( SendBuffer & sendBuffer ) -> void
    {
      const PrimitiveTypeEnum primitiveType = getPrimitiveType( primitiveID );
      const Primitive *       primitive     = getPrimitive( primitiveID );

      sendBuffer << true;
      sendBuffer << primitiveType;
      sendBuffer << *primitive;

      serializeAllPrimitiveData( sendBuffer, primitiveID );

      // Neighborhood
      // the number of neighbors of the sent primitive is already serialized
      // in its metadata - so we do not need to send it
      std::vector< PrimitiveID > neighborhood;
      primitive->getNeighborPrimitives( neighborhood );
      for ( const auto & neighborID : neighborhood )
      {
        WALBERLA_ASSERT( primitiveExistsLocally( neighborID ) || primitiveExistsInNeighborhood( neighborID ) );

        const PrimitiveTypeEnum neighborType      = getPrimitiveType( neighborID );
        const Primitive *       neighborPrimitive = getPrimitive( neighborID );

        sendBuffer << neighborType;
        sendBuffer << *neighborPrimitive;
      }
    };

    sendingFunctions[ targetRank ].push_back( sendingFunction );
  }

  // Since we do not know if we receive primitives on the receiver side
  // and since it is apparently not possible to send empty buffers via the
  // buffer system (?) we need to work around this by sending empty messages
  // to all processes that will not receive primitives.
  // It should be possible to improve this by AllReduce or something...
  auto emptySendingFunction = []( SendBuffer & sendBuffer ) -> void
  {
    // empty message only contains a false boolean
    sendBuffer << false;
  };

  for ( uint_t receiverRank = 0; receiverRank < numProcesses; receiverRank++ )
  {
    if ( sendingFunctions.count( receiverRank ) == 0 )
    {
      sendingFunctions[ receiverRank ].push_back( emptySendingFunction );
    }
  }

  // adds the sending callbacks to the buffersystem
  for ( const auto & sendFunctionVectors : sendingFunctions )
  {
    uint_t targetRank                                                       = sendFunctionVectors.first;
    std::vector< std::function< void( SendBuffer & ) > > sendFunctionVector = sendFunctionVectors.second;

    auto sendingFunctionExecuter = [ sendFunctionVector ]( SendBuffer & sendBuffer ) -> void
    {
      for ( const auto & sendingFunction : sendFunctionVector ) { sendingFunction( sendBuffer ); }
    };

    bufferSystem.addSendingFunction( static_cast< walberla::mpi::MPIRank >( targetRank ), sendingFunctionExecuter );
  }


  ///////////////////////////////////////
  // Deserialization and receiver side //
  ///////////////////////////////////////

  // Each process registers a callback that parses and deserializes the messages sent above.
  auto receivingFunction = [ = ]( RecvBuffer & recvBuffer ) -> void
  {
    while ( !recvBuffer.isEmpty() )
    {
      bool          hasContent;
      recvBuffer >> hasContent;

      if ( hasContent )
      {
        const PrimitiveID primitiveID = deserializeAndAddPrimitive( recvBuffer, false );

        initializeAndDeserializeAllPrimitiveData( recvBuffer, primitiveID );

        // Neighborhood
        const Primitive * primitive = getPrimitive( primitiveID );
        const uint_t numNeighbors = primitive->getNumNeighborPrimitives();

#ifndef NDEBUG
        std::vector< PrimitiveID > neighborPrimitives;
        primitive->getNeighborPrimitives( neighborPrimitives );
#endif

        for ( uint_t neighborCnt = 0; neighborCnt < numNeighbors; neighborCnt++ )
        {
          PrimitiveID neighborPrimitiveID = deserializeAndAddPrimitive( recvBuffer, true );

#ifndef NDEBUG
          WALBERLA_CHECK( std::find( neighborPrimitives.begin(), neighborPrimitives.end(), neighborPrimitiveID ) != neighborPrimitives.end(),
                          "Received PrimitiveID that is no neighbor of previously unpacked primitive." );
#endif
        }
      }
    }
  };

  // adds the receiving callbacks
  for ( uint_t senderRank = 0; senderRank < numProcesses; senderRank++ )
  {
    bufferSystem.addReceivingFunction( static_cast< walberla::mpi::MPIRank >( senderRank ), receivingFunction );
  }


  //////////////////////////////
  // Performing communication //
  //////////////////////////////

  bufferSystem.startCommunication();
  bufferSystem.wait();

  ////////////////////////////////////////////////////////////////
  // Erasing the migrated primitives from the locally allocated //
  ////////////////////////////////////////////////////////////////

  for ( const auto & it : primitivesToMigrate )
  {
    PrimitiveID idToErase  = it.first;
    uint_t      targetRank = it.second;
    if ( targetRank != rank ) // only erase local primitives that were migrated to other ranks than mine
    {
      if ( vertexExistsLocally( idToErase ) ) vertices_.erase( idToErase.getID() );
      if (   edgeExistsLocally( idToErase ) )    edges_.erase( idToErase.getID() );
      if (   faceExistsLocally( idToErase ) )    faces_.erase( idToErase.getID() );
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // Erasing all neighborhood primitives that are also locally allocated now //
  /////////////////////////////////////////////////////////////////////////////

  std::vector< PrimitiveID > localPrimitiveIDs;
  for ( const auto & localID : localPrimitiveIDs )
  {
    if ( vertexExistsInNeighborhood( localID ) ) neighborVertices_.erase( localID.getID() );
    if (   edgeExistsInNeighborhood( localID ) )    neighborEdges_.erase( localID.getID() );
    if (   faceExistsInNeighborhood( localID ) )    neighborFaces_.erase( localID.getID() );
  }

  /////////////////////////////////////////////////////////////////////////////////////////
  // Erasing all neighbors that are not referenced by local primitives from neighborhood //
  /////////////////////////////////////////////////////////////////////////////////////////

  // TODO

  /////////////////////////////////
  // Updating neighborhood ranks //
  /////////////////////////////////

  // TODO

#ifndef NDEBUG
  checkConsistency();
#endif
}

#if 0
void PrimitiveStorage::eraseLocalPrimitives( const std::vector< PrimitiveID > & ids )
{
  // copy of local primitives
  PrimitiveStorage::PrimitiveMap primitiveMap;
  getPrimitives( primitiveMap );

  // remove to be erased primitives from copy
  for ( const auto & id : ids )
  {
	WALBERLA_ASSERT( primitiveExistsLocally( id ), "Cannot erase non-existent primitive!" );
    primitiveMap.erase( id.getID() );
  }

  // get all neighbors of remaining primitives
  std::set< PrimitiveID > remainingPrimitivesNeighbors;
  for ( const auto it : primitiveMap )
  {
	auto primitive = it.second;
	std::vector< PrimitiveID > neighborPrimitives;
	primitive->getNeighborPrimitives( neighborPrimitives );
	remainingPrimitivesNeighbors.insert( neighborPrimitives.begin(), neighborPrimitives.end() );
  }

  // collect a set of all neighbor primitives
  std::vector< PrimitiveID > neighborPrimitives;
  for ( const auto & it : neighborVertices_ ) { neighborPrimitives.push_back( it.first ); }
  for ( const auto & it : neighborEdges_ )    { neighborPrimitives.push_back( it.first ); }
  for ( const auto & it : neighborFaces_ )    { neighborPrimitives.push_back( it.first ); }

  std::set< PrimitiveID > neighborPrimitivesSet( neighborPrimitives.begin(), neighborPrimitives.end() );

  WALBERLA_ASSERT_EQUAL( neighborPrimitives.size(), neighborPrimitivesSet.size() );

  std::vector< PrimitiveID > neighborsToErase( neighborPrimitives.size() );
  std::set_difference( neighborPrimitives.begin(), neighborPrimitives.end(),
		               remainingPrimitivesNeighbors.begin(), remainingPrimitivesNeighbors.end(),
					   neighborsToErase.begin() );

  // remove all neighbors that are not in the set of remaining neighbors
  for ( const auto & idToErase : neighborsToErase )
  {
	if ( vertexExistsInNeighborhood( idToErase ) ) neighborVertices_.erase( idToErase.getID() );
	if ( edgeExistsInNeighborhood( idToErase ) )   neighborEdges_.erase( idToErase.getID() );
	if ( faceExistsInNeighborhood( idToErase ) )   neighborFaces_.erase( idToErase.getID() );
	if ( neighborRanks_.count( idToErase.getID() ) > 0 ) neighborRanks_.erase( idToErase.getID() );
  }

  // remove actual primitives
  for ( const auto & idToErase : ids )
  {
	if ( vertexExistsLocally( idToErase ) ) vertices_.erase( idToErase.getID() );
	if ( edgeExistsLocally( idToErase ) )   edges_.erase( idToErase.getID() );
	if ( faceExistsLocally( idToErase ) )   faces_.erase( idToErase.getID() );
  }
}
#endif

PrimitiveStorage::PrimitiveTypeEnum PrimitiveStorage::getPrimitiveType( const PrimitiveID & primitiveID ) const
{
  if ( vertexExistsLocally( primitiveID ) || vertexExistsInNeighborhood( primitiveID ) ) return VERTEX;
  if (   edgeExistsLocally( primitiveID ) ||   edgeExistsInNeighborhood( primitiveID ) ) return EDGE;
  if (   faceExistsLocally( primitiveID ) ||   faceExistsInNeighborhood( primitiveID ) ) return FACE;
  return INVALID;
}


PrimitiveID PrimitiveStorage::deserializeAndAddPrimitive( walberla::mpi::RecvBuffer & recvBuffer, const bool & isNeighborPrimitive )
{
  PrimitiveTypeEnum primitiveType;
  PrimitiveID       primitiveID;

  recvBuffer >> primitiveType;

  switch ( primitiveType )
  {
  case VERTEX:
  {
    std::shared_ptr< Vertex > vertex = std::make_shared< Vertex >( recvBuffer );
    primitiveID = vertex->getID();
    if ( isNeighborPrimitive )
    {
      neighborVertices_[ primitiveID.getID() ] = vertex;
    }
    else if ( !isNeighborPrimitive )
    {
      vertices_[ primitiveID.getID() ] = vertex;
    }
    break;
  }
  case EDGE:
  {
    std::shared_ptr< Edge > edge = std::make_shared< Edge >( recvBuffer );
    primitiveID = edge->getID();
    if ( isNeighborPrimitive )
    {
      neighborEdges_[ primitiveID.getID() ] = edge;
    }
    else if ( !isNeighborPrimitive )
    {
      edges_[ primitiveID.getID() ] = edge;
    }
    break;
  }
  case FACE:
  {
    std::shared_ptr< Face > face = std::make_shared< Face >( recvBuffer );
    primitiveID = face->getID();
    if ( isNeighborPrimitive )
    {
      neighborFaces_[ primitiveID.getID() ] = face;
    }
    else if ( !isNeighborPrimitive )
    {
      faces_[ primitiveID.getID() ] = face;
    }
    break;
  }
  default:
    WALBERLA_ABORT( "Cannot deserialize primitive - unkown primitive type" );
    break;
  }

  return primitiveID;
}



void PrimitiveStorage::serializeAllPrimitiveData( walberla::mpi::SendBuffer & sendBuffer, const PrimitiveID & primitiveID )
{
  WALBERLA_ASSERT( primitiveExistsLocally( primitiveID ) );
  const PrimitiveTypeEnum primitiveType = getPrimitiveType( primitiveID );
  switch ( primitiveType )
  {
  case VERTEX:
  {
    WALBERLA_ASSERT( vertexExistsLocally( primitiveID ) );
    auto vertex = vertices_[ primitiveID.getID() ];
    for ( const auto & serializationFunction : primitiveDataSerializationFunctions_ )
    {
      serializationFunction.second( vertex, sendBuffer );
    }
    for ( const auto & serializationFunction : vertexDataSerializationFunctions_ )
    {
      serializationFunction.second( vertex, sendBuffer );
    }
    break;
  }
  case EDGE:
  {
    WALBERLA_ASSERT( edgeExistsLocally( primitiveID ) );
    auto edge = edges_[ primitiveID.getID() ];
    for ( const auto & serializationFunction : primitiveDataSerializationFunctions_ )
    {
      serializationFunction.second( edge, sendBuffer );
    }
    for ( const auto & serializationFunction : edgeDataSerializationFunctions_ )
    {
      serializationFunction.second( edge, sendBuffer );
    }
    break;
  }
  case FACE:
  {
    WALBERLA_ASSERT( faceExistsLocally( primitiveID ) );
    auto face = faces_[ primitiveID.getID() ];
    for ( const auto & serializationFunction : primitiveDataSerializationFunctions_ )
    {
      serializationFunction.second( face, sendBuffer );
    }
    for ( const auto & serializationFunction : faceDataSerializationFunctions_ )
    {
      serializationFunction.second( face, sendBuffer );
    }
    break;
  }
  default:
    WALBERLA_ABORT( "Invalid primitive type during serialization." );
    break;
  }
}


void PrimitiveStorage::initializeAndDeserializeAllPrimitiveData( walberla::mpi::RecvBuffer & recvBuffer, const PrimitiveID & primitiveID )
{
  WALBERLA_ASSERT( primitiveExistsLocally( primitiveID ) );
  const PrimitiveTypeEnum primitiveType = getPrimitiveType( primitiveID );
  switch ( primitiveType )
  {
  case VERTEX:
  {
    WALBERLA_ASSERT( vertexExistsLocally( primitiveID ) );
    auto vertex = vertices_[ primitiveID.getID() ];
    for ( const auto & initializationFunction : primitiveDataInitializationFunctions_ )
    {
      initializationFunction.second( vertex );
    }
    for ( const auto & initializationFunction : vertexDataInitializationFunctions_ )
    {
      initializationFunction.second( vertex );
    }
    for ( const auto & deserializationFunction : primitiveDataDeserializationFunctions_ )
    {
      deserializationFunction.second( vertex, recvBuffer );
    }
    for ( const auto & deserializationFunction : vertexDataDeserializationFunctions_ )
    {
      deserializationFunction.second( vertex, recvBuffer );
    }
    break;
  }
  case EDGE:
  {
    WALBERLA_ASSERT( edgeExistsLocally( primitiveID ) );
    auto edge = edges_[ primitiveID.getID() ];
    for ( const auto & initializationFunction : primitiveDataInitializationFunctions_ )
    {
      initializationFunction.second( edge );
    }
    for ( const auto & initializationFunction : edgeDataInitializationFunctions_ )
    {
      initializationFunction.second( edge );
    }
    for ( const auto & deserializationFunction : primitiveDataDeserializationFunctions_ )
    {
      deserializationFunction.second( edge, recvBuffer );
    }
    for ( const auto & deserializationFunction : edgeDataDeserializationFunctions_ )
    {
      deserializationFunction.second( edge, recvBuffer );
    }
    break;
  }
  case FACE:
  {
    WALBERLA_ASSERT( faceExistsLocally( primitiveID ) );
    auto face = faces_[ primitiveID.getID() ];
    for ( const auto & initializationFunction : primitiveDataInitializationFunctions_ )
    {
      initializationFunction.second( face );
    }
    for ( const auto & initializationFunction : faceDataInitializationFunctions_ )
    {
      initializationFunction.second( face );
    }
    for ( const auto & deserializationFunction : primitiveDataDeserializationFunctions_ )
    {
      deserializationFunction.second( face, recvBuffer );
    }
    for ( const auto & deserializationFunction : faceDataDeserializationFunctions_ )
    {
      deserializationFunction.second( face, recvBuffer );
    }
    break;
  }
  default:
    WALBERLA_ABORT( "Invalid primitive type during initialization and deserialization." );
    break;
  }
}


void PrimitiveStorage::checkConsistency()
{
  // 1. Number of data entries less than local counter
  // 2. PrimitiveIDs of maps match IDs of Primitives
  // 3. Neighborhood of Primitives
  for ( auto it = vertices_.begin(); it != vertices_.end(); it++ )
  {
    WALBERLA_CHECK_GREATER_EQUAL( primitiveDataHandlers_, it->second->getNumberOfDataEntries() );
    WALBERLA_CHECK_EQUAL( it->first, it->second->getID().getID() );
    WALBERLA_CHECK_EQUAL( it->second->getNumLowerDimNeighbors(), 0 );
  }
  for ( auto it = edges_.begin(); it != edges_.end(); it++ )
  {
    WALBERLA_CHECK_GREATER_EQUAL( primitiveDataHandlers_, it->second->getNumberOfDataEntries() );
    WALBERLA_CHECK_EQUAL( it->first, it->second->getID().getID() );
    WALBERLA_CHECK_EQUAL( it->second->getNumLowerDimNeighbors(), 2 );
  }
  for ( auto it = faces_.begin(); it != faces_.end(); it++ )
  {
    WALBERLA_CHECK_GREATER_EQUAL( primitiveDataHandlers_, it->second->getNumberOfDataEntries() );
    WALBERLA_CHECK_EQUAL( it->first, it->second->getID().getID() );
    WALBERLA_CHECK_EQUAL( it->second->getNumLowerDimNeighbors(), 3 );
  }

  // 4. Number of data entries of neighbor primitives is zero
  // 5. PrimitiveIDs of neighbor maps match IDs of neighbor Primitives
  // 6. Neighborhood of Primitives
  for ( auto it = neighborVertices_.begin(); it != neighborVertices_.end(); it++ )
  {
    WALBERLA_CHECK_GREATER_EQUAL( 0, it->second->getNumberOfDataEntries() );
    WALBERLA_CHECK_EQUAL( it->first, it->second->getID().getID() );
    WALBERLA_CHECK_EQUAL( it->second->getNumLowerDimNeighbors(), 0 );
  }
  for ( auto it = neighborEdges_.begin(); it != neighborEdges_.end(); it++ )
  {
    WALBERLA_CHECK_GREATER_EQUAL( 0, it->second->getNumberOfDataEntries() );
    WALBERLA_CHECK_EQUAL( it->first, it->second->getID().getID() );
    WALBERLA_CHECK_EQUAL( it->second->getNumLowerDimNeighbors(), 2 );
  }
  for ( auto it = neighborFaces_.begin(); it != neighborFaces_.end(); it++ )
  {
    WALBERLA_CHECK_GREATER_EQUAL( 0, it->second->getNumberOfDataEntries() );
    WALBERLA_CHECK_EQUAL( it->first, it->second->getID().getID() );
    WALBERLA_CHECK_EQUAL( it->second->getNumLowerDimNeighbors(), 3 );
  }

  // 7. Number of callbacks is less or equal to the data handling counter
  WALBERLA_CHECK_LESS_EQUAL( primitiveDataInitializationFunctions_.size() , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( primitiveDataSerializationFunctions_.size()  , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( primitiveDataDeserializationFunctions_.size(), primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( vertexDataInitializationFunctions_.size()    , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( vertexDataSerializationFunctions_.size()     , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( vertexDataDeserializationFunctions_.size()   , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( edgeDataInitializationFunctions_.size()      , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( edgeDataSerializationFunctions_.size()       , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( edgeDataDeserializationFunctions_.size()     , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( faceDataInitializationFunctions_.size()      , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( faceDataSerializationFunctions_.size()       , primitiveDataHandlers_ );
  WALBERLA_CHECK_LESS_EQUAL( faceDataDeserializationFunctions_.size()     , primitiveDataHandlers_ );

#if 0
  // 8. As many neighbor ranks as neighbors
  WALBERLA_CHECK_EQUAL( neighborRanks_.size(), neighborVertices_.size() + neighborEdges_.size() + neighborFaces_.size() );

  // 9. Local primitives do not exist in neighborhood
  std::vector< PrimitiveID > primitiveIDs;
  getPrimitiveIDs( primitiveIDs );
  for ( const auto & id : primitiveIDs )
  {
    WALBERLA_CHECK( !primitiveExistsInNeighborhood( id ), "Primitive that exists in neighborhood: " << id.getID() );
  }
#endif
}


} // namespace hhg

