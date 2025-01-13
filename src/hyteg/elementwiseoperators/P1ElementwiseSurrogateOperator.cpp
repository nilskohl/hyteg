/*
 * Copyright (c) 2017-2025 Marcus Mohr, Nils Kohl, Benjamin Mann.
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

#include "P1ElementwiseSurrogateOperator.hpp"

#include "hyteg/forms/P1RowSumForm.hpp"
#include "hyteg/forms/form_hyteg_generated/p1/p1_diffusion_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p1/p1_div_k_grad_affine_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p1/p1_div_k_grad_blending_q3.hpp"
#include "hyteg/forms/form_hyteg_generated/p1/p1_epsilon_all_forms.hpp"
#include "hyteg/forms/form_hyteg_manual/SphericalElementFormMass.hpp"

namespace hyteg {

template < class P1Form >
P1ElementwiseSurrogateOperator< P1Form >::P1ElementwiseSurrogateOperator( const std::shared_ptr< PrimitiveStorage >& storage,
                                                                          size_t                                     minLevel,
                                                                          size_t                                     maxLevel )
: P1ElementwiseSurrogateOperator< P1Form >( storage, minLevel, maxLevel, P1Form() )
{}

template < class P1Form >
P1ElementwiseSurrogateOperator< P1Form >::P1ElementwiseSurrogateOperator( const std::shared_ptr< PrimitiveStorage >& storage,
                                                                          size_t                                     minLevel,
                                                                          size_t                                     maxLevel,
                                                                          const P1Form&                              form )
: Operator( storage, minLevel, maxLevel )
, form_( form )
, is_initialized_( false )
, lsq_( maxLevel_ + 1 )
, downsampling_( maxLevel_ + 1 )
, poly_degree_( maxLevel_ + 1 )
{
   // // memory of local stiffness matrices for level 1-3
   // auto maxLvl = std::min( maxLevel_, 3 );
   // auto dataHandling_stiffness_2d =
   //     std::make_shared< LevelWiseMemoryDataHandling< LevelWiseMemory< Matrix3r >, Face > >( minLevel_, maxLvl );
   // auto dataHandling_stiffness_3d =
   //     std::make_shared< LevelWiseMemoryDataHandling< LevelWiseMemory< Matrix4r >, Cell > >( minLevel_, maxLvl );

   // memory of surrogates for level 4+ (one poly matrix for each element type)
   auto minLvl = std::max( minLevel_, min_lvl_for_surrogate );
   auto dataHandling_surrogate_2d =
       std::make_shared< LevelWiseMemoryDataHandling< LevelWiseMemory< std::array< P_matrix< 2 >, 2 > >, Face > >( minLvl,
                                                                                                                   maxLevel_ );
   auto dataHandling_surrogate_3d =
       std::make_shared< LevelWiseMemoryDataHandling< LevelWiseMemory< std::array< P_matrix< 2 >, 6 > >, Cell > >( minLvl,
                                                                                                                   maxLevel_ );

   if ( storage->hasGlobalCells() )
   {
      // storage->addCellData( stiffnessID_3d_, dataHandling_stiffness_3d, "P1SurrogateOperator_stiffness_3d" );
      storage->addCellData( surrogateID_3d_, dataHandling_surrogate_3d, "P1SurrogateOperator_surrogate_3d" );
   }
   else
   {
      // storage->addFaceData( stiffnessID_2d_, dataHandling_stiffness_2d, "P1SurrogateOperator_stiffness_2d" );
      storage->addFaceData( surrogateID_2d_, dataHandling_surrogate_2d, "P1SurrogateOperator_surrogate_2d" );
   }
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::init( uint8_t            poly_degree,
                                                     size_t             downsampling,
                                                     const std::string& path_to_svd,
                                                     bool               needsInverseDiagEntries )
{
   uint_t dim = ( storage_->hasGlobalCells() ) ? 3 : 2;

   // // precompute and store local stiffness matrices for level 1-3
   // auto maxLvl = std::min( maxLevel_, 3 );
   // for ( uint_t lvl = 0; lvl <= maxLvl; ++lvl )
   // {
   //    if ( dim == 2 )
   //    {
   //       precompute_local_stiffness_2d( lvl );
   //    }
   //    else
   //    {
   //       precompute_local_stiffness_3d( lvl );
   //    }
   // }

   // approximate local stiffness matrices for level 4+ by polynomials
   const auto minLvl = std::max( minLevel_, min_lvl_for_surrogate );
   for ( uint_t lvl = minLvl; lvl <= maxLevel_; ++lvl )
   {
      // adjust downsampling for this level
      auto ds = downsampling;
      while ( surrogate::LeastSquares::max_degree( lvl, ds ) < poly_degree && ds > 1 )
      {
         --ds;
      }
      // adjust polynomial degree for this level
      auto q = std::min( surrogate::LeastSquares::max_degree( lvl, ds ), poly_degree );

      // initialize least squares approximation
      if ( lsq_[lvl] == nullptr || downsampling_[lvl] != ds || poly_degree_[lvl] != q )
      {
         if ( path_to_svd == "" )
         {
            lsq_[lvl] = std::make_shared< surrogate::LeastSquares >( dim, q, lvl, ds );
         }
         else
         {
            lsq_[lvl] = std::make_shared< surrogate::LeastSquares >( path_to_svd, dim, q, lvl, ds );
         }
         downsampling_[lvl] = ds;
         poly_degree_[lvl]  = q;
      }

      if ( dim == 2 )
      {
         compute_local_surrogates_2d( lvl );
      }
      else
      {
         compute_local_surrogates_3d( lvl );
      }
   }

   if ( needsInverseDiagEntries )
   {
      computeInverseDiagonalOperatorValues();
   }

   is_initialized_ = true;
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::compute_local_surrogates_2d( uint_t lvl )
{
   auto  q   = poly_degree_[lvl];
   auto& lsq = *lsq_[lvl];
   // initialize rhs vectors for lsq
   RHS_matrix< 2 > rhs;
   for ( uint_t i = 0; i < rhs.size(); ++i )
   {
      for ( uint_t j = 0; j < rhs[i].size(); ++j )
      {
         rhs[i][j] = surrogate::LeastSquares::Vector( lsq.rows );
      }
   }

   for ( auto& [_, face] : storage_->getFaces() )
   {
      WALBERLA_UNUSED( _ );

      auto& all_surrogates = face->getData( surrogateID_2d_ )->getData( lvl );

      Matrix3r elMat( Matrix3r::Zero() );

      for ( const auto& fType : facedof::allFaceTypes )
      {
         // set up rhs vectors for each entry of the local stiffness matrix
         auto it = lsq.samplingIterator();
         while ( it != it.end() )
         {
            assembleLocalElementMatrix2D( *face, lvl, it.ijk(), fType, form_, elMat );
            for ( uint_t i = 0; i < rhs.size(); ++i )
            {
               for ( uint_t j = 0; j < rhs[i].size(); ++j )
               {
                  rhs[i][j]( it() ) = elMat( i, j );
               }
            }
            ++it;
         }
         // fit polynomials for each entry of the local stiffness matrix
         auto& surrogate = all_surrogates[uint_t( fType )];
         for ( uint_t i = 0; i < rhs.size(); ++i )
         {
            for ( uint_t j = 0; j < rhs[i].size(); ++j )
            {
               // apply least squares fit
               lsq.setRHS( rhs[i][j] );
               auto& coeffs    = lsq.solve();
               surrogate[i][j] = surrogate::polynomial::Polynomial( 2, q, coeffs );
            }
         }
      }
   }
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::compute_local_surrogates_3d( uint_t lvl )
{
   auto  q   = poly_degree_[lvl];
   auto& lsq = *lsq_[lvl];
   // initialize rhs vectors for lsq
   RHS_matrix< 3 > rhs;
   for ( uint_t i = 0; i < rhs.size(); ++i )
   {
      for ( uint_t j = 0; j < rhs[i].size(); ++j )
      {
         rhs[i][j] = surrogate::LeastSquares::Vector( lsq.rows );
      }
   }

   for ( auto& [_, cell] : storage_->getCells() )
   {
      WALBERLA_UNUSED( _ );

      auto& all_surrogates = cell->getData( surrogateID_3d_ )->getData( lvl );

      Matrix4r elMat( Matrix4r::Zero() );

      for ( const auto& cType : celldof::allCellTypes )
      {
         // set up rhs vectors for each entry of the local stiffness matrix
         auto it = lsq.samplingIterator();
         while ( it != it.end() )
         {
            assembleLocalElementMatrix3D( *cell, lvl, it.ijk(), cType, form_, elMat );
            for ( uint_t i = 0; i < rhs.size(); ++i )
            {
               for ( uint_t j = 0; j < rhs[i].size(); ++j )
               {
                  rhs[i][j]( it() ) = elMat( i, j );
               }
            }
            ++it;
         }
         // fit polynomials for each entry of the local stiffness matrix
         auto& surrogate = all_surrogates[uint_t( cType )];
         for ( uint_t i = 0; i < rhs.size(); ++i )
         {
            for ( uint_t j = 0; j < rhs[i].size(); ++j )
            {
               // apply least squares fit
               lsq.setRHS( rhs[i][j] );
               auto& coeffs    = lsq.solve();
               surrogate[i][j] = surrogate::polynomial::Polynomial( 3, q, coeffs );
            }
         }
      }
   }
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::apply( const P1Function< real_t >& src,
                                                      const P1Function< real_t >& dst,
                                                      size_t                      level,
                                                      DoFType                     flag,
                                                      UpdateType                  updateType ) const
{
   return gemv( real_c( 1 ), src, ( updateType == Replace ? real_c( 0 ) : real_c( 1 ) ), dst, level, flag );
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::gemv( const real_t&               alpha,
                                                     const P1Function< real_t >& src,
                                                     const real_t&               beta,
                                                     const P1Function< real_t >& dst,
                                                     size_t                      level,
                                                     DoFType                     flag ) const
{
   WALBERLA_ASSERT_NOT_IDENTICAL( std::addressof( src ), std::addressof( dst ) );

   this->startTiming( "gemv" );

   // Make sure that halos are up-to-date
   if ( this->storage_->hasGlobalCells() )
   {
      // Note that the order of communication is important, since the face -> cell communication may overwrite
      // parts of the halos that carry the macro-vertex and macro-edge unknowns.

      src.communicate< Face, Cell >( level );
      src.communicate< Edge, Cell >( level );
      src.communicate< Vertex, Cell >( level );
   }
   else
   {
      communication::syncFunctionBetweenPrimitives( src, level );
   }

   // Formerly updateType == Replace
   const bool betaIsZero = std::fpclassify( beta ) == FP_ZERO;
   // Formerly updateType == Add
   const bool betaIsOne = std::fpclassify( beta - real_c( 1.0 ) ) == FP_ZERO;

   if ( betaIsZero )
   {
      // We need to zero the destination array (including halos).
      // However, we must not zero out anything that is not flagged with the specified BCs.
      // Therefore we first zero out everything that flagged, and then, later,
      // the halos of the highest dim primitives.
      dst.interpolate( real_c( 0 ), level, flag );
   }
   else if ( !betaIsOne )
   {
      dst.assign( { beta }, { dst }, level, flag );
   }

   // domain of surrogate polynomials
   surrogate::polynomial::Coordinates poly_domain( level );

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

         auto& all_surrogates = cell.getData( surrogateID_3d_ )->getData( level );

         Matrix4r elMat( Matrix4r::Zero() );

         // loop over micro-cells
         for ( const auto& cType : celldof::allCellTypes )
         {
            auto& surrogate = all_surrogates[uint_t( cType )];

            // todo: use optimized polynomial evaluation

            for ( const auto& micro : celldof::macrocell::Iterator( level, cType, 0 ) )
            {
               if ( level < min_lvl_for_surrogate )
               {
                  // todo: use precomputed matrices for lower levels
                  // if ( localElementMatricesPrecomputed_ )
                  // {
                  //    elMat = localElementMatrix3D( cell, level, micro, cType );
                  // }
                  // else
                  {
                     assembleLocalElementMatrix3D( cell, level, micro, cType, form_, elMat );
                  }
               }
               else
               {
                  auto x = poly_domain( micro);

                  for ( uint_t i = 0; i < surrogate.size(); ++i )
                  {
                     for ( uint_t j = 0; j < surrogate[i].size(); ++j )
                     {
                        elMat( i, j ) = surrogate[i][j].eval_naive( x );
                     }
                  }
               }

               localMatrixVectorMultiply3D( level, micro, cType, srcVertexData, dstVertexData, elMat, alpha );
            }
         }
      }

      // Push result to lower-dimensional primitives
      //
      // Note: We could avoid communication here by implementing the apply() also for the respective
      //       lower dimensional primitives!
      dst.communicateAdditively< Cell, Face >( level, DoFType::All ^ flag, *storage_, betaIsZero );
      dst.communicateAdditively< Cell, Edge >( level, DoFType::All ^ flag, *storage_, betaIsZero );
      dst.communicateAdditively< Cell, Vertex >( level, DoFType::All ^ flag, *storage_, betaIsZero );
   }

   else
   {
      // we only perform computations on face primitives
      for ( auto& it : storage_->getFaces() )
      {
         Face& face = *it.second;

         Point3D         v0, v1, v2;
         indexing::Index nodeIdx;
         indexing::Index offset;

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

         auto& all_surrogates = face.getData( surrogateID_2d_ )->getData( level );

         Matrix3r elMat( Matrix3r::Zero() );

         // loop over micro-faces
         for ( const auto& fType : facedof::allFaceTypes )
         {
            auto& surrogate = all_surrogates[uint_t( fType )];

            // todo: use optimized polynomial evaluation

            for ( const auto& micro : facedof::macroface::Iterator( level, fType, 0 ) )
            {
               if ( level < min_lvl_for_surrogate )
               {
                  // todo: use precomputed matrices for lower levels

                  // if ( localElementMatricesPrecomputed_ )
                  // {
                  //    elMat = localElementMatrix2D( face, level, micro, fType );
                  // }
                  // else
                  {
                     assembleLocalElementMatrix2D( face, level, micro, fType, form_, elMat );
                  }
               }
               else
               {
                  auto x = poly_domain(micro);

                  for ( uint_t i = 0; i < surrogate.size(); ++i )
                  {
                     for ( uint_t j = 0; j < surrogate[i].size(); ++j )
                     {
                        elMat( i, j ) = surrogate[i][j].eval_naive( x );
                     }
                  }
               }
               localMatrixVectorMultiply2D( level, micro, fType, srcVertexData, dstVertexData, elMat, alpha );
            }
         }
      }

      // Push result to lower-dimensional primitives
      //
      // Note: We could avoid communication here by implementing the apply() also for the respective
      //       lower dimensional primitives!
      dst.communicateAdditively< Face, Edge >( level, DoFType::All ^ flag, *storage_, betaIsZero );
      dst.communicateAdditively< Face, Vertex >( level, DoFType::All ^ flag, *storage_, betaIsZero );
   }

   this->stopTiming( "gemv" );
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::smooth_jac( const P1Function< real_t >& dst,
                                                           const P1Function< real_t >& rhs,
                                                           const P1Function< real_t >& src,
                                                           real_t                      omega,
                                                           size_t                      level,
                                                           DoFType                     flag ) const
{
   this->startTiming( "smooth_jac" );

   // compute the current residual
   this->apply( src, dst, level, flag );
   dst.assign( { real_c( 1 ), real_c( -1 ) }, { rhs, dst }, level, flag );

   // perform Jacobi update step
   dst.multElementwise( { *getInverseDiagonalValues(), dst }, level, flag );
   dst.assign( { 1.0, omega }, { src, dst }, level, flag );

   this->stopTiming( "smooth_jac" );
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::localMatrixVectorMultiply2D( const uint_t           level,
                                                                            const indexing::Index& microFace,
                                                                            facedof::FaceType      fType,
                                                                            const real_t* const    srcVertexData,
                                                                            real_t* const          dstVertexData,
                                                                            const Matrix3r&        elMat,
                                                                            const real_t&          alpha ) const
{
   WALBERLA_ASSERT_UNEQUAL( srcVertexData, dstVertexData );

   // obtain data indices of dofs associated with micro-face
   std::array< uint_t, 3 > vertexDoFIndices;
   vertexdof::getVertexDoFDataIndicesFromMicroFace( microFace, fType, level, vertexDoFIndices );

   // assemble local element vector
   Point3D elVecOld, elVecNew;
   for ( int k = 0; k < 3; ++k )
   {
      elVecOld[k] = srcVertexData[vertexDoFIndices[uint_c( k )]];
   }

   // apply matrix (operator locally)
   elVecNew = alpha * ( elMat * elVecOld );

   // redistribute result from "local" to "global vector"
   for ( int k = 0; k < 3; ++k )
   {
      dstVertexData[vertexDoFIndices[uint_c( k )]] += elVecNew[k];
   }
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::localMatrixVectorMultiply3D( const uint_t            level,
                                                                            const indexing::Index&  microCell,
                                                                            const celldof::CellType cType,
                                                                            const real_t* const     srcVertexData,
                                                                            real_t* const           dstVertexData,
                                                                            const Matrix4r&         elMat,
                                                                            const real_t&           alpha ) const
{
   // obtain data indices of dofs associated with micro-cell
   std::array< uint_t, 4 > vertexDoFIndices;
   vertexdof::getVertexDoFDataIndicesFromMicroCell( microCell, cType, level, vertexDoFIndices );

   // assemble local element vector
   Point4D elVecOld, elVecNew;
   for ( int k = 0; k < 4; ++k )
   {
      elVecOld[k] = srcVertexData[vertexDoFIndices[uint_c( k )]];
   }

   // apply matrix (operator locally)
   elVecNew = alpha * ( elMat * elVecOld );

   // redistribute result from "local" to "global vector"
   for ( int k = 0; k < 4; ++k )
   {
      dstVertexData[vertexDoFIndices[uint_c( k )]] += elVecNew[k];
   }
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::computeDiagonalOperatorValues( bool invert )
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

            uint_t          rowsize       = levelinfo::num_microvertices_per_edge( level );
            uint_t          inner_rowsize = rowsize;
            idx_t           xIdx, yIdx;
            Point3D         v0, v1, v2;
            indexing::Index nodeIdx;
            indexing::Index offset;

            // get hold of the actual numerical data in the two functions
            PrimitiveDataID< FunctionMemory< real_t >, Face > vertexDoFIdx = targetFunction->getFaceDataID();
            real_t*                                           vertexData   = face.getData( vertexDoFIdx )->getPointer( level );

            // now loop over micro-faces of macro-face
            for ( yIdx = 0; yIdx < idx_t( rowsize ) - 2; ++yIdx )
            {
               // loop over vertices in row with two associated triangles
               for ( xIdx = 1; xIdx < idx_t( inner_rowsize ) - 1; ++xIdx )
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
void P1ElementwiseSurrogateOperator< P1Form >::computeAndStoreLocalElementMatrices()
{
   for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
   {
      // todo: implement
      // For 3D we work on cells and for 2D on faces
      if ( storage_->hasGlobalCells() )
      {
         // const uint_t numMicroCellsPerMacroCell = celldof::macrocell::numMicroCellsPerMacroCellTotal( level );

         // for ( const auto& it : storage_->getCells() )
         // {
            // auto cellID = it.first;
            // auto cell   = it.second;

            // auto& elementMatrices = localElementMatrices3D_[cellID][level];

            // // if ( !localElementMatricesPrecomputed_ )
            // {
            //    elementMatrices.resize( numMicroCellsPerMacroCell );
            // }

            // for ( const auto& cType : celldof::allCellTypes )
            // {
            //    for ( const auto& micro : celldof::macrocell::Iterator( level, cType, 0 ) )
            //    {
            //       Matrix4r& elMat = localElementMatrix3D( *cell, level, micro, cType );
            //       elMat.setZero();
            //       assembleLocalElementMatrix3D( *cell, level, micro, cType, form_, elMat );
            //    }
            // }
         // }
      }
      else
      {
         // const uint_t numMicroFacesPerMacroFace = levelinfo::num_microfaces_per_face( level );

         // for ( const auto& it : storage_->getFaces() )
         // {
         //    auto faceID = it.first;
         //    auto face   = it.second;

         //    auto& elementMatrices = localElementMatrices2D_[faceID][level];

         //    // if ( !localElementMatricesPrecomputed_ )
         //    {
         //       elementMatrices.resize( numMicroFacesPerMacroFace );
         //    }

         //    for ( const auto& fType : facedof::allFaceTypes )
         //    {
         //       for ( const auto& micro : facedof::macroface::Iterator( level, fType, 0 ) )
         //       {
         //          Matrix3r& elMat = localElementMatrix2D( *face, level, micro, fType );
         //          elMat.setZero();
         //          assembleLocalElementMatrix2D( *face, level, micro, fType, form_, elMat );
         //       }
         //    }
         // }
      }
   }

   // localElementMatricesPrecomputed_ = true;
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::computeLocalDiagonalContributions2D(
    const Face&                                face,
    const uint_t                               level,
    const idx_t                                xIdx,
    const idx_t                                yIdx,
    const P1Elements::P1Elements2D::P1Element& element,
    real_t* const                              dstVertexData )
{
   Matrix3r                elMat( Matrix3r::Zero() );
   indexing::Index         nodeIdx;
   indexing::Index         offset;
   Point3D                 v0, v1, v2;
   std::array< uint_t, 6 > dofDataIdx;
   P1Form                  form( form_ );

   // determine vertices of micro-element
   nodeIdx = indexing::Index( xIdx, yIdx, 0 );
   v0      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[1] );
   v1      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[2] );
   v2      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );

   // assemble local element matrix
   form.setGeometryMap( face.getGeometryMap() );
   form.integrateAll( { v0, v1, v2 }, elMat );

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
void P1ElementwiseSurrogateOperator< P1Form >::computeLocalDiagonalContributions3D( const Cell&             cell,
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
   Matrix4r elMat( Matrix4r::Zero() );
   P1Form   form( form_ );
   form.setGeometryMap( cell.getGeometryMap() );
   form.integrateAll( coords, elMat );

   // obtain data indices of dofs associated with micro-cell
   std::array< uint_t, 4 > vertexDoFIndices;
   vertexdof::getVertexDoFDataIndicesFromMicroCell( microCell, cType, level, vertexDoFIndices );

   // add contributions for central stencil weights
   for ( int k = 0; k < 4; ++k )
   {
      vertexData[vertexDoFIndices[uint_c( k )]] += elMat( k, k );
   }
}

// Assemble operator as sparse matrix
template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                                                         const P1Function< idx_t >&                  src,
                                                         const P1Function< idx_t >&                  dst,
                                                         uint_t                                      level,
                                                         DoFType                                     flag ) const
{
   // We currently ignore the flag provided!
   // WALBERLA_UNUSED( flag );
   if ( flag != All )
   {
      WALBERLA_LOG_WARNING_ON_ROOT( "Input flag ignored in P1ElementwiseOperator::assembleLocalMatrix(); using flag = All" );
   }

   // For 3D we work on cells and for 2D on faces
   if ( storage_->hasGlobalCells() )
   {
      // we only perform computations on cell primitives
      for ( auto& macroIter : storage_->getCells() )
      {
         Cell& cell = *macroIter.second;

         // get hold of the actual numerical data in the two indexing functions
         PrimitiveDataID< FunctionMemory< idx_t >, Cell > dstVertexDoFIdx = dst.getCellDataID();
         PrimitiveDataID< FunctionMemory< idx_t >, Cell > srcVertexDoFIdx = src.getCellDataID();

         idx_t* srcIdx = cell.getData( srcVertexDoFIdx )->getPointer( level );
         idx_t* dstIdx = cell.getData( dstVertexDoFIdx )->getPointer( level );

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

         uint_t          rowsize       = levelinfo::num_microvertices_per_edge( level );
         uint_t          inner_rowsize = rowsize;
         idx_t           xIdx, yIdx;
         Point3D         v0, v1, v2;
         indexing::Index nodeIdx;
         indexing::Index offset;

         // get hold of the actual numerical data in the two functions
         PrimitiveDataID< FunctionMemory< idx_t >, Face > dstVertexDoFIdx = dst.getFaceDataID();
         PrimitiveDataID< FunctionMemory< idx_t >, Face > srcVertexDoFIdx = src.getFaceDataID();

         idx_t* srcIndices = face.getData( srcVertexDoFIdx )->getPointer( level );
         idx_t* dstIndices = face.getData( dstVertexDoFIdx )->getPointer( level );

         // the explicit uint_c cast prevents a segfault in intel compiler 2018.4
         // now loop over micro-faces of macro-face
         for ( yIdx = 0; yIdx < idx_t( rowsize ) - 2; ++yIdx )
         {
            // loop over vertices in row with two associated triangles
            for ( xIdx = 1; xIdx < idx_t( inner_rowsize ) - 1; ++xIdx )
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
void P1ElementwiseSurrogateOperator< P1Form >::localMatrixAssembly2D( const std::shared_ptr< SparseMatrixProxy >& mat,
                                                                      const Face&                                 face,
                                                                      const uint_t                                level,
                                                                      const idx_t                                 xIdx,
                                                                      const idx_t                                 yIdx,
                                                                      const P1Elements::P1Elements2D::P1Element&  element,
                                                                      const idx_t* const                          srcIdx,
                                                                      const idx_t* const                          dstIdx ) const
{
   Matrix3r                elMat( Matrix3r::Zero() );
   indexing::Index         nodeIdx;
   indexing::Index         offset;
   Point3D                 v0, v1, v2;
   std::array< uint_t, 3 > dofDataIdx;
   P1Form                  form( form_ );

   // determine vertices of micro-element
   nodeIdx = indexing::Index( xIdx, yIdx, 0 );
   v0      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[1] );
   v1      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );
   offset  = vertexdof::logicalIndexOffsetFromVertex( element[2] );
   v2      = vertexdof::macroface::coordinateFromIndex( level, face, nodeIdx + offset );

   // assemble local element matrix
   form.setGeometryMap( face.getGeometryMap() );
   form.integrateAll( { v0, v1, v2 }, elMat );

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

   const uint_t          elMatSize = 9;
   std::vector< real_t > blockMatData( elMatSize );
   for ( uint_t i = 0; i < elMatSize; i++ )
   {
      blockMatData[i] = elMat.data()[i];
   }

   // add local matrix into global matrix
   mat->addValues( rowIdx, colIdx, blockMatData );
}

template < class P1Form >
void P1ElementwiseSurrogateOperator< P1Form >::localMatrixAssembly3D( const std::shared_ptr< SparseMatrixProxy >& mat,
                                                                      const Cell&                                 cell,
                                                                      const uint_t                                level,
                                                                      const indexing::Index&                      microCell,
                                                                      const celldof::CellType                     cType,
                                                                      const idx_t* const                          srcIdx,
                                                                      const idx_t* const                          dstIdx ) const
{
   // determine coordinates of vertices of micro-element
   std::array< indexing::Index, 4 > verts = celldof::macrocell::getMicroVerticesFromMicroCell( microCell, cType );
   std::array< Point3D, 4 >         coords;
   for ( uint_t k = 0; k < 4; ++k )
   {
      coords[k] = vertexdof::macrocell::coordinateFromIndex( level, cell, verts[k] );
   }

   // assemble local element matrix
   Matrix4r elMat( Matrix4r::Zero() );
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

   const uint_t          elMatSize = 16;
   std::vector< real_t > blockMatData( elMatSize );
   for ( uint_t i = 0; i < elMatSize; i++ )
   {
      blockMatData[i] = elMat.data()[i];
   }

   // add local matrix into global matrix
   mat->addValues( rowIdx, colIdx, blockMatData );
}

// // P1ElementwiseLaplaceOperator
// template class P1ElementwiseSurrogateOperator<
//     P1FenicsForm< p1_diffusion_cell_integral_0_otherwise, p1_tet_diffusion_cell_integral_0_otherwise > >;

// // P1ElementwisePolarLaplaceOperator
// template class P1ElementwiseSurrogateOperator< P1FenicsForm< p1_polar_laplacian_cell_integral_0_otherwise > >;

// // P1ElementwiseMassOperator
// template class P1ElementwiseSurrogateOperator<
//     P1FenicsForm< p1_mass_cell_integral_0_otherwise, p1_tet_mass_cell_integral_0_otherwise > >;

// // P1ElementwisePSPGOperator
// template class P1ElementwiseSurrogateOperator<
//     P1FenicsForm< p1_pspg_cell_integral_0_otherwise, p1_tet_pspg_tet_cell_integral_0_otherwise > >;

// template class P1ElementwiseSurrogateOperator< P1LinearCombinationForm >;

// // P1ElementwiseBlendingMassOperator3D
// template class P1ElementwiseSurrogateOperator< forms::p1_mass_blending_q4 >;

// // P1ElementwiseBlendingLaplaceOperator
// template class P1ElementwiseSurrogateOperator< forms::p1_diffusion_blending_q3 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_diffusion_blending_q2 >;

// // Needed for P1Blending(Inverse)DiagonalOperator
// template class P1ElementwiseSurrogateOperator< P1RowSumForm >;

// template class P1ElementwiseSurrogateOperator< forms::p1_div_k_grad_affine_q3 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_div_k_grad_blending_q3 >;

// template class P1ElementwiseSurrogateOperator<
//     P1FenicsForm< p1_div_cell_integral_0_otherwise, p1_tet_div_tet_cell_integral_0_otherwise > >;
// template class P1ElementwiseSurrogateOperator<
//     P1FenicsForm< p1_div_cell_integral_1_otherwise, p1_tet_div_tet_cell_integral_1_otherwise > >;
// template class P1ElementwiseSurrogateOperator< P1FenicsForm< fenics::NoAssemble, p1_tet_div_tet_cell_integral_2_otherwise > >;

// template class P1ElementwiseSurrogateOperator<
//     P1FenicsForm< p1_divt_cell_integral_0_otherwise, p1_tet_divt_tet_cell_integral_0_otherwise > >;
// template class P1ElementwiseSurrogateOperator<
//     P1FenicsForm< p1_divt_cell_integral_1_otherwise, p1_tet_divt_tet_cell_integral_1_otherwise > >;
// template class P1ElementwiseSurrogateOperator< P1FenicsForm< fenics::NoAssemble, p1_tet_divt_tet_cell_integral_2_otherwise > >;

// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_0_0_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_0_1_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_0_2_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_1_0_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_1_1_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_1_2_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_2_0_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_2_1_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsiloncc_2_2_affine_q2 >;

// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_0_0_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_0_1_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_0_2_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_1_0_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_1_1_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_1_2_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_2_0_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_2_1_affine_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_2_2_affine_q2 >;

// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_0_0_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_0_1_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_0_2_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_1_0_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_1_1_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_1_2_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_2_0_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_2_1_blending_q2 >;
// template class P1ElementwiseSurrogateOperator< forms::p1_epsilonvar_2_2_blending_q2 >;

template class P1ElementwiseSurrogateOperator< forms::p1_k_mass_affine_q4 >;

// This is a slight misuse of the P1ElementwiseOperator class, since the spherical
// elements are not P1. However, the SphericalElementFunction, like the P1Function
// is only an alias for the VertexDoFFunction, so we can re-use this operator.
// template class P1ElementwiseSurrogateOperator< SphericalElementFormMass >;

} // namespace hyteg
