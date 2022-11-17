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
#include "core/debug/Debug.h"

#include "hyteg/types/pointnd.hpp"
#include "hyteg/types/types.hpp"

using walberla::uint_t;

namespace hyteg {
namespace indexing {

/// Helper function to create a 'tuple' from two integers taking less than 5 bits of space.
/// Allows for more readable switch statements in some cases.
inline constexpr uint_t tup4( const uint_t& a, const uint_t& b )
{
#if 0
   assert( a < ( 1 << 4 ) );
   assert( b < ( 1 << 4 ) );
#endif
   return a << 4 | b;
}

inline constexpr uint_t tup4( const uint_t& a, const uint_t& b, const uint_t& c )
{
#if 0
   assert( a < ( 1 << 4 ) );
   assert( b < ( 1 << 4 ) );
   assert( c < ( 1 << 4 ) );
#endif
   return a << 8 | b << 4 | c;
}

class IndexIncrement : public PointND< int, 3 >
{
 public:
   IndexIncrement()
   : PointND< int, 3 >()
   {}
   IndexIncrement( const IndexIncrement& other )
   : PointND< int, 3 >( other )
   {}

   IndexIncrement( const int& x, const int& y, const int& z )
   {
      vector_[0] = x;
      vector_[1] = y;
      vector_[2] = z;
   }

   const int& x() const { return vector_[0]; }
   int&       x() { return vector_[0]; }

   const int& y() const { return vector_[1]; }
   int&       y() { return vector_[1]; }

   const int& z() const { return vector_[2]; }
   int&       z() { return vector_[2]; }

   void setxyz( const int& x, const int& y, const int& z )
   {
      vector_[0] = x;
      vector_[1] = y;
      vector_[2] = z;
   }

   IndexIncrement& operator+=( const IndexIncrement& increment )
   {
      x() += increment.x();
      y() += increment.y();
      z() += increment.z();
      return *this;
   }
};

/// Wrapper around Point3D for convenient access to logical indices.
class Index : public PointND< idx_t, 3 >
{
 public:
   Index()
   : PointND< idx_t, 3 >()
   {}
   Index( const Index& other )
   : PointND< idx_t, 3 >( other )
   {}

   static Index max()
   {
      return Index(
          std::numeric_limits< idx_t >::max(), std::numeric_limits< idx_t >::max(), std::numeric_limits< idx_t >::max() );
   }

   Index( const idx_t& x, const idx_t& y, const idx_t& z )
   {
      vector_[0] = x;
      vector_[1] = y;
      vector_[2] = z;
   }

   const idx_t& x() const { return vector_[0]; }
   idx_t&       x() { return vector_[0]; }

   const idx_t& y() const { return vector_[1]; }
   idx_t&       y() { return vector_[1]; }

   const idx_t& z() const { return vector_[2]; }
   idx_t&       z() { return vector_[2]; }

   const idx_t& col() const { return vector_[0]; }
   idx_t&       col() { return vector_[0]; }

   const idx_t& row() const { return vector_[1]; }
   idx_t&       row() { return vector_[1]; }

   const idx_t& dep() const { return vector_[2]; }
   idx_t&       dep() { return vector_[2]; }

   Index& operator+=( const IndexIncrement& increment )
   {
      WALBERLA_ASSERT_GREATER_EQUAL( (idx_t) x() + increment.x(), 0 );
      WALBERLA_ASSERT_GREATER_EQUAL( (idx_t) y() + increment.y(), 0 );
      WALBERLA_ASSERT_GREATER_EQUAL( (idx_t) z() + increment.z(), 0 );
      x() += increment.x();
      y() += increment.y();
      z() += increment.z();
      return *this;
   }

   Index& operator+=( const Index& other )
   {
      x() += other.x();
      y() += other.y();
      z() += other.z();
      return *this;
   }
};

inline bool operator<( const Index& lhs, const Index& rhs )
{
   return lhs.z() < rhs.z() || ( lhs.z() == rhs.z() && lhs.y() < rhs.y() ) ||
          ( lhs.z() == rhs.z() && lhs.y() == rhs.y() && lhs.x() < rhs.x() );
}

inline bool operator<( const IndexIncrement& lhs, const IndexIncrement& rhs )
{
   return lhs.z() < rhs.z() || ( lhs.z() == rhs.z() && lhs.y() < rhs.y() ) ||
          ( lhs.z() == rhs.z() && lhs.y() == rhs.y() && lhs.x() < rhs.x() );
}

inline Index operator+( Index lhs, const Index& rhs )
{
   lhs += rhs;
   return lhs;
}

inline Index operator+( Index lhs, const IndexIncrement& rhs )
{
   lhs += rhs;
   return lhs;
}

inline Index operator+( const IndexIncrement& lhs, Index rhs )
{
   rhs += lhs;
   return rhs;
}

inline IndexIncrement operator+( IndexIncrement lhs, const IndexIncrement& rhs )
{
   lhs += rhs;
   return lhs;
}

inline Index operator*( Index lhs, const idx_t& scalar )
{
   lhs.x() *= scalar;
   lhs.y() *= scalar;
   lhs.z() *= scalar;
   return lhs;
}

inline Index operator*( const idx_t& scalar, Index rhs )
{
   rhs.x() *= scalar;
   rhs.y() *= scalar;
   rhs.z() *= scalar;
   return rhs;
}

inline Index operator-( const Index& lhs, const Index& rhs )
{
   return Index( (idx_t) lhs.x() - (idx_t) rhs.x(), (idx_t) lhs.y() - (idx_t) rhs.y(), (idx_t) lhs.z() - (idx_t) rhs.z() );
}

inline IndexIncrement operator-( const IndexIncrement& lhs, const IndexIncrement& rhs )
{
   return IndexIncrement( (int) lhs.x() - (int) rhs.x(), (int) lhs.y() - (int) rhs.y(), (int) lhs.z() - (int) rhs.z() );
}

inline bool operator==( const Index& lhs, const Index& rhs )
{
   return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z();
}

inline bool operator==( const IndexIncrement& lhs, const IndexIncrement& rhs )
{
   return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z();
}

inline bool operator!=( const IndexIncrement& lhs, const IndexIncrement& rhs )
{
   return !( lhs == rhs );
}

inline std::ostream& operator<<( std::ostream& os, const Index& index )
{
   os << "( " << index.x() << ", " << index.y() << ", " << index.z() << " )";
   return os;
}

inline std::ostream& operator<<( std::ostream& os, const IndexIncrement& indexIncrement )
{
   os << "( " << indexIncrement.x() << ", " << indexIncrement.y() << ", " << indexIncrement.z() << " )";
   return os;
}

} // namespace indexing
} // namespace hyteg
