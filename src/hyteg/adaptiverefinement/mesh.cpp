/*
 * Copyright (c) 2021-2022 Benjamin Mann
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

#include "mesh.hpp"

#include <algorithm>
#include <assert.h>
#include <core/mpi/Broadcast.h>
#include <iostream>
#include <map>
#include <numeric>
#include <type_traits>

// #include "hyteg/memory/MemoryAllocation.hpp"
#include "hyteg/primitivestorage/loadbalancing/SimpleBalancer.hpp"

#include "refine_cell.hpp"
#include "simplexFactory.hpp"

namespace hyteg {
namespace adaptiveRefinement {

template < class K_Simplex >
K_Mesh< K_Simplex >::K_Mesh( const SetupPrimitiveStorage& setupStorage )
: _n_processes( setupStorage.getNumberOfProcesses() )
{
   // copy geometrymaps for each primitive in initial setupStorage
   SetupPrimitiveStorage::PrimitiveMap setupPrimitives;
   setupStorage.getSetupPrimitives( setupPrimitives );
   for ( auto& [id, primitive] : setupPrimitives )
   {
      _geometryMap[id] = primitive->getGeometryMap();
   }
   _geometryMap[size_t( -1 )] = nullptr; // used for uninitialized values

   // internal data structures are only required on rank_0
   if ( walberla::mpi::MPIManager::instance()->rank() == 0 )
   {
      // extract vertices
      _n_vertices = setupStorage.getVertices().size();
      _vertices.resize( _n_vertices );
      _vertexBoundaryFlag.resize( _n_vertices );
      _vertexGeometryMap.resize( _n_vertices );

      // [0,1,...,n-1]
      std::vector< uint_t > vtxIndices( _n_vertices );
      // convert PrimitiveID::ID to Mesh::vertexID
      std::map< PrimitiveID::IDType, uint_t > conversion;

      // initialize vertices
      uint_t idx = 0;
      for ( auto& [id, vtx] : setupStorage.getVertices() )
      {
         // extract coordinates of vertex
         _vertices[idx] = vtx->getCoordinates();
         // extract geometrymap of vertex
         _vertexGeometryMap[idx] = id;
         // extract boundaryFlag of vertex
         _vertexBoundaryFlag[idx] = vtx->getMeshBoundaryFlag();
         // prepare element setup
         conversion[id]  = idx;
         vtxIndices[idx] = idx;
         ++idx;
      }

      // initialize all edges, faces and cells

      SimplexFactory fac( nullptr, vtxIndices );
      // simplex factory does not store cells
      std::set< std::shared_ptr< Simplex3 > > cells;
      std::vector< PrimitiveID >              v;

      for ( auto& [id, edge] : setupStorage.getEdges() )
      {
         edge->getNeighborVertices( v );
         auto myEdge = fac.make_edge( conversion[v[0].getID()], conversion[v[1].getID()] );
         myEdge->setPrimitiveID( id );
         myEdge->setGeometryMap( id );
         myEdge->setBoundaryFlag( edge->getMeshBoundaryFlag() );
      }

      for ( auto& [id, face] : setupStorage.getFaces() )
      {
         face->getNeighborVertices( v );
         auto myFace = fac.make_face( conversion[v[0].getID()], conversion[v[1].getID()], conversion[v[2].getID()] );
         myFace->setPrimitiveID( id );
         myFace->setGeometryMap( id );
         myFace->setBoundaryFlag( face->getMeshBoundaryFlag() );
      }

      for ( auto& [id, cell] : setupStorage.getCells() )
      {
         cell->getNeighborVertices( v );
         auto myCell = fac.make_cell(
             conversion[v[0].getID()], conversion[v[1].getID()], conversion[v[2].getID()], conversion[v[3].getID()] );
         myCell->setPrimitiveID( id );
         myCell->setGeometryMap( id );
         myCell->setBoundaryFlag( cell->getMeshBoundaryFlag() );
         cells.insert( myCell );
      }

      // insert volume elements into _T
      if constexpr ( std::is_same_v< K_Simplex, Simplex2 > )
      {
         if ( !cells.empty() )
         {
            WALBERLA_ABORT( "Adaptive 2D mesh requires SetupPrimitiveStorage without any cells!" );
         }
         for ( auto& p : fac.faces() )
         {
            _T.insert( p.second );
         }
      }
      if constexpr ( std::is_same_v< K_Simplex, Simplex3 > )
      {
         if ( cells.empty() )
         {
            WALBERLA_ABORT( "Adaptive 3D mesh requires SetupPrimitiveStorage containing at least one cell!" );
         }

         _T = cells;
      }

      _n_elements = _T.size();
   }

   // broadcast required values to all processes
   walberla::mpi::broadcastObject( _n_elements );
   walberla::mpi::broadcastObject( _n_vertices );
}

template < class K_Simplex >
void K_Mesh< K_Simplex >::refineRG( const std::vector< PrimitiveID >& elements_to_refine, uint_t n_el_max )
{
   if ( walberla::mpi::MPIManager::instance()->rank() == 0 )
   {
      // pessimistic estimate! in most cases the actual growth will be significantly smaller
      const uint_t est_growth_factor = ( K_Simplex::DIM == 2 ) ? 18 : 138;

      uint_t predict = _T.size();

      /* green elements must not be refined any further to
         prevent mesh degeneration
      */
      remove_green_edges();

      // get elements corresponding to given IDs
      auto R = init_R( elements_to_refine );

      // unprocessed elements
      std::set< std::shared_ptr< K_Simplex > > U = _T;
      // refined elements
      std::set< std::shared_ptr< K_Simplex > > refined;

      /* successively apply recursive red-refinement to parts of R
         until predicted n_el exceeds n_el_max
      */
      auto prt      = R.begin();
      auto prt_size = R.size();
      while ( prt_size > 0 && prt != R.end() && predict < n_el_max )
      {
         // move to next chunk
         auto done = prt;
         prt_size  = ( n_el_max - predict ) / est_growth_factor;
         prt       = done + std::min( int64_t( prt_size ), int64_t( R.end() - done ) );

         std::set< std::shared_ptr< K_Simplex > > R_prt( done, prt );
         R_prt.erase( nullptr );

         /* recursively apply red refinement for elements
         that otherwise would be subject to multiple
         green refinement steps later on
         */
         while ( !R_prt.empty() )
         {
            refined.merge( refine_red( R_prt, U ) );
            R_prt = find_elements_for_red_refinement( U );
         }

         // predict number of elements after required green step
         predict = U.size() + refined.size() + predict_n_el_green( U );
      }

      // apply green refinement
      refined.merge( refine_green( U ) );

      // update current configuration
      _T = U;
      _T.merge( refined );
      _n_vertices = _vertices.size();
      _n_elements = _T.size();
   }

   walberla::mpi::broadcastObject( _n_vertices );
   walberla::mpi::broadcastObject( _n_elements );
}

