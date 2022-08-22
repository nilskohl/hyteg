
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

namespace hyteg {

namespace dg {

namespace eg {
class EGDivtFormEP1 : public hyteg::dg::DGForm2D
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

      real_t tmp_0 = -p_affine_0_0;
      real_t tmp_1 = -p_affine_0_1;
      real_t tmp_2 = ( p_affine_1_0 + tmp_0 ) * ( p_affine_2_1 + tmp_1 );
      real_t tmp_3 = p_affine_2_0 + tmp_0;
      real_t tmp_4 = p_affine_1_1 + tmp_1;
      real_t tmp_5 = 1.0 / ( tmp_2 - tmp_3 * tmp_4 );
      real_t tmp_6 = ( -2 * tmp_2 * tmp_5 - tmp_3 * tmp_5 * ( p_affine_0_1 - p_affine_1_1 ) -
                       tmp_4 * tmp_5 * ( p_affine_0_0 - p_affine_2_0 ) ) *
                     std::abs( p_affine_0_0 * p_affine_1_1 - p_affine_0_0 * p_affine_2_1 - p_affine_0_1 * p_affine_1_0 +
                               p_affine_0_1 * p_affine_2_0 + p_affine_1_0 * p_affine_2_1 - p_affine_1_1 * p_affine_2_0 );
      real_t tmp_7  = 0.025422453185103409 * tmp_6;
      real_t tmp_8  = 0.058393137863189684 * tmp_6;
      real_t tmp_9  = 0.041425537809186785 * tmp_6;
      real_t tmp_10 = 0.041425537809186785 * tmp_6;
      real_t tmp_11 = 0.025422453185103409 * tmp_6;
      real_t tmp_12 = 0.058393137863189684 * tmp_6;
      real_t tmp_13 = 0.025422453185103409 * tmp_6;
      real_t tmp_14 = 0.058393137863189684 * tmp_6;
      real_t tmp_15 = 0.041425537809186785 * tmp_6;
      real_t tmp_16 = 0.041425537809186785 * tmp_6;
      real_t tmp_17 = 0.041425537809186785 * tmp_6;
      real_t tmp_18 = 0.041425537809186785 * tmp_6;
      real_t a_0_0  = 0.053145049844816938 * tmp_10 + 0.063089014491502227 * tmp_11 + 0.24928674517091043 * tmp_12 +
                     0.87382197101699566 * tmp_13 + 0.50142650965817914 * tmp_14 + 0.053145049844816938 * tmp_15 +
                     0.63650249912139867 * tmp_16 + 0.31035245103378439 * tmp_17 + 0.31035245103378439 * tmp_18 +
                     0.063089014491502282 * tmp_7 + 0.24928674517091043 * tmp_8 + 0.63650249912139867 * tmp_9;
      real_t a_0_1 = 0.63650249912139867 * tmp_10 + 0.87382197101699555 * tmp_11 + 0.50142650965817914 * tmp_12 +
                     0.063089014491502227 * tmp_13 + 0.24928674517091043 * tmp_14 + 0.31035245103378439 * tmp_15 +
                     0.053145049844816938 * tmp_16 + 0.63650249912139867 * tmp_17 + 0.053145049844816938 * tmp_18 +
                     0.063089014491502227 * tmp_7 + 0.24928674517091043 * tmp_8 + 0.31035245103378439 * tmp_9;
      real_t a_0_2 = 0.31035245103378439 * tmp_10 + 0.063089014491502227 * tmp_11 + 0.24928674517091043 * tmp_12 +
                     0.063089014491502227 * tmp_13 + 0.24928674517091043 * tmp_14 + 0.63650249912139867 * tmp_15 +
                     0.31035245103378439 * tmp_16 + 0.053145049844816938 * tmp_17 + 0.63650249912139867 * tmp_18 +
                     0.87382197101699555 * tmp_7 + 0.50142650965817914 * tmp_8 + 0.053145049844816938 * tmp_9;
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

