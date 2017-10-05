#pragma once

#include "tinyhhg_core/levelinfo.hpp"
#include "tinyhhg_core/p1functionspace/P1Memory.hpp"
#include "tinyhhg_core/p1functionspace/P1EdgeIndex.hpp"
#include "tinyhhg_core/petsc/PETScWrapper.hpp"

#include "core/DataTypes.h"

namespace hhg {

namespace P1Edge {

template< typename ValueType, uint_t Level >
inline void interpolateTmpl(Edge &edge,
                        const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &edgeMemoryId,
                        std::function<ValueType(const hhg::Point3D &)> &expr) {
  using namespace EdgeCoordsVertex;

  EdgeP1FunctionMemory< ValueType > *edgeMemory = edge.getData(edgeMemoryId);

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  Point3D x = edge.getCoordinates()[0];
  Point3D dx = edge.getDirection()/(real_t) (rowsize - 1);

  x += dx;

  for (size_t i = 1; i < rowsize - 1; ++i) {
    edgeMemory->getPointer( Level )[index<Level>(i, VERTEX_C)] = expr(x);
    x += dx;
  }
}

SPECIALIZE_WITH_VALUETYPE( void, interpolateTmpl, interpolate )

template< typename ValueType, uint_t Level >
inline void assignTmpl(Edge &edge,
                   const std::vector<ValueType> &scalars,
                   const std::vector<PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge>> &srcIds,
                   const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &dstId) {
  using namespace EdgeCoordsVertex;

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  for (size_t i = 1; i < rowsize - 1; ++i) {
    ValueType tmp = scalars[0]*edge.getData(srcIds[0])->getPointer( Level )[index<Level>(i, VERTEX_C)];

    for (size_t k = 1; k < srcIds.size(); ++k) {
      tmp += scalars[k]*edge.getData(srcIds[k])->getPointer( Level )[index<Level>(i, VERTEX_C)];
    }

    edge.getData(dstId)->getPointer( Level )[index<Level>(i, VERTEX_C)] = tmp;
  }
}

SPECIALIZE_WITH_VALUETYPE( void, assignTmpl, assign )

template< typename ValueType, uint_t Level >
inline void addTmpl(Edge &edge,
                const std::vector<ValueType> &scalars,
                const std::vector<PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge>> &srcIds,
                const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &dstId) {
  using namespace EdgeCoordsVertex;

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  for (size_t i = 1; i < rowsize - 1; ++i) {
    ValueType tmp = 0.0;

    for (size_t k = 0; k < srcIds.size(); ++k) {
      tmp += scalars[k]*edge.getData(srcIds[k])->getPointer( Level )[index<Level>(i, VERTEX_C)];
    }

    edge.getData(dstId)->getPointer( Level )[index<Level>(i, VERTEX_C)] += tmp;
  }
}

SPECIALIZE_WITH_VALUETYPE( void, addTmpl, add )

template< typename ValueType, uint_t Level >
inline real_t dotTmpl(Edge &edge, const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &lhsMemoryId,
                  const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &rhsMemoryId) {
  using namespace EdgeCoordsVertex;

  real_t sp = 0.0;
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  for (size_t i = 1; i < rowsize - 1; ++i) {
    sp += edge.getData(lhsMemoryId)->getPointer( Level )[index<Level>(i, VERTEX_C)]
        * edge.getData(rhsMemoryId)->getPointer( Level )[index<Level>(i, VERTEX_C)];
  }

  return sp;
}

SPECIALIZE_WITH_VALUETYPE( real_t, dotTmpl, dot )

template< typename ValueType, uint_t Level >
inline void applyTmpl(Edge &edge, const PrimitiveDataID<EdgeP1StencilMemory, Edge> &operatorId,
                  const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &srcId,
                  const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &dstId, UpdateType update) {
  using namespace EdgeCoordsVertex;

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  auto &opr_data = edge.getData(operatorId)->data[Level];
  auto src = edge.getData(srcId)->getPointer( Level );
  auto dst = edge.getData(dstId)->getPointer( Level );

  ValueType tmp;

  for (size_t i = 1; i < rowsize - 1; ++i) {

    tmp = opr_data[VERTEX_C] * src[index<Level>(i, VERTEX_C)];

    for (auto& neighbor : neighbors_on_edge) {
      tmp += opr_data[neighbor] * src[index<Level>(i, neighbor)];
    }

    for (auto& neighbor : neighbors_south) {
      tmp += opr_data[neighbor] * src[index<Level>(i, neighbor)];
    }

    if (edge.getNumNeighborFaces() == 2) {
      for (auto& neighbor : neighbors_north) {
        tmp += opr_data[neighbor] * src[index<Level>(i, neighbor)];
      }
    }

    if (update == Replace) {
      dst[index<Level>(i, VERTEX_C)] = tmp;
    } else if (update == Add) {
      dst[index<Level>(i, VERTEX_C)] += tmp;
    }
  }
}

SPECIALIZE_WITH_VALUETYPE( void, applyTmpl, apply )

template< typename ValueType, uint_t Level >
inline void smoothGSTmpl(Edge &edge, const PrimitiveDataID<EdgeP1StencilMemory, Edge> &operatorId,
                      const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &dstId,
                      const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &rhsId) {
  using namespace EdgeCoordsVertex;

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  auto &opr_data = edge.getData(operatorId)->data[Level];
  auto dst = edge.getData(dstId)->getPointer( Level );
  auto rhs = edge.getData(rhsId)->getPointer( Level );

  for (size_t i = 1; i < rowsize - 1; ++i) {

    dst[index<Level>(i, VERTEX_C)] = rhs[index<Level>(i, VERTEX_C)];

    for (auto& neighbor : neighbors_on_edge) {
      dst[index<Level>(i, VERTEX_C)] -= opr_data[neighbor] * dst[index<Level>(i, neighbor)];
    }

    for (auto& neighbor : neighbors_south) {
      dst[index<Level>(i, VERTEX_C)] -= opr_data[neighbor] * dst[index<Level>(i, neighbor)];
    }

    if (edge.getNumNeighborFaces() == 2) {
      for (auto& neighbor : neighbors_north) {
        dst[index<Level>(i, VERTEX_C)] -= opr_data[neighbor] * dst[index<Level>(i, neighbor)];
      }
    }

    dst[index<Level>(i, VERTEX_C)] /= opr_data[VERTEX_C];
  }
}

SPECIALIZE_WITH_VALUETYPE( void, smoothGSTmpl, smooth_gs )

template< typename ValueType, uint_t Level >
inline void smoothJacTmpl(Edge &edge, const PrimitiveDataID<EdgeP1StencilMemory, Edge> &operatorId,
                          const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &dstId,
                          const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &rhsId,
                          const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &tmpId) {
  using namespace EdgeCoordsVertex;

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  auto &opr_data = edge.getData(operatorId)->data[Level];
  auto dst = edge.getData(dstId)->getPointer( Level );
  auto rhs = edge.getData(rhsId)->getPointer( Level );
  auto tmp = edge.getData(tmpId)->getPointer( Level );

  for (size_t i = 1; i < rowsize - 1; ++i) {

    dst[index<Level>(i, VERTEX_C)] = rhs[index<Level>(i, VERTEX_C)];

    for (auto& neighbor : neighbors_on_edge) {
      dst[index<Level>(i, VERTEX_C)] -= opr_data[neighbor] * tmp[index<Level>(i, neighbor)];
    }

    for (auto& neighbor : neighbors_south) {
      dst[index<Level>(i, VERTEX_C)] -= opr_data[neighbor] * tmp[index<Level>(i, neighbor)];
    }

    if (edge.getNumNeighborFaces() == 2) {
      for (auto& neighbor : neighbors_north) {
        dst[index<Level>(i, VERTEX_C)] -= opr_data[neighbor] * tmp[index<Level>(i, neighbor)];
      }
    }

    dst[index<Level>(i, VERTEX_C)] /= opr_data[VERTEX_C];
  }
}

SPECIALIZE_WITH_VALUETYPE( void, smoothJacTmpl, smooth_jac )

template< typename ValueType, uint_t SourceLevel >
inline void prolongateTmpl(Edge &edge, const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &memoryId) {
  using namespace EdgeCoordsVertex;

  size_t rowsize_c = levelinfo::num_microvertices_per_edge(SourceLevel);

  auto edge_data_f = edge.getData(memoryId)->getPointer( SourceLevel + 1 );
  auto edge_data_c = edge.getData(memoryId)->getPointer( SourceLevel );

  size_t i_c;
  for (i_c = 1; i_c < rowsize_c - 1; ++i_c) {

    edge_data_f[index<SourceLevel+1>(2*i_c, VERTEX_C)] = edge_data_c[index<SourceLevel>(i_c, VERTEX_C)];
    edge_data_f[index<SourceLevel+1>(2*i_c-1, VERTEX_C)] = 0.5*(edge_data_c[index<SourceLevel>(i_c-1, VERTEX_C)]
                                                              + edge_data_c[index<SourceLevel>(i_c, VERTEX_C)]);
  }

  edge_data_f[index<SourceLevel+1>(2*i_c-1, VERTEX_C)] = 0.5*(edge_data_c[index<SourceLevel>(i_c-1, VERTEX_C)]
                                                            + edge_data_c[index<SourceLevel>(i_c, VERTEX_C)]);
}

SPECIALIZE_WITH_VALUETYPE( void, prolongateTmpl, prolongate )

template< typename ValueType, uint_t Level >
inline void prolongateQuadraticTmpl(Edge &edge, const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &memoryId) {

  //TODO: rewrite using index function possible? maybe more generalized notion of Operator between different levels
  // is required.

  size_t rowsize_coarse = levelinfo::num_microvertices_per_edge(Level);
  size_t i_fine = 1;
  ValueType invtemp = 1/8.;
  const ValueType s1[3] = {3*invtemp, 6*invtemp, -invtemp};
  const ValueType s2[3] = {-invtemp, 6*invtemp, 3*invtemp};

  auto edge_data_f = edge.getData(memoryId)->getPointer( Level + 1 );
  auto edge_data_c = edge.getData(memoryId)->getPointer( Level );
  size_t i_coarse;
  for (i_coarse = 0; i_coarse < rowsize_coarse - 2; ++i_coarse) {
    edge_data_f[i_fine] =
        (s1[0]*edge_data_c[i_coarse] + s1[1]*edge_data_c[i_coarse + 1] + s1[2]*edge_data_c[i_coarse + 2]);
    edge_data_f[i_fine + 1] = edge_data_c[i_coarse + 1];
    i_fine += 2;
  }
  i_coarse--;
  edge_data_f[i_fine] =
      (s2[0]*edge_data_c[i_coarse] + s2[1]*edge_data_c[i_coarse + 1] + s2[2]*edge_data_c[i_coarse + 2]);

}

SPECIALIZE_WITH_VALUETYPE( void, prolongateQuadraticTmpl, prolongateQuadratic )

template< typename ValueType, uint_t Level >
inline void restrictTmpl(Edge &edge, const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &memoryId) {
  using namespace EdgeCoordsVertex;

  size_t rowsize_c = levelinfo::num_microvertices_per_edge(Level - 1);

  auto edge_data_f = edge.getData(memoryId)->getPointer( Level );
  auto edge_data_c = edge.getData(memoryId)->getPointer( Level - 1 );

  uint_t i_c;
  for ( i_c = 1; i_c < rowsize_c - 1; ++i_c) {
    edge_data_c[index<Level-1>(i_c, VERTEX_C)] = 1.0 * edge_data_f[index<Level>(2*i_c, VERTEX_C)];

    for (auto& neighbor : neighbors_on_edge) {
      edge_data_c[index<Level-1>(i_c, VERTEX_C)] += 0.5 * edge_data_f[index<Level>(2*i_c, neighbor)];
    }

    for (auto& neighbor : neighbors_south) {
      edge_data_c[index<Level-1>(i_c, VERTEX_C)] += 0.5 * edge_data_f[index<Level>(2*i_c, neighbor)];
    }

    if (edge.getNumNeighborFaces() == 2) {
      for (auto& neighbor : neighbors_north) {
        edge_data_c[index<Level-1>(i_c, VERTEX_C)] += 0.5 * edge_data_f[index<Level>(2*i_c, neighbor)];
      }
    }
  }
}

SPECIALIZE_WITH_VALUETYPE( void, restrictTmpl, restrict )

template< typename ValueType, uint_t Level >
inline void enumerateTmpl(Edge &edge, const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &dstId, uint_t& num) {
  using namespace EdgeCoordsVertex;

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  for (size_t i = 1; i < rowsize - 1; ++i) {
    edge.getData(dstId)->getPointer( Level )[index<Level>(i, VERTEX_C)] = walberla::real_c(num++);
  }
}

SPECIALIZE_WITH_VALUETYPE( void, enumerateTmpl, enumerate )

#ifdef HHG_BUILD_WITH_PETSC
template<uint_t Level>
inline void saveOperatorTmpl(Edge &edge, const PrimitiveDataID<EdgeP1StencilMemory, Edge> &operatorId,
                         const PrimitiveDataID<EdgeP1FunctionMemory< PetscInt >, Edge> &srcId,
                         const PrimitiveDataID<EdgeP1FunctionMemory< PetscInt >, Edge> &dstId, Mat& mat) {
  using namespace EdgeCoordsVertex;

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  auto &opr_data = edge.getData(operatorId)->data[Level];
  auto src = edge.getData(srcId)->getPointer( Level );
  auto dst = edge.getData(dstId)->getPointer( Level );


  for (uint_t i = 1; i < rowsize - 1; ++i) {
    PetscInt dstint = dst[index<Level>(i, VERTEX_C)];
    PetscInt srcint = src[index<Level>(i, VERTEX_C)];
    //out << fmt::format("{}\t{}\t{}\n", dst[index<Level>(i, VERTEX_C)], src[index<Level>(i, VERTEX_C)], opr_data[VERTEX_C]);
    MatSetValues(mat,1,&dstint,1,&srcint,&opr_data[VERTEX_C] ,INSERT_VALUES);         //TODO: Make this more efficient by grouping all of them in an array

    for (auto& neighbor : neighbors_on_edge) {
      srcint = src[index<Level>(i, neighbor)];
      //out << fmt::format("{}\t{}\t{}\n", dst[index<Level>(i, VERTEX_C)], src[index<Level>(i, neighbor)], opr_data[neighbor]);
      MatSetValues(mat,1,&dstint,1,&srcint,&opr_data[neighbor] ,INSERT_VALUES);
    }

    for (auto& neighbor : neighbors_south) {
      srcint = src[index<Level>(i, neighbor)];
      //out << fmt::format("{}\t{}\t{}\n", dst[index<Level>(i, VERTEX_C)], src[index<Level>(i, neighbor)], opr_data[neighbor]);
      MatSetValues(mat,1,&dstint,1,&srcint,&opr_data[neighbor] ,INSERT_VALUES);
    }

    if (edge.getNumNeighborFaces() == 2) {
      for (auto& neighbor : neighbors_north) {
        srcint = src[index<Level>(i, neighbor)];
        //out << fmt::format("{}\t{}\t{}\n", dst[index<Level>(i, VERTEX_C)], src[index<Level>(i, neighbor)], opr_data[neighbor]);
        MatSetValues(mat,1,&dstint,1,&srcint,&opr_data[neighbor] ,INSERT_VALUES);
      }
    }
  }
}

SPECIALIZE(void, saveOperatorTmpl, saveOperator)

template< typename ValueType, uint_t Level >
inline void createVectorFromFunctionTmpl(Edge &edge,
                                     const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &srcId,
                                     const PrimitiveDataID<EdgeP1FunctionMemory< PetscInt >, Edge> &numeratorId,
                                     Vec& vec) {
  PetscInt rowsize = (PetscInt) levelinfo::num_microvertices_per_edge(Level);

  auto src = edge.getData(srcId)->getPointer( Level );
  auto numerator = edge.getData(numeratorId)->getPointer( Level );

  VecSetValues(vec,rowsize-2,&numerator[1],&src[1],INSERT_VALUES);
}

SPECIALIZE_WITH_VALUETYPE(void, createVectorFromFunctionTmpl, createVectorFromFunction)

template< typename ValueType, uint_t Level >
inline void createFunctionFromVectorTmpl(Edge &edge,
                                         const PrimitiveDataID<EdgeP1FunctionMemory< ValueType >, Edge> &srcId,
                                         const PrimitiveDataID<EdgeP1FunctionMemory< PetscInt >, Edge> &numeratorId,
                                         Vec& vec) {
  PetscInt rowsize = (PetscInt) levelinfo::num_microvertices_per_edge(Level);

  auto numerator = edge.getData(numeratorId)->getPointer( Level );

  VecGetValues(vec,rowsize-2,&numerator[1],&edge.getData(srcId)->getPointer( Level )[1]);
}

SPECIALIZE_WITH_VALUETYPE(void, createFunctionFromVectorTmpl, createFunctionFromVector)

template< uint_t Level >
inline void applyDirichletBCTmpl(Edge &edge,std::vector<PetscInt> &mat,
                                 const PrimitiveDataID<EdgeP1FunctionMemory< PetscInt >, Edge> &numeratorId){

  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);

  for(uint_t i = 1;i<rowsize-1; i++)
  {
    mat.push_back(edge.getData(numeratorId)->getPointer( Level )[i]);
  }

}
SPECIALIZE(void, applyDirichletBCTmpl, applyDirichletBC)
#endif

}
}
