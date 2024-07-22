/*
 * Copyright (c) 2023 Ponsuganth Ilangovan P
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

#include "EdgeDoFRotationOperator.hpp"

#include "hyteg/communication/Syncing.hpp"
#include "hyteg/edgedofspace/EdgeDoFPetsc.hpp"
#include "hyteg/edgedofspace/freeslip/EdgeDoFRotation.hpp"

namespace hyteg {

EdgeDoFRotationOperator::EdgeDoFRotationOperator( const std::shared_ptr< PrimitiveStorage >&               storage,
                                                  size_t                                                   minLevel,
                                                  size_t                                                   maxLevel,
                                                  const std::function< void( const Point3D&, Point3D& ) >& normalFunction )
: Operator( storage, minLevel, maxLevel )
, normalFunction_( normalFunction )
{}

void EdgeDoFRotationOperator::rotate( const EdgeDoFFunction< real_t >& dst_u,
                                      const EdgeDoFFunction< real_t >& dst_v,
                                      const EdgeDoFFunction< real_t >& dst_w,
                                      size_t                           level,
                                      DoFType                          flag,
                                      bool                             transpose ) const
{
   this->startTiming( "Project" );
   dst_u.communicate< Vertex, Edge >( level );
   dst_u.communicate< Edge, Face >( level );
   dst_u.communicate< Face, Cell >( level );

   dst_v.communicate< Vertex, Edge >( level );
   dst_v.communicate< Edge, Face >( level );
   dst_v.communicate< Face, Cell >( level );

   if ( storage_->hasGlobalCells() )
   {
      dst_w.communicate< Vertex, Edge >( level );
      dst_w.communicate< Edge, Face >( level );
      dst_w.communicate< Face, Cell >( level );
   }

   dst_u.communicate< Cell, Face >( level );
   dst_u.communicate< Face, Edge >( level );
   dst_u.communicate< Edge, Vertex >( level );

   dst_v.communicate< Cell, Face >( level );
   dst_v.communicate< Face, Edge >( level );
   dst_v.communicate< Edge, Vertex >( level );

   if ( storage_->hasGlobalCells() )
   {
      dst_w.communicate< Cell, Face >( level );
      dst_w.communicate< Face, Edge >( level );
      dst_w.communicate< Edge, Vertex >( level );
   }

   this->timingTree_->start( "Macro-Edge" );

   if ( level >= 1 )
   {
      for ( const auto& it : storage_->getEdges() )
      {
         Edge& edge = *it.second;

         const DoFType edgeBC = dst_u.getBoundaryCondition().getBoundaryType( edge.getMeshBoundaryFlag() );
         if ( testFlag( edgeBC, flag ) )
         {
            if ( storage_->hasGlobalCells() )
            {
                  edgedof::macroedge::rotation3D< real_t >( level,
                                                            edge,
                                                            storage_,
                                                            normalFunction_,
                                                            dst_u.getEdgeDataID(),
                                                            dst_v.getEdgeDataID(),
                                                            dst_w.getEdgeDataID(), transpose );
            }
            else
            {
                  edgedof::macroedge::rotation2D< real_t >(
                      level, edge, storage_, normalFunction_, dst_u.getEdgeDataID(), dst_v.getEdgeDataID() );
            }
         }
      }
   }

   this->timingTree_->stop( "Macro-Edge" );

   this->timingTree_->start( "Macro-Face" );

   if ( level >= 2 )
   {
      for ( const auto& it : storage_->getFaces() )
      {
         Face& face = *it.second;

         const DoFType faceBC = dst_u.getBoundaryCondition().getBoundaryType( face.getMeshBoundaryFlag() );
         if ( testFlag( faceBC, flag ) )
         {
            if ( storage_->hasGlobalCells() )
            {
                  edgedof::macroface::rotation3D< real_t >( level,
                                                            face,
                                                            storage_,
                                                            normalFunction_,
                                                            dst_u.getFaceDataID(),
                                                            dst_v.getFaceDataID(),
                                                            dst_w.getFaceDataID(), transpose );
            }
         }
      }
   }

   this->timingTree_->stop( "Macro-Face" );

   this->stopTiming( "Project" );
}

void EdgeDoFRotationOperator::assembleLocalMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                                                   const EdgeDoFFunction< idx_t >&             numU,
                                                   const EdgeDoFFunction< idx_t >&             numV,
                                                   const EdgeDoFFunction< idx_t >&             numW,
                                                   uint_t                                      level,
                                                   DoFType                                     flag,
                                                   bool                                        transpose ) const
{
   communication::syncFunctionBetweenPrimitives( numU, level );
   communication::syncFunctionBetweenPrimitives( numV, level );
   communication::syncFunctionBetweenPrimitives( numW, level );

   // The matrix-free application of the projection operator (ID - nn^t) emulates
   // the application of Id by not touching the vector at all.
   // However, the Id diagonal must be assembled.

   if ( level >= 1 )
   {
      for ( const auto& it : storage_->getEdges() )
      {
         Edge& edge = *it.second;

         const DoFType edgeBC = numU.getBoundaryCondition().getBoundaryType( edge.getMeshBoundaryFlag() );

         if ( testFlag( edgeBC, flag ) )
         {
            if ( storage_->hasGlobalCells() )
            {
               edgedof::macroedge::saveRotationOperator3D( level,
                                                           edge,
                                                           storage_,
                                                           normalFunction_,
                                                           numU.getEdgeDataID(),
                                                           numV.getEdgeDataID(),
                                                           numW.getEdgeDataID(),
                                                           mat,
                                                           transpose );
            }
            else
            {
               edgedof::macroedge::saveRotationOperator2D(
                   level, edge, storage_, normalFunction_, numU.getEdgeDataID(), numV.getEdgeDataID(), mat );
            }
         }
         else
         {
            saveEdgeIdentityOperator( level, edge, numU.getEdgeDataID(), mat );
            saveEdgeIdentityOperator( level, edge, numV.getEdgeDataID(), mat );
            if ( storage_->hasGlobalCells() )
            {
               saveEdgeIdentityOperator( level, edge, numW.getEdgeDataID(), mat );
            }
         }
      }
   }

   if ( level >= 2 )
   {
      for ( const auto& it : storage_->getFaces() )
      {
         Face& face = *it.second;

         const DoFType faceBC = numU.getBoundaryCondition().getBoundaryType( face.getMeshBoundaryFlag() );
         if ( testFlag( faceBC, flag ) )
         {
            if ( storage_->hasGlobalCells() )
            {
               edgedof::macroface::saveRotationOperator3D( level,
                                                           face,
                                                           storage_,
                                                           normalFunction_,
                                                           numU.getFaceDataID(),
                                                           numV.getFaceDataID(),
                                                           numW.getFaceDataID(),
                                                           mat,
                                                           transpose );
            }
            else
            {
               WALBERLA_ABORT( "Normal projection for inner primitives?" );
            }
         }
         else
         {
            saveFaceIdentityOperator( level, face, numU.getFaceDataID(), mat );
            saveFaceIdentityOperator( level, face, numV.getFaceDataID(), mat );
            if ( storage_->hasGlobalCells() )
            {
               saveFaceIdentityOperator( level, face, numW.getFaceDataID(), mat );
            }
         }
      }

      for ( const auto& it : storage_->getCells() )
      {
         Cell& cell = *it.second;
         saveCellIdentityOperator( level, cell, numU.getCellDataID(), mat );
         saveCellIdentityOperator( level, cell, numV.getCellDataID(), mat );
         saveCellIdentityOperator( level, cell, numW.getCellDataID(), mat );
      }
   }
}

} // namespace hyteg