      real_t tmp_0  = -p_affine_0_0;
      real_t tmp_1  = p_affine_1_0 + tmp_0;
      real_t tmp_2  = -p_affine_0_1;
      real_t tmp_3  = p_affine_2_1 + tmp_2;
      real_t tmp_4  = p_affine_2_0 + tmp_0;
      real_t tmp_5  = p_affine_1_1 + tmp_2;
      real_t tmp_6  = 1.0 / ( tmp_1 * tmp_3 - tmp_4 * tmp_5 );
      real_t tmp_7  = -p_affine_6_1 + p_affine_7_1;
      real_t tmp_8  = p_affine_6_1 + tmp_2;
      real_t tmp_9  = tmp_6 * ( 0.046910077030668018 * tmp_7 + tmp_8 );
      real_t tmp_10 = tmp_1 * tmp_9;
      real_t tmp_11 = p_affine_0_0 - p_affine_2_0;
      real_t tmp_12 = tmp_11 * tmp_9;
      real_t tmp_13 = -p_affine_6_0 + p_affine_7_0;
      real_t tmp_14 = p_affine_6_0 + tmp_0;
      real_t tmp_15 = tmp_6 * ( 0.046910077030668018 * tmp_13 + tmp_14 );
      real_t tmp_16 = tmp_15 * tmp_3;
      real_t tmp_17 = p_affine_0_1 - p_affine_1_1;
      real_t tmp_18 = tmp_15 * tmp_17;
      real_t tmp_19 = -0.5 * tmp_10 - 0.5 * tmp_12 - 0.5 * tmp_16 - 0.5 * tmp_18 + 0.5;
      real_t tmp_20 = tmp_12 + tmp_16;
      real_t tmp_21 = tmp_20 - 1.0 / 3.0;
      real_t tmp_22 = tmp_10 + tmp_18;
      real_t tmp_23 = tmp_22 - 1.0 / 3.0;
      real_t tmp_24 = p_affine_10_0 * ( tmp_1 * tmp_21 + tmp_23 * tmp_4 );
      real_t tmp_25 = p_affine_10_1 * ( tmp_21 * tmp_5 + tmp_23 * tmp_3 );
      real_t tmp_26 = std::abs( std::pow( ( tmp_13 * tmp_13 ) + ( tmp_7 * tmp_7 ), 1.0 / 2.0 ) );
      real_t tmp_27 = 0.11846344252809471 * tmp_26;
      real_t tmp_28 = tmp_6 * ( 0.23076534494715845 * tmp_7 + tmp_8 );
      real_t tmp_29 = tmp_1 * tmp_28;
      real_t tmp_30 = tmp_11 * tmp_28;
      real_t tmp_31 = tmp_6 * ( 0.23076534494715845 * tmp_13 + tmp_14 );
      real_t tmp_32 = tmp_3 * tmp_31;
      real_t tmp_33 = tmp_17 * tmp_31;
      real_t tmp_34 = -0.5 * tmp_29 - 0.5 * tmp_30 - 0.5 * tmp_32 - 0.5 * tmp_33 + 0.5;
      real_t tmp_35 = tmp_30 + tmp_32;
      real_t tmp_36 = tmp_35 - 1.0 / 3.0;
      real_t tmp_37 = tmp_29 + tmp_33;
      real_t tmp_38 = tmp_37 - 1.0 / 3.0;
      real_t tmp_39 = p_affine_10_0 * ( tmp_1 * tmp_36 + tmp_38 * tmp_4 );
      real_t tmp_40 = p_affine_10_1 * ( tmp_3 * tmp_38 + tmp_36 * tmp_5 );
      real_t tmp_41 = 0.2393143352496831 * tmp_26;
      real_t tmp_42 = tmp_6 * ( 0.5 * tmp_7 + tmp_8 );
      real_t tmp_43 = tmp_1 * tmp_42;
      real_t tmp_44 = tmp_11 * tmp_42;
      real_t tmp_45 = tmp_6 * ( 0.5 * tmp_13 + tmp_14 );
      real_t tmp_46 = tmp_3 * tmp_45;
      real_t tmp_47 = tmp_17 * tmp_45;
      real_t tmp_48 = -0.5 * tmp_43 - 0.5 * tmp_44 - 0.5 * tmp_46 - 0.5 * tmp_47 + 0.5;
      real_t tmp_49 = tmp_44 + tmp_46;
      real_t tmp_50 = tmp_49 - 1.0 / 3.0;
      real_t tmp_51 = tmp_43 + tmp_47;
      real_t tmp_52 = tmp_51 - 1.0 / 3.0;
      real_t tmp_53 = p_affine_10_0 * ( tmp_1 * tmp_50 + tmp_4 * tmp_52 );
      real_t tmp_54 = p_affine_10_1 * ( tmp_3 * tmp_52 + tmp_5 * tmp_50 );
      real_t tmp_55 = 0.2844444444444445 * tmp_26;
      real_t tmp_56 = tmp_6 * ( 0.7692346550528415 * tmp_7 + tmp_8 );
      real_t tmp_57 = tmp_1 * tmp_56;
      real_t tmp_58 = tmp_11 * tmp_56;
      real_t tmp_59 = tmp_6 * ( 0.7692346550528415 * tmp_13 + tmp_14 );
      real_t tmp_60 = tmp_3 * tmp_59;
      real_t tmp_61 = tmp_17 * tmp_59;
      real_t tmp_62 = -0.5 * tmp_57 - 0.5 * tmp_58 - 0.5 * tmp_60 - 0.5 * tmp_61 + 0.5;
      real_t tmp_63 = tmp_58 + tmp_60;
      real_t tmp_64 = tmp_63 - 1.0 / 3.0;
      real_t tmp_65 = tmp_57 + tmp_61;
      real_t tmp_66 = tmp_65 - 1.0 / 3.0;
      real_t tmp_67 = p_affine_10_0 * ( tmp_1 * tmp_64 + tmp_4 * tmp_66 );
      real_t tmp_68 = p_affine_10_1 * ( tmp_3 * tmp_66 + tmp_5 * tmp_64 );
      real_t tmp_69 = 0.2393143352496831 * tmp_26;
      real_t tmp_70 = tmp_6 * ( 0.95308992296933193 * tmp_7 + tmp_8 );
      real_t tmp_71 = tmp_1 * tmp_70;
      real_t tmp_72 = tmp_11 * tmp_70;
      real_t tmp_73 = tmp_6 * ( 0.95308992296933193 * tmp_13 + tmp_14 );
      real_t tmp_74 = tmp_3 * tmp_73;
      real_t tmp_75 = tmp_17 * tmp_73;
      real_t tmp_76 = -0.5 * tmp_71 - 0.5 * tmp_72 - 0.5 * tmp_74 - 0.5 * tmp_75 + 0.5;
      real_t tmp_77 = tmp_72 + tmp_74;
      real_t tmp_78 = tmp_77 - 1.0 / 3.0;
      real_t tmp_79 = tmp_71 + tmp_75;
      real_t tmp_80 = tmp_79 - 1.0 / 3.0;
      real_t tmp_81 = p_affine_10_0 * ( tmp_1 * tmp_78 + tmp_4 * tmp_80 );
      real_t tmp_82 = p_affine_10_1 * ( tmp_3 * tmp_80 + tmp_5 * tmp_78 );
      real_t tmp_83 = 0.11846344252809471 * tmp_26;
      real_t tmp_84 = 0.5 * tmp_20;
      real_t tmp_85 = 0.5 * tmp_35;
      real_t tmp_86 = 0.5 * tmp_49;
      real_t tmp_87 = 0.5 * tmp_63;
      real_t tmp_88 = 0.5 * tmp_77;
      real_t tmp_89 = 0.5 * tmp_22;
      real_t tmp_90 = 0.5 * tmp_37;
      real_t tmp_91 = 0.5 * tmp_51;
      real_t tmp_92 = 0.5 * tmp_65;
      real_t tmp_93 = 0.5 * tmp_79;
      real_t a_0_0  = tmp_27 * ( tmp_19 * tmp_24 + tmp_19 * tmp_25 ) + tmp_41 * ( tmp_34 * tmp_39 + tmp_34 * tmp_40 ) +
                     tmp_55 * ( tmp_48 * tmp_53 + tmp_48 * tmp_54 ) + tmp_69 * ( tmp_62 * tmp_67 + tmp_62 * tmp_68 ) +
                     tmp_83 * ( tmp_76 * tmp_81 + tmp_76 * tmp_82 );
      real_t a_0_1 = tmp_27 * ( tmp_24 * tmp_84 + tmp_25 * tmp_84 ) + tmp_41 * ( tmp_39 * tmp_85 + tmp_40 * tmp_85 ) +
                     tmp_55 * ( tmp_53 * tmp_86 + tmp_54 * tmp_86 ) + tmp_69 * ( tmp_67 * tmp_87 + tmp_68 * tmp_87 ) +
                     tmp_83 * ( tmp_81 * tmp_88 + tmp_82 * tmp_88 );
      real_t a_0_2 = tmp_27 * ( tmp_24 * tmp_89 + tmp_25 * tmp_89 ) + tmp_41 * ( tmp_39 * tmp_90 + tmp_40 * tmp_90 ) +
                     tmp_55 * ( tmp_53 * tmp_91 + tmp_54 * tmp_91 ) + tmp_69 * ( tmp_67 * tmp_92 + tmp_68 * tmp_92 ) +
                     tmp_83 * ( tmp_81 * tmp_93 + tmp_82 * tmp_93 );
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
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

