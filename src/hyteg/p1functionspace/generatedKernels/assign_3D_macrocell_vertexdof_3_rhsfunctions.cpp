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

#include "assign_3D_macrocell_vertexdof_3_rhsfunctions.hpp"
#include "core/DataTypes.h"

namespace hyteg {
namespace vertexdof {
namespace macrocell {
namespace generated {

template < typename ValueType >
static void assign_3D_macrocell_vertexdof_3_rhs_functions_level_any(ValueType * RESTRICT _data_p1FaceDst, ValueType * RESTRICT _data_p1FaceSrc0, ValueType * RESTRICT _data_p1FaceSrc1, ValueType * RESTRICT _data_p1FaceSrc2, ValueType c0, ValueType c1, ValueType c2, int level)
{
   for (int ctr_3 = 1; ctr_3 < (1 << (level)); ctr_3 += 1)
   {
      for (int ctr_2 = 1; ctr_2 < -ctr_3 + (1 << (level)); ctr_2 += 1)
      {
         // cell (inner)
         for (int ctr_1 = 1; ctr_1 < -ctr_2 - ctr_3 + (1 << (level)); ctr_1 += 1)
         {
            const ValueType xi_3 = c0*_data_p1FaceSrc0[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const ValueType xi_4 = c1*_data_p1FaceSrc1[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const ValueType xi_5 = c2*_data_p1FaceSrc2[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            _data_p1FaceDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))] = xi_3 + xi_4 + xi_5;
         }
      }
   }
}


template < typename ValueType >
void assign_3D_macrocell_vertexdof_3_rhs_functions(ValueType * RESTRICT _data_p1FaceDst, ValueType * RESTRICT _data_p1FaceSrc0, ValueType * RESTRICT _data_p1FaceSrc1, ValueType * RESTRICT _data_p1FaceSrc2, ValueType c0, ValueType c1, ValueType c2, int level)
{
    switch( level )
    {

    default:
        assign_3D_macrocell_vertexdof_3_rhs_functions_level_any(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, _data_p1FaceSrc2, c0, c1, c2, level);
        break;
    }
}

// ========================
//  explicit instantiation
// ========================
template void assign_3D_macrocell_vertexdof_3_rhs_functions<walberla::float64>(walberla::float64 * RESTRICT _data_p1FaceDst, walberla::float64 * RESTRICT _data_p1FaceSrc0, walberla::float64 * RESTRICT _data_p1FaceSrc1, walberla::float64 * RESTRICT _data_p1FaceSrc2, walberla::float64 c0, walberla::float64 c1, walberla::float64 c2, int level);
template void assign_3D_macrocell_vertexdof_3_rhs_functions<walberla::float32>(walberla::float32 * RESTRICT _data_p1FaceDst, walberla::float32 * RESTRICT _data_p1FaceSrc0, walberla::float32 * RESTRICT _data_p1FaceSrc1, walberla::float32 * RESTRICT _data_p1FaceSrc2, walberla::float32 c0, walberla::float32 c1, walberla::float32 c2, int level);
#ifdef WALBERLA_BUILD_WITH_HALF_PRECISION_SUPPORT
template void assign_3D_macrocell_vertexdof_3_rhs_functions<walberla::float16>(walberla::float16 * RESTRICT _data_p1FaceDst, walberla::float16 * RESTRICT _data_p1FaceSrc0, walberla::float16 * RESTRICT _data_p1FaceSrc1, walberla::float16 * RESTRICT _data_p1FaceSrc2, walberla::float16 c0, walberla::float16 c1, walberla::float16 c2, int level);
#endif

} // namespace generated
} // namespace macrocell
} // namespace vertexdof
} // namespace hyteg