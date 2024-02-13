/*
 * Copyright (c) 2019-2023 Nils Kohl, Dominik Thoennes, Michael Zikeli.
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

//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "add_2D_macroface_vertexdof_1_rhsfunction.hpp"
#include "core/DataTypes.h"

namespace hyteg {
namespace vertexdof {
namespace macroface {
namespace generated {

template < typename ValueType >
static void add_2D_macroface_vertexdof_1_rhs_function_level_any(ValueType * RESTRICT _data_p1FaceDst, ValueType * RESTRICT _data_p1FaceSrc, ValueType c, int level)
{
   for (int ctr_2 = 1; ctr_2 < (1 << (level)); ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + (1 << (level)); ctr_1 += 1)
      {
         const auto xi_3 = c*_data_p1FaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const auto xi_4 = _data_p1FaceDst[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}


template < typename ValueType >
void add_2D_macroface_vertexdof_1_rhs_function(ValueType * RESTRICT _data_p1FaceDst, ValueType * RESTRICT _data_p1FaceSrc, ValueType c, int level)
{
    switch( level )
    {

    default:
        add_2D_macroface_vertexdof_1_rhs_function_level_any(_data_p1FaceDst, _data_p1FaceSrc, c, level);
        break;
    }
}

// ========================
//  explicit instantiation
// ========================
template void add_2D_macroface_vertexdof_1_rhs_function<walberla::float64>(walberla::float64 * RESTRICT _data_p1FaceDst, walberla::float64 * RESTRICT _data_p1FaceSrc, walberla::float64 c, int level);
template void add_2D_macroface_vertexdof_1_rhs_function<walberla::float32>(walberla::float32 * RESTRICT _data_p1FaceDst, walberla::float32 * RESTRICT _data_p1FaceSrc, walberla::float32 c, int level);
#ifdef WALBERLA_BUILD_WITH_HALF_PRECISION_SUPPORT
template void add_2D_macroface_vertexdof_1_rhs_function<walberla::float16>(walberla::float16 * RESTRICT _data_p1FaceDst, walberla::float16 * RESTRICT _data_p1FaceSrc, walberla::float16 c, int level);
#endif

} // namespace generated
} // namespace macroface
} // namespace vertexdof
} // namespace hyteg