template < class K_Simplex >
std::shared_ptr< PrimitiveStorage > K_Mesh< K_Simplex >::make_storage()
{
   // broadcast data to all processes
   walberla::mpi::broadcastObject( _vertices );
   walberla::mpi::broadcastObject( _vertexGeometryMap );
   walberla::mpi::broadcastObject( _vertexBoundaryFlag );

   // extract connectivity, geometry and boundary data and add PrimitiveIDs
   std::vector< EdgeData > edges;
   std::vector< FaceData > faces;
   std::vector< CellData > cells;
   extract_data( edges, faces, cells );

   // std::shared_ptr< SetupPrimitiveStorage > setupStorage;
   // if ( walberla::mpi::MPIManager::instance()->rank() == 0 )
   // {
   //    setupStorage = make_setupStorage( vertexIDs, edges, faces, cells, _n_processes );
   //    loadbalancing::roundRobin( *setupStorage );
   // }

   // broadcast data to all processes
   walberla::mpi::broadcastObject( edges );
   walberla::mpi::broadcastObject( faces );
   walberla::mpi::broadcastObject( cells );

   auto setupStorage = make_setupStorage( edges, faces, cells, _n_processes );
   loadbalancing::roundRobin( *setupStorage );

   // setupStorage->toStream( std::cout, true );

   auto storage = std::make_shared< PrimitiveStorage >( *setupStorage );

   // auto [id, storage] = convert_to_storage( edges, faces, cells, _n_processes );
   // // add PrimitiveIDs to volume elements
   // if ( walberla::mpi::MPIManager::instance()->rank() == 0 )
   // {
   //    for ( auto& el : _T )
   //    {
   //       el->setPrimitiveID( id );
   //       ++id;
   //    }
   // }
   // vertex data is only required by rank 0
   // else
   if ( walberla::mpi::MPIManager::instance()->rank() != 0 )
   {
      _vertices.clear();
      _vertexGeometryMap.clear();
      _vertexBoundaryFlag.clear();
   }

   return storage;
}

