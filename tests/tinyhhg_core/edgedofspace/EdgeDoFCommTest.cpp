#include "tinyhhg_core/edgedofspace/EdgeDoFFunction.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/indexing/EdgeDoFIndexing.hpp"
#include "tinyhhg_core/indexing/VertexDoFIndexing.hpp"
#include "tinyhhg_core/StencilDirections.hpp"

#include "core/mpi/all.h"
#include "core/debug/all.h"

using namespace hhg;

using walberla::real_t;

template<uint_t level>
void checkComm(std::string meshfile, bool bufferComm = false){

  //const uint_t level = 3;

  MeshInfo meshInfo = MeshInfo::fromGmshFile(meshfile);
  SetupPrimitiveStorage setupStorage(meshInfo, uint_c(walberla::mpi::MPIManager::instance()->numProcesses()));
  std::shared_ptr<PrimitiveStorage> storage = std::make_shared<PrimitiveStorage>(setupStorage);


  //const uint_t level = 4;
  hhg::EdgeDoFFunction< uint_t > x("x", storage, level, level);
  if(bufferComm) {
    x.getCommunicator(level).get()->setLocalCommunicationMode(communication::BufferedCommunicator::BUFFERED_MPI);
  }

  size_t num = 1;
  x.enumerate(level,num);

  //uint_t numberOfChecks = 0;
  uint_t totalExpectedChecks = 0;

  for(auto &edgeIt : storage->getEdges()){
    if(edgeIt.second.get()->getNumHigherDimNeighbors() == 1){

      totalExpectedChecks += 4;
    } else if(edgeIt.second.get()->getNumHigherDimNeighbors() == 2){
      totalExpectedChecks += 8;
    } else {
      WALBERLA_CHECK(false);
    }
  }

  using hhg::indexing::edgedof::macroface::BorderIterator;
  for (auto &faceIt : storage->getFaces()) {
    Face &face = *faceIt.second;
    uint_t *faceData = face.getData(x.getFaceDataID())->getPointer(level);
    std::vector<PrimitiveID> nbrEdges;
    face.getNeighborEdges(nbrEdges);
    uint_t localEdgeIdOnFace = 0;

/////////// FIRST EDGE ////////////

    Edge *firstEdge = storage->getEdge(nbrEdges[localEdgeIdOnFace].getID());
    uint_t *edgeData = firstEdge->getData(x.getEdgeDataID())->getPointer(level);
    uint_t idxCounter = 0;
    /// horizontal Dof on edge 0
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromHorizontalEdge< level >(idxCounter,stencilDirection::EDGE_HO_C)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_HO_C)]
      , "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter)
      idxCounter++;
    }
    /// horizontal Dof on Face for edge 0; offset 1 to border
    idxCounter = 1;
    stencilDirection edgeDir = firstEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_HO_SE : stencilDirection::EDGE_HO_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),1)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
              faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_HO_C)]
            ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;

    }
    /// diagonal Dof on Face for edge 0; offset 0 to border
    idxCounter = 1;
    edgeDir = firstEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_VE_S : stencilDirection::EDGE_DI_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_DI_N)]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
    }
    /// vertical Dof on Face for edge 0; offset 0 to border
    idxCounter = 1;
    edgeDir = firstEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_DI_SW : stencilDirection::EDGE_VE_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_VE_NW)]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
    }
/////////// SECOND EDGE ////////////
    localEdgeIdOnFace = 1;
    Edge *secondEdge = storage->getEdge(nbrEdges[localEdgeIdOnFace].getID());
    edgeData = secondEdge->getData(x.getEdgeDataID())->getPointer(level);
    /// horizontal Dof on edge 1
    idxCounter = 0;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromHorizontalEdge< level >(idxCounter,stencilDirection::EDGE_HO_C)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_DI_N)]
      , "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter)
      idxCounter++;
    }
    /// diagonal Dof on Face = horizontal Dof on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = secondEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_HO_SE : stencilDirection::EDGE_HO_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),1)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_DI_N)]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
    }
    /// vertical Dof on Face = diagonal Dof on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = secondEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_VE_S : stencilDirection::EDGE_DI_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)) {
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex<level>(idxCounter, edgeDir)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge<level>(it.col(), it.row(), stencilDirection::EDGE_VE_NW)],
        "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
    }
      /// horizontal Dof on Face = vertical Dof on edge; offset 1 to border
      idxCounter = 1;
      edgeDir = secondEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_DI_SW : stencilDirection::EDGE_VE_NW;
      for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
        WALBERLA_CHECK_EQUAL(
          edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
          faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_HO_C)]
        ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
        idxCounter++;
      }
