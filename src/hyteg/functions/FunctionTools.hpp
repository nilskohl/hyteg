/*
 * Copyright (c) 2024 Ponsuganth Ilangovan P
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

#include "hyteg/composites/P2P1TaylorHoodFunction.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"
#include "hyteg/p1functionspace/P1VectorFunction.hpp"
#include "hyteg/p2functionspace/P2Function.hpp"
#include "hyteg/p2functionspace/P2VectorFunction.hpp"

namespace hyteg {

template < template < typename > class FunctionType, typename value_t1, typename value_t2 >
void bccpy( const FunctionType< value_t1 >& src, FunctionType< value_t2 >& dst )
{
   if constexpr ( std::is_same_v< FunctionType< value_t1 >, P1VectorFunction< value_t1 > > ||
                  std::is_same_v< FunctionType< value_t2 >, P1VectorFunction< value_t2 > > ||
                  std::is_same_v< FunctionType< value_t1 >, P2VectorFunction< value_t1 > > ||
                  std::is_same_v< FunctionType< value_t2 >, P2VectorFunction< value_t2 > > )
   {
      uint_t dim = src.getDimension();
      for ( uint_t iDim = 0U; iDim < dim; iDim++ )
      {
         dst.component( iDim ).setBoundaryCondition( src.component( iDim ).getBoundaryCondition() );
      }
   }
   else if constexpr ( std::is_same_v< FunctionType< value_t1 >, P1Function< value_t1 > > ||
                       std::is_same_v< FunctionType< value_t2 >, P1Function< value_t2 > > ||
                       std::is_same_v< FunctionType< value_t1 >, P2Function< value_t1 > > ||
                       std::is_same_v< FunctionType< value_t2 >, P2Function< value_t2 > > )
   {
      dst.setBoundaryCondition( src.getBoundaryCondition() );
   }
   else if constexpr ( std::is_same_v< FunctionType< value_t1 >, P2P1TaylorHoodFunction< value_t1 > > ||
                       std::is_same_v< FunctionType< value_t2 >, P2P1TaylorHoodFunction< value_t2 > > )
   {
      uint_t dim = src.uvw().getDimension();
      for ( uint_t iDim = 0U; iDim < dim; iDim++ )
      {
         dst.uvw().component( iDim ).setBoundaryCondition( src.uvw().component( iDim ).getBoundaryCondition() );
      }
   }
   else
   {
      WALBERLA_ABORT( "bccpy() called with unsupported function type!" );
   }
}

} // namespace hyteg