template < class K_Simplex >
std::shared_ptr< SetupPrimitiveStorage > K_Mesh< K_Simplex >::make_setupStorage( const std::vector< EdgeData >& edges,
                                                                                 const std::vector< FaceData >& faces,
                                                                                 const std::vector< CellData >& cells,
                                                                                 const uint_t&                  n_processes )
{
   SetupPrimitiveStorage::VertexMap vertices_sps;
   SetupPrimitiveStorage::EdgeMap   edges_sps;
   SetupPrimitiveStorage::FaceMap   faces_sps;
   SetupPrimitiveStorage::CellMap   cells_sps;

   //****** add vertices to storage ******

   for ( uint_t id = 0; id < _vertices.size(); ++id )
   {
      // add new vertex
      auto primitive   = std::make_shared< Vertex >( PrimitiveID( id ), _vertices[id] );
      vertices_sps[id] = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = _vertexBoundaryFlag[id];
      primitive->geometryMap_      = _geometryMap[_vertexGeometryMap[id]];
   }

   //****** add edges to storage ******

   // identify edges with their vertex IDs
   std::map< Idx< 2 >, PrimitiveID > vertexIDsToEdgeID;

   for ( auto& edge : edges )
   {
      constexpr uint_t K = 1;

      // vertex coordinates and IDs
      auto v      = edge.get_vertices();
      auto coords = edge.get_coordinates( _vertices );

      std::array< PrimitiveID, K + 1 > vertexIDs;
      for ( uint_t i = 0; i <= K; ++i )
      {
         vertexIDs[i] = PrimitiveID( v[i] );
      }

      // add new edge
      auto primitive = std::make_shared< Edge >( edge.getPrimitiveID(), vertexIDs[0], vertexIDs[1], coords );
      edges_sps[edge.getPrimitiveID().getID()] = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = edge.getBoundaryFlag();
      primitive->geometryMap_      = _geometryMap[edge.getGeometryMap()];

      // Adding edge ID as neighbor to SetupVertices
      for ( const auto& vertexID : vertexIDs )
      {
         vertices_sps[vertexID.getID()]->addEdge( edge.getPrimitiveID() );
      }

      // Caching neighboring vertices
      vertexIDsToEdgeID[v] = edge.getPrimitiveID();
   }

   //****** add faces to storage ******

   // identify faces with their vertex IDs
   std::map< Idx< 3 >, PrimitiveID > vertexIDsToFaceID;

   for ( auto& face : faces )
   {
      constexpr uint_t K = 2;

      // vertex coordinates and IDs
      auto v      = face.get_vertices();
      auto coords = face.get_coordinates( _vertices );

      std::array< PrimitiveID, K + 1 > vertexIDs;
      for ( uint_t i = 0; i <= K; ++i )
      {
         vertexIDs[i] = PrimitiveID( v[i] );
      }

      // ordering of edges
      constexpr std::array< std::array< uint_t, 2 >, K + 1 > edgeOrder{ { { 0ul, 1ul }, { 0ul, 2ul }, { 1ul, 2ul } } };

      // edge IDs
      std::array< PrimitiveID, K + 1 > edgeIDs;
      for ( uint_t i = 0; i <= K; ++i )
      {
         edgeIDs[i] = vertexIDsToEdgeID[{ v[edgeOrder[i][0]], v[edgeOrder[i][1]] }];
      }

      // edge orientation
      std::array< int, K + 1 > edgeOrientation;
      for ( uint_t i = 0; i <= K; ++i )
      {
         std::vector< PrimitiveID > edgeVertices;
         edges_sps[edgeIDs[i].getID()]->getNeighborVertices( edgeVertices );

         if ( edgeVertices[0].getID() == v[edgeOrder[i][0]] )
            edgeOrientation[i] = 1;
         else
            edgeOrientation[i] = -1;
      }

      // add new face
      auto primitive = std::make_shared< Face >( face.getPrimitiveID(), vertexIDs, edgeIDs, edgeOrientation, coords );
      faces_sps[face.getPrimitiveID().getID()] = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = face.getBoundaryFlag();
      primitive->geometryMap_      = _geometryMap[face.getGeometryMap()];

      // Adding face ID to vertices as neighbors
      for ( const auto& vertexID : vertexIDs )
      {
         vertices_sps[vertexID.getID()]->addFace( face.getPrimitiveID() );
      }
      // Adding face ID to edges as neighbors
      for ( const auto& edgeID : edgeIDs )
      {
         edges_sps[edgeID.getID()]->addFace( face.getPrimitiveID() );
      }

      // Caching neighboring vertices
      vertexIDsToFaceID[v] = face.getPrimitiveID();
   }

   //****** add cells to storage ******

   for ( auto& cell : cells )
   {
      constexpr uint_t K = 3;

      // vertex coordinates and IDs
      auto v      = cell.get_vertices();
      auto coords = cell.get_coordinates( _vertices );

      std::vector< PrimitiveID > vertexIDs( K + 1 );
      for ( uint_t i = 0; i <= K; ++i )
      {
         vertexIDs[i] = PrimitiveID( v[i] );
      }

      // ordering of edges
      constexpr std::array< std::array< uint_t, 2 >, 6 > edgeOrder{
          { { 0ul, 1ul }, { 0ul, 2ul }, { 1ul, 2ul }, { 0ul, 3ul }, { 1ul, 3ul }, { 2ul, 3ul } } };

      // edge IDs
      std::vector< PrimitiveID > edgeIDs( 6 );
      for ( uint_t i = 0; i < 6; ++i )
      {
         edgeIDs[i] = vertexIDsToEdgeID[{ v[edgeOrder[i][0]], v[edgeOrder[i][1]] }];
      }

      // ordering of faces
      constexpr std::array< std::array< uint_t, 3 >, K + 1 > faceOrder{
          { { 0ul, 1ul, 2ul }, { 0ul, 1ul, 3ul }, { 0ul, 2ul, 3ul }, { 1ul, 2ul, 3ul } } };

      // face IDs
      std::vector< PrimitiveID > faceIDs( K + 1 );
      for ( uint_t i = 0; i <= K; ++i )
      {
         faceIDs[i] = vertexIDsToFaceID[{ v[faceOrder[i][0]], v[faceOrder[i][1]], v[faceOrder[i][2]] }];
      }

      std::array< std::map< uint_t, uint_t >, 6 > edgeLocalVertexToCellLocalVertexMaps;

      // edgeLocalVertexToCellLocalVertexMaps[ cellLocalEdgeID ][ edgeLocalVertexID ] = cellLocalVertexID;

      for ( uint_t i = 0; i < 6; ++i )
      {
         for ( const auto& j : edgeOrder[i] )
         {
            edgeLocalVertexToCellLocalVertexMaps[i][edges_sps.at( edgeIDs[i].getID() )->vertex_index( vertexIDs[j] )] = j;
         }
      }

      std::array< std::map< uint_t, uint_t >, 4 > faceLocalVertexToCellLocalVertexMaps;

      // faceLocalVertexToCellLocalVertexMaps[ cellLocalFaceID ][ faceLocalVertexID ] = cellLocalVertexID;

      for ( uint_t i = 0; i < K + 1; ++i )
      {
         for ( auto& j : faceOrder[i] )
         {
            faceLocalVertexToCellLocalVertexMaps[i][faces_sps.at( faceIDs[i].getID() )->vertex_index( vertexIDs[j] )] = j;
         }
      }

      // add new cell
      auto primitive = std::make_shared< Cell >( cell.getPrimitiveID(),
                                                 vertexIDs,
                                                 edgeIDs,
                                                 faceIDs,
                                                 coords,
                                                 edgeLocalVertexToCellLocalVertexMaps,
                                                 faceLocalVertexToCellLocalVertexMaps );

      cells_sps[cell.getPrimitiveID().getID()] = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = cell.getBoundaryFlag();
      primitive->geometryMap_      = _geometryMap[cell.getGeometryMap()];

      // Adding cell ID to vertices as neighbors
      for ( const auto& vertexID : vertexIDs )
      {
         vertices_sps[vertexID.getID()]->addCell( cell.getPrimitiveID() );
      }
      // Adding cell ID to edges as neighbors
      for ( const auto& edgeID : edgeIDs )
      {
         edges_sps[edgeID.getID()]->addCell( cell.getPrimitiveID() );
      }
      // Adding cell ID to faces as neighbors
      for ( const auto& faceID : faceIDs )
      {
         faces_sps[faceID.getID()]->addCell( cell.getPrimitiveID() );
      }
   }

   //****** add indirect neighbor faces ******

   for ( const auto& [faceID, face] : faces_sps )
   {
      std::set< PrimitiveID > indirectNeighborsSet;

      for ( const auto& vertexID : face->neighborVertices() )
      {
         auto vertex = vertices_sps[vertexID.getID()];
         for ( const auto& neighborFaceID : vertex->neighborFaces() )
         {
            if ( neighborFaceID != faceID )
            {
               indirectNeighborsSet.insert( neighborFaceID );
            }
         }
      }

      face->indirectNeighborFaceIDs_.clear();
      face->indirectNeighborFaceIDs_.insert(
          face->indirectNeighborFaceIDs_.begin(), indirectNeighborsSet.begin(), indirectNeighborsSet.end() );
   }

   //****** add indirect neighbor cells ******

   for ( const auto& [cellID, cell] : cells_sps )
   {
      std::set< PrimitiveID > indirectNeighborsSet;

      for ( const auto& vertexID : cell->neighborVertices() )
      {
         auto vertex = vertices_sps[vertexID.getID()];
         for ( const auto& neighborCellID : vertex->neighborCells() )
         {
            if ( neighborCellID != cellID )
            {
               indirectNeighborsSet.insert( neighborCellID );
            }
         }
      }

      cell->indirectNeighborCellIDs_.clear();
      cell->indirectNeighborCellIDs_.insert(
          cell->indirectNeighborCellIDs_.begin(), indirectNeighborsSet.begin(), indirectNeighborsSet.end() );
   }

   //****** construct new SetupPrimitiveStorage ******
   auto setupStorage =
       std::make_shared< SetupPrimitiveStorage >( vertices_sps, edges_sps, faces_sps, cells_sps, n_processes);
   return setupStorage;
}

