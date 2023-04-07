/*
 * Copyright (c) 2019 Nils Kohl, Dominik Thoennes.
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

#pragma once
#include "core/DataTypes.h"
#include "core/Macros.h"
#define RESTRICT WALBERLA_RESTRICT

using walberla::real_t;
using walberla::real_c;

namespace hyteg {
namespace P2 {
namespace macroface {
namespace generated {

void prolongate_2D_macroface_P2_push_from_vertexdofs(real_t  * RESTRICT _data_edgeFineDst_X, real_t  * RESTRICT _data_edgeFineDst_XY, real_t  * RESTRICT _data_edgeFineDst_Y, real_t  * RESTRICT _data_vertexCoarseSrc, real_t  * RESTRICT _data_vertexFineDst, int coarse_level, double num_neighbor_faces_edge0, double num_neighbor_faces_edge1, double num_neighbor_faces_edge2, double num_neighbor_faces_vertex0, double num_neighbor_faces_vertex1, double num_neighbor_faces_vertex2);

} // namespace generated
} // namespace macroface
} // namespace P2
} // namespace hyteg