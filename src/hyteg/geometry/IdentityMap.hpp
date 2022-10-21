/*
 * Copyright (c) 2017-2019 Daniel Drzisga, Dominik Thoennes.
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

#include "GeometryMap.hpp"

namespace hyteg {

class IdentityMap : public GeometryMap
{
 public:
   IdentityMap() {}

   void evalF( const Point3D& x, Point3D& Fx ) const override final { Fx = x; }

   void evalFinv( const Point3D& xPhys, Point3D& xComp ) const override final { xComp = xPhys; }

   void evalDF( const Point3D&, Matrix2r& DFx ) const override final
   {
      DFx( 0, 0 ) = 1.0;
      DFx( 0, 1 ) = 0.0;
      DFx( 1, 0 ) = 0.0;
      DFx( 1, 1 ) = 1.0;
   }

   real_t evalDF( const Point3D&, Matrix3r& DFx ) const override final
   {
      DFx( 0, 0 ) = 1.0;
      DFx( 0, 1 ) = 0.0;
      DFx( 0, 2 ) = 0.0;

      DFx( 1, 0 ) = 0.0;
      DFx( 1, 1 ) = 1.0;
      DFx( 1, 2 ) = 0.0;

      DFx( 2, 0 ) = 0.0;
      DFx( 2, 1 ) = 0.0;
      DFx( 2, 2 ) = 1.0;

      return 1.0;
   }

   void evalDFinv( const Point3D&, Matrix2r& DFinvx ) const override final
   {
      DFinvx( 0, 0 ) = 1.0;
      DFinvx( 0, 1 ) = 0.0;
      DFinvx( 1, 0 ) = 0.0;
      DFinvx( 1, 1 ) = 1.0;
   }

   bool verifyPointPairing( const Point3D& computationalCoordinates, const Point3D& physicalCoordinates ) const override final
   {
      return true;
   };

   void serializeSubClass( walberla::mpi::SendBuffer& sendBuffer ) const override final { sendBuffer << Type::IDENTITY; }
};

} // namespace hyteg