template < class K_Simplex >
std::pair< uint_t, std::shared_ptr< PrimitiveStorage > >
    K_Mesh< K_Simplex >::convert_to_storage( const std::vector< EdgeData >& edges,
                                             const std::vector< FaceData >& faces,
                                             const std::vector< CellData >& cells,
                                             const uint_t&                  n_processes )
{
   SetupPrimitiveStorage::VertexMap vertices_sps;
   SetupPrimitiveStorage::EdgeMap   edges_sps;
   SetupPrimitiveStorage::FaceMap   faces_sps;
   SetupPrimitiveStorage::CellMap   cells_sps;

   // give each primitive a running id
   uint_t id = 0;

   //****** add vertices to storage ******

   for ( const auto& vtx : _vertices )
   {
      PrimitiveID vtxID( id );

      // add new vertex
      auto primitive   = std::make_shared< Vertex >( vtxID, vtx );
      vertices_sps[id] = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = _vertexBoundaryFlag[id];
      primitive->geometryMap_      = _geometryMap[_vertexGeometryMap[id]];

      ++id;
   }

   //****** add edges to storage ******

   // identify edges with their vertex IDs
   std::map< Idx< 2 >, PrimitiveID > vertexIDsToEdgeID;

   for ( size_t e = 0; e < edges.size(); ++e )
   {
      constexpr uint_t K = 1;

      PrimitiveID edgeID( id );

      // simplexData
      auto v             = edges[e].get_vertices();
      auto geometryMapID = edges[e].getGeometryMap();
      auto boundaryFlag  = edges[e].getBoundaryFlag();

      // vertex coordinates and IDs
      std::array< Point3D, K + 1 >     coords;
      std::array< PrimitiveID, K + 1 > vertexIDs;
      for ( size_t i = 0; i < K + 1; ++i )
      {
         coords[i]    = _vertices[v[i]];
         vertexIDs[i] = PrimitiveID( v[i] );
      }

      // add new edge
      auto primitive = std::make_shared< Edge >( edgeID, vertexIDs[0], vertexIDs[1], coords );
      edges_sps[id]  = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = boundaryFlag;
      primitive->geometryMap_      = _geometryMap[geometryMapID];

      // Adding edge ID as neighbor to SetupVertices
      for ( const auto& vertexID : vertexIDs )
      {
         vertices_sps[vertexID.getID()]->addEdge( edgeID );
      }

      // Caching neighboring vertices
      vertexIDsToEdgeID[v] = edgeID;

      ++id;
   }

   //****** add faces to storage ******

   // write back ID of first face
   auto face0 = id;

   // identify faces with their vertex IDs
   std::map< Idx< 3 >, PrimitiveID > vertexIDsToFaceID;

   for ( size_t f = 0; f < faces.size(); ++f )
   {
      constexpr uint_t K = 2;

      PrimitiveID faceID( id );

      // simplexData
      auto v             = faces[f].get_vertices();
      auto geometryMapID = faces[f].getGeometryMap();
      auto boundaryFlag  = faces[f].getBoundaryFlag();

      // vertex coordinates and IDs
      std::array< Point3D, K + 1 >     coords;
      std::array< PrimitiveID, K + 1 > vertexIDs;
      for ( size_t i = 0; i < K + 1; ++i )
      {
         coords[i]    = _vertices[v[i]];
         vertexIDs[i] = PrimitiveID( v[i] );
      }

      // ordering of edges
      constexpr std::array< std::array< uint_t, 2 >, K + 1 > edgeOrder{ { { 0ul, 1ul }, { 0ul, 2ul }, { 1ul, 2ul } } };

      // edge IDs
      std::array< PrimitiveID, K + 1 > edgeIDs;
      for ( uint_t i = 0; i < K + 1; ++i )
      {
         edgeIDs[i] = vertexIDsToEdgeID[{ v[edgeOrder[i][0]], v[edgeOrder[i][1]] }];
      }

      // edge orientation
      std::array< int, K + 1 > edgeOrientation;
      for ( uint_t i = 0; i < K + 1; ++i )
      {
         std::vector< PrimitiveID > edgeVertices;
         edges_sps[edgeIDs[i].getID()]->getNeighborVertices( edgeVertices );

         if ( edgeVertices[0].getID() == v[edgeOrder[i][0]] )
            edgeOrientation[i] = 1;
         else
            edgeOrientation[i] = -1;
      }

      // add new face
      auto primitive = std::make_shared< Face >( faceID, vertexIDs, edgeIDs, edgeOrientation, coords );
      faces_sps[id]  = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = boundaryFlag;
      primitive->geometryMap_      = _geometryMap[geometryMapID];

      // Adding face ID to vertices as neighbors
      for ( const auto& vertexID : vertexIDs )
      {
         vertices_sps[vertexID.getID()]->addFace( faceID );
      }
      // Adding face ID to edges as neighbors
      for ( const auto& edgeID : edgeIDs )
      {
         edges_sps[edgeID.getID()]->addFace( faceID );
      }

      // Caching neighboring vertices
      vertexIDsToFaceID[v] = faceID;

      ++id;
   }

   //****** add cells to storage ******

   // write back ID of first cell
   auto cell0 = id;

   for ( uint_t c = 0; c < cells.size(); ++c )
   {
      constexpr uint_t K = 3;

      PrimitiveID cellID( id );

      // simplexData
      auto v             = cells[c].get_vertices();
      auto geometryMapID = cells[c].getGeometryMap();
      auto boundaryFlag  = cells[c].getBoundaryFlag();

      // vertex coordinates and IDs
      std::array< Point3D, K + 1 > coords;
      std::vector< PrimitiveID >   vertexIDs( K + 1 );
      for ( size_t i = 0; i < K + 1; ++i )
      {
         coords[i]    = _vertices[v[i]];
         vertexIDs[i] = PrimitiveID( v[i] );
      }

      // ordering of edges
      constexpr std::array< std::array< uint_t, 2 >, 6 > edgeOrder{
          { { 0ul, 1ul }, { 0ul, 2ul }, { 1ul, 2ul }, { 0ul, 3ul }, { 1ul, 3ul }, { 2ul, 3ul } } };

      // edge IDs
      std::vector< PrimitiveID > edgeIDs( 6 );
      for ( uint_t i = 0; i < 6; ++i )
      {
         edgeIDs[i] = vertexIDsToEdgeID[{ v[edgeOrder[i][0]], v[edgeOrder[i][1]] }];
      }

      // ordering of faces
      constexpr std::array< std::array< uint_t, 3 >, K + 1 > faceOrder{
          { { 0ul, 1ul, 2ul }, { 0ul, 1ul, 3ul }, { 0ul, 2ul, 3ul }, { 1ul, 2ul, 3ul } } };

      // face IDs
      std::vector< PrimitiveID > faceIDs( K + 1 );
      for ( uint_t i = 0; i < K + 1; ++i )
      {
         faceIDs[i] = vertexIDsToFaceID[{ v[faceOrder[i][0]], v[faceOrder[i][1]], v[faceOrder[i][2]] }];
      }

      std::array< std::map< uint_t, uint_t >, 6 > edgeLocalVertexToCellLocalVertexMaps;

      // edgeLocalVertexToCellLocalVertexMaps[ cellLocalEdgeID ][ edgeLocalVertexID ] = cellLocalVertexID;

      for ( uint_t i = 0; i < 6; ++i )
      {
         for ( const auto& j : edgeOrder[i] )
         {
            edgeLocalVertexToCellLocalVertexMaps[i][edges_sps.at( edgeIDs[i].getID() )->vertex_index( vertexIDs[j] )] = j;
         }
      }

      std::array< std::map< uint_t, uint_t >, 4 > faceLocalVertexToCellLocalVertexMaps;

      // faceLocalVertexToCellLocalVertexMaps[ cellLocalFaceID ][ faceLocalVertexID ] = cellLocalVertexID;

      for ( uint_t i = 0; i < K + 1; ++i )
      {
         for ( auto& j : faceOrder[i] )
         {
            faceLocalVertexToCellLocalVertexMaps[i][faces_sps.at( faceIDs[i].getID() )->vertex_index( vertexIDs[j] )] = j;
         }
      }

      // add new cell
      auto primitive = std::make_shared< Cell >( cellID,
                                                 vertexIDs,
                                                 edgeIDs,
                                                 faceIDs,
                                                 coords,
                                                 edgeLocalVertexToCellLocalVertexMaps,
                                                 faceLocalVertexToCellLocalVertexMaps );

      cells_sps[id] = primitive;

      // add properties
      primitive->meshBoundaryFlag_ = boundaryFlag;
      primitive->geometryMap_      = _geometryMap[geometryMapID];

      // Adding cell ID to vertices as neighbors
      for ( const auto& vertexID : vertexIDs )
      {
         vertices_sps[vertexID.getID()]->addCell( cellID );
      }
      // Adding cell ID to edges as neighbors
      for ( const auto& edgeID : edgeIDs )
      {
         edges_sps[edgeID.getID()]->addCell( cellID );
      }
      // Adding cell ID to faces as neighbors
      for ( const auto& faceID : faceIDs )
      {
         faces_sps[faceID.getID()]->addCell( cellID );
      }

      ++id;
   }

   //****** add indirect neighbor faces ******

   for ( const auto& [faceID, face] : faces_sps )
   {
      std::set< PrimitiveID > indirectNeighborsSet;

      for ( const auto& vertexID : face->neighborVertices() )
      {
         auto vertex = vertices_sps[vertexID.getID()];
         for ( const auto& neighborFaceID : vertex->neighborFaces() )
         {
            if ( neighborFaceID != faceID )
            {
               indirectNeighborsSet.insert( neighborFaceID );
            }
         }
      }

      face->indirectNeighborFaceIDs_.clear();
      face->indirectNeighborFaceIDs_.insert(
          face->indirectNeighborFaceIDs_.begin(), indirectNeighborsSet.begin(), indirectNeighborsSet.end() );
   }

   //****** add indirect neighbor cells ******

   for ( const auto& [cellID, cell] : cells_sps )
   {
      std::set< PrimitiveID > indirectNeighborsSet;

      for ( const auto& vertexID : cell->neighborVertices() )
      {
         auto vertex = vertices_sps[vertexID.getID()];
         for ( const auto& neighborCellID : vertex->neighborCells() )
         {
            if ( neighborCellID != cellID )
            {
               indirectNeighborsSet.insert( neighborCellID );
            }
         }
      }

      cell->indirectNeighborCellIDs_.clear();
      cell->indirectNeighborCellIDs_.insert(
          cell->indirectNeighborCellIDs_.begin(), indirectNeighborsSet.begin(), indirectNeighborsSet.end() );
   }

   //****** construct new PrimitiveStorage ******
   SetupPrimitiveStorage setupStorage( vertices_sps, edges_sps, faces_sps, cells_sps, n_processes );
   setupStorage.toStream( std::cout, true );

   auto                  storage = std::make_shared< PrimitiveStorage >( setupStorage );

   uint_t id0 = ( cells.size() == 0 ) ? face0 : cell0;

   return { id0, storage };
}

