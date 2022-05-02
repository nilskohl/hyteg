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

#include "hyteg/mixedoperators/MixedDummyOperators.hpp"
#include "hyteg/mixedoperators/P0ToP1Operator.hpp"
#include "hyteg/mixedoperators/P1ToP0Operator.hpp"
#include "hyteg/p0functionspace/P0Function.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"
#include "hyteg/p1functionspace/P1VectorFunction.hpp"

namespace hyteg {

using walberla::real_t;

template < class operX_t, class operY_t, class operZ_t >
class P1VectorToP0ScalarOperator : public Operator< P1VectorFunction< real_t >, P0Function< real_t > >
{
 public:
   P1VectorToP0ScalarOperator( const std::shared_ptr< PrimitiveStorage >& storage, size_t minLevel, size_t maxLevel )
   : Operator( storage, minLevel, maxLevel )
   , operX( storage, minLevel, maxLevel )
   , operY( storage, minLevel, maxLevel )
   , operZ( storage, minLevel, maxLevel )
   {}

   void apply( const P1VectorFunction< real_t >& src,
               const P0Function< real_t >&       dst,
               size_t                            level,
               DoFType                           flag,
               UpdateType                        updateType = Replace ) const
   {
      std::array< UpdateType, 3 > ut = { updateType, Add, Add };
      operX.apply( src[0], dst, level, flag, ut[0] );
      operY.apply( src[1], dst, level, flag, ut[1] );
      if ( src.getDimension() == 3 )
         operZ.apply( src[2], dst, level, flag, ut[2] );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const P1VectorFunction< idx_t >&            src,
                  const P0Function< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const
   {
      operX.toMatrix( mat, src[0], dst, level, flag );
      operY.toMatrix( mat, src[1], dst, level, flag );
      if ( src.getDimension() == 3 )
         operZ.toMatrix( mat, src[2], dst, level, flag );
   }

 private:
   operX_t operX;
   operY_t operY;
   operZ_t operZ;
};

//// Some operators we might use more often than others
typedef P1VectorToP0ScalarOperator< P1ToP0ConstantDivxOperator, P1ToP0ConstantDivyOperator, P1ToP0ConstantDivzOperator >
    P1ToP0ConstantDivOperator;

typedef P1VectorToP0ScalarOperator< P1ToP0ConstantP1EDGVectorLaplaceXCouplingOperator,
                                    P1ToP0ConstantP1EDGVectorLaplaceYCouplingOperator,
                                    P1ToP0ConstantP1EDGVectorLaplaceZCouplingOperator >
    P1ToP0ConstantP1EDGVectorLaplaceCouplingOperator;

typedef P1VectorToP0ScalarOperator< P1ToP0ConstantP1EDGVectorMassXCouplingOperator,
                                    P1ToP0ConstantP1EDGVectorMassYCouplingOperator,
                                    P1ToP0ConstantP1EDGVectorMassZCouplingOperator >
    P1ToP0ConstantP1EDGVectorMassCouplingOperator;

} // namespace hyteg
