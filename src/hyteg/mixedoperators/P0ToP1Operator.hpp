/*
* Copyright (c) 2017-2022 Nils Kohl.
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

#pragma once

#include <hyteg/communication/Syncing.hpp>

#include "hyteg/celldofspace/CellDoFIndexing.hpp"
#include "hyteg/dgfunctionspace/DGFunction.hpp"
#include "hyteg/dgfunctionspace/P0_to_P1_divt_form.hpp"
#include "hyteg/functions/Function.hpp"
#include "hyteg/indexing/Common.hpp"
#include "hyteg/indexing/MacroCellIndexing.hpp"
#include "hyteg/indexing/MacroEdgeIndexing.hpp"
#include "hyteg/indexing/MacroFaceIndexing.hpp"
#include "hyteg/memory/FunctionMemory.hpp"
#include "hyteg/operators/Operator.hpp"
#include "hyteg/p0functionspace/P0Function.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"
#include "hyteg/p1functionspace/VertexDoFIndexing.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroFace.hpp"
#include "hyteg/solvers/Smoothables.hpp"

namespace hyteg {

using namespace dg;
using facedof::FaceType;
using indexing::Index;
using volumedofspace::indexing::VolumeDoFMemoryLayout;
using walberla::int_c;
using walberla::real_t;

template < typename Form >
class P0ToP1Operator : public Operator< P0Function< real_t >, P1Function< real_t > >
{
 public:
   P0ToP1Operator( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator< P0Function< real_t >, P1Function< real_t > >( storage, minLevel, maxLevel )
   , form_( std::make_shared< Form >() )
   {}

   void apply( const P0Function< real_t >& src,
               const P1Function< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {
      assembleAndOrApply( src, dst, level, flag, nullptr, updateType );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const P0Function< idx_t >&                  src,
                  const P1Function< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      assembleAndOrApply( src, dst, level, flag, mat, Replace );
   }

   template < typename VType >
   VType* p1Data( const P1Function< VType >&                 function,
                  const std::shared_ptr< PrimitiveStorage >& storage,
                  const PrimitiveID&                         pid,
                  uint_t                                     level ) const
   {
      if ( storage->hasGlobalCells() )
      {
         WALBERLA_ASSERT( storage->cellExistsLocally( pid ) );
         auto cell = storage->getCell( pid );
         return cell->getData( function.getCellDataID() )->getPointer( level );
      }
      else
      {
         WALBERLA_ASSERT( storage->faceExistsLocally( pid ) );
         auto face = storage->getFace( pid );
         return face->getData( function.getFaceDataID() )->getPointer( level );
      }
   }

 private:
   /// \brief This is similar to the implementation in the dg::DGOperator class.
   template < typename VType >
   inline void assembleAndOrApply( const P0Function< VType >&                  src,
                                   const P1Function< VType >&                  dst,
                                   size_t                                      level,
                                   DoFType                                     flag,
                                   const std::shared_ptr< SparseMatrixProxy >& mat,
                                   UpdateType                                  updateType = Replace ) const
   {
      // To avoid code duplication in this already long method, the implementation "fuses" the 2D and 3D implementation.
      // This more or less serves as a reference - for better performance the matrix-vector multiplication should be specialized.

      DGBasisLinearLagrange_Example dstBasis;

      using indexing::Index;
      using volumedofspace::indexing::ElementNeighborInfo;

      WALBERLA_CHECK( updateType == Replace );

      const auto storage = this->getStorage();

      int dim = 2;
      if ( storage->hasGlobalCells() )
      {
         dim = 3;
      }

      std::vector< PrimitiveID > pids;
      if ( dim == 2 )
      {
         src.template communicate< Face, Face >( level );
         pids = storage->getFaceIDs();
      }
      else
      {
         src.template communicate< Cell, Cell >( level );
         pids = storage->getCellIDs();
      }

      for ( const auto& pid : pids )
      {
         const auto srcPolyDegree = 0;
         const auto dstPolyDegree = 1;

         const auto numSrcDofs = 1;
         const auto numDstDofs = dim + 1;
         ;

         const auto srcDofMemory = src.getDGFunction()->volumeDoFFunction()->dofMemory( pid, level );
         auto       dstDofMemory = p1Data< VType >( dst, storage, pid, level );

         const auto srcMemLayout = src.getDGFunction()->volumeDoFFunction()->memoryLayout();

         std::map< uint_t, VType* > glMemory;

         // TODO: Handle P1 ghost layer memory (here probably) for neighboring macros.
#if 0
         if ( dim == 2 )
         {
            WALBERLA_ASSERT( storage->faceExistsLocally( pid ) );
            const auto face = storage->getFace( pid );
            for ( const auto& [n, _] : face->getIndirectNeighborFaceIDsOverEdges() )
            {
               glMemory[n] = src.volumeDoFFunction()->glMemory( pid, level, n );
            }
         }
         else
         {
            WALBERLA_ASSERT( storage->cellExistsLocally( pid ) );
            const auto cell = storage->getCell( pid );
            for ( const auto& [n, _] : cell->getIndirectNeighborCellIDsOverFaces() )
            {
               glMemory[n] = src.volumeDoFFunction()->glMemory( pid, level, n );
            }
         }

#endif
         const uint_t numMicroVolTypes = ( storage->hasGlobalCells() ? 6 : 2 );

         for ( uint_t microVolType = 0; microVolType < numMicroVolTypes; microVolType++ )
         {
            if ( dim == 2 && microVolType >= 2 )
            {
               break;
            }

            auto faceType = facedof::allFaceTypes[microVolType];
            auto cellType = celldof::allCellTypes[microVolType];

            auto itFace = facedof::macroface::Iterator( level, faceType ).begin();
            auto itCell = celldof::macrocell::Iterator( level, cellType ).begin();

            while ( ( dim == 2 && itFace != itFace.end() ) || ( dim == 3 && itCell != itCell.end() ) )
            {
               Index elementIdx;

               if ( dim == 2 )
               {
                  elementIdx = *itFace;
                  itFace++;
               }
               else
               {
                  elementIdx = *itCell;
                  itCell++;
               }

               // TODO: all these coord computations can be executed _once_ and then the coordinates can be incremented by h
               // TODO: blending

               // This object does the heavy lifting of computing all required coordinates and normals.
               ElementNeighborInfo neighborInfo;

               if ( dim == 2 )
               {
                  neighborInfo = ElementNeighborInfo( elementIdx, faceType, level, src.getBoundaryCondition(), pid, storage_ );
               }
               else
               {
                  neighborInfo = ElementNeighborInfo( elementIdx, cellType, level, src.getBoundaryCondition(), pid, storage_ );
               }

               // We only write to the DoFs in the current volume, let's prepare a temporary vector for that.
               Eigen::Matrix< real_t, Eigen::Dynamic, 1 > dstDofs;
               dstDofs.resize( numDstDofs, Eigen::NoChange_t::NoChange );
               dstDofs.setZero();

               /////////////////////////
               // Volume contribution //
               /////////////////////////

               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic > localMat;
               localMat.resize( numDstDofs, numSrcDofs );

               // Little difference here is that the dst is now a CG P1 function.
               // So we need to write the DoFs a little differently and set the basis manually.

               form_->integrateVolume( dim,
                                       neighborInfo.elementVertexCoords(),
                                       *src.getDGFunction()->basis(),
                                       dstBasis,
                                       srcPolyDegree,
                                       dstPolyDegree,
                                       localMat );

               // P0 has only one DoF
               const auto srcDoF = srcDofMemory[volumedofspace::indexing::index(
                   elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, srcMemLayout )];

               // Getting the vertex DoF indices for the current micro volume.
               std::vector< Index > vertexDoFIndices;
               if ( dim == 2 )
               {
                  auto vertexDoFIndicesArray = facedof::macroface::getMicroVerticesFromMicroFace( elementIdx, faceType );
                  vertexDoFIndices.insert( vertexDoFIndices.begin(), vertexDoFIndicesArray.begin(), vertexDoFIndicesArray.end() );
               }
               else
               {
                  auto vertexDoFIndicesArray = celldof::macrocell::getMicroVerticesFromMicroCell( elementIdx, cellType );
                  vertexDoFIndices.insert( vertexDoFIndices.begin(), vertexDoFIndicesArray.begin(), vertexDoFIndicesArray.end() );
               }
#if 0
               for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
               {
                  if ( dim == 2 )
                  {
                     srcDofs( srcDofIdx ) = srcDofMemory[vertexdof::macroface::index(
                         level, vertexDoFIndices[srcDofIdx].x(), vertexDoFIndices[srcDofIdx].y() )];
                  }
                  else
                  {
                     srcDofs( srcDofIdx ) = srcDofMemory[vertexdof::macrocell::index( level,
                                                                                      vertexDoFIndices[srcDofIdx].x(),
                                                                                      vertexDoFIndices[srcDofIdx].y(),
                                                                                      vertexDoFIndices[srcDofIdx].z() )];
                  }
               }
#endif
               if ( mat == nullptr )
               {
                  // Matrix-vector multiplication.
                  WALBERLA_ABORT( "Not implemented / tested." );
                  dstDofs += localMat * srcDoF;
               }
               else
               {
                  // Sparse assembly.
                  for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                  {
                     if ( dim == 2 )
                     {
                        const auto globalRowIdx = dstDofMemory[vertexdof::macroface::index(
                            level, vertexDoFIndices[dstDofIdx].x(), vertexDoFIndices[dstDofIdx].y() )];
                        const auto globalColIdx = srcDofMemory[volumedofspace::indexing::index(
                            elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, srcMemLayout )];
                        mat->addValue( globalRowIdx, globalColIdx, localMat( Eigen::Index( dstDofIdx ), 0 ) );
                     }
                     else
                     {
                        WALBERLA_ABORT( "Not implemented." );
                     }
                  }
               }

               if ( !form_->onlyVolumeIntegrals() )
               {
                  /////////////////////////////
                  // Interface contributions //
                  /////////////////////////////

                  // Loop over neighboring volumes.
                  for ( uint_t n = 0; n < uint_c( dim + 1 ); n++ )
                  {
                     /////////////////////
                     // Domain boundary //
                     /////////////////////

                     if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == DirichletBoundary )
                     {
                        ////////////////////////
                        // Dirichlet boundary //
                        ////////////////////////

                        localMat.setZero();
                        form_->integrateFacetDirichletBoundary( dim,
                                                                neighborInfo.elementVertexCoords(),
                                                                neighborInfo.interfaceVertexCoords( n ),
                                                                neighborInfo.oppositeVertexCoords( n ),
                                                                neighborInfo.outwardNormal( n ),
                                                                *src.getDGFunction()->basis(),
                                                                dstBasis,
                                                                srcPolyDegree,
                                                                dstPolyDegree,
                                                                localMat );

                        if ( mat == nullptr )
                        {
                           // Matrix-vector multiplication.
                           dstDofs += localMat * srcDoF;
                        }
                        else
                        {
                           // Sparse assembly.
                           for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                           {
                              if ( dim == 2 )
                              {
                                 const auto globalRowIdx = dstDofMemory[vertexdof::macroface::index(
                                     level, vertexDoFIndices[dstDofIdx].x(), vertexDoFIndices[dstDofIdx].y() )];
                                 const auto globalColIdx = srcDofMemory[volumedofspace::indexing::index(
                                     elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, srcMemLayout )];
                                 mat->addValue( globalRowIdx, globalColIdx, localMat( Eigen::Index( dstDofIdx ), 0 ) );
                              }
                              else
                              {
                                 WALBERLA_ABORT( "Not implemented." );
                              }
                           }
                        }
                     }
                     else if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == NeumannBoundary )
                     {
                        WALBERLA_ABORT( "Neumann boundary handling not implemented." );
                     }
                     else if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == FreeslipBoundary )
                     {
                        WALBERLA_ABORT( "Free-slip boundary handling not implemented." );
                     }

                     //////////////////
                     // Inner domain //
                     //////////////////

                     else
                     {
                        ///////////////////////////////////
                        // a) inner element contribution //
                        ///////////////////////////////////

                        localMat.setZero();
                        form_->integrateFacetInner( dim,
                                                    neighborInfo.elementVertexCoords(),
                                                    neighborInfo.interfaceVertexCoords( n ),
                                                    neighborInfo.oppositeVertexCoords( n ),
                                                    neighborInfo.outwardNormal( n ),
                                                    *src.getDGFunction()->basis(),
                                                    dstBasis,
                                                    srcPolyDegree,
                                                    dstPolyDegree,
                                                    localMat );

                        if ( mat == nullptr )
                        {
                           // Matrix-vector multiplication.
                           dstDofs += localMat * srcDoF;
                        }
                        else
                        {
                           // Sparse assembly.
                           for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                           {
                              if ( dim == 2 )
                              {
                                 const auto globalRowIdx = dstDofMemory[vertexdof::macroface::index(
                                     level, vertexDoFIndices[dstDofIdx].x(), vertexDoFIndices[dstDofIdx].y() )];
                                 const auto globalColIdx = srcDofMemory[volumedofspace::indexing::index(
                                     elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, srcMemLayout )];
                                 mat->addValue( globalRowIdx, globalColIdx, localMat( Eigen::Index( dstDofIdx ), 0 ) );
                              }
                              else
                              {
                                 WALBERLA_ABORT( "Not implemented." );
                              }
                           }
                        }

                        ////////////////////////////////////////
                        // b) coupling to neighboring element //
                        ////////////////////////////////////////

                        if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == Inner )
                        {
                           WALBERLA_ABORT( "P0-P1 interface integrals at macro-macro boundary not implemented." );

                           ////////////////////////////////////////////////
                           // i) micro-interface on macro-macro-boundary //
                           ////////////////////////////////////////////////
#if 0
                           // The neighboring micro-element coords have to be computed since they are now different as for an
                           // element on the same macro-volume.
                           std::vector< Eigen::Matrix< real_t, 3, 1 > > neighborElementVertexCoords;
                           Eigen::Matrix< real_t, 3, 1 >                neighborOppositeVertexCoords;

                           neighborInfo.macroBoundaryNeighborElementVertexCoords(
                               n, neighborElementVertexCoords, neighborOppositeVertexCoords );

                           localMat.setZero();
                           form_->integrateFacetCoupling( dim,
                                                          neighborInfo.elementVertexCoords(),
                                                          neighborElementVertexCoords,
                                                          neighborInfo.interfaceVertexCoords( n ),
                                                          neighborInfo.oppositeVertexCoords( n ),
                                                          neighborOppositeVertexCoords,
                                                          neighborInfo.outwardNormal( n ),
                                                          *src.basis(),
                                                          *dst.basis(),
                                                          srcPolyDegree,
                                                          dstPolyDegree,
                                                          localMat );

                           // Now we need the DoFs from the neighboring element.
                           Eigen::Matrix< real_t, Eigen::Dynamic, 1 > nSrcDofs;
                           nSrcDofs.resize( numSrcDofs, Eigen::NoChange_t::NoChange );
                           std::vector< uint_t > nSrcDoFArrIndices( numSrcDofs );

                           for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                           {
                              if ( dim == 2 )
                              {
                                 nSrcDoFArrIndices[srcDofIdx] =
                                     volumedofspace::indexing::indexNeighborInGhostLayer( neighborInfo.macroBoundaryID( n ),
                                                                                          elementIdx.x(),
                                                                                          elementIdx.y(),
                                                                                          faceType,
                                                                                          srcDofIdx,
                                                                                          numSrcDofs,
                                                                                          level,
                                                                                          srcMemLayout );
                              }
                              else
                              {
                                 nSrcDoFArrIndices[srcDofIdx] =
                                     volumedofspace::indexing::indexNeighborInGhostLayer( neighborInfo.macroBoundaryID( n ),
                                                                                          elementIdx.x(),
                                                                                          elementIdx.y(),
                                                                                          elementIdx.z(),
                                                                                          cellType,
                                                                                          srcDofIdx,
                                                                                          numSrcDofs,
                                                                                          level,
                                                                                          srcMemLayout );
                              }

                              nSrcDofs( srcDofIdx ) = glMemory[neighborInfo.macroBoundaryID( n )][nSrcDoFArrIndices[srcDofIdx]];
                           }

                           if ( mat == nullptr )
                           {
                              // Matrix-vector multiplication.
                              dstDofs += localMat * nSrcDofs;
                           }
                           else
                           {
                              // Sparse assembly.
                              // TODO: maybe there is a nicer way to do the gl stuff ...
                              for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                              {
                                 for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                                 {
                                    uint_t globalRowIdx;
                                    if ( dim == 2 )
                                    {
                                       globalRowIdx = dstDofMemory[volumedofspace::indexing::index( elementIdx.x(),
                                                                                                    elementIdx.y(),
                                                                                                    faceType,
                                                                                                    dstDofIdx,
                                                                                                    numDstDofs,
                                                                                                    level,
                                                                                                    dstMemLayout )];
                                    }
                                    else
                                    {
                                       globalRowIdx = dstDofMemory[volumedofspace::indexing::index( elementIdx.x(),
                                                                                                    elementIdx.y(),
                                                                                                    elementIdx.z(),
                                                                                                    cellType,
                                                                                                    dstDofIdx,
                                                                                                    numDstDofs,
                                                                                                    level,
                                                                                                    dstMemLayout )];
                                    }
                                    const auto globalColIdx =
                                        glMemory[neighborInfo.macroBoundaryID( n )][nSrcDoFArrIndices[srcDofIdx]];

                                    mat->addValue( globalRowIdx, globalColIdx, localMat( dstDofIdx, srcDofIdx ) );
                                 }
                              }
                           }
#endif
                        }
                        else
                        {
                           /////////////////////////////////////////
                           // ii) micro-interface inside of macro //
                           /////////////////////////////////////////

                           localMat.setZero();
                           form_->integrateFacetCoupling( dim,
                                                          neighborInfo.elementVertexCoords(),
                                                          neighborInfo.neighborElementVertexCoords( n ),
                                                          neighborInfo.interfaceVertexCoords( n ),
                                                          neighborInfo.oppositeVertexCoords( n ),
                                                          neighborInfo.neighborOppositeVertexCoords( n ),
                                                          neighborInfo.outwardNormal( n ),
                                                          *src.getDGFunction()->basis(),
                                                          dstBasis,
                                                          srcPolyDegree,
                                                          dstPolyDegree,
                                                          localMat );

                           // Now we need the DoFs from the neighboring element.
                           // P0 has only one DoF
                           const auto nSrcDof =
                               srcDofMemory[volumedofspace::indexing::index( neighborInfo.neighborElementIndices( n ).x(),
                                                                             neighborInfo.neighborElementIndices( n ).y(),
                                                                             faceType,
                                                                             0,
                                                                             1,
                                                                             level,
                                                                             srcMemLayout )];

                           std::vector< Index > nVertexDoFIndices;
                           if ( dim == 2 )
                           {
                              auto nVertexDoFIndicesArray = facedof::macroface::getMicroVerticesFromMicroFace(
                                  neighborInfo.neighborElementIndices( n ), faceType );
                              nVertexDoFIndices.insert(
                                  nVertexDoFIndices.begin(), nVertexDoFIndicesArray.begin(), nVertexDoFIndicesArray.end() );
                           }
                           else
                           {
                              auto nVertexDoFIndicesArray = celldof::macrocell::getMicroVerticesFromMicroCell(
                                  neighborInfo.neighborElementIndices( n ), cellType );
                              nVertexDoFIndices.insert(
                                  nVertexDoFIndices.begin(), nVertexDoFIndicesArray.begin(), nVertexDoFIndicesArray.end() );
                           }
#if 0
                           for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                           {
                              if ( dim == 2 )
                              {
                                 nSrcDofs( Eigen::Index( srcDofIdx ) ) = srcDofMemory[vertexdof::macroface::index(
                                     level, nVertexDoFIndices[srcDofIdx].x(), nVertexDoFIndices[srcDofIdx].y() )];
                              }
                              else
                              {
                                 nSrcDofs( Eigen::Index( srcDofIdx ) ) =
                                     srcDofMemory[vertexdof::macrocell::index( level,
                                                                               nVertexDoFIndices[srcDofIdx].x(),
                                                                               nVertexDoFIndices[srcDofIdx].y(),
                                                                               nVertexDoFIndices[srcDofIdx].z() )];
                              }
                           }
#endif
                           if ( mat == nullptr )
                           {
                              // Matrix-vector multiplication.
                              dstDofs += localMat * nSrcDof;
                           }
                           else
                           {
                              // TODO: improve this monster
                              std::map< facedof::FaceType, uint_t > invFaceTypeMap;
                              std::map< celldof::CellType, uint_t > invCellTypeMap;

                              for ( uint_t i = 0; i < 2; i++ )
                              {
                                 invFaceTypeMap[facedof::allFaceTypes[i]] = i;
                              }
                              for ( uint_t i = 0; i < 6; i++ )
                              {
                                 invCellTypeMap[celldof::allCellTypes[i]] = i;
                              }

                              uint_t neighborMicroVolType;
                              if ( dim == 2 )
                              {
                                 neighborMicroVolType = invFaceTypeMap[neighborInfo.neighborFaceType( n )];
                              }
                              else
                              {
                                 neighborMicroVolType = invCellTypeMap[neighborInfo.neighborCellType( n )];
                              }

                              // Sparse assembly.
                              for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                              {
                                 if ( dim == 2 )
                                 {
                                    const auto globalRowIdx = dstDofMemory[vertexdof::macroface::index(
                                        level, vertexDoFIndices[dstDofIdx].x(), vertexDoFIndices[dstDofIdx].y() )];
                                    const auto globalColIdx = srcDofMemory[volumedofspace::indexing::index(
                                        neighborInfo.neighborElementIndices( n ).x(),
                                        neighborInfo.neighborElementIndices( n ).y(),
                                        faceType,
                                        0,
                                        1,
                                        level,
                                        srcMemLayout )];
                                    mat->addValue( globalRowIdx, globalColIdx, localMat( Eigen::Index( dstDofIdx ), 0 ) );
                                 }
                                 else
                                 {
                                    WALBERLA_ABORT( "Not implemented." );
                                 }
                              }
                           }
                        }
                     }
                  } // End loop over neighboring volumes.
               }    // End if( !onlyVolumeIntegrals() )

               if ( mat == nullptr )
               {
                  // Write DoFs.
                  for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                  {
                     if ( dim == 2 )
                     {
                        dstDofMemory[vertexdof::macroface::index(
                            level, vertexDoFIndices[dstDofIdx].x(), vertexDoFIndices[dstDofIdx].y() )] = dstDofs( dstDofIdx );
                     }
                     else
                     {
                        dstDofMemory[vertexdof::macrocell::index( level,
                                                                  vertexDoFIndices[dstDofIdx].x(),
                                                                  vertexDoFIndices[dstDofIdx].y(),
                                                                  vertexDoFIndices[dstDofIdx].z() )] = dstDofs( dstDofIdx );
                     }
                  }
               }
            }
         }
      }

      WALBERLA_UNUSED( flag );
   }

   /// \brief This is similar to the implementation in the dg::DGOperator class.
   template < typename VType >
   inline void assembleAndOrApplyOld( const P0Function< VType >&                  src,
                                      const P1Function< VType >&                  dst,
                                      size_t                                      level,
                                      DoFType                                     flag,
                                      const std::shared_ptr< SparseMatrixProxy >& mat,
                                      UpdateType                                  updateType = Replace ) const
   {
      using indexing::Index;

      WALBERLA_CHECK( updateType == Replace );

      auto srcDGF = src.getDGFunction();

      communication::syncFunctionBetweenPrimitives( dst, level );

      if ( this->getStorage()->hasGlobalCells() )
      {
         WALBERLA_ABORT( "P0 to P1 apply not implemented in 3D." );
      }
      else
      {
         const int dim = 2;

         for ( const auto& faceIt : this->getStorage()->getFaces() )
         {
            const auto  faceId = faceIt.first;
            const auto& face   = *faceIt.second;

            const auto srcPolyDegree = 0;
            const auto dstPolyDegree = 1;

            const auto numSrcDofs = 1;
            const auto numDstDofs = 3;

            const auto srcDofMemory = srcDGF->volumeDoFFunction()->dofMemory( faceId, level );
            auto       dstDofMemory = face.getData( dst.getFaceDataID() )->getPointer( level );

            const auto srcMemLayout = srcDGF->volumeDoFFunction()->memoryLayout();

            for ( auto faceType : facedof::allFaceTypes )
            {
               for ( auto elementIdx : facedof::macroface::Iterator( level, faceType ) )
               {
                  // TODO: all these coord computations can be executed _once_ and then the coordinates can be incremented by h
                  // TODO: blending

                  // This object does the heavy lifting of computing all required coordinates and normals.
                  volumedofspace::indexing::ElementNeighborInfo neighborInfo(
                      elementIdx, faceType, level, src.getBoundaryCondition(), faceId, this->getStorage() );

                  // We only write to the DoFs in the current volume, let's prepare a temporary vector for that.
                  Eigen::Matrix< real_t, Eigen::Dynamic, 1 > dstDofs;
                  dstDofs.resize( numDstDofs, Eigen::NoChange_t::NoChange );
                  dstDofs.setZero();

                  /////////////////////////
                  // Volume contribution //
                  /////////////////////////

                  std::array< Point3D, 3 > coords;
                  for ( uint_t i = 0; i < neighborInfo.elementVertexCoords().size(); i++ )
                  {
                     coords[i][0] = neighborInfo.elementVertexCoords().at( i )( 0 );
                     coords[i][1] = neighborInfo.elementVertexCoords().at( i )( 1 );
                     coords[i][2] = neighborInfo.elementVertexCoords().at( i )( 2 );
                  }

                  Matrixr< 3, 1 > elMat;
                  form_->integrateAll( coords, elMat );

                  // P0 has only one DoF
                  const auto srcDoF = srcDofMemory[volumedofspace::indexing::index(
                      elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, srcMemLayout )];

                  // Micro-vertex indices
                  auto vertexDoFIndices = facedof::macroface::getMicroVerticesFromMicroFace( elementIdx, faceType );

                  if ( mat == nullptr )
                  {
                     // Matrix-vector multiplication.
                     // dstDofs += localMat * srcDofs;
                     WALBERLA_ABORT( "Not implemented." );
                  }
                  else
                  {
                     // Sparse assembly.
                     for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                     {
                        const auto globalRowIdx = dstDofMemory[vertexdof::macroface::index(
                            level, vertexDoFIndices.at( dstDofIdx ).x(), vertexDoFIndices.at( dstDofIdx ).y() )];
                        const auto globalColIdx = srcDofMemory[volumedofspace::indexing::index(
                            elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, srcMemLayout )];
                        mat->addValue( globalRowIdx, globalColIdx, elMat( dstDofIdx, 0 ) );
                     }
                  }

                  if ( mat == nullptr )
                  {
                     // Write DoFs.
                     for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                     {
                        WALBERLA_ABORT( "Not implemented." );
                     }
                  }
               }
            }
         }
      }

      WALBERLA_UNUSED( flag );
   }

   std::shared_ptr< Form > form_;
};

typedef P0ToP1Operator< dg::p0_to_p1_divt_0_affine_q0 > P0ToP1ConstantDivTxOperator;
typedef P0ToP1Operator< dg::p0_to_p1_divt_1_affine_q0 > P0ToP1ConstantDivTyOperator;
typedef P0ToP1Operator< dg::p0_to_p1_divt_2_affine_q0 > P0ToP1ConstantDivTzOperator;

} // namespace hyteg