template < class K_Simplex >
void K_Mesh< K_Simplex >::extract_data( std::vector< EdgeData >& edgeData,
                                        std::vector< FaceData >& faceData,
                                        std::vector< CellData >& cellData ) const
{
   std::set< std::shared_ptr< Simplex1 > > edges;
   std::set< std::shared_ptr< Simplex2 > > faces;
   std::set< std::shared_ptr< Simplex3 > > cells;

   // collect cells
   if constexpr ( std::is_same_v< K_Simplex, Simplex3 > )
   {
      cells = _T;
   }
   // collect faces
   if constexpr ( std::is_same_v< K_Simplex, Simplex2 > )
   {
      faces = _T;
   }
   for ( auto& cell : cells )
   {
      for ( auto& face : cell->get_faces() )
      {
         faces.insert( face );
      }
   }
   // collect edges
   for ( auto& face : faces )
   {
      for ( auto& edge : face->get_edges() )
      {
         edges.insert( edge );
      }
   }

   // collect data and add PrimitiveIDs
   uint_t id = _vertices.size();
   // collect edgedata
   for ( auto& edge : edges )
   {
      edge->setPrimitiveID( id );
      edgeData.push_back( EdgeData( edge.get() ) );
      ++id;
   }
   // collect facedata
   for ( auto& face : faces )
   {
      face->setPrimitiveID( id );
      faceData.push_back( FaceData( face.get() ) );
      ++id;
   }
   // collect celldata
   for ( auto& cell : cells )
   {
      cell->setPrimitiveID( id );
      cellData.push_back( CellData( cell.get() ) );
      ++id;
   }
}