      real_t tmp_0   = -p_affine_3_0;
      real_t tmp_1   = p_affine_4_0 + tmp_0;
      real_t tmp_2   = -p_affine_3_1;
      real_t tmp_3   = p_affine_5_1 + tmp_2;
      real_t tmp_4   = 1.0 / ( tmp_1 * tmp_3 - ( p_affine_4_1 + tmp_2 ) * ( p_affine_5_0 + tmp_0 ) );
      real_t tmp_5   = -p_affine_6_1 + p_affine_7_1;
      real_t tmp_6   = p_affine_6_1 + 0.046910077030668018 * tmp_5;
      real_t tmp_7   = tmp_4 * ( tmp_2 + tmp_6 );
      real_t tmp_8   = tmp_1 * tmp_7;
      real_t tmp_9   = p_affine_3_0 - p_affine_5_0;
      real_t tmp_10  = tmp_7 * tmp_9;
      real_t tmp_11  = -p_affine_6_0 + p_affine_7_0;
      real_t tmp_12  = p_affine_6_0 + 0.046910077030668018 * tmp_11;
      real_t tmp_13  = tmp_4 * ( tmp_0 + tmp_12 );
      real_t tmp_14  = tmp_13 * tmp_3;
      real_t tmp_15  = p_affine_3_1 - p_affine_4_1;
      real_t tmp_16  = tmp_13 * tmp_15;
      real_t tmp_17  = -0.5 * tmp_10 - 0.5 * tmp_14 - 0.5 * tmp_16 - 0.5 * tmp_8 + 0.5;
      real_t tmp_18  = -p_affine_0_0;
      real_t tmp_19  = p_affine_1_0 + tmp_18;
      real_t tmp_20  = p_affine_0_0 - p_affine_2_0;
      real_t tmp_21  = -p_affine_0_1;
      real_t tmp_22  = p_affine_2_1 + tmp_21;
      real_t tmp_23  = p_affine_2_0 + tmp_18;
      real_t tmp_24  = p_affine_1_1 + tmp_21;
      real_t tmp_25  = 1.0 / ( tmp_19 * tmp_22 - tmp_23 * tmp_24 );
      real_t tmp_26  = tmp_25 * ( tmp_21 + tmp_6 );
      real_t tmp_27  = tmp_25 * ( tmp_12 + tmp_18 );
      real_t tmp_28  = tmp_20 * tmp_26 + tmp_22 * tmp_27 - 1.0 / 3.0;
      real_t tmp_29  = p_affine_0_1 - p_affine_1_1;
      real_t tmp_30  = tmp_19 * tmp_26 + tmp_27 * tmp_29 - 1.0 / 3.0;
      real_t tmp_31  = p_affine_10_0 * ( tmp_19 * tmp_28 + tmp_23 * tmp_30 );
      real_t tmp_32  = p_affine_10_1 * ( tmp_22 * tmp_30 + tmp_24 * tmp_28 );
      real_t tmp_33  = std::abs( std::pow( ( tmp_11 * tmp_11 ) + ( tmp_5 * tmp_5 ), 1.0 / 2.0 ) );
      real_t tmp_34  = 0.11846344252809471 * tmp_33;
      real_t tmp_35  = p_affine_6_1 + 0.23076534494715845 * tmp_5;
      real_t tmp_36  = tmp_4 * ( tmp_2 + tmp_35 );
      real_t tmp_37  = tmp_1 * tmp_36;
      real_t tmp_38  = tmp_36 * tmp_9;
      real_t tmp_39  = p_affine_6_0 + 0.23076534494715845 * tmp_11;
      real_t tmp_40  = tmp_4 * ( tmp_0 + tmp_39 );
      real_t tmp_41  = tmp_3 * tmp_40;
      real_t tmp_42  = tmp_15 * tmp_40;
      real_t tmp_43  = -0.5 * tmp_37 - 0.5 * tmp_38 - 0.5 * tmp_41 - 0.5 * tmp_42 + 0.5;
      real_t tmp_44  = tmp_25 * ( tmp_21 + tmp_35 );
      real_t tmp_45  = tmp_25 * ( tmp_18 + tmp_39 );
      real_t tmp_46  = tmp_20 * tmp_44 + tmp_22 * tmp_45 - 1.0 / 3.0;
      real_t tmp_47  = tmp_19 * tmp_44 + tmp_29 * tmp_45 - 1.0 / 3.0;
      real_t tmp_48  = p_affine_10_0 * ( tmp_19 * tmp_46 + tmp_23 * tmp_47 );
      real_t tmp_49  = p_affine_10_1 * ( tmp_22 * tmp_47 + tmp_24 * tmp_46 );
      real_t tmp_50  = 0.2393143352496831 * tmp_33;
      real_t tmp_51  = p_affine_6_1 + 0.5 * tmp_5;
      real_t tmp_52  = tmp_4 * ( tmp_2 + tmp_51 );
      real_t tmp_53  = tmp_1 * tmp_52;
      real_t tmp_54  = tmp_52 * tmp_9;
      real_t tmp_55  = p_affine_6_0 + 0.5 * tmp_11;
      real_t tmp_56  = tmp_4 * ( tmp_0 + tmp_55 );
      real_t tmp_57  = tmp_3 * tmp_56;
      real_t tmp_58  = tmp_15 * tmp_56;
      real_t tmp_59  = -0.5 * tmp_53 - 0.5 * tmp_54 - 0.5 * tmp_57 - 0.5 * tmp_58 + 0.5;
      real_t tmp_60  = tmp_25 * ( tmp_21 + tmp_51 );
      real_t tmp_61  = tmp_25 * ( tmp_18 + tmp_55 );
      real_t tmp_62  = tmp_20 * tmp_60 + tmp_22 * tmp_61 - 1.0 / 3.0;
      real_t tmp_63  = tmp_19 * tmp_60 + tmp_29 * tmp_61 - 1.0 / 3.0;
      real_t tmp_64  = p_affine_10_0 * ( tmp_19 * tmp_62 + tmp_23 * tmp_63 );
      real_t tmp_65  = p_affine_10_1 * ( tmp_22 * tmp_63 + tmp_24 * tmp_62 );
      real_t tmp_66  = 0.2844444444444445 * tmp_33;
      real_t tmp_67  = p_affine_6_1 + 0.7692346550528415 * tmp_5;
      real_t tmp_68  = tmp_4 * ( tmp_2 + tmp_67 );
      real_t tmp_69  = tmp_1 * tmp_68;
      real_t tmp_70  = tmp_68 * tmp_9;
      real_t tmp_71  = p_affine_6_0 + 0.7692346550528415 * tmp_11;
      real_t tmp_72  = tmp_4 * ( tmp_0 + tmp_71 );
      real_t tmp_73  = tmp_3 * tmp_72;
      real_t tmp_74  = tmp_15 * tmp_72;
      real_t tmp_75  = -0.5 * tmp_69 - 0.5 * tmp_70 - 0.5 * tmp_73 - 0.5 * tmp_74 + 0.5;
      real_t tmp_76  = tmp_25 * ( tmp_21 + tmp_67 );
      real_t tmp_77  = tmp_25 * ( tmp_18 + tmp_71 );
      real_t tmp_78  = tmp_20 * tmp_76 + tmp_22 * tmp_77 - 1.0 / 3.0;
      real_t tmp_79  = tmp_19 * tmp_76 + tmp_29 * tmp_77 - 1.0 / 3.0;
      real_t tmp_80  = p_affine_10_0 * ( tmp_19 * tmp_78 + tmp_23 * tmp_79 );
      real_t tmp_81  = p_affine_10_1 * ( tmp_22 * tmp_79 + tmp_24 * tmp_78 );
      real_t tmp_82  = 0.2393143352496831 * tmp_33;
      real_t tmp_83  = p_affine_6_1 + 0.95308992296933193 * tmp_5;
      real_t tmp_84  = tmp_4 * ( tmp_2 + tmp_83 );
      real_t tmp_85  = tmp_1 * tmp_84;
      real_t tmp_86  = tmp_84 * tmp_9;
      real_t tmp_87  = p_affine_6_0 + 0.95308992296933193 * tmp_11;
      real_t tmp_88  = tmp_4 * ( tmp_0 + tmp_87 );
      real_t tmp_89  = tmp_3 * tmp_88;
      real_t tmp_90  = tmp_15 * tmp_88;
      real_t tmp_91  = -0.5 * tmp_85 - 0.5 * tmp_86 - 0.5 * tmp_89 - 0.5 * tmp_90 + 0.5;
      real_t tmp_92  = tmp_25 * ( tmp_21 + tmp_83 );
      real_t tmp_93  = tmp_25 * ( tmp_18 + tmp_87 );
      real_t tmp_94  = tmp_20 * tmp_92 + tmp_22 * tmp_93 - 1.0 / 3.0;
      real_t tmp_95  = tmp_19 * tmp_92 + tmp_29 * tmp_93 - 1.0 / 3.0;
      real_t tmp_96  = p_affine_10_0 * ( tmp_19 * tmp_94 + tmp_23 * tmp_95 );
      real_t tmp_97  = p_affine_10_1 * ( tmp_22 * tmp_95 + tmp_24 * tmp_94 );
      real_t tmp_98  = 0.11846344252809471 * tmp_33;
      real_t tmp_99  = 0.5 * tmp_10 + 0.5 * tmp_14;
      real_t tmp_100 = 0.5 * tmp_38 + 0.5 * tmp_41;
      real_t tmp_101 = 0.5 * tmp_54 + 0.5 * tmp_57;
      real_t tmp_102 = 0.5 * tmp_70 + 0.5 * tmp_73;
      real_t tmp_103 = 0.5 * tmp_86 + 0.5 * tmp_89;
      real_t tmp_104 = 0.5 * tmp_16 + 0.5 * tmp_8;
      real_t tmp_105 = 0.5 * tmp_37 + 0.5 * tmp_42;
      real_t tmp_106 = 0.5 * tmp_53 + 0.5 * tmp_58;
      real_t tmp_107 = 0.5 * tmp_69 + 0.5 * tmp_74;
      real_t tmp_108 = 0.5 * tmp_85 + 0.5 * tmp_90;
      real_t a_0_0   = tmp_34 * ( tmp_17 * tmp_31 + tmp_17 * tmp_32 ) + tmp_50 * ( tmp_43 * tmp_48 + tmp_43 * tmp_49 ) +
                     tmp_66 * ( tmp_59 * tmp_64 + tmp_59 * tmp_65 ) + tmp_82 * ( tmp_75 * tmp_80 + tmp_75 * tmp_81 ) +
                     tmp_98 * ( tmp_91 * tmp_96 + tmp_91 * tmp_97 );
      real_t a_0_1 = tmp_34 * ( tmp_31 * tmp_99 + tmp_32 * tmp_99 ) + tmp_50 * ( tmp_100 * tmp_48 + tmp_100 * tmp_49 ) +
                     tmp_66 * ( tmp_101 * tmp_64 + tmp_101 * tmp_65 ) + tmp_82 * ( tmp_102 * tmp_80 + tmp_102 * tmp_81 ) +
                     tmp_98 * ( tmp_103 * tmp_96 + tmp_103 * tmp_97 );
      real_t a_0_2 = tmp_34 * ( tmp_104 * tmp_31 + tmp_104 * tmp_32 ) + tmp_50 * ( tmp_105 * tmp_48 + tmp_105 * tmp_49 ) +
                     tmp_66 * ( tmp_106 * tmp_64 + tmp_106 * tmp_65 ) + tmp_82 * ( tmp_107 * tmp_80 + tmp_107 * tmp_81 ) +
                     tmp_98 * ( tmp_108 * tmp_96 + tmp_108 * tmp_97 );
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
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

