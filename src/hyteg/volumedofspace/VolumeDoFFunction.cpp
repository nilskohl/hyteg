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

#include "hyteg/volumedofspace/VolumeDoFFunction.hpp"

namespace hyteg {
namespace volumedofspace {

template < typename ValueType >
void VolumeDoFFunction< ValueType >::allocateMemory()
{
   if ( storage_->hasGlobalCells() )
   {
      // 3D
      WALBERLA_ABORT( "DG not implemented in 3D" );
   }
   else
   {
      // 2D

      // Create a data handling instance that handles the initialization, serialization, and deserialization of data.
      const auto dofDataHandling = std::make_shared< MemoryDataHandling< FunctionMemory< ValueType >, Face > >();

      // Create a data ID for all faces.
      storage_->template addFaceData( faceInnerDataID_, dofDataHandling, "VolumeDoFMacroFaceData" );

      // Create a data handling instance that handles the initialization, serialization, and deserialization of data.
      const auto dofDataHandlingGL = std::make_shared< MemoryDataHandling< FunctionMemory< ValueType >, Face > >();

      // Create three data IDs for all faces.
      storage_->template addFaceData( faceGhostLayerDataIDs_[0], dofDataHandling, "VolumeDoFMacroFaceGL0Data" );
      storage_->template addFaceData( faceGhostLayerDataIDs_[1], dofDataHandling, "VolumeDoFMacroFaceGL1Data" );
      storage_->template addFaceData( faceGhostLayerDataIDs_[2], dofDataHandling, "VolumeDoFMacroFaceGL2Data" );

      // Allocate the DoFs.
      for ( auto& it : storage_->getFaces() )
      {
         const auto pid  = it.first;
         const auto face = it.second;

         // Fetching the FunctionMemory instance from each macro-face.
         FunctionMemory< ValueType >* functionMemory = face->template getData( faceInnerDataID_ );

         for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
         {
            // Allocating the specified number of scalars on each micro-element for the entire macro-primitive.
            const auto numMacroLocalScalars = numScalarsPerPrimitive_.at( pid ) * levelinfo::num_microfaces_per_face( level );
            functionMemory->addData( level, numMacroLocalScalars, ValueType( 0 ) );
         }

         // Allocating ghost-layer memory only where necessary.
         for ( const auto& [localEdgeID, npid] : face->getIndirectNeighborFaceIDs() )
         {
            FunctionMemory< ValueType >* functionGLMemory = face->template getData( faceGhostLayerDataIDs_[localEdgeID] );

            for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
            {
               const auto numGLScalars = numScalarsPerPrimitive_.at( pid ) * levelinfo::num_microedges_per_edge( level );
               functionGLMemory->addData( level, numGLScalars, ValueType( 0 ) );
            }
         }
      }
   }
}

template < typename ValueType >
void VolumeDoFFunction< ValueType >::communicateNumScalarsPerPrimitive()
{
   walberla::mpi::BufferSystem bs( walberla::mpi::MPIManager::instance()->comm() );

   const auto neighboringRanks = storage_->getNeighboringVolumeRanksOfAllVolumes();

   bs.setReceiverInfo( neighboringRanks, true );

   // Complexity is not optimal - sending more data than necessary, but usually we do not need to send that often.
   for ( auto r : neighboringRanks )
   {
      bs.sendBuffer( r ) << numScalarsPerPrimitive_;
   }

   bs.sendAll();

   for ( auto i = bs.begin(); i != bs.end(); ++i )
   {
      std::map< PrimitiveID, uint_t > nScalarsNeighbor;
      i.buffer() >> nScalarsNeighbor;
      numScalarsPerPrimitive_.insert( nScalarsNeighbor.begin(), nScalarsNeighbor.end() );
   }
}

template < typename ValueType >
void VolumeDoFFunction< ValueType >::addPackInfos()
{
   for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
   {
      communicators_[level]->addPackInfo( std::make_shared< VolumeDoFPackInfo< ValueType > >( this->getStorage(),
                                                                                              level,
                                                                                              numScalarsPerPrimitive_,
                                                                                              faceInnerDataID_,
                                                                                              cellInnerDataID_,
                                                                                              faceGhostLayerDataIDs_,
                                                                                              cellGhostLayerDataIDs_,
                                                                                              memoryLayout_ ) );
   }
}

template < typename ValueType >
VolumeDoFFunction< ValueType >::VolumeDoFFunction( const std::string&                         name,
                                                   const std::shared_ptr< PrimitiveStorage >& storage,
                                                   uint_t                                     minLevel,
                                                   uint_t                                     maxLevel,
                                                   const std::map< PrimitiveID, uint_t >&     numScalarsPerPrimitive,
                                                   indexing::VolumeDoFMemoryLayout            memoryLayout )

: Function< VolumeDoFFunction< ValueType > >( name, storage, minLevel, maxLevel )
, name_( name )
, storage_( storage )
, minLevel_( minLevel )
, maxLevel_( maxLevel )
, numScalarsPerPrimitive_( numScalarsPerPrimitive )
, memoryLayout_( memoryLayout )
{
   communicateNumScalarsPerPrimitive();
   allocateMemory();
   addPackInfos();
}

template < typename ValueType >
VolumeDoFFunction< ValueType >::VolumeDoFFunction( const std::string&                         name,
                                                   const std::shared_ptr< PrimitiveStorage >& storage,
                                                   uint_t                                     minLevel,
                                                   uint_t                                     maxLevel,
                                                   uint_t                                     numScalars,
                                                   indexing::VolumeDoFMemoryLayout            memoryLayout )

: Function< VolumeDoFFunction< ValueType > >( name, storage, minLevel, maxLevel )
, name_( name )
, storage_( storage )
, minLevel_( minLevel )
, maxLevel_( maxLevel )
, memoryLayout_( memoryLayout )
{
   numScalarsPerPrimitive_.clear();
   for ( auto pid : storage->getPrimitiveIDs() )
   {
      numScalarsPerPrimitive_[pid] = numScalars;
   }
   communicateNumScalarsPerPrimitive();
   allocateMemory();
   addPackInfos();
}

template < typename ValueType >
void VolumeDoFFunction< ValueType >::communicate( uint_t level )
{
   if ( !storage_->hasGlobalCells() )
   {
      this->communicators_[level]->template startCommunication< Face, Face >();
      this->communicators_[level]->template endCommunication< Face, Face >();
   }
   else
   {
      this->communicators_[level]->template startCommunication< Cell, Cell >();
      this->communicators_[level]->template endCommunication< Cell, Cell >();
   }
}

/// \brief Assigns a linear combination of multiple VolumeDoFFunctions to this.
template < typename ValueType >
void VolumeDoFFunction< ValueType >::assign(
    const std::vector< ValueType >&                                                      scalars,
    const std::vector< std::reference_wrapper< const VolumeDoFFunction< ValueType > > >& functions,
    uint_t                                                                               level )
{
   WALBERLA_CHECK_EQUAL( scalars.size(),
                         functions.size(),
                         "VolumeDoFFunction< ValueType >::assign(): must pass same number of scalars and functions." )

   if ( storage_->hasGlobalCells() )
   {
      WALBERLA_ABORT( "VolumeDoFFunction::assign() not implemented for 3D." );
   }
   else
   {
      for ( auto it : storage_->getFaces() )
      {
         for ( const auto& faceIt : this->getStorage()->getFaces() )
         {
            const auto faceId = faceIt.first;
            const auto face   = *faceIt.second;

            std::vector< ValueType* >                      srcPtrs( functions.size() );
            std::vector< indexing::VolumeDoFMemoryLayout > srcLayouts( functions.size() );
            for ( uint_t i = 0; i < functions.size(); i++ )
            {
               const auto f  = functions.at( i );
               srcPtrs[i]    = f.get().dofMemory( faceId, level );
               srcLayouts[i] = f.get().memoryLayout();
            }

            auto dstMem    = dofMemory( faceId, level );
            auto dstLayout = memoryLayout_;
            auto numDofs   = this->numScalarsPerPrimitive_.at( faceId );

            for ( auto faceType : facedof::allFaceTypes )
            {
               for ( auto elementIdx : facedof::macroface::Iterator( level, faceType ) )
               {
                  for ( uint_t dof = 0; dof < numDofs; dof++ )
                  {
                     ValueType sum = 0;
                     for ( uint_t i = 0; i < functions.size(); i++ )
                     {
                        const auto s = scalars.at( i );

                        sum += s * srcPtrs[i][indexing::index(
                                       elementIdx.x(), elementIdx.y(), faceType, dof, numDofs, level, srcLayouts[i] )];
                     }
                     dstMem[indexing::index( elementIdx.x(), elementIdx.y(), faceType, dof, numDofs, level, dstLayout )] = sum;
                  }
               }
            }
         }
      }
   }
}

/// \brief Evaluates the dot product on all local DoFs. No communication is involved and the results may be different on each
/// process.
template < typename ValueType >
ValueType VolumeDoFFunction< ValueType >::dotLocal( const VolumeDoFFunction< ValueType >& rhs, uint_t level ) const
{
   ValueType sum = 0;

   if ( storage_->hasGlobalCells() )
   {
      WALBERLA_ABORT( "VolumeDoFFunction::dotLocal() not implemented for 3D." );
   }
   else
   {
      for ( auto it : storage_->getFaces() )
      {
         for ( const auto& faceIt : this->getStorage()->getFaces() )
         {
            const auto faceId = faceIt.first;
            const auto face   = *faceIt.second;

            const auto mem     = dofMemory( faceId, level );
            const auto layout  = memoryLayout_;
            const auto numDofs = this->numScalarsPerPrimitive_.at( faceId );

            const auto otherMem    = rhs.dofMemory( faceId, level );
            const auto otherLayout = rhs.memoryLayout();

            for ( auto faceType : facedof::allFaceTypes )
            {
               for ( auto elementIdx : facedof::macroface::Iterator( level, faceType ) )
               {
                  for ( uint_t dof = 0; dof < numDofs; dof++ )
                  {
                     const auto idx = indexing::index( elementIdx.x(), elementIdx.y(), faceType, dof, numDofs, level, layout );
                     const auto otherIdx =
                         indexing::index( elementIdx.x(), elementIdx.y(), faceType, dof, numDofs, level, otherLayout );

                     sum += mem[idx] * otherMem[otherIdx];
                  }
               }
            }
         }
      }
   }

   return sum;
}

/// \brief Evaluates the (global) dot product. Involves communication and has to be called collectively.
template < typename ValueType >
ValueType VolumeDoFFunction< ValueType >::dotGlobal( const VolumeDoFFunction< ValueType >& rhs, uint_t level ) const
{
   const auto dLocal = dotLocal( rhs, level );
   return walberla::mpi::allReduce( dLocal, walberla::mpi::SUM );
}

/// explicit instantiation
template class VolumeDoFFunction< double >;
template class VolumeDoFFunction< float >;
template class VolumeDoFFunction< int32_t >;
template class VolumeDoFFunction< int64_t >;

} // namespace volumedofspace

} // namespace hyteg
