/*
 * Copyright (c) 2017-2019 Daniel Drzisga, Dominik Thoennes.
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

namespace hyteg {

template < class OperatorType >
class JacobiPreconditioner : public Solver< OperatorType >
{
 public:
   typedef typename OperatorType::srcType FunctionType;
   JacobiPreconditioner( const std::shared_ptr< PrimitiveStorage >& storage, size_t minLevel, size_t maxLevel, uint_t iterations )
   : iterations_( iterations )
   , tmp_( "jac_tmp", storage, minLevel, maxLevel )
   , flag_( hyteg::Inner | hyteg::NeumannBoundary )
   {}

   // y = M^{-1} * x
   void solve( const OperatorType& A, const FunctionType& x, const FunctionType& b, const uint_t level ) override
   {
      b.assign( {1.0}, {x}, level, flag_ );

      for( uint_t i = 0; i < iterations_; ++i )
      {
         tmp_.assign( {1.0}, {b}, level, flag_ );
         A.smooth_jac( b, x, tmp_, level, flag_ );
      }
   }

 private:
   uint_t       iterations_;
   FunctionType tmp_;
   hyteg::DoFType flag_;
};

} // namespace hyteg