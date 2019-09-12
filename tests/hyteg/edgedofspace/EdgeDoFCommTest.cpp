/*
 * Copyright (c) 2017-2019 Dominik Thoennes.
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
#include "hyteg/FunctionMemory.hpp"
#include "hyteg/StencilDirections.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/p1functionspace/VertexDoFIndexing.hpp"
#include "hyteg/edgedofspace/EdgeDoFFunction.hpp"
#include "hyteg/edgedofspace/EdgeDoFIndexing.hpp"
#include "hyteg/indexing/MacroFaceIndexing.hpp"

#include "core/mpi/all.h"
#include "core/debug/all.h"

using namespace hyteg;

using walberla::real_t;

void printEdgeData( uint_t level, int* edgeData, uint_t funcSize )
{
   uint_t cellOffSet =
       levelinfo::num_microedges_per_edge( level ) + 2 * ( 3 * ( levelinfo::num_microedges_per_edge( level ) ) - 1 );

   for( uint_t i = 0; i < levelinfo::num_microedges_per_edge( level ); ++i )
   {
      std::cout << std::setw( 3 ) << i << " ";
   }
   std::cout << std::endl;
   for( uint_t i = 0; i < levelinfo::num_microedges_per_edge( level ); ++i )
   {
      std::cout << std::setw( 3 ) << edgeData[i] << " ";
   }
   std::cout << std::endl << std::endl;

   for( uint_t i = levelinfo::num_microedges_per_edge( level ); i < cellOffSet; ++i )
   {
      std::cout << std::setw( 3 ) << i << " ";
   }
   std::cout << std::endl;
   for( uint_t i = levelinfo::num_microedges_per_edge( level ); i < cellOffSet; ++i )
   {
      std::cout << std::setw( 3 ) << edgeData[i] << " ";
   }
   std::cout << std::endl << std::endl;

   for( uint_t i = cellOffSet; i < funcSize; ++i )
   {
      std::cout << std::setw( 3 ) << i << " ";
   }
   std::cout << std::endl;
   for( uint_t i = cellOffSet; i < funcSize; ++i )
   {
      std::cout << std::setw( 3 ) << edgeData[i] << " ";
   }
   std::cout << std::endl;
}

void check1tet( bool bufferComm = false )
{
   MeshInfo                            meshInfo = MeshInfo::fromGmshFile( "../../data/meshes/3D/tet_1el.msh" );
   SetupPrimitiveStorage               setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );

   const uint_t level = 2;

   hyteg::EdgeDoFFunction< int > x( "x", storage, level, level );
   if( bufferComm )
   {
      x.setLocalCommunicationMode(communication::BufferedCommunicator::LocalCommunicationMode::BUFFERED_MPI);
   }

   ////////// check cell to face comm //////////
   for( auto& cellIt : storage->getCells() )
   {
      Cell& cell      = *cellIt.second;
      int*  cellData  = cell.getData( x.getCellDataID() )->getPointer( level );
      for( uint_t i = 0; i < cell.getData( x.getCellDataID() )->getSize( level ); ++i )
      {
         cellData[i]  = static_cast< int >( i );
      }
   }

   x.communicate< Cell, Face >( level );

   x.communicate< Face, Edge >( level );

   Face& bottomFace     = *( storage->getFace( PrimitiveID( 10 ) ) );
   int*  bottomFaceData = bottomFace.getData( x.getFaceDataID() )->getPointer( level );

   Cell& cell     = *( storage->getCell( PrimitiveID( 14 ) ) );
   int*  cellData = cell.getData( x.getCellDataID() )->getPointer( level );

   auto edgeIt    = storage->getEdges().begin();
   auto edge0     = ( *edgeIt ).second;
   int* edge0Data = edge0.get()->getData( x.getEdgeDataID() )->getPointer( level );

   edgeIt++;
   auto edge1     = ( *edgeIt ).second;
   int* edge1Data = edge1.get()->getData( x.getEdgeDataID() )->getPointer( level );

   edgeIt++;
   auto edge2     = ( *edgeIt ).second;
   int* edge2Data = edge2.get()->getData( x.getEdgeDataID() )->getPointer( level );

   edgeIt++;
   auto edge3     = ( *edgeIt ).second;
   int* edge3Data = edge3.get()->getData( x.getEdgeDataID() )->getPointer( level );

   edgeIt++;
   auto edge4     = ( *edgeIt ).second;
   int* edge4Data = edge4.get()->getData( x.getEdgeDataID() )->getPointer( level );

   edgeIt++;
   auto edge5     = ( *edgeIt ).second;
   int* edge5Data = edge5.get()->getData( x.getEdgeDataID() )->getPointer( level );

   WALBERLA_LOG_DEVEL( *( edge0.get() ) );
   printEdgeData( 2, edge0Data, edge0->getData( x.getEdgeDataID() )->getSize( level ) );
   WALBERLA_LOG_DEVEL( *( edge1.get() ) );
   printEdgeData( 2, edge1Data, edge1->getData( x.getEdgeDataID() )->getSize( level ) );
   WALBERLA_LOG_DEVEL( *( edge2.get() ) );
   printEdgeData( 2, edge2Data, edge2->getData( x.getEdgeDataID() )->getSize( level ) );
   WALBERLA_LOG_DEVEL( *( edge3.get() ) );
   printEdgeData( 2, edge3Data, edge3->getData( x.getEdgeDataID() )->getSize( level ) );
   WALBERLA_LOG_DEVEL( *( edge4.get() ) );
   printEdgeData( 2, edge4Data, edge4->getData( x.getEdgeDataID() )->getSize( level ) );
   WALBERLA_LOG_DEVEL( *( edge5.get() ) );
   printEdgeData( 2, edge5Data, edge5->getData( x.getEdgeDataID() )->getSize( level ) );

   ////// EDGE 0 /////
   ///// X /////
   for( uint_t i = 0; i <= 1; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::X );
      uint_t faceIdx = edgedof::macroface::index( level, i, 1, edgedof::EdgeDoFOrientation::X, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, i, 1, 1, edgedof::EdgeDoFOrientation::X );
      WALBERLA_CHECK_EQUAL(
          edge0Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge0Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
   ///// Y /////
   for( uint_t i = 0; i <= 2; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::Y );
      uint_t faceIdx = edgedof::macroface::index( level, i, 0, edgedof::EdgeDoFOrientation::Y, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, i, 0, 1, edgedof::EdgeDoFOrientation::Y );
      WALBERLA_CHECK_EQUAL(
          edge0Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge0Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
   ///// Z /////
   for( uint_t i = 0; i <= 2; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::Z );
      uint_t faceIdx = edgedof::macroface::index( level, i, 1, edgedof::EdgeDoFOrientation::Z, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, i, 1, 0, edgedof::EdgeDoFOrientation::Z );
      WALBERLA_CHECK_EQUAL(
          edge0Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge0Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
   ///// XY /////
   for( uint_t i = 0; i <= 2; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::XY );
      uint_t faceIdx = edgedof::macroface::index( level, i, 0, edgedof::EdgeDoFOrientation::XY, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, i, 0, 1, edgedof::EdgeDoFOrientation::XY );
      WALBERLA_CHECK_EQUAL(
          edge0Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge0Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
   ///// XZ /////
   for( uint_t i = 0; i <= 2; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::XZ );
      uint_t faceIdx = edgedof::macroface::index( level, i, 1, edgedof::EdgeDoFOrientation::XZ, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, i, 1, 0, edgedof::EdgeDoFOrientation::XZ );
      WALBERLA_CHECK_EQUAL(
          edge0Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge0Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
   ///// YZ /////
   for( uint_t i = 0; i <= 3; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::YZ );
      uint_t faceIdx = edgedof::macroface::index( level, i, 0, edgedof::EdgeDoFOrientation::YZ, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, i, 0, 0, edgedof::EdgeDoFOrientation::YZ );
      WALBERLA_CHECK_EQUAL(
          edge0Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge0Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
   ///// XYZ /////
   for( uint_t i = 0; i <= 2; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::XYZ );
      uint_t faceIdx = edgedof::macroface::index( level, i, 0, edgedof::EdgeDoFOrientation::XYZ, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, i, 0, 0, edgedof::EdgeDoFOrientation::XYZ );
      WALBERLA_CHECK_EQUAL(
          edge0Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge0Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }

   ///// X EDGE 1 /////
   for( uint_t i = 0; i <= 1; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::X );
      uint_t faceIdx = edgedof::macroface::index( level, 1, i, edgedof::EdgeDoFOrientation::Y, 0 );
      uint_t cellIdx = edgedof::macrocell::index( level, 1, i, 1, edgedof::EdgeDoFOrientation::Y );
      WALBERLA_CHECK_EQUAL(
          edge1Data[edgeIdx], bottomFaceData[faceIdx], i << " edgeIdx: " << edgeIdx << " faceIdx: " << faceIdx );
      WALBERLA_CHECK_EQUAL( edge1Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }

   ///// X EDGE 2 /////
   for( uint_t i = 0; i <= 1; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::X );
      uint_t cellIdx = edgedof::macrocell::index( level, 1, 1, i, edgedof::EdgeDoFOrientation::Z );
      WALBERLA_CHECK_EQUAL( edge2Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
   ///// X EDGE 3 /////
   for( uint_t i = 0; i <= 1; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::X );
      uint_t cellIdx = edgedof::macrocell::index( level, 1 - i, i, 1, edgedof::EdgeDoFOrientation::XY );
      WALBERLA_CHECK_EQUAL( edge3Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }

   ///// X EDGE 4 /////
   for( uint_t i = 0; i <= 1; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::X );
      uint_t cellIdx = edgedof::macrocell::index( level, 1 - i, 1, i, edgedof::EdgeDoFOrientation::XZ );
      WALBERLA_CHECK_EQUAL( edge4Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }

   ///// X EDGE 5 /////
   for( uint_t i = 0; i <= 1; ++i )
   {
      uint_t edgeIdx = edgedof::macroedge::indexOnNeighborCell( level, i, 0, 2, edgedof::EdgeDoFOrientation::X );
      uint_t cellIdx = edgedof::macrocell::index( level, 1, 1 - i, i, edgedof::EdgeDoFOrientation::YZ );
      WALBERLA_CHECK_EQUAL( edge5Data[edgeIdx], cellData[cellIdx], i << " edgeIdx: " << edgeIdx << " cellIdx: " << cellIdx );
   }
}

void checkComm3d( const uint_t level )
{
   MeshInfo                            meshInfo = MeshInfo::fromGmshFile( "../../data/meshes/3D/cube_6el.msh" );
   SetupPrimitiveStorage               setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );

   hyteg::EdgeDoFFunction< int > x( "x", storage, level, level );
   /// for y we set the local comm to mpi; default would be direct
   hyteg::EdgeDoFFunction< int > y( "x", storage, level, level );
   y.setLocalCommunicationMode( communication::BufferedCommunicator::LocalCommunicationMode::BUFFERED_MPI );

   ////////// check cell to face comm //////////
   for( auto& cellIt : storage->getCells() )
   {
      Cell& cell      = *cellIt.second;
      int*  cellData  = cell.getData( x.getCellDataID() )->getPointer( level );
      int*  cellDataY = cell.getData( y.getCellDataID() )->getPointer( level );
      for( uint_t i = 0; i < cell.getData( x.getCellDataID() )->getSize( level ); ++i )
      {
         cellData[i]  = 13;
         cellDataY[i] = 26;
      }
   }

   x.communicate< Cell, Face >( level );
   y.communicate< Cell, Face >( level );

   for( auto& faceIt : storage->getFaces() )
   {
      Face& face      = *faceIt.second;
      int*  faceData  = face.getData( x.getFaceDataID() )->getPointer( level );
      int*  faceDataY = face.getData( y.getFaceDataID() )->getPointer( level );
      /// all non inner DoFs should be set to 13/26 so we start after the inner DoFs
      for( uint_t i = hyteg::levelinfo::num_microedges_per_face( level ); i < face.getData( x.getFaceDataID() )->getSize( level );
           ++i )
      {
         WALBERLA_CHECK_EQUAL( faceData[i], 13, i );
         WALBERLA_CHECK_EQUAL( faceDataY[i], 26, i );
      }
   }
   /////////////////////////////////////////////

   ////////// check edge to face comm //////////
   for( auto& edgeIt : storage->getEdges() )
   {
      Edge& edge      = *edgeIt.second;
      int*  edgeData  = edge.getData( x.getEdgeDataID() )->getPointer( level );
      int*  edgeDataY = edge.getData( y.getEdgeDataID() )->getPointer( level );
      for( uint_t i = 0; i < levelinfo::num_microedges_per_edge( level ); ++i )
      {
         edgeData[i]  = 14;
         edgeDataY[i] = 26;
      }
   }

   x.communicate< Edge, Face >( level );
   y.communicate< Edge, Face >( level );

   using hyteg::edgedof::macroface::BoundaryIterator;

   for( auto& faceIt : storage->getFaces() )
   {
      Face& face      = *faceIt.second;
      int*  faceData  = face.getData( x.getFaceDataID() )->getPointer( level );
      int*  faceDataY = face.getData( y.getFaceDataID() )->getPointer( level );
      for( const auto& it : BoundaryIterator( level , indexing::FaceBoundaryDirection::BOTTOM_LEFT_TO_RIGHT, 0 ) )
      {
         WALBERLA_CHECK_EQUAL( faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_HO_C )], 14);
         WALBERLA_CHECK_EQUAL( faceDataY[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_HO_C )], 26);
      }

      for( const auto& it : BoundaryIterator( level , indexing::FaceBoundaryDirection::DIAGONAL_BOTTOM_TO_TOP, 0 ) )
      {
         WALBERLA_CHECK_EQUAL( faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_DI_N )], 14);
         WALBERLA_CHECK_EQUAL( faceDataY[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_DI_N )], 26);
      }

      for( const auto& it : BoundaryIterator( level , indexing::FaceBoundaryDirection::LEFT_BOTTOM_TO_TOP, 0 ) )
      {
         WALBERLA_CHECK_EQUAL( faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_VE_NW )], 14);
         WALBERLA_CHECK_EQUAL( faceDataY[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_VE_NW )], 26);
      }
   }

   /////////////////////////////////////////////

   ////////// check face to edge comm //////////
   //TODO: activate MPI comm tests
   for( auto& faceIt : storage->getFaces() )
   {
      Face& face      = *faceIt.second;
      int*  faceData  = face.getData( x.getFaceDataID() )->getPointer( level );
      int*  faceDataY = face.getData( y.getFaceDataID() )->getPointer( level );
      for( uint_t i = 0; i < face.getData( x.getFaceDataID() )->getSize( level ); ++i )
      {
         faceData[i]  = 15;
         faceDataY[i] = 27;
      }
   }

   x.communicate< Face, Edge >( level );
   y.communicate< Face, Edge >( level );



   for( auto& edgeIt : storage->getEdges() )
   {
      Edge& edge      = *edgeIt.second;

      int*  edgeData  = edge.getData( x.getEdgeDataID() )->getPointer( level );
      int*  edgeDataY = edge.getData( y.getEdgeDataID() )->getPointer( level );

      printEdgeData( 2, edgeData, edge.getData( x.getEdgeDataID() )->getSize( level ) );
      printEdgeData( 2, edgeDataY, edge.getData( x.getEdgeDataID() )->getSize( level ) );

      for( uint_t i = levelinfo::num_microedges_per_edge( level ); i < edge.getData( x.getEdgeDataID() )->getSize( level ); ++i )
      {
         WALBERLA_CHECK_EQUAL( edgeData[i], 15, i );
         WALBERLA_CHECK_EQUAL( edgeDataY[i], 27, i );
      }
   }
   /////////////////////////////////////////////
}

template<uint_t level>
void checkComm(const std::string &meshfile, bool bufferComm = false){

  MeshInfo meshInfo = MeshInfo::fromGmshFile(meshfile);
  SetupPrimitiveStorage setupStorage(meshInfo, uint_c(walberla::mpi::MPIManager::instance()->numProcesses()));
  std::shared_ptr<PrimitiveStorage> storage = std::make_shared<PrimitiveStorage>(setupStorage);

  hyteg::EdgeDoFFunction< int > x("x", storage, level, level);
  if(bufferComm) {
    x.setLocalCommunicationMode(communication::BufferedCommunicator::BUFFERED_MPI);
  }

  x.enumerate(level);

  uint_t numberOfChecks = 0;
  uint_t totalExpectedChecks = 0;

  for(auto &edgeIt : storage->getEdges()){
    if(edgeIt.second.get()->getNumHigherDimNeighbors() == 1){
      totalExpectedChecks += 3 * levelinfo::num_microedges_per_edge( level ) + levelinfo::num_microedges_per_edge( level ) - 1;
    } else if(edgeIt.second.get()->getNumHigherDimNeighbors() == 2){
      totalExpectedChecks += 6 * levelinfo::num_microedges_per_edge( level ) + 2 * (levelinfo::num_microedges_per_edge( level ) - 1);
    } else {
      WALBERLA_CHECK(false);
    }
  }
  for(auto &vertexIt : storage->getVertices()){
    totalExpectedChecks += vertexIt.second->getNumNeighborFaces();
    totalExpectedChecks += vertexIt.second->getNumNeighborEdges();
  }

  using hyteg::edgedof::macroface::BoundaryIterator;
  for (auto &faceIt : storage->getFaces()) {
    Face &face = *faceIt.second;
    int *faceData = face.getData(x.getFaceDataID())->getPointer(level);
    std::vector<PrimitiveID> nbrEdges;
    face.getNeighborEdges(nbrEdges);
    uint_t localEdgeIdOnFace = 0;

/////////// FIRST EDGE ////////////

    Edge *firstEdge = storage->getEdge(nbrEdges[localEdgeIdOnFace].getID());
    int *edgeData = firstEdge->getData(x.getEdgeDataID())->getPointer(level);
    uint_t idxCounter = 0;
    /// horizontal Dof on edge 0
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromHorizontalEdge( level, idxCounter, stencilDirection::EDGE_HO_C )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_HO_C )]
      , "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter)
      idxCounter++;
      numberOfChecks++;
    }
    /// horizontal Dof on Face for edge 0; offset 1 to border
    idxCounter = 1;
    stencilDirection edgeDir = firstEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_HO_SE : stencilDirection::EDGE_HO_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),1)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
              faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_HO_C )]
            ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;

    }
    /// diagonal Dof on Face for edge 0; offset 0 to border
    idxCounter = 1;
    edgeDir = firstEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_VE_S : stencilDirection::EDGE_DI_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_DI_N )]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;
    }
    /// vertical Dof on Face for edge 0; offset 0 to border
    idxCounter = 1;
    edgeDir = firstEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_DI_SW : stencilDirection::EDGE_VE_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_VE_NW )]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;
    }
/////////// SECOND EDGE ////////////
    localEdgeIdOnFace = 2;
    Edge *secondEdge = storage->getEdge(nbrEdges[localEdgeIdOnFace].getID());
    edgeData = secondEdge->getData(x.getEdgeDataID())->getPointer(level);
    /// horizontal Dof on edge 1
    idxCounter = 0;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromHorizontalEdge( level, idxCounter, stencilDirection::EDGE_HO_C )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_DI_N )]
      , "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter)
      idxCounter++;
      numberOfChecks++;
    }
    /// diagonal Dof on Face = horizontal Dof on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = secondEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_HO_SE : stencilDirection::EDGE_HO_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),1)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_DI_N )]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;
    }
    /// vertical Dof on Face = diagonal Dof on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = secondEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_VE_S : stencilDirection::EDGE_DI_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)) {
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_VE_NW )],
        "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;
    }
      /// horizontal Dof on Face = vertical Dof on edge; offset 1 to border
      idxCounter = 1;
      edgeDir = secondEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_DI_SW : stencilDirection::EDGE_VE_NW;
      for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
        WALBERLA_CHECK_EQUAL(
          edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
          faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_HO_C )]
        ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
        idxCounter++;
        numberOfChecks++;
      }
/////////// THIRD EDGE ////////////
    localEdgeIdOnFace = 1;
    Edge *thirdEdge = storage->getEdge(nbrEdges[localEdgeIdOnFace].getID());
    edgeData = thirdEdge->getData(x.getEdgeDataID())->getPointer(level);
    /// horizontal Dof on edge 2
    idxCounter = 0;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromHorizontalEdge( level, idxCounter, stencilDirection::EDGE_HO_C )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_VE_NW )]
      , "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter)
      idxCounter++;
      numberOfChecks++;
    }
    /// vertical Dof on face for edge 2 = horizontal on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = thirdEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_HO_SE : stencilDirection::EDGE_HO_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),1)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_VE_NW )]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;
    }
    /// horizontal Dof on face for edge 2 = diagonal on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = thirdEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_DI_SW : stencilDirection::EDGE_VE_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_HO_C )]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;
    }
    /// diagonal Dof on face for edge 2 = vertical on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = thirdEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_VE_S : stencilDirection::EDGE_DI_NW;
    for(const auto& it : BoundaryIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[edgedof::macroedge::indexFromVertex( level, idxCounter, edgeDir )],
        faceData[edgedof::macroface::indexFromHorizontalEdge( level, it.col(), it.row(), stencilDirection::EDGE_DI_N )]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
      numberOfChecks++;
    }
  }

  for (auto &vertexIt : storage->getVertices()) {
    Vertex &vertex = *vertexIt.second;
    int *vertexData = vertex.getData(x.getVertexDataID())->getPointer(level);

    for (const PrimitiveID& edgeId : vertex.neighborEdges()) {
      Edge *edge = storage->getEdge(edgeId);
      int *edgeData = edge->getData(x.getEdgeDataID())->getPointer(level);
      if (edge->getVertexID0() == vertex.getID()) {
        WALBERLA_CHECK_EQUAL(
          edgeData[edgedof::macroedge::indexFromVertex( level, 1, stencilDirection::EDGE_HO_W )],
          vertexData[vertex.edge_index(edgeId)],
          "vertex: " << vertex.getID().getID() << " edgeIndex: " << vertex.edge_index(edgeId))
        numberOfChecks++;
      } else if (edge->getVertexID1() == vertex.getID()) {
        WALBERLA_CHECK_EQUAL(
          edgeData[edgedof::macroedge::indexFromVertex( level, levelinfo::num_microvertices_per_edge( level ) - 1, stencilDirection::EDGE_HO_W )],
          vertexData[vertex.edge_index(edgeId)],
          " edgeIndex: " << vertex.edge_index(edgeId))
        numberOfChecks++;
      } else {
        WALBERLA_ABORT("edge is not on vertex")
      }
    }
    for (const PrimitiveID& faceId : vertex.neighborFaces()) {
      Face *face = storage->getFace(faceId);
      int *faceData = face->getData(x.getFaceDataID())->getPointer(level);
      if (face->getVertexID0() == vertex.getID()) {
        WALBERLA_CHECK_EQUAL(
          faceData[edgedof::macroface::indexFromDiagonalEdge( level, 0, 0, stencilDirection::EDGE_DI_C )],
          vertexData[vertex.getNumNeighborEdges() + vertex.face_index(faceId)],
          " faceIndex: " << vertex.face_index(faceId))
        numberOfChecks++;
      } else if (face->getVertexID1() == vertex.getID()){
        uint_t nbrEdgeDoFs = levelinfo::num_microedges_per_edge( level );
        WALBERLA_CHECK_EQUAL(
          faceData[edgedof::macroface::indexFromVerticalEdge( level, nbrEdgeDoFs - 1, 0, stencilDirection::EDGE_VE_C )],
          vertexData[vertex.getNumNeighborEdges() + vertex.face_index(faceId)],
          " index: " << vertex.getNumNeighborEdges() + vertex.face_index(faceId))
        numberOfChecks++;
      } else if (face->getVertexID2() == vertex.getID()){
        uint_t nbrEdgeDoFs = levelinfo::num_microedges_per_edge( level );
        WALBERLA_CHECK_EQUAL(
          faceData[edgedof::macroface::indexFromHorizontalEdge( level, 0, nbrEdgeDoFs - 1, stencilDirection::EDGE_HO_C )],
          vertexData[vertex.getNumNeighborEdges() + vertex.face_index(faceId)],
          " faceIndex: " << vertex.getNumNeighborEdges() + vertex.face_index(faceId))
        numberOfChecks++;
      } else {
        WALBERLA_ABORT("face it not on vertex");
      }
    }

  }

  WALBERLA_CHECK_EQUAL(totalExpectedChecks,numberOfChecks, "expected: " << totalExpectedChecks << " number: " << numberOfChecks);

}

int main (int argc, char ** argv ) {

   walberla::mpi::Environment MPIenv(argc, argv);
   walberla::MPIManager::instance()->useWorldComm();
   walberla::debug::enterTestMode();

   checkComm<3>("../../data/meshes/tri_1el.msh", true);

   checkComm<3>("../../data/meshes/tri_1el.msh", false);

   checkComm<4>("../../data/meshes/tri_1el.msh", true);

   checkComm<4>("../../data/meshes/tri_1el.msh", false);

   checkComm<3>("../../data/meshes/quad_4el.msh", true);

   checkComm<4>("../../data/meshes/quad_4el.msh", true);

   checkComm<5>("../../data/meshes/quad_4el.msh", true);

   checkComm<4>("../../data/meshes/quad_4el.msh", false);

   checkComm<5>("../../data/meshes/quad_4el.msh", false);

   checkComm<3>("../../data/meshes/bfs_12el.msh", true);

   checkComm<3>("../../data/meshes/bfs_12el.msh", false);

   check1tet();

   check1tet( true );

   checkComm3d( 2u );

   return 0;


}