template < class K_Simplex >
inline std::vector< std::shared_ptr< K_Simplex > >
    K_Mesh< K_Simplex >::init_R( const std::vector< PrimitiveID >& primitiveIDs ) const
{
   auto to_add = [&]( std::shared_ptr< K_Simplex > el, uint_t i ) -> bool {
      if ( el->has_children() )
      {
         // add element if it has a child with id=id
         for ( auto& child : el->get_children() )
         {
            if ( child->getPrimitiveID() == primitiveIDs[i] )
            {
               return true;
            }
         }
         return false;
      }
      else
      {
         // add element if id=id
         return ( el->getPrimitiveID() == primitiveIDs[i] );
      }
   };

   std::vector< std::shared_ptr< K_Simplex > > R( primitiveIDs.size() );
   for ( auto& el : _T )
   {
      for ( uint_t i = 0; i < R.size(); ++i )
      {
         if ( to_add( el, i ) )
         {
            R[i] = el;
            break;
         }
      }
   }

   return R;
}

template < class K_Simplex >
std::set< std::shared_ptr< K_Simplex > > K_Mesh< K_Simplex >::refine_red( const std::set< std::shared_ptr< K_Simplex > >& R,
                                                                          std::set< std::shared_ptr< K_Simplex > >&       U )
{
   std::set< std::shared_ptr< K_Simplex > > refined;

   for ( auto& el : R )
   {
      // mark el as processed
      if ( U.erase( el ) == 0 )
      {
         // for el ∉ U: don't try to refine
         continue;
      }

      // remove green edges
      bool check_subelements = el->kill_children();

      // apply regular refinement to el
      std::set< std::shared_ptr< K_Simplex > > subelements;
      if constexpr ( std::is_same_v< K_Simplex, Simplex2 > )
      {
         subelements = refine_face_red( _vertices, _vertexGeometryMap, _vertexBoundaryFlag, el );
      }
      if constexpr ( std::is_same_v< K_Simplex, Simplex3 > )
      {
         subelements = refine_cell_red( _vertices, _vertexGeometryMap, _vertexBoundaryFlag, el );
      }

      // if this red step only replaced a green step, subelements must be checked again
      if ( check_subelements )
      {
         U.merge( subelements );
      }
      else
      {
         refined.merge( subelements );
      }
   }

   return refined;
}