/////////// THIRD EDGE ////////////
    localEdgeIdOnFace = 2;
    Edge *thirdEdge = storage->getEdge(nbrEdges[localEdgeIdOnFace].getID());
    edgeData = thirdEdge->getData(x.getEdgeDataID())->getPointer(level);
    /// horizontal Dof on edge 2
    idxCounter = 0;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromHorizontalEdge< level >(idxCounter,stencilDirection::EDGE_HO_C)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_VE_NW)]
      , "it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter)
      idxCounter++;
    }
    /// vertical Dof on face for edge 2 = horizontal on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = thirdEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_HO_SE : stencilDirection::EDGE_HO_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),1)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_VE_NW)]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
    }
    /// horizontal Dof on face for edge 2 = diagonal on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = thirdEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_DI_SW : stencilDirection::EDGE_VE_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_HO_C)]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
    }
    /// diagonal Dof on face for edge 2 = vertical on edge; offset 1 to border
    idxCounter = 1;
    edgeDir = thirdEdge->face_index(face.getID()) == 0 ? stencilDirection::EDGE_VE_S : stencilDirection::EDGE_DI_NW;
    for(const auto& it : BorderIterator(level,indexing::getFaceBorderDirection(localEdgeIdOnFace,face.edge_orientation[localEdgeIdOnFace]),0)){
      WALBERLA_CHECK_EQUAL(
        edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(idxCounter,edgeDir)],
        faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(it.col(),it.row(),stencilDirection::EDGE_DI_N)]
      ,"it.col(): " << it.col() << " it.row(): " << it.row() << " idxCounter: " << idxCounter);
      idxCounter++;
    }
  }

  for (auto &vertexIt : storage->getVertices()) {
    Vertex &vertex = *vertexIt.second;
    uint_t *vertexData = vertex.getData(x.getVertexDataID())->getPointer(level);

    for (const PrimitiveID& edgeId : vertex.neighborEdges()) {
      Edge *edge = storage->getEdge(edgeId);
      uint_t *edgeData = edge->getData(x.getEdgeDataID())->getPointer(level);
      if (edge->getVertexID0() == vertex.getID()) {
        WALBERLA_CHECK_EQUAL(
          edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(1,stencilDirection::EDGE_HO_W)],
          vertexData[vertex.edge_index(edgeId)],
          "vertex: " << vertex.getID().getID() << " edgeIndex: " << vertex.edge_index(edgeId))
      } else if (edge->getVertexID1() == vertex.getID()) {
        WALBERLA_CHECK_EQUAL(
          edgeData[indexing::edgedof::macroedge::indexFromVertex< level >(levelinfo::num_microvertices_per_edge( level ) - 1,stencilDirection::EDGE_HO_W)],
          vertexData[vertex.edge_index(edgeId)],
          " edgeIndex: " << vertex.edge_index(edgeId))
      } else {
        WALBERLA_ABORT("edge is not on vertex")
      }
    }
    for (const PrimitiveID& faceId : vertex.neighborFaces()) {
      Face *face = storage->getFace(faceId);
      uint_t *faceData = face->getData(x.getFaceDataID())->getPointer(level);
      if (face->getVertexID0() == vertex.getID()) {
        WALBERLA_CHECK_EQUAL(
          faceData[indexing::edgedof::macroface::indexFromDiagonalEdge< level >(0,0,stencilDirection::EDGE_DI_C)],
          vertexData[vertex.getNumNeighborEdges() + vertex.face_index(faceId)],
          " faceIndex: " << vertex.face_index(faceId))
      } else if (face->getVertexID1() == vertex.getID()){
        uint_t nbrEdgeDoFs = levelinfo::num_microedges_per_edge( level );
        WALBERLA_CHECK_EQUAL(
          faceData[indexing::edgedof::macroface::indexFromVerticalEdge< level >(nbrEdgeDoFs -1 ,0,stencilDirection::EDGE_VE_C)],
          vertexData[vertex.getNumNeighborEdges() + vertex.face_index(faceId)],
          " index: " << vertex.getNumNeighborEdges() + vertex.face_index(faceId))
      } else if (face->getVertexID2() == vertex.getID()){
        uint_t nbrEdgeDoFs = levelinfo::num_microedges_per_edge( level );
        WALBERLA_CHECK_EQUAL(
          faceData[indexing::edgedof::macroface::indexFromHorizontalEdge< level >(0, nbrEdgeDoFs -1,stencilDirection::EDGE_HO_C)],
          vertexData[vertex.getNumNeighborEdges() + vertex.face_index(faceId)],
          " faceIndex: " << vertex.face_index(faceId))
      } else {
        WALBERLA_ABORT("face it not on vertex");
      }
    }

  }

  //WALBERLA_CHECK_EQUAL(totalExpectedChecks,numberOfChecks);

}

int main (int argc, char ** argv ) {

  walberla::mpi::Environment MPIenv(argc, argv);
  walberla::MPIManager::instance()->useWorldComm();
  walberla::debug::enterTestMode();

  //checkComm("../../data/meshes/tri_1el.msh", true);

  //checkComm("../../data/meshes/tri_1el.msh", false);
  checkComm<3>("../../data/meshes/tri_1el.msh", true);

  //checkComm<3>("../../data/meshes/tri_1el.msh", false);

  checkComm<4>("../../data/meshes/tri_1el.msh", true);

  //checkComm<4>("../../data/meshes/tri_1el.msh", false);


  checkComm<3>("../../data/meshes/quad_4el.msh", true);

  checkComm<4>("../../data/meshes/quad_4el.msh", true);

  checkComm<5>("../../data/meshes/quad_4el.msh", true);

  //checkComm<4>("../../data/meshes/quad_4el.msh", false);

  //checkComm<5>("../../data/meshes/quad_4el.msh", false);

  checkComm<3>("../../data/meshes/bfs_12el.msh", true);

  //checkComm<3>("../../data/meshes/bfs_12el.msh", false);

  return 0;


}