
/*
* Copyright (c) 2017-2022 Nils Kohl.
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

#include "hyteg/dgfunctionspace/DGBasisInfo.hpp"
#include "hyteg/dgfunctionspace/DGForm.hpp"
#include "hyteg/dgfunctionspace/DGForm2D.hpp"
#include "hyteg/types/matrix.hpp"
#include "hyteg/types/pointnd.hpp"

#include "Eigen/Eigen"

namespace hyteg {
namespace dg {
namespace eg {

class EGVectorMassFormP1E_0 : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t tmp_0  = -p_affine_0_0;
      real_t tmp_1  = p_affine_1_0 + tmp_0;
      real_t tmp_2  = p_affine_2_0 + tmp_0;
      real_t tmp_3  = std::abs( p_affine_0_0 * p_affine_1_1 - p_affine_0_0 * p_affine_2_1 - p_affine_0_1 * p_affine_1_0 +
                               p_affine_0_1 * p_affine_2_0 + p_affine_1_0 * p_affine_2_1 - p_affine_1_1 * p_affine_2_0 );
      real_t tmp_4  = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 + 0.54048863768366218 * tmp_2 );
      real_t tmp_5  = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 + 0.16809317632484583 * tmp_2 );
      real_t tmp_6  = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_7  = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_8  = 0.025422453185103409 * tmp_3 * ( 0.54048863768366218 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_9  = 0.058393137863189684 * tmp_3 * ( 0.16809317632484583 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_10 = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_11 = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_12 = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t tmp_13 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_14 = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_15 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t a_0_0  = 0.87382197101699566 * tmp_10 + 0.50142650965817914 * tmp_11 + 0.053145049844816938 * tmp_12 +
                     0.63650249912139867 * tmp_13 + 0.31035245103378439 * tmp_14 + 0.31035245103378439 * tmp_15 +
                     0.063089014491502282 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.63650249912139867 * tmp_6 +
                     0.053145049844816938 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      real_t a_1_0 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.31035245103378439 * tmp_12 +
                     0.053145049844816938 * tmp_13 + 0.63650249912139867 * tmp_14 + 0.053145049844816938 * tmp_15 +
                     0.063089014491502227 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.31035245103378439 * tmp_6 +
                     0.63650249912139867 * tmp_7 + 0.87382197101699555 * tmp_8 + 0.50142650965817914 * tmp_9;
      real_t a_2_0 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.63650249912139867 * tmp_12 +
                     0.31035245103378439 * tmp_13 + 0.053145049844816938 * tmp_14 + 0.63650249912139867 * tmp_15 +
                     0.87382197101699555 * tmp_4 + 0.50142650965817914 * tmp_5 + 0.053145049844816938 * tmp_6 +
                     0.31035245103378439 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      elMat( 0, 0 ) = a_0_0;
      elMat( 1, 0 ) = a_1_0;
      elMat( 2, 0 ) = a_2_0;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
     void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }

   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0  = -p_affine_0_0;
      real_t tmp_1  = p_affine_1_0 + tmp_0;
      real_t tmp_2  = p_affine_2_0 + tmp_0;
      real_t tmp_3  = p_affine_3_0 + tmp_0;
      real_t tmp_4  = p_affine_0_0 * p_affine_1_1;
      real_t tmp_5  = p_affine_0_0 * p_affine_1_2;
      real_t tmp_6  = p_affine_2_1 * p_affine_3_2;
      real_t tmp_7  = p_affine_0_1 * p_affine_1_0;
      real_t tmp_8  = p_affine_0_1 * p_affine_1_2;
      real_t tmp_9  = p_affine_2_2 * p_affine_3_0;
      real_t tmp_10 = p_affine_0_2 * p_affine_1_0;
      real_t tmp_11 = p_affine_0_2 * p_affine_1_1;
      real_t tmp_12 = p_affine_2_0 * p_affine_3_1;
      real_t tmp_13 = p_affine_2_2 * p_affine_3_1;
      real_t tmp_14 = p_affine_2_0 * p_affine_3_2;
      real_t tmp_15 = p_affine_2_1 * p_affine_3_0;
      real_t tmp_16 = std::abs( p_affine_0_0 * tmp_13 - p_affine_0_0 * tmp_6 + p_affine_0_1 * tmp_14 - p_affine_0_1 * tmp_9 -
                                p_affine_0_2 * tmp_12 + p_affine_0_2 * tmp_15 - p_affine_1_0 * tmp_13 + p_affine_1_0 * tmp_6 -
                                p_affine_1_1 * tmp_14 + p_affine_1_1 * tmp_9 + p_affine_1_2 * tmp_12 - p_affine_1_2 * tmp_15 +
                                p_affine_2_0 * tmp_11 - p_affine_2_0 * tmp_8 - p_affine_2_1 * tmp_10 + p_affine_2_1 * tmp_5 -
                                p_affine_2_2 * tmp_4 + p_affine_2_2 * tmp_7 - p_affine_3_0 * tmp_11 + p_affine_3_0 * tmp_8 +
                                p_affine_3_1 * tmp_10 - p_affine_3_1 * tmp_5 + p_affine_3_2 * tmp_4 - p_affine_3_2 * tmp_7 );
      real_t tmp_17 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 + 0.42614182511336729 * tmp_3 );
      real_t tmp_18 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 + 0.19467153665224024 * tmp_3 );
      real_t tmp_19 = 0.0012542093589233661 * tmp_16 *
                      ( 0.6230503689456981 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_20 = 0.0069606304761558151 * tmp_16 *
                      ( -0.19254512737211693 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_21 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_22 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_23 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_24 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_25 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_26 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_27 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_28 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_29 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 + 0.6230503689456981 * tmp_3 );
      real_t tmp_30 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_31 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_32 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_33 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_34 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_35 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_36 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_37 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_38 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_39 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_40 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 - 0.19254512737211693 * tmp_3 );
      real_t tmp_41 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_42 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_43 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_44 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_45 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_46 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_47 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_48 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_49 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_50 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_51 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 + 0.42614182511336729 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_52 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_53 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_54 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_55 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_56 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_57 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_58 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 + 0.19467153665224024 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_59 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 + 0.6230503689456981 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_60 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 - 0.19254512737211693 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_61 = 0.0044044418180681378 * tmp_16 *
                      ( 0.42614182511336729 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_62 = 0.0086719579272897529 * tmp_16 *
                      ( 0.19467153665224024 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t a_0_0 = 0.10795272496221098 * tmp_17 + 0.18510948778258651 * tmp_18 + 0.042316543684767338 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.6761418251133674 * tmp_21 + 0.44467153665224013 * tmp_22 +
                     0.87305036894569832 * tmp_23 + 0.057454872627883069 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.042316543684767449 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.021433930127130574 * tmp_32 + 0.20413933387602912 * tmp_33 + 0.021433930127130574 * tmp_34 +
                     0.20413933387602914 * tmp_35 + 0.71746406342630831 * tmp_36 + 0.5837973783021444 * tmp_37 +
                     0.021433930127130577 * tmp_38 + 0.20413933387602914 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.71746406342630831 * tmp_41 + 0.5837973783021444 * tmp_42 + 0.71746406342630831 * tmp_43 +
                     0.5837973783021444 * tmp_44 + 0.021433930127130574 * tmp_45 + 0.20413933387602912 * tmp_46 +
                     0.021433930127130574 * tmp_47 + 0.20413933387602912 * tmp_48 + 0.23966807631943055 * tmp_49 +
                     0.0079239539457973684 * tmp_50 + 0.10795272496221095 * tmp_51 + 0.021433930127130577 * tmp_52 +
                     0.20413933387602914 * tmp_53 + 0.23966807631943055 * tmp_54 + 0.0079239539457973962 * tmp_55 +
                     0.23966807631943055 * tmp_56 + 0.007923953945797424 * tmp_57 + 0.18510948778258654 * tmp_58 +
                     0.042316543684767394 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221092 * tmp_61 +
                     0.18510948778258654 * tmp_62;
      real_t a_1_0 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.8730503689456981 * tmp_19 +
                     0.057454872627883069 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.02143393012713057 * tmp_32 + 0.20413933387602909 * tmp_33 + 0.71746406342630831 * tmp_34 +
                     0.5837973783021444 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.71746406342630831 * tmp_38 + 0.5837973783021444 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.23966807631943055 * tmp_43 +
                     0.0079239539457973684 * tmp_44 + 0.02143393012713057 * tmp_45 + 0.20413933387602909 * tmp_46 +
                     0.23966807631943055 * tmp_47 + 0.0079239539457973684 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.23966807631943055 * tmp_52 +
                     0.0079239539457973684 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.71746406342630831 * tmp_56 + 0.5837973783021444 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.67614182511336729 * tmp_61 +
                     0.44467153665224024 * tmp_62;
      real_t a_2_0 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.71746406342630831 * tmp_32 + 0.5837973783021444 * tmp_33 + 0.02143393012713057 * tmp_34 +
                     0.20413933387602909 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.23966807631943055 * tmp_38 + 0.0079239539457973684 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.23966807631943055 * tmp_41 + 0.0079239539457973684 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.23966807631943055 * tmp_45 + 0.0079239539457973684 * tmp_46 +
                     0.02143393012713057 * tmp_47 + 0.20413933387602909 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.67614182511336729 * tmp_51 + 0.71746406342630831 * tmp_52 +
                     0.5837973783021444 * tmp_53 + 0.71746406342630831 * tmp_54 + 0.5837973783021444 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.44467153665224024 * tmp_58 +
                     0.8730503689456981 * tmp_59 + 0.057454872627883069 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      real_t a_3_0 = 0.67614182511336729 * tmp_17 + 0.44467153665224024 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.8730503689456981 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.23966807631943055 * tmp_32 + 0.0079239539457973684 * tmp_33 + 0.23966807631943055 * tmp_34 +
                     0.0079239539457973684 * tmp_35 + 0.23966807631943055 * tmp_36 + 0.0079239539457973684 * tmp_37 +
                     0.02143393012713057 * tmp_38 + 0.20413933387602909 * tmp_39 + 0.057454872627883069 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.71746406342630831 * tmp_45 + 0.5837973783021444 * tmp_46 +
                     0.71746406342630831 * tmp_47 + 0.5837973783021444 * tmp_48 + 0.71746406342630831 * tmp_49 +
                     0.5837973783021444 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.02143393012713057 * tmp_52 +
                     0.20413933387602909 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      elMat( 0, 0 ) = a_0_0;
      elMat( 1, 0 ) = a_1_0;
      elMat( 2, 0 ) = a_2_0;
      elMat( 3, 0 ) = a_3_0;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }

 
};

class EGVectorMassFormP1E_1 : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t tmp_0  = -p_affine_0_1;
      real_t tmp_1  = p_affine_1_1 + tmp_0;
      real_t tmp_2  = p_affine_2_1 + tmp_0;
      real_t tmp_3  = std::abs( p_affine_0_0 * p_affine_1_1 - p_affine_0_0 * p_affine_2_1 - p_affine_0_1 * p_affine_1_0 +
                               p_affine_0_1 * p_affine_2_0 + p_affine_1_0 * p_affine_2_1 - p_affine_1_1 * p_affine_2_0 );
      real_t tmp_4  = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 + 0.54048863768366218 * tmp_2 );
      real_t tmp_5  = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 + 0.16809317632484583 * tmp_2 );
      real_t tmp_6  = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_7  = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_8  = 0.025422453185103409 * tmp_3 * ( 0.54048863768366218 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_9  = 0.058393137863189684 * tmp_3 * ( 0.16809317632484583 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_10 = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_11 = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_12 = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t tmp_13 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_14 = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_15 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t a_0_0  = 0.87382197101699566 * tmp_10 + 0.50142650965817914 * tmp_11 + 0.053145049844816938 * tmp_12 +
                     0.63650249912139867 * tmp_13 + 0.31035245103378439 * tmp_14 + 0.31035245103378439 * tmp_15 +
                     0.063089014491502282 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.63650249912139867 * tmp_6 +
                     0.053145049844816938 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      real_t a_1_0 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.31035245103378439 * tmp_12 +
                     0.053145049844816938 * tmp_13 + 0.63650249912139867 * tmp_14 + 0.053145049844816938 * tmp_15 +
                     0.063089014491502227 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.31035245103378439 * tmp_6 +
                     0.63650249912139867 * tmp_7 + 0.87382197101699555 * tmp_8 + 0.50142650965817914 * tmp_9;
      real_t a_2_0 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.63650249912139867 * tmp_12 +
                     0.31035245103378439 * tmp_13 + 0.053145049844816938 * tmp_14 + 0.63650249912139867 * tmp_15 +
                     0.87382197101699555 * tmp_4 + 0.50142650965817914 * tmp_5 + 0.053145049844816938 * tmp_6 +
                     0.31035245103378439 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      elMat( 0, 0 ) = a_0_0;
      elMat( 1, 0 ) = a_1_0;
      elMat( 2, 0 ) = a_2_0;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }

  void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0  = -p_affine_0_1;
      real_t tmp_1  = p_affine_1_1 + tmp_0;
      real_t tmp_2  = p_affine_2_1 + tmp_0;
      real_t tmp_3  = p_affine_3_1 + tmp_0;
      real_t tmp_4  = p_affine_0_0 * p_affine_1_1;
      real_t tmp_5  = p_affine_0_0 * p_affine_1_2;
      real_t tmp_6  = p_affine_2_1 * p_affine_3_2;
      real_t tmp_7  = p_affine_0_1 * p_affine_1_0;
      real_t tmp_8  = p_affine_0_1 * p_affine_1_2;
      real_t tmp_9  = p_affine_2_2 * p_affine_3_0;
      real_t tmp_10 = p_affine_0_2 * p_affine_1_0;
      real_t tmp_11 = p_affine_0_2 * p_affine_1_1;
      real_t tmp_12 = p_affine_2_0 * p_affine_3_1;
      real_t tmp_13 = p_affine_2_2 * p_affine_3_1;
      real_t tmp_14 = p_affine_2_0 * p_affine_3_2;
      real_t tmp_15 = p_affine_2_1 * p_affine_3_0;
      real_t tmp_16 = std::abs( p_affine_0_0 * tmp_13 - p_affine_0_0 * tmp_6 + p_affine_0_1 * tmp_14 - p_affine_0_1 * tmp_9 -
                                p_affine_0_2 * tmp_12 + p_affine_0_2 * tmp_15 - p_affine_1_0 * tmp_13 + p_affine_1_0 * tmp_6 -
                                p_affine_1_1 * tmp_14 + p_affine_1_1 * tmp_9 + p_affine_1_2 * tmp_12 - p_affine_1_2 * tmp_15 +
                                p_affine_2_0 * tmp_11 - p_affine_2_0 * tmp_8 - p_affine_2_1 * tmp_10 + p_affine_2_1 * tmp_5 -
                                p_affine_2_2 * tmp_4 + p_affine_2_2 * tmp_7 - p_affine_3_0 * tmp_11 + p_affine_3_0 * tmp_8 +
                                p_affine_3_1 * tmp_10 - p_affine_3_1 * tmp_5 + p_affine_3_2 * tmp_4 - p_affine_3_2 * tmp_7 );
      real_t tmp_17 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 + 0.42614182511336729 * tmp_3 );
      real_t tmp_18 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 + 0.19467153665224024 * tmp_3 );
      real_t tmp_19 = 0.0012542093589233661 * tmp_16 *
                      ( 0.6230503689456981 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_20 = 0.0069606304761558151 * tmp_16 *
                      ( -0.19254512737211693 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_21 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_22 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_23 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_24 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_25 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_26 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_27 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_28 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_29 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 + 0.6230503689456981 * tmp_3 );
      real_t tmp_30 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_31 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_32 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_33 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_34 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_35 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_36 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_37 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_38 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_39 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_40 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 - 0.19254512737211693 * tmp_3 );
      real_t tmp_41 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_42 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_43 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_44 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_45 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_46 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_47 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_48 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_49 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_50 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_51 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 + 0.42614182511336729 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_52 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_53 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_54 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_55 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_56 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_57 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_58 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 + 0.19467153665224024 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_59 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 + 0.6230503689456981 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_60 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 - 0.19254512737211693 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_61 = 0.0044044418180681378 * tmp_16 *
                      ( 0.42614182511336729 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_62 = 0.0086719579272897529 * tmp_16 *
                      ( 0.19467153665224024 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t a_0_0 = 0.10795272496221098 * tmp_17 + 0.18510948778258651 * tmp_18 + 0.042316543684767338 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.6761418251133674 * tmp_21 + 0.44467153665224013 * tmp_22 +
                     0.87305036894569832 * tmp_23 + 0.057454872627883069 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.042316543684767449 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.021433930127130574 * tmp_32 + 0.20413933387602912 * tmp_33 + 0.021433930127130574 * tmp_34 +
                     0.20413933387602914 * tmp_35 + 0.71746406342630831 * tmp_36 + 0.5837973783021444 * tmp_37 +
                     0.021433930127130577 * tmp_38 + 0.20413933387602914 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.71746406342630831 * tmp_41 + 0.5837973783021444 * tmp_42 + 0.71746406342630831 * tmp_43 +
                     0.5837973783021444 * tmp_44 + 0.021433930127130574 * tmp_45 + 0.20413933387602912 * tmp_46 +
                     0.021433930127130574 * tmp_47 + 0.20413933387602912 * tmp_48 + 0.23966807631943055 * tmp_49 +
                     0.0079239539457973684 * tmp_50 + 0.10795272496221095 * tmp_51 + 0.021433930127130577 * tmp_52 +
                     0.20413933387602914 * tmp_53 + 0.23966807631943055 * tmp_54 + 0.0079239539457973962 * tmp_55 +
                     0.23966807631943055 * tmp_56 + 0.007923953945797424 * tmp_57 + 0.18510948778258654 * tmp_58 +
                     0.042316543684767394 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221092 * tmp_61 +
                     0.18510948778258654 * tmp_62;
      real_t a_1_0 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.8730503689456981 * tmp_19 +
                     0.057454872627883069 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.02143393012713057 * tmp_32 + 0.20413933387602909 * tmp_33 + 0.71746406342630831 * tmp_34 +
                     0.5837973783021444 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.71746406342630831 * tmp_38 + 0.5837973783021444 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.23966807631943055 * tmp_43 +
                     0.0079239539457973684 * tmp_44 + 0.02143393012713057 * tmp_45 + 0.20413933387602909 * tmp_46 +
                     0.23966807631943055 * tmp_47 + 0.0079239539457973684 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.23966807631943055 * tmp_52 +
                     0.0079239539457973684 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.71746406342630831 * tmp_56 + 0.5837973783021444 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.67614182511336729 * tmp_61 +
                     0.44467153665224024 * tmp_62;
      real_t a_2_0 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.71746406342630831 * tmp_32 + 0.5837973783021444 * tmp_33 + 0.02143393012713057 * tmp_34 +
                     0.20413933387602909 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.23966807631943055 * tmp_38 + 0.0079239539457973684 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.23966807631943055 * tmp_41 + 0.0079239539457973684 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.23966807631943055 * tmp_45 + 0.0079239539457973684 * tmp_46 +
                     0.02143393012713057 * tmp_47 + 0.20413933387602909 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.67614182511336729 * tmp_51 + 0.71746406342630831 * tmp_52 +
                     0.5837973783021444 * tmp_53 + 0.71746406342630831 * tmp_54 + 0.5837973783021444 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.44467153665224024 * tmp_58 +
                     0.8730503689456981 * tmp_59 + 0.057454872627883069 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      real_t a_3_0 = 0.67614182511336729 * tmp_17 + 0.44467153665224024 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.8730503689456981 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.23966807631943055 * tmp_32 + 0.0079239539457973684 * tmp_33 + 0.23966807631943055 * tmp_34 +
                     0.0079239539457973684 * tmp_35 + 0.23966807631943055 * tmp_36 + 0.0079239539457973684 * tmp_37 +
                     0.02143393012713057 * tmp_38 + 0.20413933387602909 * tmp_39 + 0.057454872627883069 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.71746406342630831 * tmp_45 + 0.5837973783021444 * tmp_46 +
                     0.71746406342630831 * tmp_47 + 0.5837973783021444 * tmp_48 + 0.71746406342630831 * tmp_49 +
                     0.5837973783021444 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.02143393012713057 * tmp_52 +
                     0.20413933387602909 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      elMat( 0, 0 ) = a_0_0;
      elMat( 1, 0 ) = a_1_0;
      elMat( 2, 0 ) = a_2_0;
      elMat( 3, 0 ) = a_3_0;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }


};

class EGVectorMassFormP1E_2 : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t a_0_0  = 0;
      real_t a_1_0  = 0;
      real_t a_2_0  = 0;
      elMat( 0, 0 ) = a_0_0;
      elMat( 1, 0 ) = a_1_0;
      elMat( 2, 0 ) = a_2_0;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
  void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0  = -p_affine_0_2;
      real_t tmp_1  = p_affine_1_2 + tmp_0;
      real_t tmp_2  = p_affine_2_2 + tmp_0;
      real_t tmp_3  = p_affine_3_2 + tmp_0;
      real_t tmp_4  = p_affine_0_0 * p_affine_1_1;
      real_t tmp_5  = p_affine_0_0 * p_affine_1_2;
      real_t tmp_6  = p_affine_2_1 * p_affine_3_2;
      real_t tmp_7  = p_affine_0_1 * p_affine_1_0;
      real_t tmp_8  = p_affine_0_1 * p_affine_1_2;
      real_t tmp_9  = p_affine_2_2 * p_affine_3_0;
      real_t tmp_10 = p_affine_0_2 * p_affine_1_0;
      real_t tmp_11 = p_affine_0_2 * p_affine_1_1;
      real_t tmp_12 = p_affine_2_0 * p_affine_3_1;
      real_t tmp_13 = p_affine_2_2 * p_affine_3_1;
      real_t tmp_14 = p_affine_2_0 * p_affine_3_2;
      real_t tmp_15 = p_affine_2_1 * p_affine_3_0;
      real_t tmp_16 = std::abs( p_affine_0_0 * tmp_13 - p_affine_0_0 * tmp_6 + p_affine_0_1 * tmp_14 - p_affine_0_1 * tmp_9 -
                                p_affine_0_2 * tmp_12 + p_affine_0_2 * tmp_15 - p_affine_1_0 * tmp_13 + p_affine_1_0 * tmp_6 -
                                p_affine_1_1 * tmp_14 + p_affine_1_1 * tmp_9 + p_affine_1_2 * tmp_12 - p_affine_1_2 * tmp_15 +
                                p_affine_2_0 * tmp_11 - p_affine_2_0 * tmp_8 - p_affine_2_1 * tmp_10 + p_affine_2_1 * tmp_5 -
                                p_affine_2_2 * tmp_4 + p_affine_2_2 * tmp_7 - p_affine_3_0 * tmp_11 + p_affine_3_0 * tmp_8 +
                                p_affine_3_1 * tmp_10 - p_affine_3_1 * tmp_5 + p_affine_3_2 * tmp_4 - p_affine_3_2 * tmp_7 );
      real_t tmp_17 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 + 0.42614182511336729 * tmp_3 );
      real_t tmp_18 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 + 0.19467153665224024 * tmp_3 );
      real_t tmp_19 = 0.0012542093589233661 * tmp_16 *
                      ( 0.6230503689456981 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_20 = 0.0069606304761558151 * tmp_16 *
                      ( -0.19254512737211693 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_21 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_22 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_23 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_24 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_25 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_26 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_27 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_28 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_29 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 + 0.6230503689456981 * tmp_3 );
      real_t tmp_30 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_31 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_32 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_33 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_34 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_35 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_36 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_37 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_38 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_39 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_40 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 - 0.19254512737211693 * tmp_3 );
      real_t tmp_41 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_42 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_43 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_44 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_45 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_46 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_47 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_48 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_49 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_50 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_51 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 + 0.42614182511336729 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_52 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_53 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_54 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_55 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_56 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_57 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_58 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 + 0.19467153665224024 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_59 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 + 0.6230503689456981 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_60 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 - 0.19254512737211693 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_61 = 0.0044044418180681378 * tmp_16 *
                      ( 0.42614182511336729 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_62 = 0.0086719579272897529 * tmp_16 *
                      ( 0.19467153665224024 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t a_0_0 = 0.10795272496221098 * tmp_17 + 0.18510948778258651 * tmp_18 + 0.042316543684767338 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.6761418251133674 * tmp_21 + 0.44467153665224013 * tmp_22 +
                     0.87305036894569832 * tmp_23 + 0.057454872627883069 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.042316543684767449 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.021433930127130574 * tmp_32 + 0.20413933387602912 * tmp_33 + 0.021433930127130574 * tmp_34 +
                     0.20413933387602914 * tmp_35 + 0.71746406342630831 * tmp_36 + 0.5837973783021444 * tmp_37 +
                     0.021433930127130577 * tmp_38 + 0.20413933387602914 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.71746406342630831 * tmp_41 + 0.5837973783021444 * tmp_42 + 0.71746406342630831 * tmp_43 +
                     0.5837973783021444 * tmp_44 + 0.021433930127130574 * tmp_45 + 0.20413933387602912 * tmp_46 +
                     0.021433930127130574 * tmp_47 + 0.20413933387602912 * tmp_48 + 0.23966807631943055 * tmp_49 +
                     0.0079239539457973684 * tmp_50 + 0.10795272496221095 * tmp_51 + 0.021433930127130577 * tmp_52 +
                     0.20413933387602914 * tmp_53 + 0.23966807631943055 * tmp_54 + 0.0079239539457973962 * tmp_55 +
                     0.23966807631943055 * tmp_56 + 0.007923953945797424 * tmp_57 + 0.18510948778258654 * tmp_58 +
                     0.042316543684767394 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221092 * tmp_61 +
                     0.18510948778258654 * tmp_62;
      real_t a_1_0 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.8730503689456981 * tmp_19 +
                     0.057454872627883069 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.02143393012713057 * tmp_32 + 0.20413933387602909 * tmp_33 + 0.71746406342630831 * tmp_34 +
                     0.5837973783021444 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.71746406342630831 * tmp_38 + 0.5837973783021444 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.23966807631943055 * tmp_43 +
                     0.0079239539457973684 * tmp_44 + 0.02143393012713057 * tmp_45 + 0.20413933387602909 * tmp_46 +
                     0.23966807631943055 * tmp_47 + 0.0079239539457973684 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.23966807631943055 * tmp_52 +
                     0.0079239539457973684 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.71746406342630831 * tmp_56 + 0.5837973783021444 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.67614182511336729 * tmp_61 +
                     0.44467153665224024 * tmp_62;
      real_t a_2_0 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.71746406342630831 * tmp_32 + 0.5837973783021444 * tmp_33 + 0.02143393012713057 * tmp_34 +
                     0.20413933387602909 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.23966807631943055 * tmp_38 + 0.0079239539457973684 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.23966807631943055 * tmp_41 + 0.0079239539457973684 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.23966807631943055 * tmp_45 + 0.0079239539457973684 * tmp_46 +
                     0.02143393012713057 * tmp_47 + 0.20413933387602909 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.67614182511336729 * tmp_51 + 0.71746406342630831 * tmp_52 +
                     0.5837973783021444 * tmp_53 + 0.71746406342630831 * tmp_54 + 0.5837973783021444 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.44467153665224024 * tmp_58 +
                     0.8730503689456981 * tmp_59 + 0.057454872627883069 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      real_t a_3_0 = 0.67614182511336729 * tmp_17 + 0.44467153665224024 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.8730503689456981 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.23966807631943055 * tmp_32 + 0.0079239539457973684 * tmp_33 + 0.23966807631943055 * tmp_34 +
                     0.0079239539457973684 * tmp_35 + 0.23966807631943055 * tmp_36 + 0.0079239539457973684 * tmp_37 +
                     0.02143393012713057 * tmp_38 + 0.20413933387602909 * tmp_39 + 0.057454872627883069 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.71746406342630831 * tmp_45 + 0.5837973783021444 * tmp_46 +
                     0.71746406342630831 * tmp_47 + 0.5837973783021444 * tmp_48 + 0.71746406342630831 * tmp_49 +
                     0.5837973783021444 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.02143393012713057 * tmp_52 +
                     0.20413933387602909 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      elMat( 0, 0 ) = a_0_0;
      elMat( 1, 0 ) = a_1_0;
      elMat( 2, 0 ) = a_2_0;
      elMat( 3, 0 ) = a_3_0;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 3, 0 ) = 0;
   }


};

class EGVectorMassFormEP1_0 : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t tmp_0  = -p_affine_0_0;
      real_t tmp_1  = p_affine_1_0 + tmp_0;
      real_t tmp_2  = p_affine_2_0 + tmp_0;
      real_t tmp_3  = std::abs( p_affine_0_0 * p_affine_1_1 - p_affine_0_0 * p_affine_2_1 - p_affine_0_1 * p_affine_1_0 +
                               p_affine_0_1 * p_affine_2_0 + p_affine_1_0 * p_affine_2_1 - p_affine_1_1 * p_affine_2_0 );
      real_t tmp_4  = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 + 0.54048863768366218 * tmp_2 );
      real_t tmp_5  = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 + 0.16809317632484583 * tmp_2 );
      real_t tmp_6  = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_7  = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_8  = 0.025422453185103409 * tmp_3 * ( 0.54048863768366218 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_9  = 0.058393137863189684 * tmp_3 * ( 0.16809317632484583 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_10 = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_11 = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_12 = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t tmp_13 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_14 = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_15 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t a_0_0  = 0.87382197101699566 * tmp_10 + 0.50142650965817914 * tmp_11 + 0.053145049844816938 * tmp_12 +
                     0.63650249912139867 * tmp_13 + 0.31035245103378439 * tmp_14 + 0.31035245103378439 * tmp_15 +
                     0.063089014491502282 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.63650249912139867 * tmp_6 +
                     0.053145049844816938 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      real_t a_0_1 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.31035245103378439 * tmp_12 +
                     0.053145049844816938 * tmp_13 + 0.63650249912139867 * tmp_14 + 0.053145049844816938 * tmp_15 +
                     0.063089014491502227 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.31035245103378439 * tmp_6 +
                     0.63650249912139867 * tmp_7 + 0.87382197101699555 * tmp_8 + 0.50142650965817914 * tmp_9;
      real_t a_0_2 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.63650249912139867 * tmp_12 +
                     0.31035245103378439 * tmp_13 + 0.053145049844816938 * tmp_14 + 0.63650249912139867 * tmp_15 +
                     0.87382197101699555 * tmp_4 + 0.50142650965817914 * tmp_5 + 0.053145049844816938 * tmp_6 +
                     0.31035245103378439 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
  void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0  = -p_affine_0_0;
      real_t tmp_1  = p_affine_1_0 + tmp_0;
      real_t tmp_2  = p_affine_2_0 + tmp_0;
      real_t tmp_3  = p_affine_3_0 + tmp_0;
      real_t tmp_4  = p_affine_0_0 * p_affine_1_1;
      real_t tmp_5  = p_affine_0_0 * p_affine_1_2;
      real_t tmp_6  = p_affine_2_1 * p_affine_3_2;
      real_t tmp_7  = p_affine_0_1 * p_affine_1_0;
      real_t tmp_8  = p_affine_0_1 * p_affine_1_2;
      real_t tmp_9  = p_affine_2_2 * p_affine_3_0;
      real_t tmp_10 = p_affine_0_2 * p_affine_1_0;
      real_t tmp_11 = p_affine_0_2 * p_affine_1_1;
      real_t tmp_12 = p_affine_2_0 * p_affine_3_1;
      real_t tmp_13 = p_affine_2_2 * p_affine_3_1;
      real_t tmp_14 = p_affine_2_0 * p_affine_3_2;
      real_t tmp_15 = p_affine_2_1 * p_affine_3_0;
      real_t tmp_16 = std::abs( p_affine_0_0 * tmp_13 - p_affine_0_0 * tmp_6 + p_affine_0_1 * tmp_14 - p_affine_0_1 * tmp_9 -
                                p_affine_0_2 * tmp_12 + p_affine_0_2 * tmp_15 - p_affine_1_0 * tmp_13 + p_affine_1_0 * tmp_6 -
                                p_affine_1_1 * tmp_14 + p_affine_1_1 * tmp_9 + p_affine_1_2 * tmp_12 - p_affine_1_2 * tmp_15 +
                                p_affine_2_0 * tmp_11 - p_affine_2_0 * tmp_8 - p_affine_2_1 * tmp_10 + p_affine_2_1 * tmp_5 -
                                p_affine_2_2 * tmp_4 + p_affine_2_2 * tmp_7 - p_affine_3_0 * tmp_11 + p_affine_3_0 * tmp_8 +
                                p_affine_3_1 * tmp_10 - p_affine_3_1 * tmp_5 + p_affine_3_2 * tmp_4 - p_affine_3_2 * tmp_7 );
      real_t tmp_17 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 + 0.42614182511336729 * tmp_3 );
      real_t tmp_18 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 + 0.19467153665224024 * tmp_3 );
      real_t tmp_19 = 0.0012542093589233661 * tmp_16 *
                      ( 0.6230503689456981 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_20 = 0.0069606304761558151 * tmp_16 *
                      ( -0.19254512737211693 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_21 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_22 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_23 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_24 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_25 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_26 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_27 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_28 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_29 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 + 0.6230503689456981 * tmp_3 );
      real_t tmp_30 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_31 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_32 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_33 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_34 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_35 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_36 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_37 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_38 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_39 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_40 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 - 0.19254512737211693 * tmp_3 );
      real_t tmp_41 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_42 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_43 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_44 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_45 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_46 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_47 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_48 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_49 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_50 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_51 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 + 0.42614182511336729 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_52 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_53 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_54 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_55 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_56 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_57 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_58 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 + 0.19467153665224024 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_59 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 + 0.6230503689456981 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_60 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 - 0.19254512737211693 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_61 = 0.0044044418180681378 * tmp_16 *
                      ( 0.42614182511336729 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_62 = 0.0086719579272897529 * tmp_16 *
                      ( 0.19467153665224024 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t a_0_0 = 0.10795272496221098 * tmp_17 + 0.18510948778258651 * tmp_18 + 0.042316543684767338 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.6761418251133674 * tmp_21 + 0.44467153665224013 * tmp_22 +
                     0.87305036894569832 * tmp_23 + 0.057454872627883069 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.042316543684767449 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.021433930127130574 * tmp_32 + 0.20413933387602912 * tmp_33 + 0.021433930127130574 * tmp_34 +
                     0.20413933387602914 * tmp_35 + 0.71746406342630831 * tmp_36 + 0.5837973783021444 * tmp_37 +
                     0.021433930127130577 * tmp_38 + 0.20413933387602914 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.71746406342630831 * tmp_41 + 0.5837973783021444 * tmp_42 + 0.71746406342630831 * tmp_43 +
                     0.5837973783021444 * tmp_44 + 0.021433930127130574 * tmp_45 + 0.20413933387602912 * tmp_46 +
                     0.021433930127130574 * tmp_47 + 0.20413933387602912 * tmp_48 + 0.23966807631943055 * tmp_49 +
                     0.0079239539457973684 * tmp_50 + 0.10795272496221095 * tmp_51 + 0.021433930127130577 * tmp_52 +
                     0.20413933387602914 * tmp_53 + 0.23966807631943055 * tmp_54 + 0.0079239539457973962 * tmp_55 +
                     0.23966807631943055 * tmp_56 + 0.007923953945797424 * tmp_57 + 0.18510948778258654 * tmp_58 +
                     0.042316543684767394 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221092 * tmp_61 +
                     0.18510948778258654 * tmp_62;
      real_t a_0_1 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.8730503689456981 * tmp_19 +
                     0.057454872627883069 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.02143393012713057 * tmp_32 + 0.20413933387602909 * tmp_33 + 0.71746406342630831 * tmp_34 +
                     0.5837973783021444 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.71746406342630831 * tmp_38 + 0.5837973783021444 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.23966807631943055 * tmp_43 +
                     0.0079239539457973684 * tmp_44 + 0.02143393012713057 * tmp_45 + 0.20413933387602909 * tmp_46 +
                     0.23966807631943055 * tmp_47 + 0.0079239539457973684 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.23966807631943055 * tmp_52 +
                     0.0079239539457973684 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.71746406342630831 * tmp_56 + 0.5837973783021444 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.67614182511336729 * tmp_61 +
                     0.44467153665224024 * tmp_62;
      real_t a_0_2 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.71746406342630831 * tmp_32 + 0.5837973783021444 * tmp_33 + 0.02143393012713057 * tmp_34 +
                     0.20413933387602909 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.23966807631943055 * tmp_38 + 0.0079239539457973684 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.23966807631943055 * tmp_41 + 0.0079239539457973684 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.23966807631943055 * tmp_45 + 0.0079239539457973684 * tmp_46 +
                     0.02143393012713057 * tmp_47 + 0.20413933387602909 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.67614182511336729 * tmp_51 + 0.71746406342630831 * tmp_52 +
                     0.5837973783021444 * tmp_53 + 0.71746406342630831 * tmp_54 + 0.5837973783021444 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.44467153665224024 * tmp_58 +
                     0.8730503689456981 * tmp_59 + 0.057454872627883069 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      real_t a_0_3 = 0.67614182511336729 * tmp_17 + 0.44467153665224024 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.8730503689456981 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.23966807631943055 * tmp_32 + 0.0079239539457973684 * tmp_33 + 0.23966807631943055 * tmp_34 +
                     0.0079239539457973684 * tmp_35 + 0.23966807631943055 * tmp_36 + 0.0079239539457973684 * tmp_37 +
                     0.02143393012713057 * tmp_38 + 0.20413933387602909 * tmp_39 + 0.057454872627883069 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.71746406342630831 * tmp_45 + 0.5837973783021444 * tmp_46 +
                     0.71746406342630831 * tmp_47 + 0.5837973783021444 * tmp_48 + 0.71746406342630831 * tmp_49 +
                     0.5837973783021444 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.02143393012713057 * tmp_52 +
                     0.20413933387602909 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
      elMat( 0, 3 ) = a_0_3;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }


};

class EGVectorMassFormEP1_1 : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t tmp_0  = -p_affine_0_1;
      real_t tmp_1  = p_affine_1_1 + tmp_0;
      real_t tmp_2  = p_affine_2_1 + tmp_0;
      real_t tmp_3  = std::abs( p_affine_0_0 * p_affine_1_1 - p_affine_0_0 * p_affine_2_1 - p_affine_0_1 * p_affine_1_0 +
                               p_affine_0_1 * p_affine_2_0 + p_affine_1_0 * p_affine_2_1 - p_affine_1_1 * p_affine_2_0 );
      real_t tmp_4  = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 + 0.54048863768366218 * tmp_2 );
      real_t tmp_5  = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 + 0.16809317632484583 * tmp_2 );
      real_t tmp_6  = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_7  = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_8  = 0.025422453185103409 * tmp_3 * ( 0.54048863768366218 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_9  = 0.058393137863189684 * tmp_3 * ( 0.16809317632484583 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_10 = 0.025422453185103409 * tmp_3 * ( -0.27024431884183109 * tmp_1 - 0.27024431884183109 * tmp_2 );
      real_t tmp_11 = 0.058393137863189684 * tmp_3 * ( -0.084046588162422886 * tmp_1 - 0.084046588162422886 * tmp_2 );
      real_t tmp_12 = 0.041425537809186785 * tmp_3 * ( -0.022980882299548921 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t tmp_13 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 - 0.022980882299548921 * tmp_2 );
      real_t tmp_14 = 0.041425537809186785 * tmp_3 * ( 0.30316916578806535 * tmp_1 - 0.28018828348851638 * tmp_2 );
      real_t tmp_15 = 0.041425537809186785 * tmp_3 * ( -0.28018828348851638 * tmp_1 + 0.30316916578806535 * tmp_2 );
      real_t a_0_0  = 0.87382197101699566 * tmp_10 + 0.50142650965817914 * tmp_11 + 0.053145049844816938 * tmp_12 +
                     0.63650249912139867 * tmp_13 + 0.31035245103378439 * tmp_14 + 0.31035245103378439 * tmp_15 +
                     0.063089014491502282 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.63650249912139867 * tmp_6 +
                     0.053145049844816938 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      real_t a_0_1 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.31035245103378439 * tmp_12 +
                     0.053145049844816938 * tmp_13 + 0.63650249912139867 * tmp_14 + 0.053145049844816938 * tmp_15 +
                     0.063089014491502227 * tmp_4 + 0.24928674517091043 * tmp_5 + 0.31035245103378439 * tmp_6 +
                     0.63650249912139867 * tmp_7 + 0.87382197101699555 * tmp_8 + 0.50142650965817914 * tmp_9;
      real_t a_0_2 = 0.063089014491502227 * tmp_10 + 0.24928674517091043 * tmp_11 + 0.63650249912139867 * tmp_12 +
                     0.31035245103378439 * tmp_13 + 0.053145049844816938 * tmp_14 + 0.63650249912139867 * tmp_15 +
                     0.87382197101699555 * tmp_4 + 0.50142650965817914 * tmp_5 + 0.053145049844816938 * tmp_6 +
                     0.31035245103378439 * tmp_7 + 0.063089014491502227 * tmp_8 + 0.24928674517091043 * tmp_9;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
  void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0  = -p_affine_0_1;
      real_t tmp_1  = p_affine_1_1 + tmp_0;
      real_t tmp_2  = p_affine_2_1 + tmp_0;
      real_t tmp_3  = p_affine_3_1 + tmp_0;
      real_t tmp_4  = p_affine_0_0 * p_affine_1_1;
      real_t tmp_5  = p_affine_0_0 * p_affine_1_2;
      real_t tmp_6  = p_affine_2_1 * p_affine_3_2;
      real_t tmp_7  = p_affine_0_1 * p_affine_1_0;
      real_t tmp_8  = p_affine_0_1 * p_affine_1_2;
      real_t tmp_9  = p_affine_2_2 * p_affine_3_0;
      real_t tmp_10 = p_affine_0_2 * p_affine_1_0;
      real_t tmp_11 = p_affine_0_2 * p_affine_1_1;
      real_t tmp_12 = p_affine_2_0 * p_affine_3_1;
      real_t tmp_13 = p_affine_2_2 * p_affine_3_1;
      real_t tmp_14 = p_affine_2_0 * p_affine_3_2;
      real_t tmp_15 = p_affine_2_1 * p_affine_3_0;
      real_t tmp_16 = std::abs( p_affine_0_0 * tmp_13 - p_affine_0_0 * tmp_6 + p_affine_0_1 * tmp_14 - p_affine_0_1 * tmp_9 -
                                p_affine_0_2 * tmp_12 + p_affine_0_2 * tmp_15 - p_affine_1_0 * tmp_13 + p_affine_1_0 * tmp_6 -
                                p_affine_1_1 * tmp_14 + p_affine_1_1 * tmp_9 + p_affine_1_2 * tmp_12 - p_affine_1_2 * tmp_15 +
                                p_affine_2_0 * tmp_11 - p_affine_2_0 * tmp_8 - p_affine_2_1 * tmp_10 + p_affine_2_1 * tmp_5 -
                                p_affine_2_2 * tmp_4 + p_affine_2_2 * tmp_7 - p_affine_3_0 * tmp_11 + p_affine_3_0 * tmp_8 +
                                p_affine_3_1 * tmp_10 - p_affine_3_1 * tmp_5 + p_affine_3_2 * tmp_4 - p_affine_3_2 * tmp_7 );
      real_t tmp_17 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 + 0.42614182511336729 * tmp_3 );
      real_t tmp_18 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 + 0.19467153665224024 * tmp_3 );
      real_t tmp_19 = 0.0012542093589233661 * tmp_16 *
                      ( 0.6230503689456981 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_20 = 0.0069606304761558151 * tmp_16 *
                      ( -0.19254512737211693 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_21 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_22 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_23 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_24 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_25 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_26 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_27 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_28 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_29 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 + 0.6230503689456981 * tmp_3 );
      real_t tmp_30 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_31 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_32 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_33 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_34 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_35 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_36 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_37 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_38 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_39 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_40 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 - 0.19254512737211693 * tmp_3 );
      real_t tmp_41 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_42 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_43 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_44 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_45 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_46 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_47 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_48 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_49 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_50 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_51 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 + 0.42614182511336729 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_52 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_53 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_54 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_55 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_56 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_57 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_58 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 + 0.19467153665224024 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_59 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 + 0.6230503689456981 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_60 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 - 0.19254512737211693 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_61 = 0.0044044418180681378 * tmp_16 *
                      ( 0.42614182511336729 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_62 = 0.0086719579272897529 * tmp_16 *
                      ( 0.19467153665224024 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t a_0_0 = 0.10795272496221098 * tmp_17 + 0.18510948778258651 * tmp_18 + 0.042316543684767338 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.6761418251133674 * tmp_21 + 0.44467153665224013 * tmp_22 +
                     0.87305036894569832 * tmp_23 + 0.057454872627883069 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.042316543684767449 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.021433930127130574 * tmp_32 + 0.20413933387602912 * tmp_33 + 0.021433930127130574 * tmp_34 +
                     0.20413933387602914 * tmp_35 + 0.71746406342630831 * tmp_36 + 0.5837973783021444 * tmp_37 +
                     0.021433930127130577 * tmp_38 + 0.20413933387602914 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.71746406342630831 * tmp_41 + 0.5837973783021444 * tmp_42 + 0.71746406342630831 * tmp_43 +
                     0.5837973783021444 * tmp_44 + 0.021433930127130574 * tmp_45 + 0.20413933387602912 * tmp_46 +
                     0.021433930127130574 * tmp_47 + 0.20413933387602912 * tmp_48 + 0.23966807631943055 * tmp_49 +
                     0.0079239539457973684 * tmp_50 + 0.10795272496221095 * tmp_51 + 0.021433930127130577 * tmp_52 +
                     0.20413933387602914 * tmp_53 + 0.23966807631943055 * tmp_54 + 0.0079239539457973962 * tmp_55 +
                     0.23966807631943055 * tmp_56 + 0.007923953945797424 * tmp_57 + 0.18510948778258654 * tmp_58 +
                     0.042316543684767394 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221092 * tmp_61 +
                     0.18510948778258654 * tmp_62;
      real_t a_0_1 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.8730503689456981 * tmp_19 +
                     0.057454872627883069 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.02143393012713057 * tmp_32 + 0.20413933387602909 * tmp_33 + 0.71746406342630831 * tmp_34 +
                     0.5837973783021444 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.71746406342630831 * tmp_38 + 0.5837973783021444 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.23966807631943055 * tmp_43 +
                     0.0079239539457973684 * tmp_44 + 0.02143393012713057 * tmp_45 + 0.20413933387602909 * tmp_46 +
                     0.23966807631943055 * tmp_47 + 0.0079239539457973684 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.23966807631943055 * tmp_52 +
                     0.0079239539457973684 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.71746406342630831 * tmp_56 + 0.5837973783021444 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.67614182511336729 * tmp_61 +
                     0.44467153665224024 * tmp_62;
      real_t a_0_2 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.71746406342630831 * tmp_32 + 0.5837973783021444 * tmp_33 + 0.02143393012713057 * tmp_34 +
                     0.20413933387602909 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.23966807631943055 * tmp_38 + 0.0079239539457973684 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.23966807631943055 * tmp_41 + 0.0079239539457973684 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.23966807631943055 * tmp_45 + 0.0079239539457973684 * tmp_46 +
                     0.02143393012713057 * tmp_47 + 0.20413933387602909 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.67614182511336729 * tmp_51 + 0.71746406342630831 * tmp_52 +
                     0.5837973783021444 * tmp_53 + 0.71746406342630831 * tmp_54 + 0.5837973783021444 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.44467153665224024 * tmp_58 +
                     0.8730503689456981 * tmp_59 + 0.057454872627883069 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      real_t a_0_3 = 0.67614182511336729 * tmp_17 + 0.44467153665224024 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.8730503689456981 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.23966807631943055 * tmp_32 + 0.0079239539457973684 * tmp_33 + 0.23966807631943055 * tmp_34 +
                     0.0079239539457973684 * tmp_35 + 0.23966807631943055 * tmp_36 + 0.0079239539457973684 * tmp_37 +
                     0.02143393012713057 * tmp_38 + 0.20413933387602909 * tmp_39 + 0.057454872627883069 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.71746406342630831 * tmp_45 + 0.5837973783021444 * tmp_46 +
                     0.71746406342630831 * tmp_47 + 0.5837973783021444 * tmp_48 + 0.71746406342630831 * tmp_49 +
                     0.5837973783021444 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.02143393012713057 * tmp_52 +
                     0.20413933387602909 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
      elMat( 0, 3 ) = a_0_3;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }

};

class EGVectorMassFormEP1_2 : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t a_0_0  = 0;
      real_t a_0_1  = 0;
      real_t a_0_2  = 0;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
  void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0  = -p_affine_0_2;
      real_t tmp_1  = p_affine_1_2 + tmp_0;
      real_t tmp_2  = p_affine_2_2 + tmp_0;
      real_t tmp_3  = p_affine_3_2 + tmp_0;
      real_t tmp_4  = p_affine_0_0 * p_affine_1_1;
      real_t tmp_5  = p_affine_0_0 * p_affine_1_2;
      real_t tmp_6  = p_affine_2_1 * p_affine_3_2;
      real_t tmp_7  = p_affine_0_1 * p_affine_1_0;
      real_t tmp_8  = p_affine_0_1 * p_affine_1_2;
      real_t tmp_9  = p_affine_2_2 * p_affine_3_0;
      real_t tmp_10 = p_affine_0_2 * p_affine_1_0;
      real_t tmp_11 = p_affine_0_2 * p_affine_1_1;
      real_t tmp_12 = p_affine_2_0 * p_affine_3_1;
      real_t tmp_13 = p_affine_2_2 * p_affine_3_1;
      real_t tmp_14 = p_affine_2_0 * p_affine_3_2;
      real_t tmp_15 = p_affine_2_1 * p_affine_3_0;
      real_t tmp_16 = std::abs( p_affine_0_0 * tmp_13 - p_affine_0_0 * tmp_6 + p_affine_0_1 * tmp_14 - p_affine_0_1 * tmp_9 -
                                p_affine_0_2 * tmp_12 + p_affine_0_2 * tmp_15 - p_affine_1_0 * tmp_13 + p_affine_1_0 * tmp_6 -
                                p_affine_1_1 * tmp_14 + p_affine_1_1 * tmp_9 + p_affine_1_2 * tmp_12 - p_affine_1_2 * tmp_15 +
                                p_affine_2_0 * tmp_11 - p_affine_2_0 * tmp_8 - p_affine_2_1 * tmp_10 + p_affine_2_1 * tmp_5 -
                                p_affine_2_2 * tmp_4 + p_affine_2_2 * tmp_7 - p_affine_3_0 * tmp_11 + p_affine_3_0 * tmp_8 +
                                p_affine_3_1 * tmp_10 - p_affine_3_1 * tmp_5 + p_affine_3_2 * tmp_4 - p_affine_3_2 * tmp_7 );
      real_t tmp_17 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 + 0.42614182511336729 * tmp_3 );
      real_t tmp_18 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 + 0.19467153665224024 * tmp_3 );
      real_t tmp_19 = 0.0012542093589233661 * tmp_16 *
                      ( 0.6230503689456981 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_20 = 0.0069606304761558151 * tmp_16 *
                      ( -0.19254512737211693 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_21 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_22 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_23 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_24 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_25 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_26 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_27 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 - 0.18559132858383021 * tmp_3 );
      real_t tmp_28 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_29 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 - 0.20768345631523272 * tmp_2 + 0.6230503689456981 * tmp_3 );
      real_t tmp_30 = 0.0060468217102181351 * tmp_16 *
                      ( 0.18559132858383021 * tmp_1 - 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_31 = 0.0060468217102181351 * tmp_16 *
                      ( -0.18559132858383021 * tmp_1 + 0.18559132858383021 * tmp_2 + 0.18559132858383021 * tmp_3 );
      real_t tmp_32 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_33 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_34 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_35 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_36 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.010331923680569455 * tmp_3 );
      real_t tmp_37 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.24207604605420263 * tmp_3 );
      real_t tmp_38 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_39 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_40 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 + 0.064181709124038977 * tmp_2 - 0.19254512737211693 * tmp_3 );
      real_t tmp_41 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_42 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_43 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_44 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_45 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.010331923680569455 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_46 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.24207604605420263 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_47 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_48 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_49 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 - 0.22856606987286943 * tmp_2 + 0.46746406342630831 * tmp_3 );
      real_t tmp_50 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 - 0.045860666123970911 * tmp_2 + 0.3337973783021444 * tmp_3 );
      real_t tmp_51 = 0.0044044418180681378 * tmp_16 *
                      ( -0.14204727503778911 * tmp_1 + 0.42614182511336729 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_52 = 0.0011928171484740719 * tmp_16 *
                      ( -0.010331923680569455 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_53 = 0.0025755810251600563 * tmp_16 *
                      ( -0.24207604605420263 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_54 = 0.0011928171484740719 * tmp_16 *
                      ( -0.22856606987286943 * tmp_1 + 0.46746406342630831 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_55 = 0.0025755810251600563 * tmp_16 *
                      ( -0.045860666123970911 * tmp_1 + 0.3337973783021444 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_56 = 0.0011928171484740719 * tmp_16 *
                      ( 0.46746406342630831 * tmp_1 - 0.22856606987286943 * tmp_2 - 0.22856606987286943 * tmp_3 );
      real_t tmp_57 = 0.0025755810251600563 * tmp_16 *
                      ( 0.3337973783021444 * tmp_1 - 0.045860666123970911 * tmp_2 - 0.045860666123970911 * tmp_3 );
      real_t tmp_58 = 0.0086719579272897529 * tmp_16 *
                      ( -0.064890512217413404 * tmp_1 + 0.19467153665224024 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t tmp_59 = 0.0012542093589233661 * tmp_16 *
                      ( -0.20768345631523272 * tmp_1 + 0.6230503689456981 * tmp_2 - 0.20768345631523272 * tmp_3 );
      real_t tmp_60 = 0.0069606304761558151 * tmp_16 *
                      ( 0.064181709124038977 * tmp_1 - 0.19254512737211693 * tmp_2 + 0.064181709124038977 * tmp_3 );
      real_t tmp_61 = 0.0044044418180681378 * tmp_16 *
                      ( 0.42614182511336729 * tmp_1 - 0.14204727503778911 * tmp_2 - 0.14204727503778911 * tmp_3 );
      real_t tmp_62 = 0.0086719579272897529 * tmp_16 *
                      ( 0.19467153665224024 * tmp_1 - 0.064890512217413404 * tmp_2 - 0.064890512217413404 * tmp_3 );
      real_t a_0_0 = 0.10795272496221098 * tmp_17 + 0.18510948778258651 * tmp_18 + 0.042316543684767338 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.6761418251133674 * tmp_21 + 0.44467153665224013 * tmp_22 +
                     0.87305036894569832 * tmp_23 + 0.057454872627883069 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.042316543684767449 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.021433930127130574 * tmp_32 + 0.20413933387602912 * tmp_33 + 0.021433930127130574 * tmp_34 +
                     0.20413933387602914 * tmp_35 + 0.71746406342630831 * tmp_36 + 0.5837973783021444 * tmp_37 +
                     0.021433930127130577 * tmp_38 + 0.20413933387602914 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.71746406342630831 * tmp_41 + 0.5837973783021444 * tmp_42 + 0.71746406342630831 * tmp_43 +
                     0.5837973783021444 * tmp_44 + 0.021433930127130574 * tmp_45 + 0.20413933387602912 * tmp_46 +
                     0.021433930127130574 * tmp_47 + 0.20413933387602912 * tmp_48 + 0.23966807631943055 * tmp_49 +
                     0.0079239539457973684 * tmp_50 + 0.10795272496221095 * tmp_51 + 0.021433930127130577 * tmp_52 +
                     0.20413933387602914 * tmp_53 + 0.23966807631943055 * tmp_54 + 0.0079239539457973962 * tmp_55 +
                     0.23966807631943055 * tmp_56 + 0.007923953945797424 * tmp_57 + 0.18510948778258654 * tmp_58 +
                     0.042316543684767394 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221092 * tmp_61 +
                     0.18510948778258654 * tmp_62;
      real_t a_0_1 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.8730503689456981 * tmp_19 +
                     0.057454872627883069 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.43559132858383021 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.064408671416169794 * tmp_31 +
                     0.02143393012713057 * tmp_32 + 0.20413933387602909 * tmp_33 + 0.71746406342630831 * tmp_34 +
                     0.5837973783021444 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.71746406342630831 * tmp_38 + 0.5837973783021444 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.23966807631943055 * tmp_43 +
                     0.0079239539457973684 * tmp_44 + 0.02143393012713057 * tmp_45 + 0.20413933387602909 * tmp_46 +
                     0.23966807631943055 * tmp_47 + 0.0079239539457973684 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.23966807631943055 * tmp_52 +
                     0.0079239539457973684 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.71746406342630831 * tmp_56 + 0.5837973783021444 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.67614182511336729 * tmp_61 +
                     0.44467153665224024 * tmp_62;
      real_t a_0_2 = 0.10795272496221089 * tmp_17 + 0.1851094877825866 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.43559132858383021 * tmp_26 + 0.43559132858383021 * tmp_27 + 0.064408671416169794 * tmp_28 +
                     0.042316543684767283 * tmp_29 + 0.064408671416169794 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.71746406342630831 * tmp_32 + 0.5837973783021444 * tmp_33 + 0.02143393012713057 * tmp_34 +
                     0.20413933387602909 * tmp_35 + 0.02143393012713057 * tmp_36 + 0.20413933387602909 * tmp_37 +
                     0.23966807631943055 * tmp_38 + 0.0079239539457973684 * tmp_39 + 0.31418170912403898 * tmp_40 +
                     0.23966807631943055 * tmp_41 + 0.0079239539457973684 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.23966807631943055 * tmp_45 + 0.0079239539457973684 * tmp_46 +
                     0.02143393012713057 * tmp_47 + 0.20413933387602909 * tmp_48 + 0.02143393012713057 * tmp_49 +
                     0.20413933387602909 * tmp_50 + 0.67614182511336729 * tmp_51 + 0.71746406342630831 * tmp_52 +
                     0.5837973783021444 * tmp_53 + 0.71746406342630831 * tmp_54 + 0.5837973783021444 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.44467153665224024 * tmp_58 +
                     0.8730503689456981 * tmp_59 + 0.057454872627883069 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      real_t a_0_3 = 0.67614182511336729 * tmp_17 + 0.44467153665224024 * tmp_18 + 0.042316543684767283 * tmp_19 +
                     0.31418170912403898 * tmp_20 + 0.10795272496221089 * tmp_21 + 0.1851094877825866 * tmp_22 +
                     0.042316543684767283 * tmp_23 + 0.31418170912403898 * tmp_24 + 0.064408671416169794 * tmp_25 +
                     0.064408671416169794 * tmp_26 + 0.064408671416169794 * tmp_27 + 0.43559132858383021 * tmp_28 +
                     0.8730503689456981 * tmp_29 + 0.43559132858383021 * tmp_30 + 0.43559132858383021 * tmp_31 +
                     0.23966807631943055 * tmp_32 + 0.0079239539457973684 * tmp_33 + 0.23966807631943055 * tmp_34 +
                     0.0079239539457973684 * tmp_35 + 0.23966807631943055 * tmp_36 + 0.0079239539457973684 * tmp_37 +
                     0.02143393012713057 * tmp_38 + 0.20413933387602909 * tmp_39 + 0.057454872627883069 * tmp_40 +
                     0.02143393012713057 * tmp_41 + 0.20413933387602909 * tmp_42 + 0.02143393012713057 * tmp_43 +
                     0.20413933387602909 * tmp_44 + 0.71746406342630831 * tmp_45 + 0.5837973783021444 * tmp_46 +
                     0.71746406342630831 * tmp_47 + 0.5837973783021444 * tmp_48 + 0.71746406342630831 * tmp_49 +
                     0.5837973783021444 * tmp_50 + 0.10795272496221089 * tmp_51 + 0.02143393012713057 * tmp_52 +
                     0.20413933387602909 * tmp_53 + 0.02143393012713057 * tmp_54 + 0.20413933387602909 * tmp_55 +
                     0.02143393012713057 * tmp_56 + 0.20413933387602909 * tmp_57 + 0.1851094877825866 * tmp_58 +
                     0.042316543684767283 * tmp_59 + 0.31418170912403898 * tmp_60 + 0.10795272496221089 * tmp_61 +
                     0.1851094877825866 * tmp_62;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
      elMat( 0, 3 ) = a_0_3;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
   }


};

class EGVectorMassFormEE : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t tmp_0  = std::abs( p_affine_0_0 * p_affine_1_1 - p_affine_0_0 * p_affine_2_1 - p_affine_0_1 * p_affine_1_0 +
                               p_affine_0_1 * p_affine_2_0 + p_affine_1_0 * p_affine_2_1 - p_affine_1_1 * p_affine_2_0 );
      real_t tmp_1  = -0.27024431884183109;
      real_t tmp_2  = -p_affine_0_0;
      real_t tmp_3  = p_affine_1_0 + tmp_2;
      real_t tmp_4  = 0.54048863768366218;
      real_t tmp_5  = p_affine_2_0 + tmp_2;
      real_t tmp_6  = -p_affine_0_1;
      real_t tmp_7  = p_affine_1_1 + tmp_6;
      real_t tmp_8  = p_affine_2_1 + tmp_6;
      real_t tmp_9  = -0.084046588162422886;
      real_t tmp_10 = 0.16809317632484583;
      real_t tmp_11 = -0.022980882299548921;
      real_t tmp_12 = -0.28018828348851638;
      real_t tmp_13 = 0.30316916578806535;
      real_t tmp_14 = -0.022980882299548921;
      real_t tmp_15 = 0.54048863768366218;
      real_t tmp_16 = -0.27024431884183109;
      real_t tmp_17 = 0.16809317632484583;
      real_t tmp_18 = -0.084046588162422886;
      real_t tmp_19 = -0.27024431884183109;
      real_t tmp_20 = -0.27024431884183109;
      real_t tmp_21 = -0.084046588162422886;
      real_t tmp_22 = -0.084046588162422886;
      real_t tmp_23 = -0.022980882299548921;
      real_t tmp_24 = 0.30316916578806535;
      real_t tmp_25 = -0.28018828348851638;
      real_t tmp_26 = -0.022980882299548921;
      real_t tmp_27 = 0.30316916578806535;
      real_t tmp_28 = -0.28018828348851638;
      real_t tmp_29 = -0.28018828348851638;
      real_t tmp_30 = 0.30316916578806535;
      real_t a_0_0  = 0.025422453185103409 * tmp_0 *
                         ( ( ( tmp_1 * tmp_3 + tmp_4 * tmp_5 ) * ( tmp_1 * tmp_3 + tmp_4 * tmp_5 ) ) +
                           ( ( tmp_1 * tmp_7 + tmp_4 * tmp_8 ) * ( tmp_1 * tmp_7 + tmp_4 * tmp_8 ) ) ) +
                     0.058393137863189684 * tmp_0 *
                         ( ( ( tmp_10 * tmp_5 + tmp_3 * tmp_9 ) * ( tmp_10 * tmp_5 + tmp_3 * tmp_9 ) ) +
                           ( ( tmp_10 * tmp_8 + tmp_7 * tmp_9 ) * ( tmp_10 * tmp_8 + tmp_7 * tmp_9 ) ) ) +
                     0.041425537809186785 * tmp_0 *
                         ( ( ( tmp_11 * tmp_3 + tmp_12 * tmp_5 ) * ( tmp_11 * tmp_3 + tmp_12 * tmp_5 ) ) +
                           ( ( tmp_11 * tmp_7 + tmp_12 * tmp_8 ) * ( tmp_11 * tmp_7 + tmp_12 * tmp_8 ) ) ) +
                     0.041425537809186785 * tmp_0 *
                         ( ( ( tmp_13 * tmp_3 + tmp_14 * tmp_5 ) * ( tmp_13 * tmp_3 + tmp_14 * tmp_5 ) ) +
                           ( ( tmp_13 * tmp_7 + tmp_14 * tmp_8 ) * ( tmp_13 * tmp_7 + tmp_14 * tmp_8 ) ) ) +
                     0.025422453185103409 * tmp_0 *
                         ( ( ( tmp_15 * tmp_3 + tmp_16 * tmp_5 ) * ( tmp_15 * tmp_3 + tmp_16 * tmp_5 ) ) +
                           ( ( tmp_15 * tmp_7 + tmp_16 * tmp_8 ) * ( tmp_15 * tmp_7 + tmp_16 * tmp_8 ) ) ) +
                     0.058393137863189684 * tmp_0 *
                         ( ( ( tmp_17 * tmp_3 + tmp_18 * tmp_5 ) * ( tmp_17 * tmp_3 + tmp_18 * tmp_5 ) ) +
                           ( ( tmp_17 * tmp_7 + tmp_18 * tmp_8 ) * ( tmp_17 * tmp_7 + tmp_18 * tmp_8 ) ) ) +
                     0.025422453185103409 * tmp_0 *
                         ( ( ( tmp_19 * tmp_3 + tmp_20 * tmp_5 ) * ( tmp_19 * tmp_3 + tmp_20 * tmp_5 ) ) +
                           ( ( tmp_19 * tmp_7 + tmp_20 * tmp_8 ) * ( tmp_19 * tmp_7 + tmp_20 * tmp_8 ) ) ) +
                     0.058393137863189684 * tmp_0 *
                         ( ( ( tmp_21 * tmp_3 + tmp_22 * tmp_5 ) * ( tmp_21 * tmp_3 + tmp_22 * tmp_5 ) ) +
                           ( ( tmp_21 * tmp_7 + tmp_22 * tmp_8 ) * ( tmp_21 * tmp_7 + tmp_22 * tmp_8 ) ) ) +
                     0.041425537809186785 * tmp_0 *
                         ( ( ( tmp_23 * tmp_3 + tmp_24 * tmp_5 ) * ( tmp_23 * tmp_3 + tmp_24 * tmp_5 ) ) +
                           ( ( tmp_23 * tmp_7 + tmp_24 * tmp_8 ) * ( tmp_23 * tmp_7 + tmp_24 * tmp_8 ) ) ) +
                     0.041425537809186785 * tmp_0 *
                         ( ( ( tmp_25 * tmp_3 + tmp_26 * tmp_5 ) * ( tmp_25 * tmp_3 + tmp_26 * tmp_5 ) ) +
                           ( ( tmp_25 * tmp_7 + tmp_26 * tmp_8 ) * ( tmp_25 * tmp_7 + tmp_26 * tmp_8 ) ) ) +
                     0.041425537809186785 * tmp_0 *
                         ( ( ( tmp_27 * tmp_3 + tmp_28 * tmp_5 ) * ( tmp_27 * tmp_3 + tmp_28 * tmp_5 ) ) +
                           ( ( tmp_27 * tmp_7 + tmp_28 * tmp_8 ) * ( tmp_27 * tmp_7 + tmp_28 * tmp_8 ) ) ) +
                     0.041425537809186785 * tmp_0 *
                         ( ( ( tmp_29 * tmp_3 + tmp_30 * tmp_5 ) * ( tmp_29 * tmp_3 + tmp_30 * tmp_5 ) ) +
                           ( ( tmp_29 * tmp_7 + tmp_30 * tmp_8 ) * ( tmp_29 * tmp_7 + tmp_30 * tmp_8 ) ) );
      elMat( 0, 0 ) = a_0_0;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
  void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }


   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0   = -0.14204727503778911;
      real_t tmp_1   = -p_affine_0_0;
      real_t tmp_2   = p_affine_1_0 + tmp_1;
      real_t tmp_3   = -0.14204727503778911;
      real_t tmp_4   = p_affine_2_0 + tmp_1;
      real_t tmp_5   = 0.42614182511336729;
      real_t tmp_6   = p_affine_3_0 + tmp_1;
      real_t tmp_7   = -p_affine_0_1;
      real_t tmp_8   = p_affine_1_1 + tmp_7;
      real_t tmp_9   = p_affine_2_1 + tmp_7;
      real_t tmp_10  = p_affine_3_1 + tmp_7;
      real_t tmp_11  = -p_affine_0_2;
      real_t tmp_12  = p_affine_1_2 + tmp_11;
      real_t tmp_13  = p_affine_2_2 + tmp_11;
      real_t tmp_14  = p_affine_3_2 + tmp_11;
      real_t tmp_15  = p_affine_0_0 * p_affine_1_1;
      real_t tmp_16  = p_affine_0_0 * p_affine_1_2;
      real_t tmp_17  = p_affine_2_1 * p_affine_3_2;
      real_t tmp_18  = p_affine_0_1 * p_affine_1_0;
      real_t tmp_19  = p_affine_0_1 * p_affine_1_2;
      real_t tmp_20  = p_affine_2_2 * p_affine_3_0;
      real_t tmp_21  = p_affine_0_2 * p_affine_1_0;
      real_t tmp_22  = p_affine_0_2 * p_affine_1_1;
      real_t tmp_23  = p_affine_2_0 * p_affine_3_1;
      real_t tmp_24  = p_affine_2_2 * p_affine_3_1;
      real_t tmp_25  = p_affine_2_0 * p_affine_3_2;
      real_t tmp_26  = p_affine_2_1 * p_affine_3_0;
      real_t tmp_27  = std::abs( p_affine_0_0 * tmp_17 - p_affine_0_0 * tmp_24 + p_affine_0_1 * tmp_20 - p_affine_0_1 * tmp_25 +
                                p_affine_0_2 * tmp_23 - p_affine_0_2 * tmp_26 - p_affine_1_0 * tmp_17 + p_affine_1_0 * tmp_24 -
                                p_affine_1_1 * tmp_20 + p_affine_1_1 * tmp_25 - p_affine_1_2 * tmp_23 + p_affine_1_2 * tmp_26 +
                                p_affine_2_0 * tmp_19 - p_affine_2_0 * tmp_22 - p_affine_2_1 * tmp_16 + p_affine_2_1 * tmp_21 +
                                p_affine_2_2 * tmp_15 - p_affine_2_2 * tmp_18 - p_affine_3_0 * tmp_19 + p_affine_3_0 * tmp_22 +
                                p_affine_3_1 * tmp_16 - p_affine_3_1 * tmp_21 - p_affine_3_2 * tmp_15 + p_affine_3_2 * tmp_18 );
      real_t tmp_28  = -0.064890512217413404;
      real_t tmp_29  = -0.064890512217413404;
      real_t tmp_30  = 0.19467153665224024;
      real_t tmp_31  = 0.6230503689456981;
      real_t tmp_32  = -0.20768345631523272;
      real_t tmp_33  = -0.20768345631523272;
      real_t tmp_34  = -0.19254512737211693;
      real_t tmp_35  = 0.064181709124038977;
      real_t tmp_36  = 0.064181709124038977;
      real_t tmp_37  = -0.14204727503778911;
      real_t tmp_38  = -0.14204727503778911;
      real_t tmp_39  = -0.14204727503778911;
      real_t tmp_40  = -0.064890512217413404;
      real_t tmp_41  = -0.064890512217413404;
      real_t tmp_42  = -0.064890512217413404;
      real_t tmp_43  = -0.20768345631523272;
      real_t tmp_44  = -0.20768345631523272;
      real_t tmp_45  = -0.20768345631523272;
      real_t tmp_46  = 0.064181709124038977;
      real_t tmp_47  = 0.064181709124038977;
      real_t tmp_48  = 0.064181709124038977;
      real_t tmp_49  = 0.18559132858383021;
      real_t tmp_50  = -0.18559132858383021;
      real_t tmp_51  = -0.18559132858383021;
      real_t tmp_52  = -0.18559132858383021;
      real_t tmp_53  = 0.18559132858383021;
      real_t tmp_54  = -0.18559132858383021;
      real_t tmp_55  = 0.18559132858383021;
      real_t tmp_56  = 0.18559132858383021;
      real_t tmp_57  = -0.18559132858383021;
      real_t tmp_58  = -0.18559132858383021;
      real_t tmp_59  = -0.18559132858383021;
      real_t tmp_60  = 0.18559132858383021;
      real_t tmp_61  = -0.20768345631523272;
      real_t tmp_62  = -0.20768345631523272;
      real_t tmp_63  = 0.6230503689456981;
      real_t tmp_64  = 0.18559132858383021;
      real_t tmp_65  = -0.18559132858383021;
      real_t tmp_66  = 0.18559132858383021;
      real_t tmp_67  = -0.18559132858383021;
      real_t tmp_68  = 0.18559132858383021;
      real_t tmp_69  = 0.18559132858383021;
      real_t tmp_70  = -0.22856606987286943;
      real_t tmp_71  = 0.46746406342630831;
      real_t tmp_72  = -0.010331923680569455;
      real_t tmp_73  = -0.045860666123970911;
      real_t tmp_74  = 0.3337973783021444;
      real_t tmp_75  = -0.24207604605420263;
      real_t tmp_76  = 0.46746406342630831;
      real_t tmp_77  = -0.22856606987286943;
      real_t tmp_78  = -0.010331923680569455;
      real_t tmp_79  = 0.3337973783021444;
      real_t tmp_80  = -0.045860666123970911;
      real_t tmp_81  = -0.24207604605420263;
      real_t tmp_82  = -0.22856606987286943;
      real_t tmp_83  = -0.22856606987286943;
      real_t tmp_84  = -0.010331923680569455;
      real_t tmp_85  = -0.045860666123970911;
      real_t tmp_86  = -0.045860666123970911;
      real_t tmp_87  = -0.24207604605420263;
      real_t tmp_88  = 0.46746406342630831;
      real_t tmp_89  = -0.010331923680569455;
      real_t tmp_90  = -0.22856606987286943;
      real_t tmp_91  = 0.3337973783021444;
      real_t tmp_92  = -0.24207604605420263;
      real_t tmp_93  = -0.045860666123970911;
      real_t tmp_94  = 0.064181709124038977;
      real_t tmp_95  = 0.064181709124038977;
      real_t tmp_96  = -0.19254512737211693;
      real_t tmp_97  = -0.22856606987286943;
      real_t tmp_98  = -0.010331923680569455;
      real_t tmp_99  = -0.22856606987286943;
      real_t tmp_100 = -0.045860666123970911;
      real_t tmp_101 = -0.24207604605420263;
      real_t tmp_102 = -0.045860666123970911;
      real_t tmp_103 = -0.010331923680569455;
      real_t tmp_104 = -0.22856606987286943;
      real_t tmp_105 = -0.22856606987286943;
      real_t tmp_106 = -0.24207604605420263;
      real_t tmp_107 = -0.045860666123970911;
      real_t tmp_108 = -0.045860666123970911;
      real_t tmp_109 = -0.22856606987286943;
      real_t tmp_110 = -0.010331923680569455;
      real_t tmp_111 = 0.46746406342630831;
      real_t tmp_112 = -0.045860666123970911;
      real_t tmp_113 = -0.24207604605420263;
      real_t tmp_114 = 0.3337973783021444;
      real_t tmp_115 = -0.010331923680569455;
      real_t tmp_116 = -0.22856606987286943;
      real_t tmp_117 = 0.46746406342630831;
      real_t tmp_118 = -0.24207604605420263;
      real_t tmp_119 = -0.045860666123970911;
      real_t tmp_120 = 0.3337973783021444;
      real_t tmp_121 = -0.22856606987286943;
      real_t tmp_122 = -0.22856606987286943;
      real_t tmp_123 = 0.46746406342630831;
      real_t tmp_124 = -0.045860666123970911;
      real_t tmp_125 = -0.045860666123970911;
      real_t tmp_126 = 0.3337973783021444;
      real_t tmp_127 = -0.14204727503778911;
      real_t tmp_128 = 0.42614182511336729;
      real_t tmp_129 = -0.14204727503778911;
      real_t tmp_130 = -0.010331923680569455;
      real_t tmp_131 = 0.46746406342630831;
      real_t tmp_132 = -0.22856606987286943;
      real_t tmp_133 = -0.24207604605420263;
      real_t tmp_134 = 0.3337973783021444;
      real_t tmp_135 = -0.045860666123970911;
      real_t tmp_136 = -0.22856606987286943;
      real_t tmp_137 = 0.46746406342630831;
      real_t tmp_138 = -0.22856606987286943;
      real_t tmp_139 = -0.045860666123970911;
      real_t tmp_140 = 0.3337973783021444;
      real_t tmp_141 = -0.045860666123970911;
      real_t tmp_142 = 0.46746406342630831;
      real_t tmp_143 = -0.22856606987286943;
      real_t tmp_144 = -0.22856606987286943;
      real_t tmp_145 = 0.3337973783021444;
      real_t tmp_146 = -0.045860666123970911;
      real_t tmp_147 = -0.045860666123970911;
      real_t tmp_148 = -0.064890512217413404;
      real_t tmp_149 = 0.19467153665224024;
      real_t tmp_150 = -0.064890512217413404;
      real_t tmp_151 = -0.20768345631523272;
      real_t tmp_152 = 0.6230503689456981;
      real_t tmp_153 = -0.20768345631523272;
      real_t tmp_154 = 0.064181709124038977;
      real_t tmp_155 = -0.19254512737211693;
      real_t tmp_156 = 0.064181709124038977;
      real_t tmp_157 = 0.42614182511336729;
      real_t tmp_158 = -0.14204727503778911;
      real_t tmp_159 = -0.14204727503778911;
      real_t tmp_160 = 0.19467153665224024;
      real_t tmp_161 = -0.064890512217413404;
      real_t tmp_162 = -0.064890512217413404;
      real_t a_0_0 =
          0.0044044418180681378 * tmp_27 *
              ( ( ( tmp_0 * tmp_12 + tmp_13 * tmp_3 + tmp_14 * tmp_5 ) * ( tmp_0 * tmp_12 + tmp_13 * tmp_3 + tmp_14 * tmp_5 ) ) +
                ( ( tmp_0 * tmp_2 + tmp_3 * tmp_4 + tmp_5 * tmp_6 ) * ( tmp_0 * tmp_2 + tmp_3 * tmp_4 + tmp_5 * tmp_6 ) ) +
                ( ( tmp_0 * tmp_8 + tmp_10 * tmp_5 + tmp_3 * tmp_9 ) * ( tmp_0 * tmp_8 + tmp_10 * tmp_5 + tmp_3 * tmp_9 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_102 + tmp_100 * tmp_8 + tmp_101 * tmp_9 ) *
                  ( tmp_10 * tmp_102 + tmp_100 * tmp_8 + tmp_101 * tmp_9 ) ) +
                ( ( tmp_100 * tmp_12 + tmp_101 * tmp_13 + tmp_102 * tmp_14 ) *
                  ( tmp_100 * tmp_12 + tmp_101 * tmp_13 + tmp_102 * tmp_14 ) ) +
                ( ( tmp_100 * tmp_2 + tmp_101 * tmp_4 + tmp_102 * tmp_6 ) *
                  ( tmp_100 * tmp_2 + tmp_101 * tmp_4 + tmp_102 * tmp_6 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_105 + tmp_103 * tmp_8 + tmp_104 * tmp_9 ) *
                  ( tmp_10 * tmp_105 + tmp_103 * tmp_8 + tmp_104 * tmp_9 ) ) +
                ( ( tmp_103 * tmp_12 + tmp_104 * tmp_13 + tmp_105 * tmp_14 ) *
                  ( tmp_103 * tmp_12 + tmp_104 * tmp_13 + tmp_105 * tmp_14 ) ) +
                ( ( tmp_103 * tmp_2 + tmp_104 * tmp_4 + tmp_105 * tmp_6 ) *
                  ( tmp_103 * tmp_2 + tmp_104 * tmp_4 + tmp_105 * tmp_6 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_108 + tmp_106 * tmp_8 + tmp_107 * tmp_9 ) *
                  ( tmp_10 * tmp_108 + tmp_106 * tmp_8 + tmp_107 * tmp_9 ) ) +
                ( ( tmp_106 * tmp_12 + tmp_107 * tmp_13 + tmp_108 * tmp_14 ) *
                  ( tmp_106 * tmp_12 + tmp_107 * tmp_13 + tmp_108 * tmp_14 ) ) +
                ( ( tmp_106 * tmp_2 + tmp_107 * tmp_4 + tmp_108 * tmp_6 ) *
                  ( tmp_106 * tmp_2 + tmp_107 * tmp_4 + tmp_108 * tmp_6 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_111 + tmp_109 * tmp_8 + tmp_110 * tmp_9 ) *
                  ( tmp_10 * tmp_111 + tmp_109 * tmp_8 + tmp_110 * tmp_9 ) ) +
                ( ( tmp_109 * tmp_12 + tmp_110 * tmp_13 + tmp_111 * tmp_14 ) *
                  ( tmp_109 * tmp_12 + tmp_110 * tmp_13 + tmp_111 * tmp_14 ) ) +
                ( ( tmp_109 * tmp_2 + tmp_110 * tmp_4 + tmp_111 * tmp_6 ) *
                  ( tmp_109 * tmp_2 + tmp_110 * tmp_4 + tmp_111 * tmp_6 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_114 + tmp_112 * tmp_8 + tmp_113 * tmp_9 ) *
                  ( tmp_10 * tmp_114 + tmp_112 * tmp_8 + tmp_113 * tmp_9 ) ) +
                ( ( tmp_112 * tmp_12 + tmp_113 * tmp_13 + tmp_114 * tmp_14 ) *
                  ( tmp_112 * tmp_12 + tmp_113 * tmp_13 + tmp_114 * tmp_14 ) ) +
                ( ( tmp_112 * tmp_2 + tmp_113 * tmp_4 + tmp_114 * tmp_6 ) *
                  ( tmp_112 * tmp_2 + tmp_113 * tmp_4 + tmp_114 * tmp_6 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_117 + tmp_115 * tmp_8 + tmp_116 * tmp_9 ) *
                  ( tmp_10 * tmp_117 + tmp_115 * tmp_8 + tmp_116 * tmp_9 ) ) +
                ( ( tmp_115 * tmp_12 + tmp_116 * tmp_13 + tmp_117 * tmp_14 ) *
                  ( tmp_115 * tmp_12 + tmp_116 * tmp_13 + tmp_117 * tmp_14 ) ) +
                ( ( tmp_115 * tmp_2 + tmp_116 * tmp_4 + tmp_117 * tmp_6 ) *
                  ( tmp_115 * tmp_2 + tmp_116 * tmp_4 + tmp_117 * tmp_6 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_120 + tmp_118 * tmp_8 + tmp_119 * tmp_9 ) *
                  ( tmp_10 * tmp_120 + tmp_118 * tmp_8 + tmp_119 * tmp_9 ) ) +
                ( ( tmp_118 * tmp_12 + tmp_119 * tmp_13 + tmp_120 * tmp_14 ) *
                  ( tmp_118 * tmp_12 + tmp_119 * tmp_13 + tmp_120 * tmp_14 ) ) +
                ( ( tmp_118 * tmp_2 + tmp_119 * tmp_4 + tmp_120 * tmp_6 ) *
                  ( tmp_118 * tmp_2 + tmp_119 * tmp_4 + tmp_120 * tmp_6 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_123 + tmp_121 * tmp_8 + tmp_122 * tmp_9 ) *
                  ( tmp_10 * tmp_123 + tmp_121 * tmp_8 + tmp_122 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_121 + tmp_122 * tmp_13 + tmp_123 * tmp_14 ) *
                  ( tmp_12 * tmp_121 + tmp_122 * tmp_13 + tmp_123 * tmp_14 ) ) +
                ( ( tmp_121 * tmp_2 + tmp_122 * tmp_4 + tmp_123 * tmp_6 ) *
                  ( tmp_121 * tmp_2 + tmp_122 * tmp_4 + tmp_123 * tmp_6 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_126 + tmp_124 * tmp_8 + tmp_125 * tmp_9 ) *
                  ( tmp_10 * tmp_126 + tmp_124 * tmp_8 + tmp_125 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_124 + tmp_125 * tmp_13 + tmp_126 * tmp_14 ) *
                  ( tmp_12 * tmp_124 + tmp_125 * tmp_13 + tmp_126 * tmp_14 ) ) +
                ( ( tmp_124 * tmp_2 + tmp_125 * tmp_4 + tmp_126 * tmp_6 ) *
                  ( tmp_124 * tmp_2 + tmp_125 * tmp_4 + tmp_126 * tmp_6 ) ) ) +
          0.0044044418180681378 * tmp_27 *
              ( ( ( tmp_10 * tmp_129 + tmp_127 * tmp_8 + tmp_128 * tmp_9 ) *
                  ( tmp_10 * tmp_129 + tmp_127 * tmp_8 + tmp_128 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_127 + tmp_128 * tmp_13 + tmp_129 * tmp_14 ) *
                  ( tmp_12 * tmp_127 + tmp_128 * tmp_13 + tmp_129 * tmp_14 ) ) +
                ( ( tmp_127 * tmp_2 + tmp_128 * tmp_4 + tmp_129 * tmp_6 ) *
                  ( tmp_127 * tmp_2 + tmp_128 * tmp_4 + tmp_129 * tmp_6 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_132 + tmp_130 * tmp_8 + tmp_131 * tmp_9 ) *
                  ( tmp_10 * tmp_132 + tmp_130 * tmp_8 + tmp_131 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_130 + tmp_13 * tmp_131 + tmp_132 * tmp_14 ) *
                  ( tmp_12 * tmp_130 + tmp_13 * tmp_131 + tmp_132 * tmp_14 ) ) +
                ( ( tmp_130 * tmp_2 + tmp_131 * tmp_4 + tmp_132 * tmp_6 ) *
                  ( tmp_130 * tmp_2 + tmp_131 * tmp_4 + tmp_132 * tmp_6 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_135 + tmp_133 * tmp_8 + tmp_134 * tmp_9 ) *
                  ( tmp_10 * tmp_135 + tmp_133 * tmp_8 + tmp_134 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_133 + tmp_13 * tmp_134 + tmp_135 * tmp_14 ) *
                  ( tmp_12 * tmp_133 + tmp_13 * tmp_134 + tmp_135 * tmp_14 ) ) +
                ( ( tmp_133 * tmp_2 + tmp_134 * tmp_4 + tmp_135 * tmp_6 ) *
                  ( tmp_133 * tmp_2 + tmp_134 * tmp_4 + tmp_135 * tmp_6 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_138 + tmp_136 * tmp_8 + tmp_137 * tmp_9 ) *
                  ( tmp_10 * tmp_138 + tmp_136 * tmp_8 + tmp_137 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_136 + tmp_13 * tmp_137 + tmp_138 * tmp_14 ) *
                  ( tmp_12 * tmp_136 + tmp_13 * tmp_137 + tmp_138 * tmp_14 ) ) +
                ( ( tmp_136 * tmp_2 + tmp_137 * tmp_4 + tmp_138 * tmp_6 ) *
                  ( tmp_136 * tmp_2 + tmp_137 * tmp_4 + tmp_138 * tmp_6 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_141 + tmp_139 * tmp_8 + tmp_140 * tmp_9 ) *
                  ( tmp_10 * tmp_141 + tmp_139 * tmp_8 + tmp_140 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_139 + tmp_13 * tmp_140 + tmp_14 * tmp_141 ) *
                  ( tmp_12 * tmp_139 + tmp_13 * tmp_140 + tmp_14 * tmp_141 ) ) +
                ( ( tmp_139 * tmp_2 + tmp_140 * tmp_4 + tmp_141 * tmp_6 ) *
                  ( tmp_139 * tmp_2 + tmp_140 * tmp_4 + tmp_141 * tmp_6 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_144 + tmp_142 * tmp_8 + tmp_143 * tmp_9 ) *
                  ( tmp_10 * tmp_144 + tmp_142 * tmp_8 + tmp_143 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_142 + tmp_13 * tmp_143 + tmp_14 * tmp_144 ) *
                  ( tmp_12 * tmp_142 + tmp_13 * tmp_143 + tmp_14 * tmp_144 ) ) +
                ( ( tmp_142 * tmp_2 + tmp_143 * tmp_4 + tmp_144 * tmp_6 ) *
                  ( tmp_142 * tmp_2 + tmp_143 * tmp_4 + tmp_144 * tmp_6 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_147 + tmp_145 * tmp_8 + tmp_146 * tmp_9 ) *
                  ( tmp_10 * tmp_147 + tmp_145 * tmp_8 + tmp_146 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_145 + tmp_13 * tmp_146 + tmp_14 * tmp_147 ) *
                  ( tmp_12 * tmp_145 + tmp_13 * tmp_146 + tmp_14 * tmp_147 ) ) +
                ( ( tmp_145 * tmp_2 + tmp_146 * tmp_4 + tmp_147 * tmp_6 ) *
                  ( tmp_145 * tmp_2 + tmp_146 * tmp_4 + tmp_147 * tmp_6 ) ) ) +
          0.0086719579272897529 * tmp_27 *
              ( ( ( tmp_10 * tmp_150 + tmp_148 * tmp_8 + tmp_149 * tmp_9 ) *
                  ( tmp_10 * tmp_150 + tmp_148 * tmp_8 + tmp_149 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_148 + tmp_13 * tmp_149 + tmp_14 * tmp_150 ) *
                  ( tmp_12 * tmp_148 + tmp_13 * tmp_149 + tmp_14 * tmp_150 ) ) +
                ( ( tmp_148 * tmp_2 + tmp_149 * tmp_4 + tmp_150 * tmp_6 ) *
                  ( tmp_148 * tmp_2 + tmp_149 * tmp_4 + tmp_150 * tmp_6 ) ) ) +
          0.0012542093589233661 * tmp_27 *
              ( ( ( tmp_10 * tmp_153 + tmp_151 * tmp_8 + tmp_152 * tmp_9 ) *
                  ( tmp_10 * tmp_153 + tmp_151 * tmp_8 + tmp_152 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_151 + tmp_13 * tmp_152 + tmp_14 * tmp_153 ) *
                  ( tmp_12 * tmp_151 + tmp_13 * tmp_152 + tmp_14 * tmp_153 ) ) +
                ( ( tmp_151 * tmp_2 + tmp_152 * tmp_4 + tmp_153 * tmp_6 ) *
                  ( tmp_151 * tmp_2 + tmp_152 * tmp_4 + tmp_153 * tmp_6 ) ) ) +
          0.0069606304761558151 * tmp_27 *
              ( ( ( tmp_10 * tmp_156 + tmp_154 * tmp_8 + tmp_155 * tmp_9 ) *
                  ( tmp_10 * tmp_156 + tmp_154 * tmp_8 + tmp_155 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_154 + tmp_13 * tmp_155 + tmp_14 * tmp_156 ) *
                  ( tmp_12 * tmp_154 + tmp_13 * tmp_155 + tmp_14 * tmp_156 ) ) +
                ( ( tmp_154 * tmp_2 + tmp_155 * tmp_4 + tmp_156 * tmp_6 ) *
                  ( tmp_154 * tmp_2 + tmp_155 * tmp_4 + tmp_156 * tmp_6 ) ) ) +
          0.0044044418180681378 * tmp_27 *
              ( ( ( tmp_10 * tmp_159 + tmp_157 * tmp_8 + tmp_158 * tmp_9 ) *
                  ( tmp_10 * tmp_159 + tmp_157 * tmp_8 + tmp_158 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_157 + tmp_13 * tmp_158 + tmp_14 * tmp_159 ) *
                  ( tmp_12 * tmp_157 + tmp_13 * tmp_158 + tmp_14 * tmp_159 ) ) +
                ( ( tmp_157 * tmp_2 + tmp_158 * tmp_4 + tmp_159 * tmp_6 ) *
                  ( tmp_157 * tmp_2 + tmp_158 * tmp_4 + tmp_159 * tmp_6 ) ) ) +
          0.0086719579272897529 * tmp_27 *
              ( ( ( tmp_10 * tmp_162 + tmp_160 * tmp_8 + tmp_161 * tmp_9 ) *
                  ( tmp_10 * tmp_162 + tmp_160 * tmp_8 + tmp_161 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_160 + tmp_13 * tmp_161 + tmp_14 * tmp_162 ) *
                  ( tmp_12 * tmp_160 + tmp_13 * tmp_161 + tmp_14 * tmp_162 ) ) +
                ( ( tmp_160 * tmp_2 + tmp_161 * tmp_4 + tmp_162 * tmp_6 ) *
                  ( tmp_160 * tmp_2 + tmp_161 * tmp_4 + tmp_162 * tmp_6 ) ) ) +
          0.0086719579272897529 * tmp_27 *
              ( ( ( tmp_10 * tmp_30 + tmp_28 * tmp_8 + tmp_29 * tmp_9 ) *
                  ( tmp_10 * tmp_30 + tmp_28 * tmp_8 + tmp_29 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_28 + tmp_13 * tmp_29 + tmp_14 * tmp_30 ) *
                  ( tmp_12 * tmp_28 + tmp_13 * tmp_29 + tmp_14 * tmp_30 ) ) +
                ( ( tmp_2 * tmp_28 + tmp_29 * tmp_4 + tmp_30 * tmp_6 ) *
                  ( tmp_2 * tmp_28 + tmp_29 * tmp_4 + tmp_30 * tmp_6 ) ) ) +
          0.0012542093589233661 * tmp_27 *
              ( ( ( tmp_10 * tmp_33 + tmp_31 * tmp_8 + tmp_32 * tmp_9 ) *
                  ( tmp_10 * tmp_33 + tmp_31 * tmp_8 + tmp_32 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_31 + tmp_13 * tmp_32 + tmp_14 * tmp_33 ) *
                  ( tmp_12 * tmp_31 + tmp_13 * tmp_32 + tmp_14 * tmp_33 ) ) +
                ( ( tmp_2 * tmp_31 + tmp_32 * tmp_4 + tmp_33 * tmp_6 ) *
                  ( tmp_2 * tmp_31 + tmp_32 * tmp_4 + tmp_33 * tmp_6 ) ) ) +
          0.0069606304761558151 * tmp_27 *
              ( ( ( tmp_10 * tmp_36 + tmp_34 * tmp_8 + tmp_35 * tmp_9 ) *
                  ( tmp_10 * tmp_36 + tmp_34 * tmp_8 + tmp_35 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_34 + tmp_13 * tmp_35 + tmp_14 * tmp_36 ) *
                  ( tmp_12 * tmp_34 + tmp_13 * tmp_35 + tmp_14 * tmp_36 ) ) +
                ( ( tmp_2 * tmp_34 + tmp_35 * tmp_4 + tmp_36 * tmp_6 ) *
                  ( tmp_2 * tmp_34 + tmp_35 * tmp_4 + tmp_36 * tmp_6 ) ) ) +
          0.0044044418180681378 * tmp_27 *
              ( ( ( tmp_10 * tmp_39 + tmp_37 * tmp_8 + tmp_38 * tmp_9 ) *
                  ( tmp_10 * tmp_39 + tmp_37 * tmp_8 + tmp_38 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_37 + tmp_13 * tmp_38 + tmp_14 * tmp_39 ) *
                  ( tmp_12 * tmp_37 + tmp_13 * tmp_38 + tmp_14 * tmp_39 ) ) +
                ( ( tmp_2 * tmp_37 + tmp_38 * tmp_4 + tmp_39 * tmp_6 ) *
                  ( tmp_2 * tmp_37 + tmp_38 * tmp_4 + tmp_39 * tmp_6 ) ) ) +
          0.0086719579272897529 * tmp_27 *
              ( ( ( tmp_10 * tmp_42 + tmp_40 * tmp_8 + tmp_41 * tmp_9 ) *
                  ( tmp_10 * tmp_42 + tmp_40 * tmp_8 + tmp_41 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_40 + tmp_13 * tmp_41 + tmp_14 * tmp_42 ) *
                  ( tmp_12 * tmp_40 + tmp_13 * tmp_41 + tmp_14 * tmp_42 ) ) +
                ( ( tmp_2 * tmp_40 + tmp_4 * tmp_41 + tmp_42 * tmp_6 ) *
                  ( tmp_2 * tmp_40 + tmp_4 * tmp_41 + tmp_42 * tmp_6 ) ) ) +
          0.0012542093589233661 * tmp_27 *
              ( ( ( tmp_10 * tmp_45 + tmp_43 * tmp_8 + tmp_44 * tmp_9 ) *
                  ( tmp_10 * tmp_45 + tmp_43 * tmp_8 + tmp_44 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_43 + tmp_13 * tmp_44 + tmp_14 * tmp_45 ) *
                  ( tmp_12 * tmp_43 + tmp_13 * tmp_44 + tmp_14 * tmp_45 ) ) +
                ( ( tmp_2 * tmp_43 + tmp_4 * tmp_44 + tmp_45 * tmp_6 ) *
                  ( tmp_2 * tmp_43 + tmp_4 * tmp_44 + tmp_45 * tmp_6 ) ) ) +
          0.0069606304761558151 * tmp_27 *
              ( ( ( tmp_10 * tmp_48 + tmp_46 * tmp_8 + tmp_47 * tmp_9 ) *
                  ( tmp_10 * tmp_48 + tmp_46 * tmp_8 + tmp_47 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_46 + tmp_13 * tmp_47 + tmp_14 * tmp_48 ) *
                  ( tmp_12 * tmp_46 + tmp_13 * tmp_47 + tmp_14 * tmp_48 ) ) +
                ( ( tmp_2 * tmp_46 + tmp_4 * tmp_47 + tmp_48 * tmp_6 ) *
                  ( tmp_2 * tmp_46 + tmp_4 * tmp_47 + tmp_48 * tmp_6 ) ) ) +
          0.0060468217102181351 * tmp_27 *
              ( ( ( tmp_10 * tmp_51 + tmp_49 * tmp_8 + tmp_50 * tmp_9 ) *
                  ( tmp_10 * tmp_51 + tmp_49 * tmp_8 + tmp_50 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_49 + tmp_13 * tmp_50 + tmp_14 * tmp_51 ) *
                  ( tmp_12 * tmp_49 + tmp_13 * tmp_50 + tmp_14 * tmp_51 ) ) +
                ( ( tmp_2 * tmp_49 + tmp_4 * tmp_50 + tmp_51 * tmp_6 ) *
                  ( tmp_2 * tmp_49 + tmp_4 * tmp_50 + tmp_51 * tmp_6 ) ) ) +
          0.0060468217102181351 * tmp_27 *
              ( ( ( tmp_10 * tmp_54 + tmp_52 * tmp_8 + tmp_53 * tmp_9 ) *
                  ( tmp_10 * tmp_54 + tmp_52 * tmp_8 + tmp_53 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_52 + tmp_13 * tmp_53 + tmp_14 * tmp_54 ) *
                  ( tmp_12 * tmp_52 + tmp_13 * tmp_53 + tmp_14 * tmp_54 ) ) +
                ( ( tmp_2 * tmp_52 + tmp_4 * tmp_53 + tmp_54 * tmp_6 ) *
                  ( tmp_2 * tmp_52 + tmp_4 * tmp_53 + tmp_54 * tmp_6 ) ) ) +
          0.0060468217102181351 * tmp_27 *
              ( ( ( tmp_10 * tmp_57 + tmp_55 * tmp_8 + tmp_56 * tmp_9 ) *
                  ( tmp_10 * tmp_57 + tmp_55 * tmp_8 + tmp_56 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_55 + tmp_13 * tmp_56 + tmp_14 * tmp_57 ) *
                  ( tmp_12 * tmp_55 + tmp_13 * tmp_56 + tmp_14 * tmp_57 ) ) +
                ( ( tmp_2 * tmp_55 + tmp_4 * tmp_56 + tmp_57 * tmp_6 ) *
                  ( tmp_2 * tmp_55 + tmp_4 * tmp_56 + tmp_57 * tmp_6 ) ) ) +
          0.0060468217102181351 * tmp_27 *
              ( ( ( tmp_10 * tmp_60 + tmp_58 * tmp_8 + tmp_59 * tmp_9 ) *
                  ( tmp_10 * tmp_60 + tmp_58 * tmp_8 + tmp_59 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_58 + tmp_13 * tmp_59 + tmp_14 * tmp_60 ) *
                  ( tmp_12 * tmp_58 + tmp_13 * tmp_59 + tmp_14 * tmp_60 ) ) +
                ( ( tmp_2 * tmp_58 + tmp_4 * tmp_59 + tmp_6 * tmp_60 ) *
                  ( tmp_2 * tmp_58 + tmp_4 * tmp_59 + tmp_6 * tmp_60 ) ) ) +
          0.0012542093589233661 * tmp_27 *
              ( ( ( tmp_10 * tmp_63 + tmp_61 * tmp_8 + tmp_62 * tmp_9 ) *
                  ( tmp_10 * tmp_63 + tmp_61 * tmp_8 + tmp_62 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_61 + tmp_13 * tmp_62 + tmp_14 * tmp_63 ) *
                  ( tmp_12 * tmp_61 + tmp_13 * tmp_62 + tmp_14 * tmp_63 ) ) +
                ( ( tmp_2 * tmp_61 + tmp_4 * tmp_62 + tmp_6 * tmp_63 ) *
                  ( tmp_2 * tmp_61 + tmp_4 * tmp_62 + tmp_6 * tmp_63 ) ) ) +
          0.0060468217102181351 * tmp_27 *
              ( ( ( tmp_10 * tmp_66 + tmp_64 * tmp_8 + tmp_65 * tmp_9 ) *
                  ( tmp_10 * tmp_66 + tmp_64 * tmp_8 + tmp_65 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_64 + tmp_13 * tmp_65 + tmp_14 * tmp_66 ) *
                  ( tmp_12 * tmp_64 + tmp_13 * tmp_65 + tmp_14 * tmp_66 ) ) +
                ( ( tmp_2 * tmp_64 + tmp_4 * tmp_65 + tmp_6 * tmp_66 ) *
                  ( tmp_2 * tmp_64 + tmp_4 * tmp_65 + tmp_6 * tmp_66 ) ) ) +
          0.0060468217102181351 * tmp_27 *
              ( ( ( tmp_10 * tmp_69 + tmp_67 * tmp_8 + tmp_68 * tmp_9 ) *
                  ( tmp_10 * tmp_69 + tmp_67 * tmp_8 + tmp_68 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_67 + tmp_13 * tmp_68 + tmp_14 * tmp_69 ) *
                  ( tmp_12 * tmp_67 + tmp_13 * tmp_68 + tmp_14 * tmp_69 ) ) +
                ( ( tmp_2 * tmp_67 + tmp_4 * tmp_68 + tmp_6 * tmp_69 ) *
                  ( tmp_2 * tmp_67 + tmp_4 * tmp_68 + tmp_6 * tmp_69 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_72 + tmp_70 * tmp_8 + tmp_71 * tmp_9 ) *
                  ( tmp_10 * tmp_72 + tmp_70 * tmp_8 + tmp_71 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_70 + tmp_13 * tmp_71 + tmp_14 * tmp_72 ) *
                  ( tmp_12 * tmp_70 + tmp_13 * tmp_71 + tmp_14 * tmp_72 ) ) +
                ( ( tmp_2 * tmp_70 + tmp_4 * tmp_71 + tmp_6 * tmp_72 ) *
                  ( tmp_2 * tmp_70 + tmp_4 * tmp_71 + tmp_6 * tmp_72 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_75 + tmp_73 * tmp_8 + tmp_74 * tmp_9 ) *
                  ( tmp_10 * tmp_75 + tmp_73 * tmp_8 + tmp_74 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_73 + tmp_13 * tmp_74 + tmp_14 * tmp_75 ) *
                  ( tmp_12 * tmp_73 + tmp_13 * tmp_74 + tmp_14 * tmp_75 ) ) +
                ( ( tmp_2 * tmp_73 + tmp_4 * tmp_74 + tmp_6 * tmp_75 ) *
                  ( tmp_2 * tmp_73 + tmp_4 * tmp_74 + tmp_6 * tmp_75 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_78 + tmp_76 * tmp_8 + tmp_77 * tmp_9 ) *
                  ( tmp_10 * tmp_78 + tmp_76 * tmp_8 + tmp_77 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_76 + tmp_13 * tmp_77 + tmp_14 * tmp_78 ) *
                  ( tmp_12 * tmp_76 + tmp_13 * tmp_77 + tmp_14 * tmp_78 ) ) +
                ( ( tmp_2 * tmp_76 + tmp_4 * tmp_77 + tmp_6 * tmp_78 ) *
                  ( tmp_2 * tmp_76 + tmp_4 * tmp_77 + tmp_6 * tmp_78 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_81 + tmp_79 * tmp_8 + tmp_80 * tmp_9 ) *
                  ( tmp_10 * tmp_81 + tmp_79 * tmp_8 + tmp_80 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_79 + tmp_13 * tmp_80 + tmp_14 * tmp_81 ) *
                  ( tmp_12 * tmp_79 + tmp_13 * tmp_80 + tmp_14 * tmp_81 ) ) +
                ( ( tmp_2 * tmp_79 + tmp_4 * tmp_80 + tmp_6 * tmp_81 ) *
                  ( tmp_2 * tmp_79 + tmp_4 * tmp_80 + tmp_6 * tmp_81 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_84 + tmp_8 * tmp_82 + tmp_83 * tmp_9 ) *
                  ( tmp_10 * tmp_84 + tmp_8 * tmp_82 + tmp_83 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_82 + tmp_13 * tmp_83 + tmp_14 * tmp_84 ) *
                  ( tmp_12 * tmp_82 + tmp_13 * tmp_83 + tmp_14 * tmp_84 ) ) +
                ( ( tmp_2 * tmp_82 + tmp_4 * tmp_83 + tmp_6 * tmp_84 ) *
                  ( tmp_2 * tmp_82 + tmp_4 * tmp_83 + tmp_6 * tmp_84 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_87 + tmp_8 * tmp_85 + tmp_86 * tmp_9 ) *
                  ( tmp_10 * tmp_87 + tmp_8 * tmp_85 + tmp_86 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_85 + tmp_13 * tmp_86 + tmp_14 * tmp_87 ) *
                  ( tmp_12 * tmp_85 + tmp_13 * tmp_86 + tmp_14 * tmp_87 ) ) +
                ( ( tmp_2 * tmp_85 + tmp_4 * tmp_86 + tmp_6 * tmp_87 ) *
                  ( tmp_2 * tmp_85 + tmp_4 * tmp_86 + tmp_6 * tmp_87 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_90 + tmp_8 * tmp_88 + tmp_89 * tmp_9 ) *
                  ( tmp_10 * tmp_90 + tmp_8 * tmp_88 + tmp_89 * tmp_9 ) ) +
                ( ( tmp_12 * tmp_88 + tmp_13 * tmp_89 + tmp_14 * tmp_90 ) *
                  ( tmp_12 * tmp_88 + tmp_13 * tmp_89 + tmp_14 * tmp_90 ) ) +
                ( ( tmp_2 * tmp_88 + tmp_4 * tmp_89 + tmp_6 * tmp_90 ) *
                  ( tmp_2 * tmp_88 + tmp_4 * tmp_89 + tmp_6 * tmp_90 ) ) ) +
          0.0025755810251600563 * tmp_27 *
              ( ( ( tmp_10 * tmp_93 + tmp_8 * tmp_91 + tmp_9 * tmp_92 ) *
                  ( tmp_10 * tmp_93 + tmp_8 * tmp_91 + tmp_9 * tmp_92 ) ) +
                ( ( tmp_12 * tmp_91 + tmp_13 * tmp_92 + tmp_14 * tmp_93 ) *
                  ( tmp_12 * tmp_91 + tmp_13 * tmp_92 + tmp_14 * tmp_93 ) ) +
                ( ( tmp_2 * tmp_91 + tmp_4 * tmp_92 + tmp_6 * tmp_93 ) *
                  ( tmp_2 * tmp_91 + tmp_4 * tmp_92 + tmp_6 * tmp_93 ) ) ) +
          0.0069606304761558151 * tmp_27 *
              ( ( ( tmp_10 * tmp_96 + tmp_8 * tmp_94 + tmp_9 * tmp_95 ) *
                  ( tmp_10 * tmp_96 + tmp_8 * tmp_94 + tmp_9 * tmp_95 ) ) +
                ( ( tmp_12 * tmp_94 + tmp_13 * tmp_95 + tmp_14 * tmp_96 ) *
                  ( tmp_12 * tmp_94 + tmp_13 * tmp_95 + tmp_14 * tmp_96 ) ) +
                ( ( tmp_2 * tmp_94 + tmp_4 * tmp_95 + tmp_6 * tmp_96 ) *
                  ( tmp_2 * tmp_94 + tmp_4 * tmp_95 + tmp_6 * tmp_96 ) ) ) +
          0.0011928171484740719 * tmp_27 *
              ( ( ( tmp_10 * tmp_99 + tmp_8 * tmp_97 + tmp_9 * tmp_98 ) *
                  ( tmp_10 * tmp_99 + tmp_8 * tmp_97 + tmp_9 * tmp_98 ) ) +
                ( ( tmp_12 * tmp_97 + tmp_13 * tmp_98 + tmp_14 * tmp_99 ) *
                  ( tmp_12 * tmp_97 + tmp_13 * tmp_98 + tmp_14 * tmp_99 ) ) +
                ( ( tmp_2 * tmp_97 + tmp_4 * tmp_98 + tmp_6 * tmp_99 ) * ( tmp_2 * tmp_97 + tmp_4 * tmp_98 + tmp_6 * tmp_99 ) ) );
      elMat( 0, 0 ) = a_0_0;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
   }


};

class EGMassFormP0P0 : public hyteg::dg::DGForm
{
 protected:
   void integrateVolume2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );

      real_t a_0_0  = 0;
      real_t a_0_1  = 0;
      real_t a_0_2  = 0;
      real_t a_1_0  = 0;
      real_t a_1_1  = 0;
      real_t a_1_2  = 0;
      real_t a_2_0  = 0;
      real_t a_2_1  = 0;
      real_t a_2_2  = 0;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
      elMat( 1, 0 ) = a_1_0;
      elMat( 1, 1 ) = a_1_1;
      elMat( 1, 2 ) = a_1_2;
      elMat( 2, 0 ) = a_2_0;
      elMat( 2, 1 ) = a_2_1;
      elMat( 2, 2 ) = a_2_2;
   }

   virtual void integrateFacetInner2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                       const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                       const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                       const DGBasisInfo&                                       trialBasis,
                                       const DGBasisInfo&                                       testBasis,
                                       int                                                      trialDegree,
                                       int                                                      testDegree,
                                       Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 1, 1 ) = 0;
      elMat( 1, 2 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 2, 1 ) = 0;
      elMat( 2, 2 ) = 0;
   }

   virtual void integrateFacetCoupling2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementInner,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElementOuter,
                                          const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexInnerElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertexOuterElement,
                                          const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                          const DGBasisInfo&                                       trialBasis,
                                          const DGBasisInfo&                                       testBasis,
                                          int                                                      trialDegree,
                                          int                                                      testDegree,
                                          Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );

      const auto p_affine_3_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_3_1 = coordsElementOuter[0]( 1 );

      const auto p_affine_4_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[1]( 1 );

      const auto p_affine_5_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertexInnerElement( 0 );
      const auto p_affine_8_1 = oppositeVertexInnerElement( 1 );

      const auto p_affine_9_0 = oppositeVertexOuterElement( 0 );
      const auto p_affine_9_1 = oppositeVertexOuterElement( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 1, 1 ) = 0;
      elMat( 1, 2 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 2, 1 ) = 0;
      elMat( 2, 2 ) = 0;
   };

   virtual void integrateFacetDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                                   const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                                   const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                                   const DGBasisInfo&                                       trialBasis,
                                                   const DGBasisInfo&                                       testBasis,
                                                   int                                                      trialDegree,
                                                   int                                                      testDegree,
                                                   Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( testBasis.numDoFsPerElement( 2, testDegree ), trialBasis.numDoFsPerElement( 2, trialDegree ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );

      const auto p_affine_6_0 = coordsFacet[0]( 0 );
      const auto p_affine_6_1 = coordsFacet[0]( 1 );

      const auto p_affine_7_0 = coordsFacet[1]( 0 );
      const auto p_affine_7_1 = coordsFacet[1]( 1 );

      const auto p_affine_8_0 = oppositeVertex( 0 );
      const auto p_affine_8_1 = oppositeVertex( 1 );

      const auto p_affine_10_0 = outwardNormal( 0 );
      const auto p_affine_10_1 = outwardNormal( 1 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 1, 1 ) = 0;
      elMat( 1, 2 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 2, 1 ) = 0;
      elMat( 2, 2 ) = 0;
   }

   void integrateRHSDirichletBoundary2D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
  void integrateRHSDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsElement,
                                         const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coordsFacet,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     oppositeVertex,
                                         const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                         const DGBasisInfo&                                       basis,
                                         int                                                      degree,
                                         Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const override
   {
      WALBERLA_UNUSED( coordsElement );
      WALBERLA_UNUSED( coordsFacet );
      WALBERLA_UNUSED( oppositeVertex );
      WALBERLA_UNUSED( outwardNormal );
      WALBERLA_UNUSED( basis );
      WALBERLA_UNUSED( degree );
      WALBERLA_UNUSED( elMat );

      // Does nothing.
   }
   void integrateVolume3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >&      coords,
                           const DGBasisInfo&                                       trialBasis,
                           const DGBasisInfo&                                       testBasis,
                           int                                                      trialDegree,
                           int                                                      testDegree,
                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coords[0]( 0 );
      const auto p_affine_0_1 = coords[0]( 1 );
      const auto p_affine_0_2 = coords[0]( 2 );

      const auto p_affine_1_0 = coords[1]( 0 );
      const auto p_affine_1_1 = coords[1]( 1 );
      const auto p_affine_1_2 = coords[1]( 2 );

      const auto p_affine_2_0 = coords[2]( 0 );
      const auto p_affine_2_1 = coords[2]( 1 );
      const auto p_affine_2_2 = coords[2]( 2 );

      const auto p_affine_3_0 = coords[3]( 0 );
      const auto p_affine_3_1 = coords[3]( 1 );
      const auto p_affine_3_2 = coords[3]( 2 );

      real_t tmp_0   = 0.10795272496221098;
      real_t tmp_1   = p_affine_0_0 * p_affine_1_1;
      real_t tmp_2   = p_affine_0_0 * p_affine_1_2;
      real_t tmp_3   = p_affine_2_1 * p_affine_3_2;
      real_t tmp_4   = p_affine_0_1 * p_affine_1_0;
      real_t tmp_5   = p_affine_0_1 * p_affine_1_2;
      real_t tmp_6   = p_affine_2_2 * p_affine_3_0;
      real_t tmp_7   = p_affine_0_2 * p_affine_1_0;
      real_t tmp_8   = p_affine_0_2 * p_affine_1_1;
      real_t tmp_9   = p_affine_2_0 * p_affine_3_1;
      real_t tmp_10  = p_affine_2_2 * p_affine_3_1;
      real_t tmp_11  = p_affine_2_0 * p_affine_3_2;
      real_t tmp_12  = p_affine_2_1 * p_affine_3_0;
      real_t tmp_13  = std::abs( p_affine_0_0 * tmp_10 - p_affine_0_0 * tmp_3 + p_affine_0_1 * tmp_11 - p_affine_0_1 * tmp_6 +
                                p_affine_0_2 * tmp_12 - p_affine_0_2 * tmp_9 - p_affine_1_0 * tmp_10 + p_affine_1_0 * tmp_3 -
                                p_affine_1_1 * tmp_11 + p_affine_1_1 * tmp_6 - p_affine_1_2 * tmp_12 + p_affine_1_2 * tmp_9 -
                                p_affine_2_0 * tmp_5 + p_affine_2_0 * tmp_8 + p_affine_2_1 * tmp_2 - p_affine_2_1 * tmp_7 -
                                p_affine_2_2 * tmp_1 + p_affine_2_2 * tmp_4 + p_affine_3_0 * tmp_5 - p_affine_3_0 * tmp_8 -
                                p_affine_3_1 * tmp_2 + p_affine_3_1 * tmp_7 + p_affine_3_2 * tmp_1 - p_affine_3_2 * tmp_4 );
      real_t tmp_14  = 0.0044044418180681378 * tmp_13;
      real_t tmp_15  = 0.18510948778258651;
      real_t tmp_16  = 0.0086719579272897529 * tmp_13;
      real_t tmp_17  = 0.042316543684767338;
      real_t tmp_18  = 0.0012542093589233661 * tmp_13;
      real_t tmp_19  = 0.31418170912403898;
      real_t tmp_20  = 0.0069606304761558151 * tmp_13;
      real_t tmp_21  = 0.6761418251133674;
      real_t tmp_22  = 0.0044044418180681378 * tmp_13;
      real_t tmp_23  = 0.44467153665224013;
      real_t tmp_24  = 0.0086719579272897529 * tmp_13;
      real_t tmp_25  = 0.87305036894569832;
      real_t tmp_26  = 0.0012542093589233661 * tmp_13;
      real_t tmp_27  = 0.057454872627883069;
      real_t tmp_28  = 0.0069606304761558151 * tmp_13;
      real_t tmp_29  = 0.43559132858383021;
      real_t tmp_30  = 0.0060468217102181351 * tmp_13;
      real_t tmp_31  = 0.43559132858383021;
      real_t tmp_32  = 0.0060468217102181351 * tmp_13;
      real_t tmp_33  = 0.064408671416169794;
      real_t tmp_34  = 0.0060468217102181351 * tmp_13;
      real_t tmp_35  = 0.43559132858383021;
      real_t tmp_36  = 0.0060468217102181351 * tmp_13;
      real_t tmp_37  = 0.042316543684767449;
      real_t tmp_38  = 0.0012542093589233661 * tmp_13;
      real_t tmp_39  = 0.064408671416169794;
      real_t tmp_40  = 0.0060468217102181351 * tmp_13;
      real_t tmp_41  = 0.064408671416169794;
      real_t tmp_42  = 0.0060468217102181351 * tmp_13;
      real_t tmp_43  = 0.021433930127130574;
      real_t tmp_44  = 0.0011928171484740719 * tmp_13;
      real_t tmp_45  = 0.20413933387602912;
      real_t tmp_46  = 0.0025755810251600563 * tmp_13;
      real_t tmp_47  = 0.021433930127130574;
      real_t tmp_48  = 0.0011928171484740719 * tmp_13;
      real_t tmp_49  = 0.20413933387602914;
      real_t tmp_50  = 0.0025755810251600563 * tmp_13;
      real_t tmp_51  = 0.71746406342630831;
      real_t tmp_52  = 0.0011928171484740719 * tmp_13;
      real_t tmp_53  = 0.5837973783021444;
      real_t tmp_54  = 0.0025755810251600563 * tmp_13;
      real_t tmp_55  = 0.021433930127130577;
      real_t tmp_56  = 0.0011928171484740719 * tmp_13;
      real_t tmp_57  = 0.20413933387602914;
      real_t tmp_58  = 0.0025755810251600563 * tmp_13;
      real_t tmp_59  = 0.31418170912403898;
      real_t tmp_60  = 0.0069606304761558151 * tmp_13;
      real_t tmp_61  = 0.71746406342630831;
      real_t tmp_62  = 0.0011928171484740719 * tmp_13;
      real_t tmp_63  = 0.5837973783021444;
      real_t tmp_64  = 0.0025755810251600563 * tmp_13;
      real_t tmp_65  = 0.71746406342630831;
      real_t tmp_66  = 0.0011928171484740719 * tmp_13;
      real_t tmp_67  = 0.5837973783021444;
      real_t tmp_68  = 0.0025755810251600563 * tmp_13;
      real_t tmp_69  = 0.021433930127130574;
      real_t tmp_70  = 0.0011928171484740719 * tmp_13;
      real_t tmp_71  = 0.20413933387602912;
      real_t tmp_72  = 0.0025755810251600563 * tmp_13;
      real_t tmp_73  = 0.021433930127130574;
      real_t tmp_74  = 0.0011928171484740719 * tmp_13;
      real_t tmp_75  = 0.20413933387602912;
      real_t tmp_76  = 0.0025755810251600563 * tmp_13;
      real_t tmp_77  = 0.23966807631943055;
      real_t tmp_78  = 0.0011928171484740719 * tmp_13;
      real_t tmp_79  = 0.0079239539457973684;
      real_t tmp_80  = 0.0025755810251600563 * tmp_13;
      real_t tmp_81  = 0.10795272496221095;
      real_t tmp_82  = 0.0044044418180681378 * tmp_13;
      real_t tmp_83  = 0.021433930127130577;
      real_t tmp_84  = 0.0011928171484740719 * tmp_13;
      real_t tmp_85  = 0.20413933387602914;
      real_t tmp_86  = 0.0025755810251600563 * tmp_13;
      real_t tmp_87  = 0.23966807631943055;
      real_t tmp_88  = 0.0011928171484740719 * tmp_13;
      real_t tmp_89  = 0.0079239539457973962;
      real_t tmp_90  = 0.0025755810251600563 * tmp_13;
      real_t tmp_91  = 0.23966807631943055;
      real_t tmp_92  = 0.0011928171484740719 * tmp_13;
      real_t tmp_93  = 0.007923953945797424;
      real_t tmp_94  = 0.0025755810251600563 * tmp_13;
      real_t tmp_95  = 0.18510948778258654;
      real_t tmp_96  = 0.0086719579272897529 * tmp_13;
      real_t tmp_97  = 0.042316543684767394;
      real_t tmp_98  = 0.0012542093589233661 * tmp_13;
      real_t tmp_99  = 0.31418170912403898;
      real_t tmp_100 = 0.0069606304761558151 * tmp_13;
      real_t tmp_101 = 0.10795272496221092;
      real_t tmp_102 = 0.0044044418180681378 * tmp_13;
      real_t tmp_103 = 0.18510948778258654;
      real_t tmp_104 = 0.0086719579272897529 * tmp_13;
      real_t tmp_105 = tmp_0 * tmp_14;
      real_t tmp_106 = tmp_17 * tmp_18;
      real_t tmp_107 = tmp_19 * tmp_20;
      real_t tmp_108 = tmp_21 * tmp_22;
      real_t tmp_109 = tmp_23 * tmp_24;
      real_t tmp_110 = tmp_25 * tmp_26;
      real_t tmp_111 = tmp_27 * tmp_28;
      real_t tmp_112 = tmp_29 * tmp_30;
      real_t tmp_113 = tmp_31 * tmp_32;
      real_t tmp_114 = tmp_33 * tmp_34;
      real_t tmp_115 = tmp_35 * tmp_36;
      real_t tmp_116 = tmp_15 * tmp_16;
      real_t tmp_117 = tmp_39 * tmp_40;
      real_t tmp_118 = tmp_41 * tmp_42;
      real_t tmp_119 = tmp_43 * tmp_44;
      real_t tmp_120 = tmp_45 * tmp_46;
      real_t tmp_121 = tmp_47 * tmp_48;
      real_t tmp_122 = tmp_49 * tmp_50;
      real_t tmp_123 = tmp_51 * tmp_52;
      real_t tmp_124 = tmp_53 * tmp_54;
      real_t tmp_125 = tmp_55 * tmp_56;
      real_t tmp_126 = tmp_57 * tmp_58;
      real_t tmp_127 = tmp_37 * tmp_38;
      real_t tmp_128 = tmp_61 * tmp_62;
      real_t tmp_129 = tmp_63 * tmp_64;
      real_t tmp_130 = tmp_65 * tmp_66;
      real_t tmp_131 = tmp_67 * tmp_68;
      real_t tmp_132 = tmp_69 * tmp_70;
      real_t tmp_133 = tmp_71 * tmp_72;
      real_t tmp_134 = tmp_73 * tmp_74;
      real_t tmp_135 = tmp_75 * tmp_76;
      real_t tmp_136 = tmp_77 * tmp_78;
      real_t tmp_137 = tmp_79 * tmp_80;
      real_t tmp_138 = tmp_59 * tmp_60;
      real_t tmp_139 = tmp_83 * tmp_84;
      real_t tmp_140 = tmp_85 * tmp_86;
      real_t tmp_141 = tmp_87 * tmp_88;
      real_t tmp_142 = tmp_89 * tmp_90;
      real_t tmp_143 = tmp_91 * tmp_92;
      real_t tmp_144 = tmp_93 * tmp_94;
      real_t tmp_145 = tmp_81 * tmp_82;
      real_t tmp_146 = tmp_95 * tmp_96;
      real_t tmp_147 = tmp_97 * tmp_98;
      real_t tmp_148 = tmp_100 * tmp_99;
      real_t tmp_149 = tmp_101 * tmp_102;
      real_t tmp_150 = tmp_103 * tmp_104;
      real_t tmp_151 = 0.10795272496221089 * tmp_105 + 0.8730503689456981 * tmp_106 + 0.057454872627883069 * tmp_107 +
                       0.10795272496221089 * tmp_108 + 0.1851094877825866 * tmp_109 + 0.042316543684767283 * tmp_110 +
                       0.31418170912403898 * tmp_111 + 0.43559132858383021 * tmp_112 + 0.064408671416169794 * tmp_113 +
                       0.43559132858383021 * tmp_114 + 0.064408671416169794 * tmp_115 + 0.1851094877825866 * tmp_116 +
                       0.43559132858383021 * tmp_117 + 0.064408671416169794 * tmp_118 + 0.02143393012713057 * tmp_119 +
                       0.20413933387602909 * tmp_120 + 0.71746406342630831 * tmp_121 + 0.5837973783021444 * tmp_122 +
                       0.02143393012713057 * tmp_123 + 0.20413933387602909 * tmp_124 + 0.71746406342630831 * tmp_125 +
                       0.5837973783021444 * tmp_126 + 0.042316543684767283 * tmp_127 + 0.02143393012713057 * tmp_128 +
                       0.20413933387602909 * tmp_129 + 0.23966807631943055 * tmp_130 + 0.0079239539457973684 * tmp_131 +
                       0.02143393012713057 * tmp_132 + 0.20413933387602909 * tmp_133 + 0.23966807631943055 * tmp_134 +
                       0.0079239539457973684 * tmp_135 + 0.02143393012713057 * tmp_136 + 0.20413933387602909 * tmp_137 +
                       0.31418170912403898 * tmp_138 + 0.23966807631943055 * tmp_139 + 0.0079239539457973684 * tmp_140 +
                       0.02143393012713057 * tmp_141 + 0.20413933387602909 * tmp_142 + 0.71746406342630831 * tmp_143 +
                       0.5837973783021444 * tmp_144 + 0.10795272496221089 * tmp_145 + 0.1851094877825866 * tmp_146 +
                       0.042316543684767283 * tmp_147 + 0.31418170912403898 * tmp_148 + 0.67614182511336729 * tmp_149 +
                       0.44467153665224024 * tmp_150;
      real_t tmp_152 = 0.10795272496221089 * tmp_105 + 0.042316543684767283 * tmp_106 + 0.31418170912403898 * tmp_107 +
                       0.10795272496221089 * tmp_108 + 0.1851094877825866 * tmp_109 + 0.042316543684767283 * tmp_110 +
                       0.31418170912403898 * tmp_111 + 0.064408671416169794 * tmp_112 + 0.43559132858383021 * tmp_113 +
                       0.43559132858383021 * tmp_114 + 0.064408671416169794 * tmp_115 + 0.1851094877825866 * tmp_116 +
                       0.064408671416169794 * tmp_117 + 0.43559132858383021 * tmp_118 + 0.71746406342630831 * tmp_119 +
                       0.5837973783021444 * tmp_120 + 0.02143393012713057 * tmp_121 + 0.20413933387602909 * tmp_122 +
                       0.02143393012713057 * tmp_123 + 0.20413933387602909 * tmp_124 + 0.23966807631943055 * tmp_125 +
                       0.0079239539457973684 * tmp_126 + 0.042316543684767283 * tmp_127 + 0.23966807631943055 * tmp_128 +
                       0.0079239539457973684 * tmp_129 + 0.02143393012713057 * tmp_130 + 0.20413933387602909 * tmp_131 +
                       0.23966807631943055 * tmp_132 + 0.0079239539457973684 * tmp_133 + 0.02143393012713057 * tmp_134 +
                       0.20413933387602909 * tmp_135 + 0.02143393012713057 * tmp_136 + 0.20413933387602909 * tmp_137 +
                       0.31418170912403898 * tmp_138 + 0.71746406342630831 * tmp_139 + 0.5837973783021444 * tmp_140 +
                       0.71746406342630831 * tmp_141 + 0.5837973783021444 * tmp_142 + 0.02143393012713057 * tmp_143 +
                       0.20413933387602909 * tmp_144 + 0.67614182511336729 * tmp_145 + 0.44467153665224024 * tmp_146 +
                       0.8730503689456981 * tmp_147 + 0.057454872627883069 * tmp_148 + 0.10795272496221089 * tmp_149 +
                       0.1851094877825866 * tmp_150;
      real_t tmp_153 = 0.67614182511336729 * tmp_105 + 0.042316543684767283 * tmp_106 + 0.31418170912403898 * tmp_107 +
                       0.10795272496221089 * tmp_108 + 0.1851094877825866 * tmp_109 + 0.042316543684767283 * tmp_110 +
                       0.31418170912403898 * tmp_111 + 0.064408671416169794 * tmp_112 + 0.064408671416169794 * tmp_113 +
                       0.064408671416169794 * tmp_114 + 0.43559132858383021 * tmp_115 + 0.44467153665224024 * tmp_116 +
                       0.43559132858383021 * tmp_117 + 0.43559132858383021 * tmp_118 + 0.23966807631943055 * tmp_119 +
                       0.0079239539457973684 * tmp_120 + 0.23966807631943055 * tmp_121 + 0.0079239539457973684 * tmp_122 +
                       0.23966807631943055 * tmp_123 + 0.0079239539457973684 * tmp_124 + 0.02143393012713057 * tmp_125 +
                       0.20413933387602909 * tmp_126 + 0.8730503689456981 * tmp_127 + 0.02143393012713057 * tmp_128 +
                       0.20413933387602909 * tmp_129 + 0.02143393012713057 * tmp_130 + 0.20413933387602909 * tmp_131 +
                       0.71746406342630831 * tmp_132 + 0.5837973783021444 * tmp_133 + 0.71746406342630831 * tmp_134 +
                       0.5837973783021444 * tmp_135 + 0.71746406342630831 * tmp_136 + 0.5837973783021444 * tmp_137 +
                       0.057454872627883069 * tmp_138 + 0.02143393012713057 * tmp_139 + 0.20413933387602909 * tmp_140 +
                       0.02143393012713057 * tmp_141 + 0.20413933387602909 * tmp_142 + 0.02143393012713057 * tmp_143 +
                       0.20413933387602909 * tmp_144 + 0.10795272496221089 * tmp_145 + 0.1851094877825866 * tmp_146 +
                       0.042316543684767283 * tmp_147 + 0.31418170912403898 * tmp_148 + 0.10795272496221089 * tmp_149 +
                       0.1851094877825866 * tmp_150;
      real_t tmp_154 = 0.10795272496221089 * tmp_14;
      real_t tmp_155 = 0.8730503689456981 * tmp_18;
      real_t tmp_156 = 0.057454872627883069 * tmp_20;
      real_t tmp_157 = 0.10795272496221089 * tmp_22;
      real_t tmp_158 = 0.1851094877825866 * tmp_24;
      real_t tmp_159 = 0.042316543684767283 * tmp_26;
      real_t tmp_160 = 0.31418170912403898 * tmp_28;
      real_t tmp_161 = 0.43559132858383021 * tmp_30;
      real_t tmp_162 = 0.064408671416169794 * tmp_32;
      real_t tmp_163 = 0.43559132858383021 * tmp_34;
      real_t tmp_164 = 0.064408671416169794 * tmp_36;
      real_t tmp_165 = 0.1851094877825866 * tmp_16;
      real_t tmp_166 = 0.43559132858383021 * tmp_40;
      real_t tmp_167 = 0.064408671416169794 * tmp_42;
      real_t tmp_168 = 0.02143393012713057 * tmp_44;
      real_t tmp_169 = 0.20413933387602909 * tmp_46;
      real_t tmp_170 = 0.71746406342630831 * tmp_48;
      real_t tmp_171 = 0.5837973783021444 * tmp_50;
      real_t tmp_172 = 0.02143393012713057 * tmp_52;
      real_t tmp_173 = 0.20413933387602909 * tmp_54;
      real_t tmp_174 = 0.71746406342630831 * tmp_56;
      real_t tmp_175 = 0.5837973783021444 * tmp_58;
      real_t tmp_176 = 0.042316543684767283 * tmp_38;
      real_t tmp_177 = 0.02143393012713057 * tmp_62;
      real_t tmp_178 = 0.20413933387602909 * tmp_64;
      real_t tmp_179 = 0.23966807631943055 * tmp_66;
      real_t tmp_180 = 0.0079239539457973684 * tmp_68;
      real_t tmp_181 = 0.02143393012713057 * tmp_70;
      real_t tmp_182 = 0.20413933387602909 * tmp_72;
      real_t tmp_183 = 0.23966807631943055 * tmp_74;
      real_t tmp_184 = 0.0079239539457973684 * tmp_76;
      real_t tmp_185 = 0.02143393012713057 * tmp_78;
      real_t tmp_186 = 0.20413933387602909 * tmp_80;
      real_t tmp_187 = 0.31418170912403898 * tmp_60;
      real_t tmp_188 = 0.23966807631943055 * tmp_84;
      real_t tmp_189 = 0.0079239539457973684 * tmp_86;
      real_t tmp_190 = 0.02143393012713057 * tmp_88;
      real_t tmp_191 = 0.20413933387602909 * tmp_90;
      real_t tmp_192 = 0.71746406342630831 * tmp_92;
      real_t tmp_193 = 0.5837973783021444 * tmp_94;
      real_t tmp_194 = 0.10795272496221089 * tmp_82;
      real_t tmp_195 = 0.1851094877825866 * tmp_96;
      real_t tmp_196 = 0.042316543684767283 * tmp_98;
      real_t tmp_197 = 0.31418170912403898 * tmp_100;
      real_t tmp_198 = 0.67614182511336729 * tmp_102;
      real_t tmp_199 = 0.44467153665224024 * tmp_104;
      real_t tmp_200 = 0.10795272496221089 * tmp_154 + 0.042316543684767283 * tmp_155 + 0.31418170912403898 * tmp_156 +
                       0.10795272496221089 * tmp_157 + 0.1851094877825866 * tmp_158 + 0.042316543684767283 * tmp_159 +
                       0.31418170912403898 * tmp_160 + 0.064408671416169794 * tmp_161 + 0.43559132858383021 * tmp_162 +
                       0.43559132858383021 * tmp_163 + 0.064408671416169794 * tmp_164 + 0.1851094877825866 * tmp_165 +
                       0.064408671416169794 * tmp_166 + 0.43559132858383021 * tmp_167 + 0.71746406342630831 * tmp_168 +
                       0.5837973783021444 * tmp_169 + 0.02143393012713057 * tmp_170 + 0.20413933387602909 * tmp_171 +
                       0.02143393012713057 * tmp_172 + 0.20413933387602909 * tmp_173 + 0.23966807631943055 * tmp_174 +
                       0.0079239539457973684 * tmp_175 + 0.042316543684767283 * tmp_176 + 0.23966807631943055 * tmp_177 +
                       0.0079239539457973684 * tmp_178 + 0.02143393012713057 * tmp_179 + 0.20413933387602909 * tmp_180 +
                       0.23966807631943055 * tmp_181 + 0.0079239539457973684 * tmp_182 + 0.02143393012713057 * tmp_183 +
                       0.20413933387602909 * tmp_184 + 0.02143393012713057 * tmp_185 + 0.20413933387602909 * tmp_186 +
                       0.31418170912403898 * tmp_187 + 0.71746406342630831 * tmp_188 + 0.5837973783021444 * tmp_189 +
                       0.71746406342630831 * tmp_190 + 0.5837973783021444 * tmp_191 + 0.02143393012713057 * tmp_192 +
                       0.20413933387602909 * tmp_193 + 0.67614182511336729 * tmp_194 + 0.44467153665224024 * tmp_195 +
                       0.8730503689456981 * tmp_196 + 0.057454872627883069 * tmp_197 + 0.10795272496221089 * tmp_198 +
                       0.1851094877825866 * tmp_199;
      real_t tmp_201 = 0.67614182511336729 * tmp_154 + 0.042316543684767283 * tmp_155 + 0.31418170912403898 * tmp_156 +
                       0.10795272496221089 * tmp_157 + 0.1851094877825866 * tmp_158 + 0.042316543684767283 * tmp_159 +
                       0.31418170912403898 * tmp_160 + 0.064408671416169794 * tmp_161 + 0.064408671416169794 * tmp_162 +
                       0.064408671416169794 * tmp_163 + 0.43559132858383021 * tmp_164 + 0.44467153665224024 * tmp_165 +
                       0.43559132858383021 * tmp_166 + 0.43559132858383021 * tmp_167 + 0.23966807631943055 * tmp_168 +
                       0.0079239539457973684 * tmp_169 + 0.23966807631943055 * tmp_170 + 0.0079239539457973684 * tmp_171 +
                       0.23966807631943055 * tmp_172 + 0.0079239539457973684 * tmp_173 + 0.02143393012713057 * tmp_174 +
                       0.20413933387602909 * tmp_175 + 0.8730503689456981 * tmp_176 + 0.02143393012713057 * tmp_177 +
                       0.20413933387602909 * tmp_178 + 0.02143393012713057 * tmp_179 + 0.20413933387602909 * tmp_180 +
                       0.71746406342630831 * tmp_181 + 0.5837973783021444 * tmp_182 + 0.71746406342630831 * tmp_183 +
                       0.5837973783021444 * tmp_184 + 0.71746406342630831 * tmp_185 + 0.5837973783021444 * tmp_186 +
                       0.057454872627883069 * tmp_187 + 0.02143393012713057 * tmp_188 + 0.20413933387602909 * tmp_189 +
                       0.02143393012713057 * tmp_190 + 0.20413933387602909 * tmp_191 + 0.02143393012713057 * tmp_192 +
                       0.20413933387602909 * tmp_193 + 0.10795272496221089 * tmp_194 + 0.1851094877825866 * tmp_195 +
                       0.042316543684767283 * tmp_196 + 0.31418170912403898 * tmp_197 + 0.10795272496221089 * tmp_198 +
                       0.1851094877825866 * tmp_199;
      real_t tmp_202 = 0.018051270079732267 * tmp_100 + 0.011653790826766751 * tmp_102 + 0.034265522467131576 * tmp_104 +
                       0.072991352481910632 * tmp_14 + 0.082312920381191867 * tmp_16 + 0.0017906898694248178 * tmp_18 +
                       0.09871014634810224 * tmp_20 + 0.011653790826766751 * tmp_22 + 0.034265522467131576 * tmp_24 +
                       0.0017906898694248178 * tmp_26 + 0.09871014634810224 * tmp_28 + 0.0041484769535961282 * tmp_30 +
                       0.02805585875448877 * tmp_32 + 0.02805585875448877 * tmp_34 + 0.02805585875448877 * tmp_36 +
                       0.036944474076492824 * tmp_38 + 0.02805585875448877 * tmp_40 + 0.18973980553742634 * tmp_42 +
                       0.17195323190970521 * tmp_44 + 0.0046259835393434364 * tmp_46 + 0.0051370288015344708 * tmp_48 +
                       0.001617590680159407 * tmp_50 + 0.0051370288015344708 * tmp_52 + 0.001617590680159407 * tmp_54 +
                       0.0051370288015344708 * tmp_56 + 0.001617590680159407 * tmp_58 + 0.018051270079732267 * tmp_60 +
                       0.0051370288015344708 * tmp_62 + 0.001617590680159407 * tmp_64 + 0.00045941336069471551 * tmp_66 +
                       0.04167286763534888 * tmp_68 + 0.17195323190970521 * tmp_70 + 0.0046259835393434364 * tmp_72 +
                       0.015378074604206668 * tmp_74 + 0.11917600792517191 * tmp_76 + 0.015378074604206668 * tmp_78 +
                       0.11917600792517191 * tmp_80 + 0.072991352481910632 * tmp_82 + 0.015378074604206668 * tmp_84 +
                       0.11917600792517191 * tmp_86 + 0.015378074604206668 * tmp_88 + 0.11917600792517191 * tmp_90 +
                       0.00045941336069471551 * tmp_92 + 0.04167286763534888 * tmp_94 + 0.082312920381191867 * tmp_96 +
                       0.036944474076492824 * tmp_98;
      real_t a_0_0 = ( tmp_0 * tmp_0 ) * tmp_14 + tmp_100 * ( tmp_99 * tmp_99 ) + ( tmp_101 * tmp_101 ) * tmp_102 +
                     ( tmp_103 * tmp_103 ) * tmp_104 + ( tmp_15 * tmp_15 ) * tmp_16 + ( tmp_17 * tmp_17 ) * tmp_18 +
                     ( tmp_19 * tmp_19 ) * tmp_20 + ( tmp_21 * tmp_21 ) * tmp_22 + ( tmp_23 * tmp_23 ) * tmp_24 +
                     ( tmp_25 * tmp_25 ) * tmp_26 + ( tmp_27 * tmp_27 ) * tmp_28 + ( tmp_29 * tmp_29 ) * tmp_30 +
                     ( tmp_31 * tmp_31 ) * tmp_32 + ( tmp_33 * tmp_33 ) * tmp_34 + ( tmp_35 * tmp_35 ) * tmp_36 +
                     ( tmp_37 * tmp_37 ) * tmp_38 + ( tmp_39 * tmp_39 ) * tmp_40 + ( tmp_41 * tmp_41 ) * tmp_42 +
                     ( tmp_43 * tmp_43 ) * tmp_44 + ( tmp_45 * tmp_45 ) * tmp_46 + ( tmp_47 * tmp_47 ) * tmp_48 +
                     ( tmp_49 * tmp_49 ) * tmp_50 + ( tmp_51 * tmp_51 ) * tmp_52 + ( tmp_53 * tmp_53 ) * tmp_54 +
                     ( tmp_55 * tmp_55 ) * tmp_56 + ( tmp_57 * tmp_57 ) * tmp_58 + ( tmp_59 * tmp_59 ) * tmp_60 +
                     ( tmp_61 * tmp_61 ) * tmp_62 + ( tmp_63 * tmp_63 ) * tmp_64 + ( tmp_65 * tmp_65 ) * tmp_66 +
                     ( tmp_67 * tmp_67 ) * tmp_68 + ( tmp_69 * tmp_69 ) * tmp_70 + ( tmp_71 * tmp_71 ) * tmp_72 +
                     ( tmp_73 * tmp_73 ) * tmp_74 + ( tmp_75 * tmp_75 ) * tmp_76 + ( tmp_77 * tmp_77 ) * tmp_78 +
                     ( tmp_79 * tmp_79 ) * tmp_80 + ( tmp_81 * tmp_81 ) * tmp_82 + ( tmp_83 * tmp_83 ) * tmp_84 +
                     ( tmp_85 * tmp_85 ) * tmp_86 + ( tmp_87 * tmp_87 ) * tmp_88 + ( tmp_89 * tmp_89 ) * tmp_90 +
                     ( tmp_91 * tmp_91 ) * tmp_92 + ( tmp_93 * tmp_93 ) * tmp_94 + ( tmp_95 * tmp_95 ) * tmp_96 +
                     ( tmp_97 * tmp_97 ) * tmp_98;
      real_t a_0_1 = tmp_151;
      real_t a_0_2 = tmp_152;
      real_t a_0_3 = tmp_153;
      real_t a_1_0 = tmp_151;
      real_t a_1_1 = 0.09871014634810224 * tmp_100 + 0.45716776766763534 * tmp_102 + 0.19773277550866464 * tmp_104 +
                     0.011653790826766751 * tmp_14 + 0.034265522467131576 * tmp_16 + 0.76221694671621953 * tmp_18 +
                     0.0033010623886862672 * tmp_20 + 0.011653790826766751 * tmp_22 + 0.034265522467131576 * tmp_24 +
                     0.0017906898694248178 * tmp_26 + 0.09871014634810224 * tmp_28 + 0.18973980553742634 * tmp_30 +
                     0.0041484769535961282 * tmp_32 + 0.18973980553742634 * tmp_34 + 0.0041484769535961282 * tmp_36 +
                     0.0017906898694248178 * tmp_38 + 0.18973980553742634 * tmp_40 + 0.0041484769535961282 * tmp_42 +
                     0.00045941336069471551 * tmp_44 + 0.04167286763534888 * tmp_46 + 0.51475468230818977 * tmp_48 +
                     0.34081937891245712 * tmp_50 + 0.00045941336069471551 * tmp_52 + 0.04167286763534888 * tmp_54 +
                     0.51475468230818977 * tmp_56 + 0.34081937891245712 * tmp_58 + 0.09871014634810224 * tmp_60 +
                     0.00045941336069471551 * tmp_62 + 0.04167286763534888 * tmp_64 + 0.057440786806656381 * tmp_66 +
                     6.2789046135117683e-5 * tmp_68 + 0.00045941336069471551 * tmp_70 + 0.04167286763534888 * tmp_72 +
                     0.057440786806656381 * tmp_74 + 6.2789046135117683e-5 * tmp_76 + 0.00045941336069471551 * tmp_78 +
                     0.04167286763534888 * tmp_80 + 0.011653790826766751 * tmp_82 + 0.057440786806656381 * tmp_84 +
                     6.2789046135117683e-5 * tmp_86 + 0.00045941336069471551 * tmp_88 + 0.04167286763534888 * tmp_90 +
                     0.51475468230818977 * tmp_92 + 0.34081937891245712 * tmp_94 + 0.034265522467131576 * tmp_96 +
                     0.0017906898694248178 * tmp_98;
      real_t a_1_2 = tmp_200;
      real_t a_1_3 = tmp_201;
      real_t a_2_0 = tmp_152;
      real_t a_2_1 = tmp_200;
      real_t a_2_2 = 0.0033010623886862672 * tmp_100 + 0.011653790826766751 * tmp_102 + 0.034265522467131576 * tmp_104 +
                     0.011653790826766751 * tmp_14 + 0.034265522467131576 * tmp_16 + 0.0017906898694248178 * tmp_18 +
                     0.09871014634810224 * tmp_20 + 0.011653790826766751 * tmp_22 + 0.034265522467131576 * tmp_24 +
                     0.0017906898694248178 * tmp_26 + 0.09871014634810224 * tmp_28 + 0.0041484769535961282 * tmp_30 +
                     0.18973980553742634 * tmp_32 + 0.18973980553742634 * tmp_34 + 0.0041484769535961282 * tmp_36 +
                     0.0017906898694248178 * tmp_38 + 0.0041484769535961282 * tmp_40 + 0.18973980553742634 * tmp_42 +
                     0.51475468230818977 * tmp_44 + 0.34081937891245712 * tmp_46 + 0.00045941336069471551 * tmp_48 +
                     0.04167286763534888 * tmp_50 + 0.00045941336069471551 * tmp_52 + 0.04167286763534888 * tmp_54 +
                     0.057440786806656381 * tmp_56 + 6.2789046135117683e-5 * tmp_58 + 0.09871014634810224 * tmp_60 +
                     0.057440786806656381 * tmp_62 + 6.2789046135117683e-5 * tmp_64 + 0.00045941336069471551 * tmp_66 +
                     0.04167286763534888 * tmp_68 + 0.057440786806656381 * tmp_70 + 6.2789046135117683e-5 * tmp_72 +
                     0.00045941336069471551 * tmp_74 + 0.04167286763534888 * tmp_76 + 0.00045941336069471551 * tmp_78 +
                     0.04167286763534888 * tmp_80 + 0.45716776766763534 * tmp_82 + 0.51475468230818977 * tmp_84 +
                     0.34081937891245712 * tmp_86 + 0.51475468230818977 * tmp_88 + 0.34081937891245712 * tmp_90 +
                     0.00045941336069471551 * tmp_92 + 0.04167286763534888 * tmp_94 + 0.19773277550866464 * tmp_96 +
                     0.76221694671621953 * tmp_98;
      real_t a_2_3 = tmp_202;
      real_t a_3_0 = tmp_153;
      real_t a_3_1 = tmp_201;
      real_t a_3_2 = tmp_202;
      real_t a_3_3 = 0.09871014634810224 * tmp_100 + 0.011653790826766751 * tmp_102 + 0.034265522467131576 * tmp_104 +
                     0.45716776766763534 * tmp_14 + 0.19773277550866464 * tmp_16 + 0.0017906898694248178 * tmp_18 +
                     0.09871014634810224 * tmp_20 + 0.011653790826766751 * tmp_22 + 0.034265522467131576 * tmp_24 +
                     0.0017906898694248178 * tmp_26 + 0.09871014634810224 * tmp_28 + 0.0041484769535961282 * tmp_30 +
                     0.0041484769535961282 * tmp_32 + 0.0041484769535961282 * tmp_34 + 0.18973980553742634 * tmp_36 +
                     0.76221694671621953 * tmp_38 + 0.18973980553742634 * tmp_40 + 0.18973980553742634 * tmp_42 +
                     0.057440786806656381 * tmp_44 + 6.2789046135117683e-5 * tmp_46 + 0.057440786806656381 * tmp_48 +
                     6.2789046135117683e-5 * tmp_50 + 0.057440786806656381 * tmp_52 + 6.2789046135117683e-5 * tmp_54 +
                     0.00045941336069471551 * tmp_56 + 0.04167286763534888 * tmp_58 + 0.0033010623886862672 * tmp_60 +
                     0.00045941336069471551 * tmp_62 + 0.04167286763534888 * tmp_64 + 0.00045941336069471551 * tmp_66 +
                     0.04167286763534888 * tmp_68 + 0.51475468230818977 * tmp_70 + 0.34081937891245712 * tmp_72 +
                     0.51475468230818977 * tmp_74 + 0.34081937891245712 * tmp_76 + 0.51475468230818977 * tmp_78 +
                     0.34081937891245712 * tmp_80 + 0.011653790826766751 * tmp_82 + 0.00045941336069471551 * tmp_84 +
                     0.04167286763534888 * tmp_86 + 0.00045941336069471551 * tmp_88 + 0.04167286763534888 * tmp_90 +
                     0.00045941336069471551 * tmp_92 + 0.04167286763534888 * tmp_94 + 0.034265522467131576 * tmp_96 +
                     0.0017906898694248178 * tmp_98;
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
      elMat( 0, 3 ) = a_0_3;
      elMat( 1, 0 ) = a_1_0;
      elMat( 1, 1 ) = a_1_1;
      elMat( 1, 2 ) = a_1_2;
      elMat( 1, 3 ) = a_1_3;
      elMat( 2, 0 ) = a_2_0;
      elMat( 2, 1 ) = a_2_1;
      elMat( 2, 2 ) = a_2_2;
      elMat( 2, 3 ) = a_2_3;
      elMat( 3, 0 ) = a_3_0;
      elMat( 3, 1 ) = a_3_1;
      elMat( 3, 2 ) = a_3_2;
      elMat( 3, 3 ) = a_3_3;
   }

   void integrateFacetInner3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                               const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                               const Eigen::Matrix< real_t, 3, 1 >&,
                               const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                               const DGBasisInfo&                                       trialBasis,
                               const DGBasisInfo&                                       testBasis,
                               int                                                      trialDegree,
                               int                                                      testDegree,
                               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 1, 1 ) = 0;
      elMat( 1, 2 ) = 0;
      elMat( 1, 3 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 2, 1 ) = 0;
      elMat( 2, 2 ) = 0;
      elMat( 2, 3 ) = 0;
      elMat( 3, 0 ) = 0;
      elMat( 3, 1 ) = 0;
      elMat( 3, 2 ) = 0;
      elMat( 3, 3 ) = 0;
   }

   void integrateFacetCoupling3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementInner,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElementOuter,
                                  const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&,
                                  const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                  const DGBasisInfo&                                       trialBasis,
                                  const DGBasisInfo&                                       testBasis,
                                  int                                                      trialDegree,
                                  int                                                      testDegree,
                                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElementInner[0]( 0 );
      const auto p_affine_0_1 = coordsElementInner[0]( 1 );
      const auto p_affine_0_2 = coordsElementInner[0]( 2 );

      const auto p_affine_1_0 = coordsElementInner[1]( 0 );
      const auto p_affine_1_1 = coordsElementInner[1]( 1 );
      const auto p_affine_1_2 = coordsElementInner[1]( 2 );

      const auto p_affine_2_0 = coordsElementInner[2]( 0 );
      const auto p_affine_2_1 = coordsElementInner[2]( 1 );
      const auto p_affine_2_2 = coordsElementInner[2]( 2 );

      const auto p_affine_3_0 = coordsElementInner[3]( 0 );
      const auto p_affine_3_1 = coordsElementInner[3]( 1 );
      const auto p_affine_3_2 = coordsElementInner[3]( 2 );

      const auto p_affine_4_0 = coordsElementOuter[0]( 0 );
      const auto p_affine_4_1 = coordsElementOuter[0]( 1 );
      const auto p_affine_4_2 = coordsElementOuter[0]( 2 );

      const auto p_affine_5_0 = coordsElementOuter[1]( 0 );
      const auto p_affine_5_1 = coordsElementOuter[1]( 1 );
      const auto p_affine_5_2 = coordsElementOuter[1]( 2 );

      const auto p_affine_6_0 = coordsElementOuter[2]( 0 );
      const auto p_affine_6_1 = coordsElementOuter[2]( 1 );
      const auto p_affine_6_2 = coordsElementOuter[2]( 2 );

      const auto p_affine_7_0 = coordsElementOuter[3]( 0 );
      const auto p_affine_7_1 = coordsElementOuter[3]( 1 );
      const auto p_affine_7_2 = coordsElementOuter[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 1, 1 ) = 0;
      elMat( 1, 2 ) = 0;
      elMat( 1, 3 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 2, 1 ) = 0;
      elMat( 2, 2 ) = 0;
      elMat( 2, 3 ) = 0;
      elMat( 3, 0 ) = 0;
      elMat( 3, 1 ) = 0;
      elMat( 3, 2 ) = 0;
      elMat( 3, 3 ) = 0;
   }

   void integrateFacetDirichletBoundary3D( const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsElement,
                                           const std::vector< Eigen::Matrix< real_t, 3, 1 > >& coordsFacet,
                                           const Eigen::Matrix< real_t, 3, 1 >&,
                                           const Eigen::Matrix< real_t, 3, 1 >&                     outwardNormal,
                                           const DGBasisInfo&                                       trialBasis,
                                           const DGBasisInfo&                                       testBasis,
                                           int                                                      trialDegree,
                                           int                                                      testDegree,
                                           Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic >& elMat ) const
   {
      elMat.resize( Eigen::Index( testBasis.numDoFsPerElement( 3, uint_c( testDegree ) ) ),
                    Eigen::Index( trialBasis.numDoFsPerElement( 3, uint_c( trialDegree ) ) ) );

      const auto p_affine_0_0 = coordsElement[0]( 0 );
      const auto p_affine_0_1 = coordsElement[0]( 1 );
      const auto p_affine_0_2 = coordsElement[0]( 2 );

      const auto p_affine_1_0 = coordsElement[1]( 0 );
      const auto p_affine_1_1 = coordsElement[1]( 1 );
      const auto p_affine_1_2 = coordsElement[1]( 2 );

      const auto p_affine_2_0 = coordsElement[2]( 0 );
      const auto p_affine_2_1 = coordsElement[2]( 1 );
      const auto p_affine_2_2 = coordsElement[2]( 2 );

      const auto p_affine_3_0 = coordsElement[3]( 0 );
      const auto p_affine_3_1 = coordsElement[3]( 1 );
      const auto p_affine_3_2 = coordsElement[3]( 2 );

      const auto p_affine_8_0 = coordsFacet[0]( 0 );
      const auto p_affine_8_1 = coordsFacet[0]( 1 );
      const auto p_affine_8_2 = coordsFacet[0]( 2 );

      const auto p_affine_9_0 = coordsFacet[1]( 0 );
      const auto p_affine_9_1 = coordsFacet[1]( 1 );
      const auto p_affine_9_2 = coordsFacet[1]( 2 );

      const auto p_affine_10_0 = coordsFacet[2]( 0 );
      const auto p_affine_10_1 = coordsFacet[2]( 1 );
      const auto p_affine_10_2 = coordsFacet[2]( 2 );

      const auto p_affine_13_0 = outwardNormal( 0 );
      const auto p_affine_13_1 = outwardNormal( 1 );
      const auto p_affine_13_2 = outwardNormal( 2 );

      elMat( 0, 0 ) = 0;
      elMat( 0, 1 ) = 0;
      elMat( 0, 2 ) = 0;
      elMat( 0, 3 ) = 0;
      elMat( 1, 0 ) = 0;
      elMat( 1, 1 ) = 0;
      elMat( 1, 2 ) = 0;
      elMat( 1, 3 ) = 0;
      elMat( 2, 0 ) = 0;
      elMat( 2, 1 ) = 0;
      elMat( 2, 2 ) = 0;
      elMat( 2, 3 ) = 0;
      elMat( 3, 0 ) = 0;
      elMat( 3, 1 ) = 0;
      elMat( 3, 2 ) = 0;
      elMat( 3, 3 ) = 0;
   }


};

} // namespace eg

} // namespace dg
} // namespace hyteg