      real_t tmp_0  = -p_affine_0_0;
      real_t tmp_1  = p_affine_1_0 + tmp_0;
      real_t tmp_2  = -p_affine_0_1;
      real_t tmp_3  = p_affine_2_1 + tmp_2;
      real_t tmp_4  = p_affine_2_0 + tmp_0;
      real_t tmp_5  = p_affine_1_1 + tmp_2;
      real_t tmp_6  = 1.0 / ( tmp_1 * tmp_3 - tmp_4 * tmp_5 );
      real_t tmp_7  = -p_affine_6_1 + p_affine_7_1;
      real_t tmp_8  = p_affine_6_1 + tmp_2;
      real_t tmp_9  = tmp_6 * ( 0.046910077030668018 * tmp_7 + tmp_8 );
      real_t tmp_10 = tmp_1 * tmp_9;
      real_t tmp_11 = p_affine_0_0 - p_affine_2_0;
      real_t tmp_12 = tmp_11 * tmp_9;
      real_t tmp_13 = -p_affine_6_0 + p_affine_7_0;
      real_t tmp_14 = p_affine_6_0 + tmp_0;
      real_t tmp_15 = tmp_6 * ( 0.046910077030668018 * tmp_13 + tmp_14 );
      real_t tmp_16 = tmp_15 * tmp_3;
      real_t tmp_17 = p_affine_0_1 - p_affine_1_1;
      real_t tmp_18 = tmp_15 * tmp_17;
      real_t tmp_19 = -tmp_10 - tmp_12 - tmp_16 - tmp_18 + 1;
      real_t tmp_20 = tmp_12 + tmp_16;
      real_t tmp_21 = tmp_20 - 1.0 / 3.0;
      real_t tmp_22 = tmp_10 + tmp_18;
      real_t tmp_23 = tmp_22 - 1.0 / 3.0;
      real_t tmp_24 = p_affine_10_0 * ( tmp_1 * tmp_21 + tmp_23 * tmp_4 );
      real_t tmp_25 = p_affine_10_1 * ( tmp_21 * tmp_5 + tmp_23 * tmp_3 );
      real_t tmp_26 = std::abs( std::pow( ( tmp_13 * tmp_13 ) + ( tmp_7 * tmp_7 ), 1.0 / 2.0 ) );
      real_t tmp_27 = 0.11846344252809471 * tmp_26;
      real_t tmp_28 = tmp_6 * ( 0.23076534494715845 * tmp_7 + tmp_8 );
      real_t tmp_29 = tmp_1 * tmp_28;
      real_t tmp_30 = tmp_11 * tmp_28;
      real_t tmp_31 = tmp_6 * ( 0.23076534494715845 * tmp_13 + tmp_14 );
      real_t tmp_32 = tmp_3 * tmp_31;
      real_t tmp_33 = tmp_17 * tmp_31;
      real_t tmp_34 = -tmp_29 - tmp_30 - tmp_32 - tmp_33 + 1;
      real_t tmp_35 = tmp_30 + tmp_32;
      real_t tmp_36 = tmp_35 - 1.0 / 3.0;
      real_t tmp_37 = tmp_29 + tmp_33;
      real_t tmp_38 = tmp_37 - 1.0 / 3.0;
      real_t tmp_39 = p_affine_10_0 * ( tmp_1 * tmp_36 + tmp_38 * tmp_4 );
      real_t tmp_40 = p_affine_10_1 * ( tmp_3 * tmp_38 + tmp_36 * tmp_5 );
      real_t tmp_41 = 0.2393143352496831 * tmp_26;
      real_t tmp_42 = tmp_6 * ( 0.5 * tmp_7 + tmp_8 );
      real_t tmp_43 = tmp_1 * tmp_42;
      real_t tmp_44 = tmp_11 * tmp_42;
      real_t tmp_45 = tmp_6 * ( 0.5 * tmp_13 + tmp_14 );
      real_t tmp_46 = tmp_3 * tmp_45;
      real_t tmp_47 = tmp_17 * tmp_45;
      real_t tmp_48 = -tmp_43 - tmp_44 - tmp_46 - tmp_47 + 1;
      real_t tmp_49 = tmp_44 + tmp_46;
      real_t tmp_50 = tmp_49 - 1.0 / 3.0;
      real_t tmp_51 = tmp_43 + tmp_47;
      real_t tmp_52 = tmp_51 - 1.0 / 3.0;
      real_t tmp_53 = p_affine_10_0 * ( tmp_1 * tmp_50 + tmp_4 * tmp_52 );
      real_t tmp_54 = p_affine_10_1 * ( tmp_3 * tmp_52 + tmp_5 * tmp_50 );
      real_t tmp_55 = 0.2844444444444445 * tmp_26;
      real_t tmp_56 = tmp_6 * ( 0.7692346550528415 * tmp_7 + tmp_8 );
      real_t tmp_57 = tmp_1 * tmp_56;
      real_t tmp_58 = tmp_11 * tmp_56;
      real_t tmp_59 = tmp_6 * ( 0.7692346550528415 * tmp_13 + tmp_14 );
      real_t tmp_60 = tmp_3 * tmp_59;
      real_t tmp_61 = tmp_17 * tmp_59;
      real_t tmp_62 = -tmp_57 - tmp_58 - tmp_60 - tmp_61 + 1;
      real_t tmp_63 = tmp_58 + tmp_60;
      real_t tmp_64 = tmp_63 - 1.0 / 3.0;
      real_t tmp_65 = tmp_57 + tmp_61;
      real_t tmp_66 = tmp_65 - 1.0 / 3.0;
      real_t tmp_67 = p_affine_10_0 * ( tmp_1 * tmp_64 + tmp_4 * tmp_66 );
      real_t tmp_68 = p_affine_10_1 * ( tmp_3 * tmp_66 + tmp_5 * tmp_64 );
      real_t tmp_69 = 0.2393143352496831 * tmp_26;
      real_t tmp_70 = tmp_6 * ( 0.95308992296933193 * tmp_7 + tmp_8 );
      real_t tmp_71 = tmp_1 * tmp_70;
      real_t tmp_72 = tmp_11 * tmp_70;
      real_t tmp_73 = tmp_6 * ( 0.95308992296933193 * tmp_13 + tmp_14 );
      real_t tmp_74 = tmp_3 * tmp_73;
      real_t tmp_75 = tmp_17 * tmp_73;
      real_t tmp_76 = -tmp_71 - tmp_72 - tmp_74 - tmp_75 + 1;
      real_t tmp_77 = tmp_72 + tmp_74;
      real_t tmp_78 = tmp_77 - 1.0 / 3.0;
      real_t tmp_79 = tmp_71 + tmp_75;
      real_t tmp_80 = tmp_79 - 1.0 / 3.0;
      real_t tmp_81 = p_affine_10_0 * ( tmp_1 * tmp_78 + tmp_4 * tmp_80 );
      real_t tmp_82 = p_affine_10_1 * ( tmp_3 * tmp_80 + tmp_5 * tmp_78 );
      real_t tmp_83 = 0.11846344252809471 * tmp_26;
      real_t a_0_0  = tmp_27 * ( tmp_19 * tmp_24 + tmp_19 * tmp_25 ) + tmp_41 * ( tmp_34 * tmp_39 + tmp_34 * tmp_40 ) +
                     tmp_55 * ( tmp_48 * tmp_53 + tmp_48 * tmp_54 ) + tmp_69 * ( tmp_62 * tmp_67 + tmp_62 * tmp_68 ) +
                     tmp_83 * ( tmp_76 * tmp_81 + tmp_76 * tmp_82 );
      real_t a_0_1 = tmp_27 * ( tmp_20 * tmp_24 + tmp_20 * tmp_25 ) + tmp_41 * ( tmp_35 * tmp_39 + tmp_35 * tmp_40 ) +
                     tmp_55 * ( tmp_49 * tmp_53 + tmp_49 * tmp_54 ) + tmp_69 * ( tmp_63 * tmp_67 + tmp_63 * tmp_68 ) +
                     tmp_83 * ( tmp_77 * tmp_81 + tmp_77 * tmp_82 );
      real_t a_0_2 = tmp_27 * ( tmp_22 * tmp_24 + tmp_22 * tmp_25 ) + tmp_41 * ( tmp_37 * tmp_39 + tmp_37 * tmp_40 ) +
                     tmp_55 * ( tmp_51 * tmp_53 + tmp_51 * tmp_54 ) + tmp_69 * ( tmp_65 * tmp_67 + tmp_65 * tmp_68 ) +
                     tmp_83 * ( tmp_79 * tmp_81 + tmp_79 * tmp_82 );
      elMat( 0, 0 ) = a_0_0;
      elMat( 0, 1 ) = a_0_1;
      elMat( 0, 2 ) = a_0_2;
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
};



class EGDivtFormEP0 : public hyteg::dg::DGForm2D
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

