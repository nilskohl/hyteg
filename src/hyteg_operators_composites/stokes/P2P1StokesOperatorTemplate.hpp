/*
* Copyright (c) 2017-2024 Nils Kohl.
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
#include "hyteg_operators_composites/divergence/P2ToP1DivergenceOperator.hpp"
#include "hyteg_operators_composites/gradient/P1ToP2GradientOperator.hpp"
#include "hyteg_operators_composites/viscousblock/P2ViscousBlockFullOperator.hpp"

namespace hyteg {
namespace operatorgeneration {
namespace detail {

/// PLEASE DO NOT USE THIS TEMPLATE DIRECTLY. Internals are subject to change.
///
/// -> Instead, use the aliases outside of the _detail_ namespace.
///
/// Class template for the construction of Stokes operators of the form
///
///         /        \
///     K = |  A  Bᵀ |
///         |  B  0  |
///         \        /
///
/// where the operators A, Bᵀ, and B are template parameters, and A does not depend on a scalar viscosity function.
///
/// \tparam ViscousOperator_T    A
/// \tparam GradientOperator_T   Bᵀ
/// \tparam DivergenceOperator_T B
///
template < typename ViscousOperator_T, typename GradientOperator_T, typename DivergenceOperator_T >
class P2P1StokesConstViscOperatorTemplate : public Operator< P2P1TaylorHoodFunction< real_t >, P2P1TaylorHoodFunction< real_t > >
{
 public:
   P2P1StokesConstViscOperatorTemplate( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator( storage, minLevel, maxLevel )
   , A( storage, minLevel, maxLevel )
   , BT( storage, minLevel, maxLevel )
   , B( storage, minLevel, maxLevel )
   {}

   void apply( const P2P1TaylorHoodFunction< real_t >& src,
               const P2P1TaylorHoodFunction< real_t >& dst,
               const uint_t                            level,
               const DoFType                           flag,
               const UpdateType                        updateType = Replace ) const
   {
      A.apply( src.uvw(), dst.uvw(), level, flag, updateType );
      BT.apply( src.p(), dst.uvw(), level, flag, Add );
      B.apply( src.uvw(), dst.p(), level, flag, updateType );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const P2P1TaylorHoodFunction< idx_t >&      src,
                  const P2P1TaylorHoodFunction< idx_t >&      dst,
                  size_t                                      level,
                  DoFType                                     flag ) const
   {
      A.toMatrix( mat, src.uvw(), dst.uvw(), level, flag );
      BT.toMatrix( mat, src.p(), dst.uvw(), level, flag );
      B.toMatrix( mat, src.uvw(), dst.p(), level, flag );
   }

   ViscousOperator_T    A;
   GradientOperator_T   BT;
   DivergenceOperator_T B;
};

/// PLEASE DO NOT USE THIS TEMPLATE DIRECTLY. Internals are subject to change.
///
/// -> Instead, use the aliases outside of the _detail_ namespace.
///
/// Class template for the construction of Stokes operators of the form
///
///         /        \
///     K = |  A  Bᵀ |
///         |  B  0  |
///         \        /
///
/// where the operators A, Bᵀ, and B are template parameters, and A depends on a scalar viscosity function.
///
/// \tparam ViscousOperator_T    A
/// \tparam GradientOperator_T   Bᵀ
/// \tparam DivergenceOperator_T B
///
template < typename ViscousOperator_T, typename GradientOperator_T, typename DivergenceOperator_T >
class P2P1StokesVarViscOperatorTemplate : public Operator< P2P1TaylorHoodFunction< real_t >, P2P1TaylorHoodFunction< real_t > >
{
 public:
   P2P1StokesVarViscOperatorTemplate( const std::shared_ptr< PrimitiveStorage >& storage,
                                      uint_t                                     minLevel,
                                      uint_t                                     maxLevel,
                                      const P2Function< real_t >&                mu )
   : Operator( storage, minLevel, maxLevel )
   , A( storage, minLevel, maxLevel, mu )
   , BT( storage, minLevel, maxLevel )
   , B( storage, minLevel, maxLevel )
   {}

   void apply( const P2P1TaylorHoodFunction< real_t >& src,
               const P2P1TaylorHoodFunction< real_t >& dst,
               const uint_t                            level,
               const DoFType                           flag,
               const UpdateType                        updateType = Replace ) const
   {
      A.apply( src.uvw(), dst.uvw(), level, flag, updateType );
      BT.apply( src.p(), dst.uvw(), level, flag, Add );
      B.apply( src.uvw(), dst.p(), level, flag, updateType );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const P2P1TaylorHoodFunction< idx_t >&      src,
                  const P2P1TaylorHoodFunction< idx_t >&      dst,
                  size_t                                      level,
                  DoFType                                     flag ) const
   {
      A.toMatrix( mat, src.uvw(), dst.uvw(), level, flag );
      BT.toMatrix( mat, src.p(), dst.uvw(), level, flag );
      B.toMatrix( mat, src.uvw(), dst.p(), level, flag );
   }

   ViscousOperator_T    A;
   GradientOperator_T   BT;
   DivergenceOperator_T B;
};

} // namespace detail
} // namespace operatorgeneration
} // namespace hyteg