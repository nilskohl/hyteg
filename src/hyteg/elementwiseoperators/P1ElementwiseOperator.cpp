/*
 * Copyright (c) 2017-2019 Marcus Mohr.
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

#include "P1ElementwiseOperator.hpp"

namespace hyteg {

template < class P1Form >
P1ElementwiseOperator< P1Form >::P1ElementwiseOperator( const std::shared_ptr< PrimitiveStorage >& storage,
                                                        size_t                                     minLevel,
                                                        size_t                                     maxLevel )
: P1ElementwiseOperator< P1Form >( storage, minLevel, maxLevel, P1Form(), true )
{}

template < class P1Form >
P1ElementwiseOperator< P1Form >::P1ElementwiseOperator( const std::shared_ptr< PrimitiveStorage >& storage,
                                                        size_t                                     minLevel,
                                                        size_t                                     maxLevel,
                                                        const P1Form&                              form )
: P1ElementwiseOperator< P1Form >( storage, minLevel, maxLevel, form, true )
{}

template < class P1Form >
P1ElementwiseOperator< P1Form >::P1ElementwiseOperator( const std::shared_ptr< PrimitiveStorage >& storage,
                                                        size_t                                     minLevel,
                                                        size_t                                     maxLevel,
                                                        const P1Form&                              form,
                                                        bool                                       needsInverseDiagEntries )
: Operator( storage, minLevel, maxLevel )
, form_( form )
{
   if ( needsInverseDiagEntries )
   {
      computeInverseDiagonalOperatorValues();
   }
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::apply( const P1Function< real_t >& src,
                                             const P1Function< real_t >& dst,
                                             size_t                      level,
                                             DoFType                     flag,
                                             UpdateType                  updateType ) const
{
   WALBERLA_ASSERT_NOT_IDENTICAL( std::addressof( src ), std::addressof( dst ) );

   this->startTiming( "apply" );

   // Make sure that halos are up-to-date (can we improve communication here?)
   communication::syncFunctionBetweenPrimitives( src, level );

   if ( updateType == Replace )
   {
      // We need to zero the destination array (including halos).
      // However, we must not zero out anything that is not flagged with the specified BCs.
      // Therefore we first zero out everything that flagged, and then, later,
      // the halos of the highest dim primitives.

      dst.interpolate( real_c(0), level, flag );
   }

   // For 3D we work on cells and for 2D on faces
   if ( storage_->hasGlobalCells() )
   {
      // we only perform computations on cell primitives
      for ( auto& macroIter : storage_->getCells() )
      {
         Cell& cell = *macroIter.second;

         // get hold of the actual numerical data in the two functions
         PrimitiveDataID< FunctionMemory< real_t >, Cell > dstVertexDoFIdx = dst.getCellDataID();
         PrimitiveDataID< FunctionMemory< real_t >, Cell > srcVertexDoFIdx = src.getCellDataID();

         real_t* srcVertexData = cell.getData( srcVertexDoFIdx )->getPointer( level );
         real_t* dstVertexData = cell.getData( dstVertexDoFIdx )->getPointer( level );

         // Zero out dst halos only
         //
         // This is also necessary when using update type == Add.
         // During additive comm we then skip zeroing the data on the lower-dim primitives.

         for ( const auto& idx : vertexdof::macrocell::Iterator( level ) )
         {
            if ( !vertexdof::macrocell::isOnCellFace( idx, level ).empty() )
            {
               auto arrayIdx           = vertexdof::macrocell::index( level, idx.x(), idx.y(), idx.z() );
               dstVertexData[arrayIdx] = real_c( 0 );
            }
         }

         // loop over micro-cells
         for ( const auto& cType : celldof::allCellTypes )
         {
            for ( const auto& micro : celldof::macrocell::Iterator( level, cType, 0 ) )
            {
               localMatrixVectorMultiply3D( cell, level, micro, cType, srcVertexData, dstVertexData );
            }
         }
      }

      // Push result to lower-dimensional primitives
      //
      // Note: We could avoid communication here by implementing the apply() also for the respective
      //       lower dimensional primitives!
      dst.communicateAdditively< Cell, Face >( level, DoFType::All ^ flag, *storage_, updateType == Replace );
      dst.communicateAdditively< Cell, Edge >( level, DoFType::All ^ flag, *storage_, updateType == Replace );
      dst.communicateAdditively< Cell, Vertex >( level, DoFType::All ^ flag, *storage_, updateType == Replace );
   }

   else
   {
      // we only perform computations on face primitives
      for ( auto& it : storage_->getFaces() )
      {
         Face& face = *it.second;

         Point3D x0( face.coords[0] );
         Point3D x1( face.coords[1] );
         Point3D x2( face.coords[2] );

         uint_t                   rowsize       = levelinfo::num_microvertices_per_edge( level );
         uint_t                   inner_rowsize = rowsize;
         uint_t                   xIdx, yIdx;
         Point3D                  v0, v1, v2;
         indexing::Index          nodeIdx;
         indexing::IndexIncrement offset;

         // get hold of the actual numerical data in the two functions
         PrimitiveDataID< FunctionMemory< real_t >, Face > dstVertexDoFIdx = dst.getFaceDataID();
         PrimitiveDataID< FunctionMemory< real_t >, Face > srcVertexDoFIdx = src.getFaceDataID();

         real_t* srcVertexData = face.getData( srcVertexDoFIdx )->getPointer( level );
         real_t* dstVertexData = face.getData( dstVertexDoFIdx )->getPointer( level );

         // Zero out dst halos only
         //
         // This is also necessary when using update type == Add.
         // During additive comm we then skip zeroing the data on the lower-dim primitives.

         for ( const auto& idx : vertexdof::macroface::Iterator( level ) )
         {
            if ( vertexdof::macroface::isVertexOnBoundary( level, idx ) )
            {
               auto arrayIdx           = vertexdof::macroface::index( level, idx.x(), idx.y() );
               dstVertexData[arrayIdx] = real_c( 0 );
            }
         }

         // the explicit uint_c cast prevents a segfault in intel compiler 2018.4
         // now loop over micro-faces of macro-face
         for ( yIdx = uint_c( 0 ); yIdx < rowsize - 2; ++yIdx )
         {
            // loop over vertices in row with two associated triangles
            for ( xIdx = uint_c( 1 ); xIdx < inner_rowsize - 1; ++xIdx )
            {
               // we associate two elements with current micro-vertex
               localMatrixVectorMultiply2D(
                   face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementN, srcVertexData, dstVertexData );
               localMatrixVectorMultiply2D(
                   face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementNW, srcVertexData, dstVertexData );
            }
            --inner_rowsize;

            // final micro-vertex in row has only one associated micro-face
            localMatrixVectorMultiply2D(
                face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementNW, srcVertexData, dstVertexData );
         }

         // top north-west micro-element not treated, yet
         localMatrixVectorMultiply2D( face, level, 1, yIdx, P1Elements::P1Elements2D::elementNW, srcVertexData, dstVertexData );
      }

      // Push result to lower-dimensional primitives
      //
      // Note: We could avoid communication here by implementing the apply() also for the respective
      //       lower dimensional primitives!
      dst.communicateAdditively< Face, Edge >( level, DoFType::All ^ flag, *storage_, updateType == Replace );
      dst.communicateAdditively< Face, Vertex >( level, DoFType::All ^ flag, *storage_, updateType == Replace );
   }

   this->stopTiming( "apply" );
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::smooth_jac( const P1Function< real_t >& dst,
                                                  const P1Function< real_t >& rhs,
                                                  const P1Function< real_t >& src,
                                                  real_t                      omega,
                                                  size_t                      level,
                                                  DoFType                     flag ) const
{
   this->startTiming( "smooth_jac" );

   // compute the current residual
   this->apply( src, dst, level, flag );
   dst.assign( {real_c( 1 ), real_c( -1 )}, {rhs, dst}, level, flag );

   // perform Jacobi update step
   dst.multElementwise( {*getInverseDiagonalValues(), dst}, level, flag );
   dst.assign( {1.0, omega}, {src, dst}, level, flag );

   this->stopTiming( "smooth_jac" );
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::localMatrixVectorMultiply2D( const Face&                                face,
                                                                   const uint_t                               level,
                                                                   const uint_t                               xIdx,
                                                                   const uint_t                               yIdx,
                                                                   const P1Elements::P1Elements2D::P1Element& element,
                                                                   const real_t* const                        srcVertexData,
                                                                   real_t* const dstVertexData ) const
{
   WALBERLA_ASSERT_UNEQUAL( srcVertexData, dstVertexData );

   Matrix3r                 elMat;
   Point3D                  elVecOld, elVecNew;
   indexing::Index          nodeIdx;
   indexing::IndexIncrement offset;
   Point3D                  v0, v1, v2;
   std::array< uint_t, 3 >  dofDataIdx;
   P1Form                   form( form_ );

   // determine vertices of micro-element
   nodeIdx = indexing::Index( xIdx, yIdx, 0 );
   v0      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[1] );
   v1      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[2] );
   v2      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );

   // assemble local element matrix
   form.setGeometryMap( face.getGeometryMap() );
   form.integrateAll( {v0, v1, v2}, elMat );

   // assemble local element vector
   dofDataIdx[0] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[0] );
   dofDataIdx[1] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[1] );
   dofDataIdx[2] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[2] );

   elVecOld[0] = srcVertexData[dofDataIdx[0]];
   elVecOld[1] = srcVertexData[dofDataIdx[1]];
   elVecOld[2] = srcVertexData[dofDataIdx[2]];

   // apply matrix (operator locally)
   elVecNew = elMat.mul( elVecOld );

   // redistribute result from "local" to "global vector"
   dstVertexData[dofDataIdx[0]] += elVecNew[0];
   dstVertexData[dofDataIdx[1]] += elVecNew[1];
   dstVertexData[dofDataIdx[2]] += elVecNew[2];
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::localMatrixVectorMultiply3D( const Cell&             cell,
                                                                   const uint_t            level,
                                                                   const indexing::Index&  microCell,
                                                                   const celldof::CellType cType,
                                                                   const real_t* const     srcVertexData,
                                                                   real_t* const           dstVertexData ) const
{
   // determine coordinates of vertices of micro-element
   std::array< indexing::Index, 4 > verts = celldof::macrocell::getMicroVerticesFromMicroCell( microCell, cType );
   std::array< Point3D, 4 >         coords;
   for ( uint_t k = 0; k < 4; ++k )
   {
      coords[k] = vertexdof::macrocell::coordinateFromIndex( level, cell, verts[k] );
   }

   // assemble local element matrix
   Matrix4r elMat;
   P1Form   form( form_ );
   form.setGeometryMap( cell.getGeometryMap() );
   form.integrateAll( coords, elMat );

   // obtain data indices of dofs associated with micro-cell
   std::array< uint_t, 4 > vertexDoFIndices;
   vertexdof::getVertexDoFDataIndicesFromMicroCell( microCell, cType, level, vertexDoFIndices );

   // assemble local element vector
   Point4D elVecOld, elVecNew;
   for ( uint_t k = 0; k < 4; ++k )
   {
      elVecOld[k] = srcVertexData[vertexDoFIndices[k]];
   }

   // apply matrix (operator locally)
   elVecNew = elMat.mul( elVecOld );

   // redistribute result from "local" to "global vector"
   for ( uint_t k = 0; k < 4; ++k )
   {
      dstVertexData[vertexDoFIndices[k]] += elVecNew[k];
   }
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::computeDiagonalOperatorValues( bool invert )
{
   std::shared_ptr< P1Function< real_t > > targetFunction;
   if ( invert )
   {
      if ( !inverseDiagonalValues_ )
      {
         inverseDiagonalValues_ =
             std::make_shared< P1Function< real_t > >( "inverse diagonal entries", storage_, minLevel_, maxLevel_ );
      }
      targetFunction = inverseDiagonalValues_;
   }
   else
   {
      if ( !diagonalValues_ )
      {
         diagonalValues_ = std::make_shared< P1Function< real_t > >( "diagonal entries", storage_, minLevel_, maxLevel_ );
      }
      targetFunction = diagonalValues_;
   }

   for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
   {
      // Make sure that halos are up-to-date (can we improve communication here?)
      communication::syncFunctionBetweenPrimitives( *targetFunction, level );

      // Zero destination before performing additive computation
      targetFunction->setToZero( level );

      // For 3D we work on cells and for 2D on faces
      if ( storage_->hasGlobalCells() )
      {
         // we only perform computations on cell primitives
         for ( auto& macroIter : storage_->getCells() )
         {
            Cell& cell = *macroIter.second;

            // get hold of the actual numerical data
            PrimitiveDataID< FunctionMemory< real_t >, Cell > diagVertexDoFIdx = targetFunction->getCellDataID();
            real_t* diagVertexData = cell.getData( diagVertexDoFIdx )->getPointer( level );

            // loop over micro-cells
            for ( const auto& cType : celldof::allCellTypes )
            {
               for ( const auto& micro : celldof::macrocell::Iterator( level, cType, 0 ) )
               {
                  computeLocalDiagonalContributions3D( cell, level, micro, cType, diagVertexData );
               }
            }
         }

         // Push result to lower-dimensional primitives
         targetFunction->communicateAdditively< Cell, Face >( level );
         targetFunction->communicateAdditively< Cell, Edge >( level );
         targetFunction->communicateAdditively< Cell, Vertex >( level );
      }

      else
      {
         // we only perform computations on face primitives
         for ( auto& it : storage_->getFaces() )
         {
            Face& face = *it.second;

            Point3D x0( face.coords[0] );
            Point3D x1( face.coords[1] );
            Point3D x2( face.coords[2] );

            uint_t                   rowsize       = levelinfo::num_microvertices_per_edge( level );
            uint_t                   inner_rowsize = rowsize;
            uint_t                   xIdx, yIdx;
            Point3D                  v0, v1, v2;
            indexing::Index          nodeIdx;
            indexing::IndexIncrement offset;

            // get hold of the actual numerical data in the two functions
            PrimitiveDataID< FunctionMemory< real_t >, Face > vertexDoFIdx = targetFunction->getFaceDataID();
            real_t*                                           vertexData   = face.getData( vertexDoFIdx )->getPointer( level );

            // now loop over micro-faces of macro-face
            for ( yIdx = 0; yIdx < rowsize - 2; ++yIdx )
            {
               // loop over vertices in row with two associated triangles
               for ( xIdx = 1; xIdx < inner_rowsize - 1; ++xIdx )
               {
                  // we associate two elements with current micro-vertex
                  computeLocalDiagonalContributions2D( face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementN, vertexData );
                  computeLocalDiagonalContributions2D( face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementNW, vertexData );
               }
               --inner_rowsize;

               // final micro-vertex in row has only one associated micro-face
               computeLocalDiagonalContributions2D( face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementNW, vertexData );
            }

            // top north-west micro-element not treated, yet
            computeLocalDiagonalContributions2D( face, level, 1, yIdx, P1Elements::P1Elements2D::elementNW, vertexData );
         }

         // Push result to lower-dimensional primitives
         targetFunction->communicateAdditively< Face, Edge >( level );
         targetFunction->communicateAdditively< Face, Vertex >( level );

         // Retrieve assembled data values
         targetFunction->communicate< Vertex, Edge >( level );
         targetFunction->communicate< Edge, Face >( level );
      }

      // Invert values if desired (note: using false below means we only invert in the interior of the primitives,
      // the values in the halos are untouched; should be okay for using diagonalValue_ in smoothers)
      if ( invert )
      {
         targetFunction->invertElementwise( level, All, false );
      }
   }
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::computeLocalDiagonalContributions2D( const Face&                                face,
                                                                           const uint_t                               level,
                                                                           const uint_t                               xIdx,
                                                                           const uint_t                               yIdx,
                                                                           const P1Elements::P1Elements2D::P1Element& element,
                                                                           real_t* const dstVertexData )
{
   Matrix3r                 elMat;
   indexing::Index          nodeIdx;
   indexing::IndexIncrement offset;
   Point3D                  v0, v1, v2;
   std::array< uint_t, 6 >  dofDataIdx;
   P1Form                   form( form_ );

   // determine vertices of micro-element
   nodeIdx = indexing::Index( xIdx, yIdx, 0 );
   v0      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[1] );
   v1      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[2] );
   v2      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );

   // assemble local element matrix
   form.setGeometryMap( face.getGeometryMap() );
   form.integrateAll( {v0, v1, v2}, elMat );

   // get global indices for local dofs
   dofDataIdx[0] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[0] );
   dofDataIdx[1] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[1] );
   dofDataIdx[2] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[2] );

   // add local contributions to diagonal entries
   dstVertexData[dofDataIdx[0]] += elMat( 0, 0 );
   dstVertexData[dofDataIdx[1]] += elMat( 1, 1 );
   dstVertexData[dofDataIdx[2]] += elMat( 2, 2 );
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::computeLocalDiagonalContributions3D( const Cell&             cell,
                                                                           const uint_t            level,
                                                                           const indexing::Index&  microCell,
                                                                           const celldof::CellType cType,
                                                                           real_t* const           vertexData )
{
   // determine coordinates of vertices of micro-element
   std::array< indexing::Index, 4 > verts = celldof::macrocell::getMicroVerticesFromMicroCell( microCell, cType );
   std::array< Point3D, 4 >         coords;
   for ( uint_t k = 0; k < 4; ++k )
   {
      coords[k] = vertexdof::macrocell::coordinateFromIndex( level, cell, verts[k] );
   }

   // assemble local element matrix
   Matrix4r elMat;
   P1Form   form( form_ );
   form.setGeometryMap( cell.getGeometryMap() );
   form.integrateAll( coords, elMat );

   // obtain data indices of dofs associated with micro-cell
   std::array< uint_t, 4 > vertexDoFIndices;
   vertexdof::getVertexDoFDataIndicesFromMicroCell( microCell, cType, level, vertexDoFIndices );

   // add contributions for central stencil weights
   for ( uint_t k = 0; k < 4; ++k )
   {
      vertexData[vertexDoFIndices[k]] += elMat( k, k );
   }
}

#ifdef HYTEG_BUILD_WITH_PETSC

// Assemble operator as sparse matrix
template < class P1Form >
void P1ElementwiseOperator< P1Form >::assembleLocalMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                                                           const P1Function< PetscInt >&               src,
                                                           const P1Function< PetscInt >&               dst,
                                                           uint_t                                      level,
                                                           DoFType                                     flag ) const
{
   // We currently ignore the flag provided!
   WALBERLA_UNUSED( flag );

   // For 3D we work on cells and for 2D on faces
   if ( storage_->hasGlobalCells() )
   {
      // we only perform computations on cell primitives
      for ( auto& macroIter : storage_->getCells() )
      {
         Cell& cell = *macroIter.second;

         // get hold of the actual numerical data in the two indexing functions
         PrimitiveDataID< FunctionMemory< PetscInt >, Cell > dstVertexDoFIdx = dst.getCellDataID();
         PrimitiveDataID< FunctionMemory< PetscInt >, Cell > srcVertexDoFIdx = src.getCellDataID();

         PetscInt* srcIdx = cell.getData( srcVertexDoFIdx )->getPointer( level );
         PetscInt* dstIdx = cell.getData( dstVertexDoFIdx )->getPointer( level );

         // loop over micro-cells
         for ( const auto& cType : celldof::allCellTypes )
         {
            for ( const auto& micro : celldof::macrocell::Iterator( level, cType, 0 ) )
            {
               localMatrixAssembly3D( mat, cell, level, micro, cType, srcIdx, dstIdx );
            }
         }
      }
   }

   else
   {
      // we only perform computations on face primitives
      for ( auto& it : storage_->getFaces() )
      {
         Face& face = *it.second;

         Point3D x0( face.coords[0] );
         Point3D x1( face.coords[1] );
         Point3D x2( face.coords[2] );

         uint_t                   rowsize       = levelinfo::num_microvertices_per_edge( level );
         uint_t                   inner_rowsize = rowsize;
         uint_t                   xIdx, yIdx;
         Point3D                  v0, v1, v2;
         indexing::Index          nodeIdx;
         indexing::IndexIncrement offset;

         // get hold of the actual numerical data in the two functions
         PrimitiveDataID< FunctionMemory< PetscInt >, Face > dstVertexDoFIdx = dst.getFaceDataID();
         PrimitiveDataID< FunctionMemory< PetscInt >, Face > srcVertexDoFIdx = src.getFaceDataID();

         PetscInt* srcIndices = face.getData( srcVertexDoFIdx )->getPointer( level );
         PetscInt* dstIndices = face.getData( dstVertexDoFIdx )->getPointer( level );

         // the explicit uint_c cast prevents a segfault in intel compiler 2018.4
         // now loop over micro-faces of macro-face
         for ( yIdx = uint_c( 0 ); yIdx < rowsize - 2; ++yIdx )
         {
            // loop over vertices in row with two associated triangles
            for ( xIdx = uint_c( 1 ); xIdx < inner_rowsize - 1; ++xIdx )
            {
               // we associate two elements with current micro-vertex
               localMatrixAssembly2D( mat, face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementN, srcIndices, dstIndices );
               localMatrixAssembly2D( mat, face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementNW, srcIndices, dstIndices );
            }
            --inner_rowsize;

            // final micro-vertex in row has only one associated micro-face
            localMatrixAssembly2D( mat, face, level, xIdx, yIdx, P1Elements::P1Elements2D::elementNW, srcIndices, dstIndices );
         }

         // top north-west micro-element not treated, yet
         localMatrixAssembly2D( mat, face, level, 1, yIdx, P1Elements::P1Elements2D::elementNW, srcIndices, dstIndices );
      }
   }
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::localMatrixAssembly2D( const std::shared_ptr< SparseMatrixProxy >& mat,
                                                             const Face&                                 face,
                                                             const uint_t                                level,
                                                             const uint_t                                xIdx,
                                                             const uint_t                                yIdx,
                                                             const P1Elements::P1Elements2D::P1Element&  element,
                                                             const PetscInt* const                       srcIdx,
                                                             const PetscInt* const                       dstIdx ) const
{
   Matrix3r                 elMat;
   indexing::Index          nodeIdx;
   indexing::IndexIncrement offset;
   Point3D                  v0, v1, v2;
   std::array< uint_t, 3 >  dofDataIdx;
   P1Form                   form( form_ );

   // determine vertices of micro-element
   nodeIdx = indexing::Index( xIdx, yIdx, 0 );
   v0      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[1] );
   v1      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[2] );
   v2      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );

   // assemble local element matrix
   form.setGeometryMap( face.getGeometryMap() );
   form.integrateAll( {v0, v1, v2}, elMat );

   // determine global indices of our local DoFs
   dofDataIdx[0] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[0] );
   dofDataIdx[1] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[1] );
   dofDataIdx[2] = vertexdof::macroface::indexFromVertex( level, xIdx, yIdx, element[2] );

   std::vector< uint_t > rowIdx( 3 );
   rowIdx[0] = uint_c( dstIdx[dofDataIdx[0]] );
   rowIdx[1] = uint_c( dstIdx[dofDataIdx[1]] );
   rowIdx[2] = uint_c( dstIdx[dofDataIdx[2]] );

   std::vector< uint_t > colIdx( 3 );
   colIdx[0] = uint_c( srcIdx[dofDataIdx[0]] );
   colIdx[1] = uint_c( srcIdx[dofDataIdx[1]] );
   colIdx[2] = uint_c( srcIdx[dofDataIdx[2]] );

   const uint_t elMatSize = 9;
   std::vector< real_t > blockMatData( elMatSize );
   for ( uint_t i = 0; i < elMatSize; i++ )
   {
      blockMatData[i] = elMat.data()[i];
   }

   // add local matrix into global matrix
   mat->addValues( rowIdx, colIdx, blockMatData );
}

template < class P1Form >
void P1ElementwiseOperator< P1Form >::localMatrixAssembly3D( const std::shared_ptr< SparseMatrixProxy >& mat,
                                                             const Cell&                                 cell,
                                                             const uint_t                                level,
                                                             const indexing::Index&                      microCell,
                                                             const celldof::CellType                     cType,
                                                             const PetscInt* const                       srcIdx,
                                                             const PetscInt* const                       dstIdx ) const
{
   // determine coordinates of vertices of micro-element
   std::array< indexing::Index, 4 > verts = celldof::macrocell::getMicroVerticesFromMicroCell( microCell, cType );
   std::array< Point3D, 4 >         coords;
   for ( uint_t k = 0; k < 4; ++k )
   {
      coords[k] = vertexdof::macrocell::coordinateFromIndex( level, cell, verts[k] );
   }

   // assemble local element matrix
   Matrix4r elMat;
   P1Form   form( form_ );
   form.setGeometryMap( cell.getGeometryMap() );
   form.integrateAll( coords, elMat );

   // obtain data indices of dofs associated with micro-cell
   std::array< uint_t, 4 > vertexDoFDataIdx;
   vertexdof::getVertexDoFDataIndicesFromMicroCell( microCell, cType, level, vertexDoFDataIdx );

   std::vector< uint_t > rowIdx( 4 );
   std::vector< uint_t > colIdx( 4 );
   for ( uint_t k = 0; k < 4; ++k )
   {
      rowIdx[k] = uint_c( dstIdx[vertexDoFDataIdx[k]] );
      colIdx[k] = uint_c( srcIdx[vertexDoFDataIdx[k]] );
   }

   const uint_t elMatSize = 16;
   std::vector< real_t > blockMatData( elMatSize );
   for ( uint_t i = 0; i < elMatSize; i++ )
   {
      blockMatData[i] = elMat.data()[i];
   }

   // add local matrix into global matrix
   mat->addValues( rowIdx, colIdx, blockMatData );
}

#endif

// P1ElementwiseLaplaceOperator
template class P1ElementwiseOperator<
    P1FenicsForm< p1_diffusion_cell_integral_0_otherwise, p1_tet_diffusion_cell_integral_0_otherwise > >;

// P1ElementwisePolarLaplaceOperator
template class P1ElementwiseOperator< P1FenicsForm< p1_polar_laplacian_cell_integral_0_otherwise > >;

// P1ElementwiseMassOperator
template class P1ElementwiseOperator< P1FenicsForm< p1_mass_cell_integral_0_otherwise, p1_tet_mass_cell_integral_0_otherwise > >;

// P1ElementwisePSPGOperator
template class P1ElementwiseOperator< P1FenicsForm< p1_pspg_cell_integral_0_otherwise, p1_tet_pspg_tet_cell_integral_0_otherwise > >;

// P1ElementwiseBlendingMassOperator
template class P1ElementwiseOperator< P1Form_mass >;

// P1ElementwiseBlendingMassOperator3D
template class P1ElementwiseOperator< P1Form_mass3D >;

// P1ElementwiseBlendingLaplaceOperator
template class P1ElementwiseOperator< P1Form_laplace >;

} // namespace hyteg