      real_t tmp_0 = -p_affine_0_0;
      real_t tmp_1 = -p_affine_0_1;
      real_t tmp_2 = ( p_affine_1_0 + tmp_0 ) * ( p_affine_2_1 + tmp_1 );
      real_t tmp_3 = p_affine_2_0 + tmp_0;
      real_t tmp_4 = p_affine_1_1 + tmp_1;
      real_t tmp_5 = 1.0 / ( tmp_2 - tmp_3 * tmp_4 );
      real_t tmp_6 = ( -2 * tmp_2 * tmp_5 - tmp_3 * tmp_5 * ( p_affine_0_1 - p_affine_1_1 ) -
                       tmp_4 * tmp_5 * ( p_affine_0_0 - p_affine_2_0 ) ) *
                     std::abs( p_affine_0_0 * p_affine_1_1 - p_affine_0_0 * p_affine_2_1 - p_affine_0_1 * p_affine_1_0 +
                               p_affine_0_1 * p_affine_2_0 + p_affine_1_0 * p_affine_2_1 - p_affine_1_1 * p_affine_2_0 );
      real_t a_0_0  = 0.5 * tmp_6;
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

      real_t tmp_0  = -p_affine_6_0 + p_affine_7_0;
      real_t tmp_1  = -p_affine_6_1 + p_affine_7_1;
      real_t tmp_2  = std::abs( std::pow( ( tmp_0 * tmp_0 ) + ( tmp_1 * tmp_1 ), 1.0 / 2.0 ) );
      real_t tmp_3  = -p_affine_0_0;
      real_t tmp_4  = p_affine_1_0 + tmp_3;
      real_t tmp_5  = p_affine_0_0 - p_affine_2_0;
      real_t tmp_6  = -p_affine_0_1;
      real_t tmp_7  = p_affine_2_1 + tmp_6;
      real_t tmp_8  = p_affine_2_0 + tmp_3;
      real_t tmp_9  = p_affine_1_1 + tmp_6;
      real_t tmp_10 = 1.0 / ( tmp_4 * tmp_7 - tmp_8 * tmp_9 );
      real_t tmp_11 = p_affine_6_1 + tmp_6;
      real_t tmp_12 = tmp_10 * ( 0.046910077030668018 * tmp_1 + tmp_11 );
      real_t tmp_13 = p_affine_6_0 + tmp_3;
      real_t tmp_14 = tmp_10 * ( 0.046910077030668018 * tmp_0 + tmp_13 );
      real_t tmp_15 = tmp_12 * tmp_5 + tmp_14 * tmp_7 - 1.0 / 3.0;
      real_t tmp_16 = p_affine_0_1 - p_affine_1_1;
      real_t tmp_17 = tmp_12 * tmp_4 + tmp_14 * tmp_16 - 1.0 / 3.0;
      real_t tmp_18 = 0.5 * p_affine_10_0;
      real_t tmp_19 = 0.5 * p_affine_10_1;
      real_t tmp_20 = tmp_10 * ( 0.23076534494715845 * tmp_1 + tmp_11 );
      real_t tmp_21 = tmp_10 * ( 0.23076534494715845 * tmp_0 + tmp_13 );
      real_t tmp_22 = tmp_20 * tmp_5 + tmp_21 * tmp_7 - 1.0 / 3.0;
      real_t tmp_23 = tmp_16 * tmp_21 + tmp_20 * tmp_4 - 1.0 / 3.0;
      real_t tmp_24 = tmp_10 * ( 0.5 * tmp_1 + tmp_11 );
      real_t tmp_25 = tmp_10 * ( 0.5 * tmp_0 + tmp_13 );
      real_t tmp_26 = tmp_24 * tmp_5 + tmp_25 * tmp_7 - 1.0 / 3.0;
      real_t tmp_27 = tmp_16 * tmp_25 + tmp_24 * tmp_4 - 1.0 / 3.0;
      real_t tmp_28 = tmp_10 * ( 0.7692346550528415 * tmp_1 + tmp_11 );
      real_t tmp_29 = tmp_10 * ( 0.7692346550528415 * tmp_0 + tmp_13 );
      real_t tmp_30 = tmp_28 * tmp_5 + tmp_29 * tmp_7 - 1.0 / 3.0;
      real_t tmp_31 = tmp_16 * tmp_29 + tmp_28 * tmp_4 - 1.0 / 3.0;
      real_t tmp_32 = tmp_10 * ( 0.95308992296933193 * tmp_1 + tmp_11 );
      real_t tmp_33 = tmp_10 * ( 0.95308992296933193 * tmp_0 + tmp_13 );
      real_t tmp_34 = tmp_32 * tmp_5 + tmp_33 * tmp_7 - 1.0 / 3.0;
      real_t tmp_35 = tmp_16 * tmp_33 + tmp_32 * tmp_4 - 1.0 / 3.0;
      real_t a_0_0  = 0.11846344252809471 * tmp_2 *
                         ( tmp_18 * ( tmp_15 * tmp_4 + tmp_17 * tmp_8 ) + tmp_19 * ( tmp_15 * tmp_9 + tmp_17 * tmp_7 ) ) +
                     0.2393143352496831 * tmp_2 *
                         ( tmp_18 * ( tmp_22 * tmp_4 + tmp_23 * tmp_8 ) + tmp_19 * ( tmp_22 * tmp_9 + tmp_23 * tmp_7 ) ) +
                     0.2844444444444445 * tmp_2 *
                         ( tmp_18 * ( tmp_26 * tmp_4 + tmp_27 * tmp_8 ) + tmp_19 * ( tmp_26 * tmp_9 + tmp_27 * tmp_7 ) ) +
                     0.2393143352496831 * tmp_2 *
                         ( tmp_18 * ( tmp_30 * tmp_4 + tmp_31 * tmp_8 ) + tmp_19 * ( tmp_30 * tmp_9 + tmp_31 * tmp_7 ) ) +
                     0.11846344252809471 * tmp_2 *
                         ( tmp_18 * ( tmp_34 * tmp_4 + tmp_35 * tmp_8 ) + tmp_19 * ( tmp_34 * tmp_9 + tmp_35 * tmp_7 ) );
      elMat( 0, 0 ) = a_0_0;
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

