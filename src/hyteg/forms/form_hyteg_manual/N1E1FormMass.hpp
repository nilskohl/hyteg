/*
 * Copyright (c) 2022 Daniel Bauer.
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

#include "hyteg/eigen/typeAliases.hpp"
#include "hyteg/forms/N1E1Form.hpp"

using walberla::real_c;

namespace hyteg {
namespace n1e1 {

class N1E1Form_mass : public N1E1Form
{
 public:
   /// Edges are in FEniCS ordering:
   ///
   /// 3
   /// |\`\.
   /// | 0 `\.
   /// |  \   1
   /// 3  2 _  `\.
   /// |  /  `-2 `\.
   /// | 4      `\_`\
   /// 0------5------1
   void integrateAll( const std::array< Point3D, 4 >& coords,
                      const std::array< int, 6 >&     edgeDirections,
                      Matrix6r&                       elMat ) const final
   {
      elMat.setAll( real_c( 0 ) );

      // F maps from reference tet K' to affine tet K
      // K = F(K') = Bx' + b
      // B is the Jacobian of the transformation
      Eigen::Matrix3r B;
      B.col( 0 ) = coords[1].vector_ - coords[0].vector_;
      B.col( 1 ) = coords[2].vector_ - coords[0].vector_;
      B.col( 2 ) = coords[3].vector_ - coords[0].vector_;

      const real_t absDetB = std::abs( B.determinant() );

      const Eigen::Matrix3r b    = B.inverse();
      const real_t          b_11 = b( 0, 0 );
      const real_t          b_12 = b( 0, 1 );
      const real_t          b_13 = b( 0, 2 );
      const real_t          b_21 = b( 1, 0 );
      const real_t          b_22 = b( 1, 1 );
      const real_t          b_23 = b( 1, 2 );
      const real_t          b_31 = b( 2, 0 );
      const real_t          b_32 = b( 2, 1 );
      const real_t          b_33 = b( 2, 2 );

      // clang-format off
      elMat(0, 0) = absDetB*((1.0/60.0)*std::pow(b_21, 2)*std::pow(edgeDirections[0], 2) - 1.0/60.0*b_21*b_31*std::pow(edgeDirections[0], 2) + (1.0/60.0)*std::pow(b_22, 2)*std::pow(edgeDirections[0], 2) - 1.0/60.0*b_22*b_32*std::pow(edgeDirections[0], 2) + (1.0/60.0)*std::pow(b_23, 2)*std::pow(edgeDirections[0], 2) - 1.0/60.0*b_23*b_33*std::pow(edgeDirections[0], 2) + (1.0/60.0)*std::pow(b_31, 2)*std::pow(edgeDirections[0], 2) + (1.0/60.0)*std::pow(b_32, 2)*std::pow(edgeDirections[0], 2) + (1.0/60.0)*std::pow(b_33, 2)*std::pow(edgeDirections[0], 2));
      elMat(0, 1) = absDetB*((1.0/60.0)*b_11*b_21*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_11*b_31*edgeDirections[0]*edgeDirections[1] + (1.0/60.0)*b_12*b_22*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_12*b_32*edgeDirections[0]*edgeDirections[1] + (1.0/60.0)*b_13*b_23*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_13*b_33*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_21*b_31*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_22*b_32*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_23*b_33*edgeDirections[0]*edgeDirections[1] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[1] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[1] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[1]);
      elMat(0, 2) = absDetB*((1.0/120.0)*b_11*b_21*edgeDirections[0]*edgeDirections[2] - 1.0/60.0*b_11*b_31*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_12*b_22*edgeDirections[0]*edgeDirections[2] - 1.0/60.0*b_12*b_32*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_13*b_23*edgeDirections[0]*edgeDirections[2] - 1.0/60.0*b_13*b_33*edgeDirections[0]*edgeDirections[2] - 1.0/120.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_21*b_31*edgeDirections[0]*edgeDirections[2] - 1.0/120.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_22*b_32*edgeDirections[0]*edgeDirections[2] - 1.0/120.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_23*b_33*edgeDirections[0]*edgeDirections[2]);
      elMat(0, 3) = absDetB*(-1.0/60.0*b_11*b_21*edgeDirections[0]*edgeDirections[3] + (1.0/120.0)*b_11*b_31*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_12*b_22*edgeDirections[0]*edgeDirections[3] + (1.0/120.0)*b_12*b_32*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_13*b_23*edgeDirections[0]*edgeDirections[3] + (1.0/120.0)*b_13*b_33*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_21*b_31*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_22*b_32*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_23*b_33*edgeDirections[0]*edgeDirections[3] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[3] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[3] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[3]);
      elMat(0, 4) = absDetB*(-1.0/120.0*b_11*b_21*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_11*b_31*edgeDirections[0]*edgeDirections[4] - 1.0/120.0*b_12*b_22*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_12*b_32*edgeDirections[0]*edgeDirections[4] - 1.0/120.0*b_13*b_23*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_13*b_33*edgeDirections[0]*edgeDirections[4] - 1.0/60.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_21*b_31*edgeDirections[0]*edgeDirections[4] - 1.0/60.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_22*b_32*edgeDirections[0]*edgeDirections[4] - 1.0/60.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_23*b_33*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[4]);
      elMat(0, 5) = absDetB*(-1.0/60.0*b_11*b_21*edgeDirections[0]*edgeDirections[5] + (1.0/60.0)*b_11*b_31*edgeDirections[0]*edgeDirections[5] - 1.0/60.0*b_12*b_22*edgeDirections[0]*edgeDirections[5] + (1.0/60.0)*b_12*b_32*edgeDirections[0]*edgeDirections[5] - 1.0/60.0*b_13*b_23*edgeDirections[0]*edgeDirections[5] + (1.0/60.0)*b_13*b_33*edgeDirections[0]*edgeDirections[5] - 1.0/120.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[5] - 1.0/120.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[5] - 1.0/120.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[5] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[5] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[5] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[5]);
      elMat(1, 0) = absDetB*((1.0/60.0)*b_11*b_21*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_11*b_31*edgeDirections[0]*edgeDirections[1] + (1.0/60.0)*b_12*b_22*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_12*b_32*edgeDirections[0]*edgeDirections[1] + (1.0/60.0)*b_13*b_23*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_13*b_33*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_21*b_31*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_22*b_32*edgeDirections[0]*edgeDirections[1] - 1.0/120.0*b_23*b_33*edgeDirections[0]*edgeDirections[1] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[1] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[1] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[1]);
      elMat(1, 1) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*std::pow(edgeDirections[1], 2) - 1.0/60.0*b_11*b_31*std::pow(edgeDirections[1], 2) + (1.0/60.0)*std::pow(b_12, 2)*std::pow(edgeDirections[1], 2) - 1.0/60.0*b_12*b_32*std::pow(edgeDirections[1], 2) + (1.0/60.0)*std::pow(b_13, 2)*std::pow(edgeDirections[1], 2) - 1.0/60.0*b_13*b_33*std::pow(edgeDirections[1], 2) + (1.0/60.0)*std::pow(b_31, 2)*std::pow(edgeDirections[1], 2) + (1.0/60.0)*std::pow(b_32, 2)*std::pow(edgeDirections[1], 2) + (1.0/60.0)*std::pow(b_33, 2)*std::pow(edgeDirections[1], 2));
      elMat(1, 2) = absDetB*((1.0/120.0)*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_11*b_21*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_11*b_31*edgeDirections[1]*edgeDirections[2] + (1.0/120.0)*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_12*b_22*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_12*b_32*edgeDirections[1]*edgeDirections[2] + (1.0/120.0)*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_13*b_23*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_13*b_33*edgeDirections[1]*edgeDirections[2] + (1.0/60.0)*b_21*b_31*edgeDirections[1]*edgeDirections[2] + (1.0/60.0)*b_22*b_32*edgeDirections[1]*edgeDirections[2] + (1.0/60.0)*b_23*b_33*edgeDirections[1]*edgeDirections[2]);
      elMat(1, 3) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_11*b_21*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_11*b_31*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_12*b_22*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_12*b_32*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_13*b_23*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_13*b_33*edgeDirections[1]*edgeDirections[3] + (1.0/120.0)*b_21*b_31*edgeDirections[1]*edgeDirections[3] + (1.0/120.0)*b_22*b_32*edgeDirections[1]*edgeDirections[3] + (1.0/120.0)*b_23*b_33*edgeDirections[1]*edgeDirections[3] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[1]*edgeDirections[3] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[1]*edgeDirections[3] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[1]*edgeDirections[3]);
      elMat(1, 4) = absDetB*(-1.0/120.0*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[4] - 1.0/60.0*b_11*b_21*edgeDirections[1]*edgeDirections[4] - 1.0/120.0*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[4] - 1.0/60.0*b_12*b_22*edgeDirections[1]*edgeDirections[4] - 1.0/120.0*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[4] - 1.0/60.0*b_13*b_23*edgeDirections[1]*edgeDirections[4] + (1.0/60.0)*b_21*b_31*edgeDirections[1]*edgeDirections[4] + (1.0/60.0)*b_22*b_32*edgeDirections[1]*edgeDirections[4] + (1.0/60.0)*b_23*b_33*edgeDirections[1]*edgeDirections[4] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[1]*edgeDirections[4] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[1]*edgeDirections[4] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[1]*edgeDirections[4]);
      elMat(1, 5) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[5] - 1.0/120.0*b_11*b_21*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_11*b_31*edgeDirections[1]*edgeDirections[5] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[5] - 1.0/120.0*b_12*b_22*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_12*b_32*edgeDirections[1]*edgeDirections[5] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[5] - 1.0/120.0*b_13*b_23*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_13*b_33*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_21*b_31*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_22*b_32*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_23*b_33*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[1]*edgeDirections[5]);
      elMat(2, 0) = absDetB*((1.0/120.0)*b_11*b_21*edgeDirections[0]*edgeDirections[2] - 1.0/60.0*b_11*b_31*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_12*b_22*edgeDirections[0]*edgeDirections[2] - 1.0/60.0*b_12*b_32*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_13*b_23*edgeDirections[0]*edgeDirections[2] - 1.0/60.0*b_13*b_33*edgeDirections[0]*edgeDirections[2] - 1.0/120.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_21*b_31*edgeDirections[0]*edgeDirections[2] - 1.0/120.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_22*b_32*edgeDirections[0]*edgeDirections[2] - 1.0/120.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[2] + (1.0/120.0)*b_23*b_33*edgeDirections[0]*edgeDirections[2]);
      elMat(2, 1) = absDetB*((1.0/120.0)*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_11*b_21*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_11*b_31*edgeDirections[1]*edgeDirections[2] + (1.0/120.0)*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_12*b_22*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_12*b_32*edgeDirections[1]*edgeDirections[2] + (1.0/120.0)*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_13*b_23*edgeDirections[1]*edgeDirections[2] - 1.0/120.0*b_13*b_33*edgeDirections[1]*edgeDirections[2] + (1.0/60.0)*b_21*b_31*edgeDirections[1]*edgeDirections[2] + (1.0/60.0)*b_22*b_32*edgeDirections[1]*edgeDirections[2] + (1.0/60.0)*b_23*b_33*edgeDirections[1]*edgeDirections[2]);
      elMat(2, 2) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*std::pow(edgeDirections[2], 2) - 1.0/60.0*b_11*b_21*std::pow(edgeDirections[2], 2) + (1.0/60.0)*std::pow(b_12, 2)*std::pow(edgeDirections[2], 2) - 1.0/60.0*b_12*b_22*std::pow(edgeDirections[2], 2) + (1.0/60.0)*std::pow(b_13, 2)*std::pow(edgeDirections[2], 2) - 1.0/60.0*b_13*b_23*std::pow(edgeDirections[2], 2) + (1.0/60.0)*std::pow(b_21, 2)*std::pow(edgeDirections[2], 2) + (1.0/60.0)*std::pow(b_22, 2)*std::pow(edgeDirections[2], 2) + (1.0/60.0)*std::pow(b_23, 2)*std::pow(edgeDirections[2], 2));
      elMat(2, 3) = absDetB*(-1.0/120.0*std::pow(b_11, 2)*edgeDirections[2]*edgeDirections[3] - 1.0/60.0*b_11*b_31*edgeDirections[2]*edgeDirections[3] - 1.0/120.0*std::pow(b_12, 2)*edgeDirections[2]*edgeDirections[3] - 1.0/60.0*b_12*b_32*edgeDirections[2]*edgeDirections[3] - 1.0/120.0*std::pow(b_13, 2)*edgeDirections[2]*edgeDirections[3] - 1.0/60.0*b_13*b_33*edgeDirections[2]*edgeDirections[3] + (1.0/120.0)*std::pow(b_21, 2)*edgeDirections[2]*edgeDirections[3] + (1.0/60.0)*b_21*b_31*edgeDirections[2]*edgeDirections[3] + (1.0/120.0)*std::pow(b_22, 2)*edgeDirections[2]*edgeDirections[3] + (1.0/60.0)*b_22*b_32*edgeDirections[2]*edgeDirections[3] + (1.0/120.0)*std::pow(b_23, 2)*edgeDirections[2]*edgeDirections[3] + (1.0/60.0)*b_23*b_33*edgeDirections[2]*edgeDirections[3]);
      elMat(2, 4) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_11*b_21*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_11*b_31*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_12*b_22*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_12*b_32*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_13*b_23*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_13*b_33*edgeDirections[2]*edgeDirections[4] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[2]*edgeDirections[4] + (1.0/120.0)*b_21*b_31*edgeDirections[2]*edgeDirections[4] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[2]*edgeDirections[4] + (1.0/120.0)*b_22*b_32*edgeDirections[2]*edgeDirections[4] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[2]*edgeDirections[4] + (1.0/120.0)*b_23*b_33*edgeDirections[2]*edgeDirections[4]);
      elMat(2, 5) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_11*b_21*edgeDirections[2]*edgeDirections[5] - 1.0/120.0*b_11*b_31*edgeDirections[2]*edgeDirections[5] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_12*b_22*edgeDirections[2]*edgeDirections[5] - 1.0/120.0*b_12*b_32*edgeDirections[2]*edgeDirections[5] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_13*b_23*edgeDirections[2]*edgeDirections[5] - 1.0/120.0*b_13*b_33*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_21*b_31*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_22*b_32*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_23*b_33*edgeDirections[2]*edgeDirections[5]);
      elMat(3, 0) = absDetB*(-1.0/60.0*b_11*b_21*edgeDirections[0]*edgeDirections[3] + (1.0/120.0)*b_11*b_31*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_12*b_22*edgeDirections[0]*edgeDirections[3] + (1.0/120.0)*b_12*b_32*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_13*b_23*edgeDirections[0]*edgeDirections[3] + (1.0/120.0)*b_13*b_33*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_21*b_31*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_22*b_32*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[3] - 1.0/60.0*b_23*b_33*edgeDirections[0]*edgeDirections[3] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[3] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[3] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[3]);
      elMat(3, 1) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_11*b_21*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_11*b_31*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_12*b_22*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_12*b_32*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_13*b_23*edgeDirections[1]*edgeDirections[3] - 1.0/60.0*b_13*b_33*edgeDirections[1]*edgeDirections[3] + (1.0/120.0)*b_21*b_31*edgeDirections[1]*edgeDirections[3] + (1.0/120.0)*b_22*b_32*edgeDirections[1]*edgeDirections[3] + (1.0/120.0)*b_23*b_33*edgeDirections[1]*edgeDirections[3] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[1]*edgeDirections[3] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[1]*edgeDirections[3] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[1]*edgeDirections[3]);
      elMat(3, 2) = absDetB*(-1.0/120.0*std::pow(b_11, 2)*edgeDirections[2]*edgeDirections[3] - 1.0/60.0*b_11*b_31*edgeDirections[2]*edgeDirections[3] - 1.0/120.0*std::pow(b_12, 2)*edgeDirections[2]*edgeDirections[3] - 1.0/60.0*b_12*b_32*edgeDirections[2]*edgeDirections[3] - 1.0/120.0*std::pow(b_13, 2)*edgeDirections[2]*edgeDirections[3] - 1.0/60.0*b_13*b_33*edgeDirections[2]*edgeDirections[3] + (1.0/120.0)*std::pow(b_21, 2)*edgeDirections[2]*edgeDirections[3] + (1.0/60.0)*b_21*b_31*edgeDirections[2]*edgeDirections[3] + (1.0/120.0)*std::pow(b_22, 2)*edgeDirections[2]*edgeDirections[3] + (1.0/60.0)*b_22*b_32*edgeDirections[2]*edgeDirections[3] + (1.0/120.0)*std::pow(b_23, 2)*edgeDirections[2]*edgeDirections[3] + (1.0/60.0)*b_23*b_33*edgeDirections[2]*edgeDirections[3]);
      elMat(3, 3) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*std::pow(edgeDirections[3], 2) + (1.0/30.0)*b_11*b_21*std::pow(edgeDirections[3], 2) + (1.0/20.0)*b_11*b_31*std::pow(edgeDirections[3], 2) + (1.0/60.0)*std::pow(b_12, 2)*std::pow(edgeDirections[3], 2) + (1.0/30.0)*b_12*b_22*std::pow(edgeDirections[3], 2) + (1.0/20.0)*b_12*b_32*std::pow(edgeDirections[3], 2) + (1.0/60.0)*std::pow(b_13, 2)*std::pow(edgeDirections[3], 2) + (1.0/30.0)*b_13*b_23*std::pow(edgeDirections[3], 2) + (1.0/20.0)*b_13*b_33*std::pow(edgeDirections[3], 2) + (1.0/60.0)*std::pow(b_21, 2)*std::pow(edgeDirections[3], 2) + (1.0/20.0)*b_21*b_31*std::pow(edgeDirections[3], 2) + (1.0/60.0)*std::pow(b_22, 2)*std::pow(edgeDirections[3], 2) + (1.0/20.0)*b_22*b_32*std::pow(edgeDirections[3], 2) + (1.0/60.0)*std::pow(b_23, 2)*std::pow(edgeDirections[3], 2) + (1.0/20.0)*b_23*b_33*std::pow(edgeDirections[3], 2) + (1.0/20.0)*std::pow(b_31, 2)*std::pow(edgeDirections[3], 2) + (1.0/20.0)*std::pow(b_32, 2)*std::pow(edgeDirections[3], 2) + (1.0/20.0)*std::pow(b_33, 2)*std::pow(edgeDirections[3], 2));
      elMat(3, 4) = absDetB*((1.0/120.0)*std::pow(b_11, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_11*b_21*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_11*b_31*edgeDirections[3]*edgeDirections[4] + (1.0/120.0)*std::pow(b_12, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_12*b_22*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_12*b_32*edgeDirections[3]*edgeDirections[4] + (1.0/120.0)*std::pow(b_13, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_13*b_23*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_13*b_33*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/20.0)*b_21*b_31*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/20.0)*b_22*b_32*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/20.0)*b_23*b_33*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[3]*edgeDirections[4]);
      elMat(3, 5) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_11*b_21*edgeDirections[3]*edgeDirections[5] + (1.0/20.0)*b_11*b_31*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_12, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_12*b_22*edgeDirections[3]*edgeDirections[5] + (1.0/20.0)*b_12*b_32*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_13, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_13*b_23*edgeDirections[3]*edgeDirections[5] + (1.0/20.0)*b_13*b_33*edgeDirections[3]*edgeDirections[5] + (1.0/120.0)*std::pow(b_21, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_21*b_31*edgeDirections[3]*edgeDirections[5] + (1.0/120.0)*std::pow(b_22, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_22*b_32*edgeDirections[3]*edgeDirections[5] + (1.0/120.0)*std::pow(b_23, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_23*b_33*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[3]*edgeDirections[5]);
      elMat(4, 0) = absDetB*(-1.0/120.0*b_11*b_21*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_11*b_31*edgeDirections[0]*edgeDirections[4] - 1.0/120.0*b_12*b_22*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_12*b_32*edgeDirections[0]*edgeDirections[4] - 1.0/120.0*b_13*b_23*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_13*b_33*edgeDirections[0]*edgeDirections[4] - 1.0/60.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_21*b_31*edgeDirections[0]*edgeDirections[4] - 1.0/60.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_22*b_32*edgeDirections[0]*edgeDirections[4] - 1.0/60.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*b_23*b_33*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[4] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[4]);
      elMat(4, 1) = absDetB*(-1.0/120.0*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[4] - 1.0/60.0*b_11*b_21*edgeDirections[1]*edgeDirections[4] - 1.0/120.0*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[4] - 1.0/60.0*b_12*b_22*edgeDirections[1]*edgeDirections[4] - 1.0/120.0*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[4] - 1.0/60.0*b_13*b_23*edgeDirections[1]*edgeDirections[4] + (1.0/60.0)*b_21*b_31*edgeDirections[1]*edgeDirections[4] + (1.0/60.0)*b_22*b_32*edgeDirections[1]*edgeDirections[4] + (1.0/60.0)*b_23*b_33*edgeDirections[1]*edgeDirections[4] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[1]*edgeDirections[4] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[1]*edgeDirections[4] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[1]*edgeDirections[4]);
      elMat(4, 2) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_11*b_21*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_11*b_31*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_12*b_22*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_12*b_32*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_13*b_23*edgeDirections[2]*edgeDirections[4] - 1.0/60.0*b_13*b_33*edgeDirections[2]*edgeDirections[4] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[2]*edgeDirections[4] + (1.0/120.0)*b_21*b_31*edgeDirections[2]*edgeDirections[4] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[2]*edgeDirections[4] + (1.0/120.0)*b_22*b_32*edgeDirections[2]*edgeDirections[4] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[2]*edgeDirections[4] + (1.0/120.0)*b_23*b_33*edgeDirections[2]*edgeDirections[4]);
      elMat(4, 3) = absDetB*((1.0/120.0)*std::pow(b_11, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_11*b_21*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_11*b_31*edgeDirections[3]*edgeDirections[4] + (1.0/120.0)*std::pow(b_12, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_12*b_22*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_12*b_32*edgeDirections[3]*edgeDirections[4] + (1.0/120.0)*std::pow(b_13, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_13*b_23*edgeDirections[3]*edgeDirections[4] + (1.0/40.0)*b_13*b_33*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/20.0)*b_21*b_31*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/20.0)*b_22*b_32*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/20.0)*b_23*b_33*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[3]*edgeDirections[4] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[3]*edgeDirections[4]);
      elMat(4, 4) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*std::pow(edgeDirections[4], 2) + (1.0/20.0)*b_11*b_21*std::pow(edgeDirections[4], 2) + (1.0/30.0)*b_11*b_31*std::pow(edgeDirections[4], 2) + (1.0/60.0)*std::pow(b_12, 2)*std::pow(edgeDirections[4], 2) + (1.0/20.0)*b_12*b_22*std::pow(edgeDirections[4], 2) + (1.0/30.0)*b_12*b_32*std::pow(edgeDirections[4], 2) + (1.0/60.0)*std::pow(b_13, 2)*std::pow(edgeDirections[4], 2) + (1.0/20.0)*b_13*b_23*std::pow(edgeDirections[4], 2) + (1.0/30.0)*b_13*b_33*std::pow(edgeDirections[4], 2) + (1.0/20.0)*std::pow(b_21, 2)*std::pow(edgeDirections[4], 2) + (1.0/20.0)*b_21*b_31*std::pow(edgeDirections[4], 2) + (1.0/20.0)*std::pow(b_22, 2)*std::pow(edgeDirections[4], 2) + (1.0/20.0)*b_22*b_32*std::pow(edgeDirections[4], 2) + (1.0/20.0)*std::pow(b_23, 2)*std::pow(edgeDirections[4], 2) + (1.0/20.0)*b_23*b_33*std::pow(edgeDirections[4], 2) + (1.0/60.0)*std::pow(b_31, 2)*std::pow(edgeDirections[4], 2) + (1.0/60.0)*std::pow(b_32, 2)*std::pow(edgeDirections[4], 2) + (1.0/60.0)*std::pow(b_33, 2)*std::pow(edgeDirections[4], 2));
      elMat(4, 5) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/20.0)*b_11*b_21*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_11*b_31*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_12, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/20.0)*b_12*b_22*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_12*b_32*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_13, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/20.0)*b_13*b_23*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_13*b_33*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_21*b_31*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_22*b_32*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_23*b_33*edgeDirections[4]*edgeDirections[5] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[4]*edgeDirections[5]);
      elMat(5, 0) = absDetB*(-1.0/60.0*b_11*b_21*edgeDirections[0]*edgeDirections[5] + (1.0/60.0)*b_11*b_31*edgeDirections[0]*edgeDirections[5] - 1.0/60.0*b_12*b_22*edgeDirections[0]*edgeDirections[5] + (1.0/60.0)*b_12*b_32*edgeDirections[0]*edgeDirections[5] - 1.0/60.0*b_13*b_23*edgeDirections[0]*edgeDirections[5] + (1.0/60.0)*b_13*b_33*edgeDirections[0]*edgeDirections[5] - 1.0/120.0*std::pow(b_21, 2)*edgeDirections[0]*edgeDirections[5] - 1.0/120.0*std::pow(b_22, 2)*edgeDirections[0]*edgeDirections[5] - 1.0/120.0*std::pow(b_23, 2)*edgeDirections[0]*edgeDirections[5] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[0]*edgeDirections[5] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[0]*edgeDirections[5] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[0]*edgeDirections[5]);
      elMat(5, 1) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[1]*edgeDirections[5] - 1.0/120.0*b_11*b_21*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_11*b_31*edgeDirections[1]*edgeDirections[5] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[1]*edgeDirections[5] - 1.0/120.0*b_12*b_22*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_12*b_32*edgeDirections[1]*edgeDirections[5] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[1]*edgeDirections[5] - 1.0/120.0*b_13*b_23*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_13*b_33*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_21*b_31*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_22*b_32*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*b_23*b_33*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[1]*edgeDirections[5] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[1]*edgeDirections[5]);
      elMat(5, 2) = absDetB*(-1.0/60.0*std::pow(b_11, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_11*b_21*edgeDirections[2]*edgeDirections[5] - 1.0/120.0*b_11*b_31*edgeDirections[2]*edgeDirections[5] - 1.0/60.0*std::pow(b_12, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_12*b_22*edgeDirections[2]*edgeDirections[5] - 1.0/120.0*b_12*b_32*edgeDirections[2]*edgeDirections[5] - 1.0/60.0*std::pow(b_13, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_13*b_23*edgeDirections[2]*edgeDirections[5] - 1.0/120.0*b_13*b_33*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_21*b_31*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_22*b_32*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[2]*edgeDirections[5] + (1.0/60.0)*b_23*b_33*edgeDirections[2]*edgeDirections[5]);
      elMat(5, 3) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_11*b_21*edgeDirections[3]*edgeDirections[5] + (1.0/20.0)*b_11*b_31*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_12, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_12*b_22*edgeDirections[3]*edgeDirections[5] + (1.0/20.0)*b_12*b_32*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_13, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_13*b_23*edgeDirections[3]*edgeDirections[5] + (1.0/20.0)*b_13*b_33*edgeDirections[3]*edgeDirections[5] + (1.0/120.0)*std::pow(b_21, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_21*b_31*edgeDirections[3]*edgeDirections[5] + (1.0/120.0)*std::pow(b_22, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_22*b_32*edgeDirections[3]*edgeDirections[5] + (1.0/120.0)*std::pow(b_23, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/40.0)*b_23*b_33*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_31, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_32, 2)*edgeDirections[3]*edgeDirections[5] + (1.0/60.0)*std::pow(b_33, 2)*edgeDirections[3]*edgeDirections[5]);
      elMat(5, 4) = absDetB*((1.0/60.0)*std::pow(b_11, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/20.0)*b_11*b_21*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_11*b_31*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_12, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/20.0)*b_12*b_22*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_12*b_32*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_13, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/20.0)*b_13*b_23*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_13*b_33*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_21, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_21*b_31*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_22, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_22*b_32*edgeDirections[4]*edgeDirections[5] + (1.0/60.0)*std::pow(b_23, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/40.0)*b_23*b_33*edgeDirections[4]*edgeDirections[5] + (1.0/120.0)*std::pow(b_31, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/120.0)*std::pow(b_32, 2)*edgeDirections[4]*edgeDirections[5] + (1.0/120.0)*std::pow(b_33, 2)*edgeDirections[4]*edgeDirections[5]);
      elMat(5, 5) = absDetB*((1.0/20.0)*std::pow(b_11, 2)*std::pow(edgeDirections[5], 2) + (1.0/20.0)*b_11*b_21*std::pow(edgeDirections[5], 2) + (1.0/20.0)*b_11*b_31*std::pow(edgeDirections[5], 2) + (1.0/20.0)*std::pow(b_12, 2)*std::pow(edgeDirections[5], 2) + (1.0/20.0)*b_12*b_22*std::pow(edgeDirections[5], 2) + (1.0/20.0)*b_12*b_32*std::pow(edgeDirections[5], 2) + (1.0/20.0)*std::pow(b_13, 2)*std::pow(edgeDirections[5], 2) + (1.0/20.0)*b_13*b_23*std::pow(edgeDirections[5], 2) + (1.0/20.0)*b_13*b_33*std::pow(edgeDirections[5], 2) + (1.0/60.0)*std::pow(b_21, 2)*std::pow(edgeDirections[5], 2) + (1.0/30.0)*b_21*b_31*std::pow(edgeDirections[5], 2) + (1.0/60.0)*std::pow(b_22, 2)*std::pow(edgeDirections[5], 2) + (1.0/30.0)*b_22*b_32*std::pow(edgeDirections[5], 2) + (1.0/60.0)*std::pow(b_23, 2)*std::pow(edgeDirections[5], 2) + (1.0/30.0)*b_23*b_33*std::pow(edgeDirections[5], 2) + (1.0/60.0)*std::pow(b_31, 2)*std::pow(edgeDirections[5], 2) + (1.0/60.0)*std::pow(b_32, 2)*std::pow(edgeDirections[5], 2) + (1.0/60.0)*std::pow(b_33, 2)*std::pow(edgeDirections[5], 2));      // clang-format on
   };

   bool assemble2D() const override
   {
      WALBERLA_ABORT( "Not implemented." );
      return false;
   };
   bool assemble3D() const override
   {
      WALBERLA_ABORT( "Not implemented." );
      return false;
   };
   bool assembly2DDefined() const override
   {
      WALBERLA_ABORT( "Not implemented." );
      return false;
   };
   bool assembly3DDefined() const override
   {
      WALBERLA_ABORT( "Not implemented." );
      return false;
   };
};

} // namespace n1e1
} // namespace hyteg
