/*
 * Copyright (c) 2017-2019 Dominik Thoennes, Nils Kohl.
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

#include <map>
#include <set>

namespace hyteg {
namespace indexing {

using walberla::uint_t;

const std::map< uint_t, std::set< uint_t > > cellLocalEdgeIDsToCellLocalNeighborFaceIDs = {
  { 0, std::set< uint_t >( { 0, 1 } ) },
  { 1, std::set< uint_t >( { 0, 2 } ) },
  { 2, std::set< uint_t >( { 0, 3 } ) },
  { 3, std::set< uint_t >( { 1, 2 } ) },
  { 4, std::set< uint_t >( { 1, 3 } ) },
  { 5, std::set< uint_t >( { 2, 3 } ) }
};

const std::map< uint_t, std::set< uint_t > > cellLocalFaceIDsToSpanningVertexIDs = {
  { 0, std::set< uint_t >( { 0, 1, 2 } ) },
  { 1, std::set< uint_t >( { 0, 1, 3 } ) },
  { 2, std::set< uint_t >( { 0, 2, 3 } ) },
  { 3, std::set< uint_t >( { 1, 2, 3 } ) }
};


}
}