      real_t tmp_0  = -p_affine_6_0 + p_affine_7_0;
      real_t tmp_1  = -p_affine_6_1 + p_affine_7_1;
      real_t tmp_2  = std::abs( std::pow( ( tmp_0 * tmp_0 ) + ( tmp_1 * tmp_1 ), 1.0 / 2.0 ) );
      real_t tmp_3  = -p_affine_0_0;
      real_t tmp_4  = p_affine_1_0 + tmp_3;
      real_t tmp_5  = p_affine_0_0 - p_affine_2_0;
      real_t tmp_6  = -p_affine_0_1;
      real_t tmp_7  = p_affine_2_1 + tmp_6;
      real_t tmp_8  = p_affine_2_0 + tmp_3;
      real_t tmp_9  = p_affine_1_1 + tmp_6;
      real_t tmp_10 = 1.0 / ( tmp_4 * tmp_7 - tmp_8 * tmp_9 );
      real_t tmp_11 = p_affine_6_1 + tmp_6;
      real_t tmp_12 = tmp_10 * ( 0.046910077030668018 * tmp_1 + tmp_11 );
      real_t tmp_13 = p_affine_6_0 + tmp_3;
      real_t tmp_14 = tmp_10 * ( 0.046910077030668018 * tmp_0 + tmp_13 );
      real_t tmp_15 = tmp_12 * tmp_5 + tmp_14 * tmp_7 - 1.0 / 3.0;
      real_t tmp_16 = p_affine_0_1 - p_affine_1_1;
      real_t tmp_17 = tmp_12 * tmp_4 + tmp_14 * tmp_16 - 1.0 / 3.0;
      real_t tmp_18 = 0.5 * p_affine_10_0;
      real_t tmp_19 = 0.5 * p_affine_10_1;
      real_t tmp_20 = tmp_10 * ( 0.23076534494715845 * tmp_1 + tmp_11 );
      real_t tmp_21 = tmp_10 * ( 0.23076534494715845 * tmp_0 + tmp_13 );
      real_t tmp_22 = tmp_20 * tmp_5 + tmp_21 * tmp_7 - 1.0 / 3.0;
      real_t tmp_23 = tmp_16 * tmp_21 + tmp_20 * tmp_4 - 1.0 / 3.0;
      real_t tmp_24 = tmp_10 * ( 0.5 * tmp_1 + tmp_11 );
      real_t tmp_25 = tmp_10 * ( 0.5 * tmp_0 + tmp_13 );
      real_t tmp_26 = tmp_24 * tmp_5 + tmp_25 * tmp_7 - 1.0 / 3.0;
      real_t tmp_27 = tmp_16 * tmp_25 + tmp_24 * tmp_4 - 1.0 / 3.0;
      real_t tmp_28 = tmp_10 * ( 0.7692346550528415 * tmp_1 + tmp_11 );
      real_t tmp_29 = tmp_10 * ( 0.7692346550528415 * tmp_0 + tmp_13 );
      real_t tmp_30 = tmp_28 * tmp_5 + tmp_29 * tmp_7 - 1.0 / 3.0;
      real_t tmp_31 = tmp_16 * tmp_29 + tmp_28 * tmp_4 - 1.0 / 3.0;
      real_t tmp_32 = tmp_10 * ( 0.95308992296933193 * tmp_1 + tmp_11 );
      real_t tmp_33 = tmp_10 * ( 0.95308992296933193 * tmp_0 + tmp_13 );
      real_t tmp_34 = tmp_32 * tmp_5 + tmp_33 * tmp_7 - 1.0 / 3.0;
      real_t tmp_35 = tmp_16 * tmp_33 + tmp_32 * tmp_4 - 1.0 / 3.0;
      real_t a_0_0  = 0.11846344252809471 * tmp_2 *
                         ( tmp_18 * ( tmp_15 * tmp_4 + tmp_17 * tmp_8 ) + tmp_19 * ( tmp_15 * tmp_9 + tmp_17 * tmp_7 ) ) +
                     0.2393143352496831 * tmp_2 *
                         ( tmp_18 * ( tmp_22 * tmp_4 + tmp_23 * tmp_8 ) + tmp_19 * ( tmp_22 * tmp_9 + tmp_23 * tmp_7 ) ) +
                     0.2844444444444445 * tmp_2 *
                         ( tmp_18 * ( tmp_26 * tmp_4 + tmp_27 * tmp_8 ) + tmp_19 * ( tmp_26 * tmp_9 + tmp_27 * tmp_7 ) ) +
                     0.2393143352496831 * tmp_2 *
                         ( tmp_18 * ( tmp_30 * tmp_4 + tmp_31 * tmp_8 ) + tmp_19 * ( tmp_30 * tmp_9 + tmp_31 * tmp_7 ) ) +
                     0.11846344252809471 * tmp_2 *
                         ( tmp_18 * ( tmp_34 * tmp_4 + tmp_35 * tmp_8 ) + tmp_19 * ( tmp_34 * tmp_9 + tmp_35 * tmp_7 ) );
      elMat( 0, 0 ) = a_0_0;
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

