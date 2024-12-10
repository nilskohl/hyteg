/*
 * Copyright (c) 2024 Benjamin Mann.
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

namespace hyteg {
namespace surrogate {

using walberla::uint_t;

namespace polynomial {

// helper function to compute binomial coefficients
template < uint_t n, uint_t k >
static constexpr uint_t binom = binom< n - 1, k - 1 > * n / k;
template < uint_t n >
static constexpr uint_t binom< n, 0 > = 1;
template < uint_t n >
static constexpr uint_t binom< n, n > = 1;

// dimension of polynomial space of degree Q over R^D
template < uint_t D, uint_t Q >
static constexpr uint_t dimP = binom< D + Q, D >;

// monomial basis of polynomial space, given by the exponents of the monomials
template < uint8_t D, uint8_t Q >
struct Basis : public std::array< std::array< uint8_t, 3 >, dimP< D, Q > >
{
   constexpr Basis()
   : std::array< std::array< uint8_t, 3 >, dimP< D, Q > >{}
   {
      // 1d basis
      for ( uint8_t i = 0; i <= Q; ++i )
      {
         ( *this )[i] = { i, 0, 0 };
      }
      if constexpr ( D == 1 )
      {
         return;
      }
      // extend to 2d
      auto ij = dimP< 1, Q >;
      for ( uint8_t i = 0; i < Q; ++i )
      {
         for ( uint8_t j = 1; i + j <= Q; ++j )
         {
            ( *this )[ij++] = { i, j, 0 };
         }
      }
      if constexpr ( D == 2 )
      {
         return;
      }
      // extend to 3d
      auto ijk = dimP< 2, Q >;
      for ( uint8_t i = 0; i < Q; ++i )
      {
         for ( uint8_t k = 1; i + k <= Q; ++k )
         {
            ( *this )[ijk++] = { i, 0, k };
         }
      }
      for ( uint8_t i = 0; i < Q; ++i )
      {
         for ( uint8_t j = 1; i + j < Q; ++j )
         {
            for ( uint8_t k = 1; i + j + k <= Q; ++k )
            {
               ( *this )[ijk++] = { i, j, k };
            }
         }
      }
   }

   // evaluate the i-th basis function at x
   constexpr double eval( uint_t i, const std::array< double, 3 >& x ) const
   {
      double val = 1.0;
      for ( uint8_t d = 0; d < D; ++d )
      {
         for ( uint8_t p = 0; p < ( *this )[i][d]; ++p )
         {
            val *= x[d];
         }
      }
      return val;
   }
};

static constexpr uint8_t d = 2;
static constexpr uint8_t q = 2;

static constexpr auto basis = Basis< d, q >();
static constexpr auto n     = basis.size();
static constexpr auto b0    = basis[0];
static constexpr auto b5    = basis[5];

/* Coordinate system for polynomial evaluation.
 ! Different from the coordinates of PDE domain !
*/
struct Coordinates
{
   constexpr Coordinates( uint_t lvl )
   : scaling( 4.0 / double( ( 1 << lvl ) - 1 ) )
   {}
   // convert index i to coordinate x ∈ [-1,3]
   constexpr double x( uint_t i ) const { return scaling * i - 1.0; }
   // convert indices i,j,k to coordinate x ∈ [-1,3]^3
   constexpr std::array< double, 3 > x( uint_t i, uint_t j, uint_t k ) const { return { x( i ), x( j ), x( k ) }; }

   // convert index i ∈ {0,..., 2^lvl - 1} to coordinate x ∈ [-1,3]
   const double scaling;
};

// polynomials of degree Q over R^D
template < uint8_t D, uint8_t Q >
class Polynomial
{
 public:
   static constexpr uint8_t X = 0;
   static constexpr uint8_t Y = 1;
   static constexpr uint8_t Z = 2;

   static constexpr uint_t nc = dimP< 1, Q >; // number of coefficients

   inline constexpr Polynomial()
   : c{ 0.0 }
   , restriction()
   {}

   inline constexpr Polynomial( const std::array< double, nc >& coeffs )
   : c{ coeffs }
   , restriction()
   {}

   template < uint8_t YorZ >
   inline constexpr void fix_coordinate( const double val )
   {
      static_assert( YorZ == Y || YorZ == Z );
      if constexpr ( YorZ == Y )
      {
         static_assert( D >= 2 );
         if constexpr ( D == 2 )
         {
            // todo restrict polynomial to lower dimensional subset
            // starting index of 2d-part of basis
            double yn = 1.0; // y^n
            for ( uint_t ij = restriction.nc; ij < nc; ++ij )
            {
               if ( basis[ij][Y] > basis[ij - 1][Y] )
               {
                  yn *= val;
               }
               c[d] = 0.0;
            }
         }
         else
         {
            restriction.fix_coordinate< Y >( val );
         }
      }
      else
      {
         static_assert( D == 3 );
         // todo restrict polynomial to lower dimensional subset
      }
   }

   // evaluate 1d polynomial using Horner's method
   inline constexpr double eval( const double x ) const
   {
      if constexpr ( D == 1 )
      {
         auto val = c[nc - 1];
         for ( int i = nc - 2; i >= 0; --i )
         {
            val = val * x + c[i];
         }
         return val;
      }
      else
      {
         return restriction.eval( x );
      }
   }

//  private:
   static constexpr Basis< D, Q > basis;

   std::array< double, nc > c; // coefficients

   Polynomial< D - 1, Q > restriction; // restriction to lower dimension
};

template < uint8_t Q >
class Polynomial< 0, Q >
{};

// static constexpr Polynomial< 1, 2 > p( { 1.0, 2.0, 3.0 } );
// static constexpr auto               val = p.eval( 2 );

// static constexpr Coordinates coords( 2 );
// static constexpr auto x = coords.x( 2 );

// static constexpr uint8_t d = 1;
// static constexpr uint8_t q = 2;

// static constexpr auto basis = Basis< d, q >();
// static constexpr auto n     = basis.size();
// static constexpr auto b0    = basis[0];
// static constexpr auto b5    = basis[17];
// static constexpr std::array<double,3> xyz{2.0, 3.0, 4.0};
// static constexpr auto p = basis.eval( 17, xyz );

} // namespace polynomial
} // namespace surrogate
} // namespace hyteg