template < class K_Simplex >
void K_Mesh< K_Simplex >::remove_green_edges()
{
   auto T_cpy = _T;

   for ( auto& el : T_cpy )
   {
      if ( el->has_green_edge() )
      {
         _T.erase( el );
         _T.insert( el->get_parent() );
      }
   }
}

template <>
std::set< std::shared_ptr< Simplex2 > >
    K_Mesh< Simplex2 >::find_elements_for_red_refinement( const std::set< std::shared_ptr< Simplex2 > >& U )
{
   std::set< std::shared_ptr< Simplex2 > > R;

   for ( auto& el : U )
   {
      if ( el->vertices_on_edges() > 1 )
      {
         R.insert( el );
      }
   }

   return R;
}

template <>
std::set< std::shared_ptr< Simplex3 > >
    K_Mesh< Simplex3 >::find_elements_for_red_refinement( const std::set< std::shared_ptr< Simplex3 > >& U )
{
   std::set< std::shared_ptr< Simplex3 > > R;

   for ( auto& el : U )
   {
      uint_t n_red = 0;

      for ( auto& face : el->get_faces() )
      {
         if ( face->vertices_on_edges() > 1 )
         {
            if ( face->get_children().size() == 2 )
            {
               // remove green edge from face
               face->kill_children();
            }

            if ( !face->has_children() )
            {
               // apply red refinement to face
               refine_face_red( _vertices, _vertexGeometryMap, _vertexBoundaryFlag, face );
            }

            ++n_red;
         }
      }

      // if more than one face has been red-refined, mark cell for red refinement
      if ( n_red > 1 )
      {
         R.insert( el );
      }
   }

   return R;
}