      real_t tmp_0  = -p_affine_6_0 + p_affine_7_0;
      real_t tmp_1  = -p_affine_6_1 + p_affine_7_1;
      real_t tmp_2  = std::abs( std::pow( ( tmp_0 * tmp_0 ) + ( tmp_1 * tmp_1 ), 1.0 / 2.0 ) );
      real_t tmp_3  = -p_affine_0_0;
      real_t tmp_4  = p_affine_1_0 + tmp_3;
      real_t tmp_5  = p_affine_0_0 - p_affine_2_0;
      real_t tmp_6  = -p_affine_0_1;
      real_t tmp_7  = p_affine_2_1 + tmp_6;
      real_t tmp_8  = p_affine_2_0 + tmp_3;
      real_t tmp_9  = p_affine_1_1 + tmp_6;
      real_t tmp_10 = 1.0 / ( tmp_4 * tmp_7 - tmp_8 * tmp_9 );
      real_t tmp_11 = p_affine_6_1 + tmp_6;
      real_t tmp_12 = tmp_10 * ( 0.046910077030668018 * tmp_1 + tmp_11 );
      real_t tmp_13 = p_affine_6_0 + tmp_3;
      real_t tmp_14 = tmp_10 * ( 0.046910077030668018 * tmp_0 + tmp_13 );
      real_t tmp_15 = tmp_12 * tmp_5 + tmp_14 * tmp_7 - 1.0 / 3.0;
      real_t tmp_16 = p_affine_0_1 - p_affine_1_1;
      real_t tmp_17 = tmp_12 * tmp_4 + tmp_14 * tmp_16 - 1.0 / 3.0;
      real_t tmp_18 = tmp_10 * ( 0.23076534494715845 * tmp_1 + tmp_11 );
      real_t tmp_19 = tmp_10 * ( 0.23076534494715845 * tmp_0 + tmp_13 );
      real_t tmp_20 = tmp_18 * tmp_5 + tmp_19 * tmp_7 - 1.0 / 3.0;
      real_t tmp_21 = tmp_16 * tmp_19 + tmp_18 * tmp_4 - 1.0 / 3.0;
      real_t tmp_22 = tmp_10 * ( 0.5 * tmp_1 + tmp_11 );
      real_t tmp_23 = tmp_10 * ( 0.5 * tmp_0 + tmp_13 );
      real_t tmp_24 = tmp_22 * tmp_5 + tmp_23 * tmp_7 - 1.0 / 3.0;
      real_t tmp_25 = tmp_16 * tmp_23 + tmp_22 * tmp_4 - 1.0 / 3.0;
      real_t tmp_26 = tmp_10 * ( 0.7692346550528415 * tmp_1 + tmp_11 );
      real_t tmp_27 = tmp_10 * ( 0.7692346550528415 * tmp_0 + tmp_13 );
      real_t tmp_28 = tmp_26 * tmp_5 + tmp_27 * tmp_7 - 1.0 / 3.0;
      real_t tmp_29 = tmp_16 * tmp_27 + tmp_26 * tmp_4 - 1.0 / 3.0;
      real_t tmp_30 = tmp_10 * ( 0.95308992296933193 * tmp_1 + tmp_11 );
      real_t tmp_31 = tmp_10 * ( 0.95308992296933193 * tmp_0 + tmp_13 );
      real_t tmp_32 = tmp_30 * tmp_5 + tmp_31 * tmp_7 - 1.0 / 3.0;
      real_t tmp_33 = tmp_16 * tmp_31 + tmp_30 * tmp_4 - 1.0 / 3.0;
      real_t a_0_0 =
          0.11846344252809471 * tmp_2 *
              ( p_affine_10_0 * ( tmp_15 * tmp_4 + tmp_17 * tmp_8 ) + p_affine_10_1 * ( tmp_15 * tmp_9 + tmp_17 * tmp_7 ) ) +
          0.2393143352496831 * tmp_2 *
              ( p_affine_10_0 * ( tmp_20 * tmp_4 + tmp_21 * tmp_8 ) + p_affine_10_1 * ( tmp_20 * tmp_9 + tmp_21 * tmp_7 ) ) +
          0.2844444444444445 * tmp_2 *
              ( p_affine_10_0 * ( tmp_24 * tmp_4 + tmp_25 * tmp_8 ) + p_affine_10_1 * ( tmp_24 * tmp_9 + tmp_25 * tmp_7 ) ) +
          0.2393143352496831 * tmp_2 *
              ( p_affine_10_0 * ( tmp_28 * tmp_4 + tmp_29 * tmp_8 ) + p_affine_10_1 * ( tmp_28 * tmp_9 + tmp_29 * tmp_7 ) ) +
          0.11846344252809471 * tmp_2 *
              ( p_affine_10_0 * ( tmp_32 * tmp_4 + tmp_33 * tmp_8 ) + p_affine_10_1 * ( tmp_32 * tmp_9 + tmp_33 * tmp_7 ) );
      elMat( 0, 0 ) = a_0_0;
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
};

} // namespace eg

} // namespace dg
} // namespace hyteg