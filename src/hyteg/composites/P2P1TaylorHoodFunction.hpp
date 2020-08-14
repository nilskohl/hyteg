/*
 * Copyright (c) 2017-2019 Daniel Drzisga, Dominik Thoennes, Marcus Mohr, Nils Kohl.
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

#include "hyteg/FunctionTraits.hpp"
#include "hyteg/composites/P2VectorFunction.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"
#include "hyteg/p2functionspace/P2Function.hpp"

namespace hyteg {

template < typename ValueType >
class P2P1TaylorHoodFunction
{
 public:
   using valueType = ValueType;

   template < typename VType >
   using FunctionType = P2P1TaylorHoodFunction< VType >;

   using VelocityFunction_T = P2VectorFunction< ValueType >;
   using PressureFunction_T = P1Function< ValueType >;

   using Tag = typename FunctionTrait< P2P1TaylorHoodFunction< ValueType > >::Tag;

   P2P1TaylorHoodFunction( const std::string&                         _name,
                           const std::shared_ptr< PrimitiveStorage >& storage,
                           size_t                                     minLevel,
                           size_t                                     maxLevel )
   : uvw( _name + "_vector", storage, minLevel, maxLevel )
   , p( _name + "_p", storage, minLevel, maxLevel, BoundaryCondition::createAllInnerBC() )
   {}

   P2P1TaylorHoodFunction( const std::string&                         _name,
                           const std::shared_ptr< PrimitiveStorage >& storage,
                           size_t                                     minLevel,
                           size_t                                     maxLevel,
                           BoundaryCondition                          velocityBC )
   : uvw( _name + "_vector", storage, minLevel, maxLevel, velocityBC )
   , p( _name + "_p", storage, minLevel, maxLevel, BoundaryCondition::createAllInnerBC() )
   {}

   std::shared_ptr< PrimitiveStorage > getStorage() const { return uvw.getStorage(); }

   bool isDummy() const { return false; }

   void interpolate( const std::function< real_t( const hyteg::Point3D& ) >& expr, size_t level, DoFType flag = All ) const
   {
      uvw.interpolate( expr, level, flag );
      p.interpolate( expr, level, flag );
   }

   void interpolate( const real_t& constant, size_t level, DoFType flag = All ) const
   {
      uvw.interpolate( constant, level, flag );
      p.interpolate( constant, level, flag );
   }

   void swap( const P2P1TaylorHoodFunction< ValueType >& other, const uint_t& level, const DoFType& flag = All ) const
   {
      uvw.swap( other.uvw, level, flag );
      p.swap( other.p, level, flag );
   }

   /// \brief Copies all values function data from other to this.
   ///
   /// This method can be used safely if the other function is located on a different PrimitiveStorage.
   /// This method also works, if the storages are distributed differently.
   ///
   /// \param other another function
   /// \param level the refinement level
   /// \param localPrimitiveIDsToRank Map that contains as keys all primitive IDs of all primitives that are local regarding the
   ///                                storage of this function, and as values the MPI ranks of the processes that own these
   ///                                primitives regarding the storage of the other function
   /// \param otherPrimitiveIDsToRank Map that contains as keys all primitive IDs of all primitives that are local regarding the
   ///                                storage of the other function, and as values the MPI ranks of the processes that own these
   ///                                primitives regarding the storage this function lives on.
   ///
   void copyFrom( const P2P1TaylorHoodFunction< ValueType >&     other,
                  const uint_t&                                  level,
                  const std::map< PrimitiveID::IDType, uint_t >& localPrimitiveIDsToRank,
                  const std::map< PrimitiveID::IDType, uint_t >& otherPrimitiveIDsToRank ) const
   {
      uvw.copyFrom( other.uvw, level, localPrimitiveIDsToRank, otherPrimitiveIDsToRank );
      p.copyFrom( other.p, level, localPrimitiveIDsToRank, otherPrimitiveIDsToRank );
   }

   void assign( const std::vector< walberla::real_t >                                                     scalars,
                const std::vector< std::reference_wrapper< const P2P1TaylorHoodFunction< ValueType > > >& functions,
                size_t                                                                                    level,
                DoFType                                                                                   flag = All ) const
   {
      std::vector< std::reference_wrapper< const VelocityFunction_T > > functions_uvw;
      std::vector< std::reference_wrapper< const PressureFunction_T > > functions_p;

      for ( const P2P1TaylorHoodFunction< ValueType >& function : functions )
      {
         functions_uvw.push_back( function.uvw );
         functions_p.push_back( function.p );
      }

      uvw.assign( scalars, functions_uvw, level, flag );
      p.assign( scalars, functions_p, level, flag );
   }

   void add( const std::vector< walberla::real_t >                                                     scalars,
             const std::vector< std::reference_wrapper< const P2P1TaylorHoodFunction< ValueType > > >& functions,
             size_t                                                                                    level,
             DoFType                                                                                   flag = All ) const
   {
      std::vector< std::reference_wrapper< const VelocityFunction_T > > functions_uvw;
      std::vector< std::reference_wrapper< const PressureFunction_T > > functions_p;

      for ( const P2P1TaylorHoodFunction< ValueType >& function : functions )
      {
         functions_uvw.push_back( function.uvw );
         functions_p.push_back( function.p );
      }

      uvw.add( scalars, functions_uvw, level, flag );
      p.add( scalars, functions_p, level, flag );
   }

   walberla::real_t
       dotGlobal( const P2P1TaylorHoodFunction< ValueType >& rhs, const size_t level, const DoFType flag = All ) const
   {
      walberla::real_t sum = uvw.dotLocal( rhs.uvw, level, flag );
      sum += p.dotLocal( rhs.p, level, flag | DirichletBoundary );
      walberla::mpi::allReduceInplace( sum, walberla::mpi::SUM, walberla::mpi::MPIManager::instance()->comm() );
      return sum;
   }

   void prolongate( const size_t level, const DoFType flag = All ) const
   {
      uvw.prolongate( level, flag );
      p.prolongate( level, flag );
   }

   void restrict( const size_t level, const DoFType flag = All ) const
   {
      uvw.restrict( level, flag );
      p.restrict( level, flag );
   }

   void enableTiming( const std::shared_ptr< walberla::WcTimingTree >& timingTree ) const
   {
      uvw.enableTiming( timingTree );
      p.enableTiming( timingTree );
   }

   void enumerate( uint_t level ) const
   {
      uint_t counterDoFs = hyteg::numberOfLocalDoFs< Tag >( *( getStorage() ), level );

      std::vector< uint_t > doFsPerRank = walberla::mpi::allGather( counterDoFs );

      ValueType offset = 0;

      for ( uint_t i = 0; i < uint_c( walberla::MPIManager::instance()->rank() ); ++i )
      {
         offset += static_cast< ValueType >( doFsPerRank[i] );
      }

      uvw.u.enumerate( level, offset );
      uvw.v.enumerate( level, offset );
      uvw.w.enumerate( level, offset );
      p.enumerate( level, offset );
   }

   VelocityFunction_T uvw;
   PressureFunction_T p;
};

} // namespace hyteg