template < class K_Simplex >
uint_t K_Mesh< K_Simplex >::predict_n_el_green( const std::set< std::shared_ptr< K_Simplex > >& U ) const
{
   uint_t n_el_green = 0;

   for ( auto& el : U )
   {
      uint_t new_vertices = el->vertices_on_edges();

      n_el_green += ( new_vertices == 2 ) ? 3 : new_vertices;
   }

   return n_el_green;
}

template <>
std::set< std::shared_ptr< Simplex2 > > K_Mesh< Simplex2 >::refine_green( std::set< std::shared_ptr< Simplex2 > >& U )
{
   std::set< std::shared_ptr< Simplex2 > > refined;
   std::set< std::shared_ptr< Simplex2 > > U_cpy = U;

   for ( auto& el : U_cpy )
   {
      // count number of new vertices on the edges of el
      uint_t new_vertices = el->vertices_on_edges();

      if ( new_vertices > 0 )
      {
         WALBERLA_ASSERT( !el->has_green_edge() );
         WALBERLA_ASSERT( new_vertices == 1 );

         /* if green refinement had been applied to the same element before,
            nothing has to be done
         */
         if ( el->has_children() )
         {
            for ( auto& child : el->get_children() )
            {
               refined.insert( child );
            }
         }
         else
         {
            refined.merge( refine_face_green( el ) );
         }

         // mark el as processed
         U.erase( el );
      }
   }

   return refined;
}

template <>
std::set< std::shared_ptr< Simplex3 > > K_Mesh< Simplex3 >::refine_green( std::set< std::shared_ptr< Simplex3 > >& U )
{
   std::set< std::shared_ptr< Simplex3 > > refined;
   std::set< std::shared_ptr< Simplex3 > > U_cpy = U;

   auto keepChildren = [&]( std::shared_ptr< Simplex3 > el ) {
      for ( auto& child : el->get_children() )
      {
         refined.insert( child );
      }
   };

   for ( auto& el : U_cpy )
   {
      uint_t new_vertices = el->vertices_on_edges();

      switch ( new_vertices )
      {
      case 0:
         continue;
         break;

      case 1:
         if ( el->has_children() )
         {
            WALBERLA_ASSERT( el->get_children().size() == 2 );
            keepChildren( el );
         }
         else
         {
            refined.merge( refine_cell_green_1( el ) );
         }
         break;

      case 2:
         if ( el->has_children() && el->get_children().size() == 4 )
         {
            keepChildren( el );
         }
         else
         {
            WALBERLA_ASSERT( el->get_children().size() == 0 || el->get_children().size() == 2 );
            el->kill_children();
            refined.merge( refine_cell_green_2( el ) );
         }
         break;

      case 3:
         if ( el->has_children() && el->get_children().size() == 4 )
         {
            keepChildren( el );
         }
         else
         {
            WALBERLA_ASSERT( el->get_children().size() == 0 || el->get_children().size() == 2 );
            el->kill_children();
            refined.merge( refine_cell_green_3( el ) );
         }
         break;

      default:
         WALBERLA_ASSERT( new_vertices <= 3 );
         break;
      }

      // mark el as processed
      if ( new_vertices > 0 )
      {
         U.erase( el );
      }
   }

   return refined;
}

template < class K_Simplex >
std::pair< real_t, real_t > K_Mesh< K_Simplex >::min_max_angle() const
{
   std::pair< real_t, real_t > mm{ 10, 0 };

   if ( walberla::mpi::MPIManager::instance()->rank() == 0 )
   {
      for ( auto& el : _T )
      {
         auto mm_el = el->min_max_angle( _vertices );

         mm.first  = std::min( mm.first, mm_el.first );
         mm.second = std::max( mm.second, mm_el.second );
      }
   }

   walberla::mpi::broadcastObject( mm );

   return mm;
}

template < class K_Simplex >
real_t K_Mesh< K_Simplex >::volume() const
{
   real_t v_tot = 0;

   if ( walberla::mpi::MPIManager::instance()->rank() == 0 )
   {
      for ( auto& el : _T )
      {
         v_tot += el->volume( _vertices );
      }
   }

   walberla::mpi::broadcastObject( v_tot );

   return v_tot;
}

template class K_Mesh< Simplex2 >;
template class K_Mesh< Simplex3 >;

} // namespace adaptiveRefinement
} // namespace hyteg
