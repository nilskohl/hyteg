/*
 * Copyright (c) 2017-2019 Dominik Thoennes.
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

#include "core/DataTypes.h"

#include "hyteg/solvers/Solver.hpp"
#include "hyteg/types/flags.hpp"
#include "hyteg/solvers/Smoothables.hpp"

namespace hyteg {

template < class OperatorType >
class GaussSeidelSmoother : public Solver< OperatorType >
{
 public:
   GaussSeidelSmoother()
   : flag_( hyteg::Inner | hyteg::NeumannBoundary )
   {}

   void solve( const OperatorType&                   A,
               const typename OperatorType::srcType& x,
               const typename OperatorType::dstType& b,
               const walberla::uint_t                level ) override
   {
      if ( const auto* A_gs = dynamic_cast< const GSSmoothable< typename OperatorType::srcType >* >( &A ) )
      {
         A_gs->smooth_gs( x, b, level, flag_ );
      }
      else
      {
         throw std::runtime_error( "The Gauss-Seidel Operator requires the GSSmoothable interface." );
      }
   }

 private:
   DoFType flag_;
};

} // namespace hyteg