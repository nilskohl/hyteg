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
#include "core/Abort.h"

#include "hyteg/Levelinfo.hpp"
#include "hyteg/indexing/Common.hpp"
#include "hyteg/indexing/MacroCellIndexing.hpp"

namespace hyteg {
namespace celldof {

using walberla::uint_t;
using indexing::Index;

enum class CellType : uint_t
{
  WHITE_UP,
  BLUE_UP,
  GREEN_UP,
  WHITE_DOWN,
  BLUE_DOWN,
  GREEN_DOWN
};

const std::array< CellType, 6 > allCellTypes = {{ CellType::WHITE_UP, CellType::BLUE_UP, CellType::GREEN_UP,
                                                  CellType::WHITE_DOWN, CellType::BLUE_DOWN, CellType::GREEN_DOWN }};

namespace macrocell {

inline uint_t numCellsPerRowByType( const uint_t & level, const CellType & cellType )
{
  switch ( cellType )
  {
    case CellType::WHITE_UP:
      return levelinfo::num_microedges_per_edge( level );
    case CellType::BLUE_UP:
      return levelinfo::num_microedges_per_edge( level ) - 1;
    case CellType::GREEN_UP:
      return levelinfo::num_microedges_per_edge( level ) - 1;
    case CellType::WHITE_DOWN:
      return levelinfo::num_microedges_per_edge( level ) - 2;
    case CellType::BLUE_DOWN:
      return levelinfo::num_microedges_per_edge( level ) - 1;
    case CellType::GREEN_DOWN:
      return levelinfo::num_microedges_per_edge( level ) - 1;
    default:
      WALBERLA_ABORT( "Invalid cell type" );
      return 0;
  }
}

/// Returns an array of the four logical micro-vertex-indices that span the micro-cell of the given indices and cell type.
inline std::array< Index, 4 > getMicroVerticesFromMicroCell( const Index & microCellIndex, const CellType & microCellType )
{
  const uint_t cellX = microCellIndex.x();
  const uint_t cellY = microCellIndex.y();
  const uint_t cellZ = microCellIndex.z();

  switch ( microCellType )
  {
  case CellType::WHITE_UP:
    return std::array< Index, 4 >( {{
      Index( cellX    , cellY    , cellZ     ),
      Index( cellX + 1, cellY    , cellZ     ),
      Index( cellX    , cellY + 1, cellZ     ),
      Index( cellX    , cellY    , cellZ + 1 )
    }} );
  case CellType::BLUE_UP:
    return std::array< Index, 4 >( {{
      Index( cellX + 1, cellY    , cellZ     ),
      Index( cellX + 1, cellY + 1, cellZ     ),
      Index( cellX    , cellY + 1, cellZ     ),
      Index( cellX + 1, cellY    , cellZ + 1 )
    }} );
  case CellType::GREEN_UP:
    return std::array< Index, 4 >( {{
      Index( cellX + 1, cellY    , cellZ     ),
      Index( cellX    , cellY + 1, cellZ     ),
      Index( cellX + 1, cellY    , cellZ + 1 ),
      Index( cellX    , cellY    , cellZ + 1 )
    }} );
  case CellType::WHITE_DOWN:
    return std::array< Index, 4 >( {{
      Index( cellX + 1, cellY + 1, cellZ     ),
      Index( cellX + 1, cellY + 1, cellZ + 1 ),
      Index( cellX    , cellY + 1, cellZ + 1 ),
      Index( cellX + 1, cellY    , cellZ + 1 )
    }} );
  case CellType::BLUE_DOWN:
    return std::array< Index, 4 >( {{
      Index( cellX + 1, cellY    , cellZ + 1 ),
      Index( cellX    , cellY + 1, cellZ + 1 ),
      Index( cellX    , cellY    , cellZ + 1 ),
      Index( cellX    , cellY + 1, cellZ     )
    }} );
  case CellType::GREEN_DOWN:
    return std::array< Index, 4 >( {{
      Index( cellX    , cellY + 1, cellZ     ),
      Index( cellX + 1, cellY + 1, cellZ     ),
      Index( cellX + 1, cellY    , cellZ + 1 ),
      Index( cellX    , cellY + 1, cellZ + 1 )
    }} );
  default:
    WALBERLA_ABORT( "Not implemented for this cell type." );
    break;
  }
  return std::array< Index, 4 >();
}

// Iterators

class Iterator : public indexing::CellIterator
{
public:
    Iterator( const uint_t & level, const CellType & cellType, const uint_t & offsetToCenter = 0 ) :
      CellIterator( numCellsPerRowByType( level, cellType ), offsetToCenter )
    {}
};

}
}
}