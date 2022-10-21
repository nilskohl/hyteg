/*
 * Copyright (c) 2017-2019 Daniel Drzisga, Dominik Thoennes, Marcus Mohr.
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

#include "hyteg/types/matrix.hpp"
#include "hyteg/types/pointnd.hpp"

using walberla::real_c;

namespace hyteg {

/// Class describing a geometrical mapping from reference to physical space
class GeometryMap
{
 public:
   enum class Type : uint_t
   {
      IDENTITY          = 0,
      AFFINE            = 1,
      CIRCULAR          = 2,
      POLAR_COORDS      = 3,
      ANNULUS           = 4,
      ICOSAHEDRAL_SHELL = 5,
      AFFINE_2D         = 6,
      AFFINE_3D         = 7
   };

   virtual ~GeometryMap(){};

   /// Mapping of reference coordinates \p x to physical coordinates \p Fx
   /// \param x Reference input coordinates
   /// \param Fx Physical output coordinates
   virtual void evalF( const Point3D& x, Point3D& Fx ) const = 0;

   /// Maps point from physical back to computational domain (inverse blending)
   /// \param xPhys coordinates of point in physical domain
   /// \param xComp coordinates of point in computational domain
   virtual void evalFinv( const Point3D& xPhys, Point3D& xComp ) const
   {
      WALBERLA_UNUSED( xPhys );
      WALBERLA_UNUSED( xComp );
      WALBERLA_ABORT( "GeometryMap::evalFinv() not implemented for current child map" );
   }

   /// Evaluation of the Jacobian matrix at reference position \p x
   /// \param x Reference input coordinates
   /// \param DFx Jacobian matrix
   virtual void evalDF( const Point3D& x, Matrix2r& DFx ) const = 0;

   /// Evaluation of the Jacobian matrix at reference position \p x
   /// \param x Reference input coordinates
   /// \param DFx Jacobian matrix
   /// \return value of Jacobian determinant
   virtual real_t evalDF( const Point3D& x, Matrix3r& DFx ) const
   {
      WALBERLA_UNUSED( x );
      WALBERLA_UNUSED( DFx );
      WALBERLA_ABORT( "GeometryMap::evalDF() not implemented for 3D in child class!" );
   };

   /// Evaluation of the Jacobian matrix at reference position \p x
   /// \param x Reference input coordinates
   /// \param DFinvx Inverse of the Jacobian matrix
   virtual void evalDFinv( const Point3D& x, Matrix2r& DFinvx ) const = 0;

   /// Evaluation of the determinant of the Jacobian matrix at reference position \p x
   /// \param x Reference input coordinates
   real_t evalDetDF( const Point3D& x );

   /// Verify that the given point from the physical domain is connected to the given
   /// point on the computational domain.
   ///
   /// We require a blending map to be a homeomorphism globally. However, we allow that global blending
   /// maps are constructed in a piecewise fashion from maps that differ locally between primitives.
   /// These need to be homeomorphisms locally on the respective primitives, but not globally. This
   /// can cause problems when we try to map a point back from the physical to the computational domain,
   /// but do not know to which primitive the point will belong on the computational domain.
   ///
   /// This method is supposed to test, whether mapping a point from the computational domain to the
   /// physical domain gives the desired coordinates. As this is no issue for global homeomorphism,
   /// we implement an optimistic version in this base class and allow children to override it with
   /// their own implementation where the details of the mapping are known.
   ///
   /// For details and an example see issue 184.
   virtual bool verifyPointPairing( const Point3D& computationalCoordinates, const Point3D& physicalCoordinates ) const = 0;

   /// Serialization of a GeometryMap object
   static void serialize( const std::shared_ptr< GeometryMap >& map, walberla::mpi::SendBuffer& sendBuffer );

   /// Deserialization of a GeometryMap object
   static std::shared_ptr< GeometryMap > deserialize( walberla::mpi::RecvBuffer& recvBuffer );

 protected:
   virtual void serializeSubClass( walberla::mpi::SendBuffer& sendBuffer ) const = 0;

   /// Default threshold for allowed distance in verifyPointPairing()
   real_t defaultThresholdForPointComparison = real_c( 1e-12 );
};

} // namespace hyteg
