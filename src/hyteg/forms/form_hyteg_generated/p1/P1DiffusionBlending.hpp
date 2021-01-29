/*
 * Copyright (c) 2017-2021 Nils Kohl.
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

/*
 * The entire file was generated with the HyTeG form generator.
 * 
 * Software:
 *
 * - quadpy version: 0.16.5
 *
 * Avoid modifying this file. If buggy, consider fixing the generator itself.
 */

#pragma once

#include "hyteg/geometry/GeometryMap.hpp"
#include "hyteg/forms/form_hyteg_base/P1FormHyTeG.hpp"
#include "hyteg/forms/form_hyteg_base/P2FormHyTeG.hpp"

namespace hyteg {

/// Implementation of the integration of a weak form over an element.
///
/// - name:        P1DiffusionBlending
/// - description: 
/// - trial space: Lagrange, degree: 1
/// - test space:  Lagrange, degree: 1
///
class P1DiffusionBlending : public P1FormHyTeG
{

 public:

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (3, 3)
   /// - quadrature rule:                        Hillion 7 | points: 4, degree: 3, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    abs    assignments    function_calls
   ///                                           ------  ------  ------  -----  -------------  ----------------
   ///                                              130     164       5      5            147                 4
   ///
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 3, 3 >& elMat ) const override
   {
      real_t p_affine_0_0 = coords[0][0];
      real_t p_affine_0_1 = coords[0][1];
      real_t p_affine_1_0 = coords[1][0];
      real_t p_affine_1_1 = coords[1][1];
      real_t p_affine_2_0 = coords[2][0];
      real_t p_affine_2_1 = coords[2][1];
      real_t Blending_DF_Triangle_0_0 = 0;
      real_t Blending_DF_Triangle_0_1 = 0;
      real_t Blending_DF_Triangle_0_2 = 0;
      real_t Blending_DF_Triangle_0_3 = 0;
      real_t Blending_DF_Triangle_1_0 = 0;
      real_t Blending_DF_Triangle_1_1 = 0;
      real_t Blending_DF_Triangle_1_2 = 0;
      real_t Blending_DF_Triangle_1_3 = 0;
      real_t Blending_DF_Triangle_2_0 = 0;
      real_t Blending_DF_Triangle_2_1 = 0;
      real_t Blending_DF_Triangle_2_2 = 0;
      real_t Blending_DF_Triangle_2_3 = 0;
      real_t Blending_DF_Triangle_3_0 = 0;
      real_t Blending_DF_Triangle_3_1 = 0;
      real_t Blending_DF_Triangle_3_2 = 0;
      real_t Blending_DF_Triangle_3_3 = 0;
      real_t q_p_0_0 = 0.17855872826361643;
      real_t q_p_0_1 = 0.1550510257216822;
      real_t q_p_1_0 = 0.075031110222608124;
      real_t q_p_1_1 = 0.64494897427831777;
      real_t q_p_2_0 = 0.66639024601470143;
      real_t q_p_2_1 = 0.1550510257216822;
      real_t q_p_3_0 = 0.28001991549907407;
      real_t q_p_3_1 = 0.64494897427831777;
      real_t w_p_0 = 0.15902069087198858;
      real_t w_p_1 = 0.090979309128011415;
      real_t w_p_2 = 0.15902069087198858;
      real_t w_p_3 = 0.090979309128011415;
      Blending_DF_Triangle( p_affine_0_0 + q_p_0_0*(-p_affine_0_0 + p_affine_1_0) + q_p_0_1*(-p_affine_0_0 + p_affine_2_0), p_affine_0_1 + q_p_0_0*(-p_affine_0_1 + p_affine_1_1) + q_p_0_1*(-p_affine_0_1 + p_affine_2_1), &Blending_DF_Triangle_0_0, &Blending_DF_Triangle_0_1, &Blending_DF_Triangle_0_2, &Blending_DF_Triangle_0_3 );
      Blending_DF_Triangle( p_affine_0_0 + q_p_1_0*(-p_affine_0_0 + p_affine_1_0) + q_p_1_1*(-p_affine_0_0 + p_affine_2_0), p_affine_0_1 + q_p_1_0*(-p_affine_0_1 + p_affine_1_1) + q_p_1_1*(-p_affine_0_1 + p_affine_2_1), &Blending_DF_Triangle_1_0, &Blending_DF_Triangle_1_1, &Blending_DF_Triangle_1_2, &Blending_DF_Triangle_1_3 );
      Blending_DF_Triangle( p_affine_0_0 + q_p_2_0*(-p_affine_0_0 + p_affine_1_0) + q_p_2_1*(-p_affine_0_0 + p_affine_2_0), p_affine_0_1 + q_p_2_0*(-p_affine_0_1 + p_affine_1_1) + q_p_2_1*(-p_affine_0_1 + p_affine_2_1), &Blending_DF_Triangle_2_0, &Blending_DF_Triangle_2_1, &Blending_DF_Triangle_2_2, &Blending_DF_Triangle_2_3 );
      Blending_DF_Triangle( p_affine_0_0 + q_p_3_0*(-p_affine_0_0 + p_affine_1_0) + q_p_3_1*(-p_affine_0_0 + p_affine_2_0), p_affine_0_1 + q_p_3_0*(-p_affine_0_1 + p_affine_1_1) + q_p_3_1*(-p_affine_0_1 + p_affine_2_1), &Blending_DF_Triangle_3_0, &Blending_DF_Triangle_3_1, &Blending_DF_Triangle_3_2, &Blending_DF_Triangle_3_3 );
      real_t tmp_0 = -p_affine_0_1;
      real_t tmp_1 = p_affine_2_1 + tmp_0;
      real_t tmp_2 = Blending_DF_Triangle_0_0*Blending_DF_Triangle_0_3 - Blending_DF_Triangle_0_1*Blending_DF_Triangle_0_2;
      real_t tmp_3 = -p_affine_0_0;
      real_t tmp_4 = p_affine_1_0 + tmp_3;
      real_t tmp_5 = 1.0 / (tmp_1*tmp_4 - (p_affine_1_1 + tmp_0)*(p_affine_2_0 + tmp_3));
      real_t tmp_6 = tmp_5/tmp_2;
      real_t tmp_7 = Blending_DF_Triangle_0_1*tmp_6;
      real_t tmp_8 = tmp_1*tmp_7;
      real_t tmp_9 = p_affine_0_1 - p_affine_1_1;
      real_t tmp_10 = tmp_7*tmp_9;
      real_t tmp_11 = Blending_DF_Triangle_0_0*tmp_6;
      real_t tmp_12 = tmp_11*tmp_4;
      real_t tmp_13 = p_affine_0_0 - p_affine_2_0;
      real_t tmp_14 = tmp_11*tmp_13;
      real_t tmp_15 = tmp_10 - tmp_12 - tmp_14 + tmp_8;
      real_t tmp_16 = Blending_DF_Triangle_0_2*tmp_6;
      real_t tmp_17 = tmp_16*tmp_4;
      real_t tmp_18 = tmp_13*tmp_16;
      real_t tmp_19 = Blending_DF_Triangle_0_3*tmp_6;
      real_t tmp_20 = tmp_1*tmp_19;
      real_t tmp_21 = tmp_19*tmp_9;
      real_t tmp_22 = tmp_17 + tmp_18 - tmp_20 - tmp_21;
      real_t tmp_23 = std::abs(p_affine_0_0*p_affine_1_1 - p_affine_0_0*p_affine_2_1 - p_affine_0_1*p_affine_1_0 + p_affine_0_1*p_affine_2_0 + p_affine_1_0*p_affine_2_1 - p_affine_1_1*p_affine_2_0);
      real_t tmp_24 = tmp_23*w_p_0*std::abs(tmp_2);
      real_t tmp_25 = Blending_DF_Triangle_1_0*Blending_DF_Triangle_1_3 - Blending_DF_Triangle_1_1*Blending_DF_Triangle_1_2;
      real_t tmp_26 = tmp_5/tmp_25;
      real_t tmp_27 = Blending_DF_Triangle_1_1*tmp_26;
      real_t tmp_28 = tmp_1*tmp_27;
      real_t tmp_29 = tmp_27*tmp_9;
      real_t tmp_30 = Blending_DF_Triangle_1_0*tmp_26;
      real_t tmp_31 = tmp_30*tmp_4;
      real_t tmp_32 = tmp_13*tmp_30;
      real_t tmp_33 = tmp_28 + tmp_29 - tmp_31 - tmp_32;
      real_t tmp_34 = Blending_DF_Triangle_1_2*tmp_26;
      real_t tmp_35 = tmp_34*tmp_4;
      real_t tmp_36 = tmp_13*tmp_34;
      real_t tmp_37 = Blending_DF_Triangle_1_3*tmp_26;
      real_t tmp_38 = tmp_1*tmp_37;
      real_t tmp_39 = tmp_37*tmp_9;
      real_t tmp_40 = tmp_35 + tmp_36 - tmp_38 - tmp_39;
      real_t tmp_41 = tmp_23*w_p_1*std::abs(tmp_25);
      real_t tmp_42 = Blending_DF_Triangle_2_0*Blending_DF_Triangle_2_3 - Blending_DF_Triangle_2_1*Blending_DF_Triangle_2_2;
      real_t tmp_43 = tmp_5/tmp_42;
      real_t tmp_44 = Blending_DF_Triangle_2_1*tmp_43;
      real_t tmp_45 = tmp_1*tmp_44;
      real_t tmp_46 = tmp_44*tmp_9;
      real_t tmp_47 = Blending_DF_Triangle_2_0*tmp_43;
      real_t tmp_48 = tmp_4*tmp_47;
      real_t tmp_49 = tmp_13*tmp_47;
      real_t tmp_50 = tmp_45 + tmp_46 - tmp_48 - tmp_49;
      real_t tmp_51 = Blending_DF_Triangle_2_2*tmp_43;
      real_t tmp_52 = tmp_4*tmp_51;
      real_t tmp_53 = tmp_13*tmp_51;
      real_t tmp_54 = Blending_DF_Triangle_2_3*tmp_43;
      real_t tmp_55 = tmp_1*tmp_54;
      real_t tmp_56 = tmp_54*tmp_9;
      real_t tmp_57 = tmp_52 + tmp_53 - tmp_55 - tmp_56;
      real_t tmp_58 = tmp_23*w_p_2*std::abs(tmp_42);
      real_t tmp_59 = Blending_DF_Triangle_3_0*Blending_DF_Triangle_3_3 - Blending_DF_Triangle_3_1*Blending_DF_Triangle_3_2;
      real_t tmp_60 = tmp_5/tmp_59;
      real_t tmp_61 = Blending_DF_Triangle_3_1*tmp_60;
      real_t tmp_62 = tmp_1*tmp_61;
      real_t tmp_63 = tmp_61*tmp_9;
      real_t tmp_64 = Blending_DF_Triangle_3_0*tmp_60;
      real_t tmp_65 = tmp_4*tmp_64;
      real_t tmp_66 = tmp_13*tmp_64;
      real_t tmp_67 = tmp_62 + tmp_63 - tmp_65 - tmp_66;
      real_t tmp_68 = Blending_DF_Triangle_3_2*tmp_60;
      real_t tmp_69 = tmp_4*tmp_68;
      real_t tmp_70 = tmp_13*tmp_68;
      real_t tmp_71 = Blending_DF_Triangle_3_3*tmp_60;
      real_t tmp_72 = tmp_1*tmp_71;
      real_t tmp_73 = tmp_71*tmp_9;
      real_t tmp_74 = tmp_69 + tmp_70 - tmp_72 - tmp_73;
      real_t tmp_75 = tmp_23*w_p_3*std::abs(tmp_59);
      real_t tmp_76 = tmp_14 - tmp_8;
      real_t tmp_77 = -tmp_18 + tmp_20;
      real_t tmp_78 = -tmp_28 + tmp_32;
      real_t tmp_79 = -tmp_36 + tmp_38;
      real_t tmp_80 = -tmp_45 + tmp_49;
      real_t tmp_81 = -tmp_53 + tmp_55;
      real_t tmp_82 = -tmp_62 + tmp_66;
      real_t tmp_83 = -tmp_70 + tmp_72;
      real_t tmp_84 = tmp_24*(tmp_15*tmp_76 + tmp_22*tmp_77) + tmp_41*(tmp_33*tmp_78 + tmp_40*tmp_79) + tmp_58*(tmp_50*tmp_80 + tmp_57*tmp_81) + tmp_75*(tmp_67*tmp_82 + tmp_74*tmp_83);
      real_t tmp_85 = -tmp_10 + tmp_12;
      real_t tmp_86 = -tmp_17 + tmp_21;
      real_t tmp_87 = -tmp_29 + tmp_31;
      real_t tmp_88 = -tmp_35 + tmp_39;
      real_t tmp_89 = -tmp_46 + tmp_48;
      real_t tmp_90 = -tmp_52 + tmp_56;
      real_t tmp_91 = -tmp_63 + tmp_65;
      real_t tmp_92 = -tmp_69 + tmp_73;
      real_t tmp_93 = tmp_24*(tmp_15*tmp_85 + tmp_22*tmp_86) + tmp_41*(tmp_33*tmp_87 + tmp_40*tmp_88) + tmp_58*(tmp_50*tmp_89 + tmp_57*tmp_90) + tmp_75*(tmp_67*tmp_91 + tmp_74*tmp_92);
      real_t tmp_94 = tmp_24*(tmp_76*tmp_85 + tmp_77*tmp_86) + tmp_41*(tmp_78*tmp_87 + tmp_79*tmp_88) + tmp_58*(tmp_80*tmp_89 + tmp_81*tmp_90) + tmp_75*(tmp_82*tmp_91 + tmp_83*tmp_92);
      real_t a_0_0 = tmp_24*((tmp_15*tmp_15) + (tmp_22*tmp_22)) + tmp_41*((tmp_33*tmp_33) + (tmp_40*tmp_40)) + tmp_58*((tmp_50*tmp_50) + (tmp_57*tmp_57)) + tmp_75*((tmp_67*tmp_67) + (tmp_74*tmp_74));
      real_t a_0_1 = tmp_84;
      real_t a_0_2 = tmp_93;
      real_t a_1_0 = tmp_84;
      real_t a_1_1 = tmp_24*((tmp_76*tmp_76) + (tmp_77*tmp_77)) + tmp_41*((tmp_78*tmp_78) + (tmp_79*tmp_79)) + tmp_58*((tmp_80*tmp_80) + (tmp_81*tmp_81)) + tmp_75*((tmp_82*tmp_82) + (tmp_83*tmp_83));
      real_t a_1_2 = tmp_94;
      real_t a_2_0 = tmp_93;
      real_t a_2_1 = tmp_94;
      real_t a_2_2 = tmp_24*((tmp_85*tmp_85) + (tmp_86*tmp_86)) + tmp_41*((tmp_87*tmp_87) + (tmp_88*tmp_88)) + tmp_58*((tmp_89*tmp_89) + (tmp_90*tmp_90)) + tmp_75*((tmp_91*tmp_91) + (tmp_92*tmp_92));
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
      (elMat(1, 0)) = a_1_0;
      (elMat(1, 1)) = a_1_1;
      (elMat(1, 2)) = a_1_2;
      (elMat(2, 0)) = a_2_0;
      (elMat(2, 1)) = a_2_1;
      (elMat(2, 2)) = a_2_2;
   }

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (4, 4)
   /// - quadrature rule:                        Xiao-Gimbutas 3 | points: 6, degree: 3, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    abs    assignments    function_calls
   ///                                           ------  ------  ------  -----  -------------  ----------------
   ///                                              660     732       7      7            511                 6
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 4, 4 >& elMat ) const override
   {
      real_t p_affine_0_0 = coords[0][0];
      real_t p_affine_0_1 = coords[0][1];
      real_t p_affine_0_2 = coords[0][2];
      real_t p_affine_1_0 = coords[1][0];
      real_t p_affine_1_1 = coords[1][1];
      real_t p_affine_1_2 = coords[1][2];
      real_t p_affine_2_0 = coords[2][0];
      real_t p_affine_2_1 = coords[2][1];
      real_t p_affine_2_2 = coords[2][2];
      real_t p_affine_3_0 = coords[3][0];
      real_t p_affine_3_1 = coords[3][1];
      real_t p_affine_3_2 = coords[3][2];
      real_t Blending_DF_Tetrahedron_0_0 = 0;
      real_t Blending_DF_Tetrahedron_0_1 = 0;
      real_t Blending_DF_Tetrahedron_0_2 = 0;
      real_t Blending_DF_Tetrahedron_0_3 = 0;
      real_t Blending_DF_Tetrahedron_0_4 = 0;
      real_t Blending_DF_Tetrahedron_0_5 = 0;
      real_t Blending_DF_Tetrahedron_0_6 = 0;
      real_t Blending_DF_Tetrahedron_0_7 = 0;
      real_t Blending_DF_Tetrahedron_0_8 = 0;
      real_t Blending_DF_Tetrahedron_1_0 = 0;
      real_t Blending_DF_Tetrahedron_1_1 = 0;
      real_t Blending_DF_Tetrahedron_1_2 = 0;
      real_t Blending_DF_Tetrahedron_1_3 = 0;
      real_t Blending_DF_Tetrahedron_1_4 = 0;
      real_t Blending_DF_Tetrahedron_1_5 = 0;
      real_t Blending_DF_Tetrahedron_1_6 = 0;
      real_t Blending_DF_Tetrahedron_1_7 = 0;
      real_t Blending_DF_Tetrahedron_1_8 = 0;
      real_t Blending_DF_Tetrahedron_2_0 = 0;
      real_t Blending_DF_Tetrahedron_2_1 = 0;
      real_t Blending_DF_Tetrahedron_2_2 = 0;
      real_t Blending_DF_Tetrahedron_2_3 = 0;
      real_t Blending_DF_Tetrahedron_2_4 = 0;
      real_t Blending_DF_Tetrahedron_2_5 = 0;
      real_t Blending_DF_Tetrahedron_2_6 = 0;
      real_t Blending_DF_Tetrahedron_2_7 = 0;
      real_t Blending_DF_Tetrahedron_2_8 = 0;
      real_t Blending_DF_Tetrahedron_3_0 = 0;
      real_t Blending_DF_Tetrahedron_3_1 = 0;
      real_t Blending_DF_Tetrahedron_3_2 = 0;
      real_t Blending_DF_Tetrahedron_3_3 = 0;
      real_t Blending_DF_Tetrahedron_3_4 = 0;
      real_t Blending_DF_Tetrahedron_3_5 = 0;
      real_t Blending_DF_Tetrahedron_3_6 = 0;
      real_t Blending_DF_Tetrahedron_3_7 = 0;
      real_t Blending_DF_Tetrahedron_3_8 = 0;
      real_t Blending_DF_Tetrahedron_4_0 = 0;
      real_t Blending_DF_Tetrahedron_4_1 = 0;
      real_t Blending_DF_Tetrahedron_4_2 = 0;
      real_t Blending_DF_Tetrahedron_4_3 = 0;
      real_t Blending_DF_Tetrahedron_4_4 = 0;
      real_t Blending_DF_Tetrahedron_4_5 = 0;
      real_t Blending_DF_Tetrahedron_4_6 = 0;
      real_t Blending_DF_Tetrahedron_4_7 = 0;
      real_t Blending_DF_Tetrahedron_4_8 = 0;
      real_t Blending_DF_Tetrahedron_5_0 = 0;
      real_t Blending_DF_Tetrahedron_5_1 = 0;
      real_t Blending_DF_Tetrahedron_5_2 = 0;
      real_t Blending_DF_Tetrahedron_5_3 = 0;
      real_t Blending_DF_Tetrahedron_5_4 = 0;
      real_t Blending_DF_Tetrahedron_5_5 = 0;
      real_t Blending_DF_Tetrahedron_5_6 = 0;
      real_t Blending_DF_Tetrahedron_5_7 = 0;
      real_t Blending_DF_Tetrahedron_5_8 = 0;
      real_t q_p_0_0 = 0.16200149169852451;
      real_t q_p_0_1 = 0.18385035049209769;
      real_t q_p_0_2 = 0.012718366313681451;
      real_t q_p_1_0 = 0.010905212211189241;
      real_t q_p_1_1 = 0.28152380212354622;
      real_t q_p_1_2 = 0.3621268299455338;
      real_t q_p_2_0 = 0.19011700243928389;
      real_t q_p_2_1 = 0.011403329444557171;
      real_t q_p_2_2 = 0.35862072046688392;
      real_t q_p_3_0 = 0.170816925164989;
      real_t q_p_3_1 = 0.15281814309092731;
      real_t q_p_3_2 = 0.63849329996172666;
      real_t q_p_4_0 = 0.15868516322744061;
      real_t q_p_4_1 = 0.58566280565521578;
      real_t q_p_4_2 = 0.1308471689520965;
      real_t q_p_5_0 = 0.57122605214911515;
      real_t q_p_5_1 = 0.14691839008716959;
      real_t q_p_5_2 = 0.14037280579421069;
      real_t w_p_0 = 0.020387000459557512;
      real_t w_p_1 = 0.021344402118457811;
      real_t w_p_2 = 0.022094671190740864;
      real_t w_p_3 = 0.023437401610067198;
      real_t w_p_4 = 0.037402527819592891;
      real_t w_p_5 = 0.042000663468250377;
      Blending_DF_Tetrahedron( p_affine_0_0 + q_p_0_0*(-p_affine_0_0 + p_affine_1_0) + q_p_0_1*(-p_affine_0_0 + p_affine_2_0) + q_p_0_2*(-p_affine_0_0 + p_affine_3_0), p_affine_0_1 + q_p_0_0*(-p_affine_0_1 + p_affine_1_1) + q_p_0_1*(-p_affine_0_1 + p_affine_2_1) + q_p_0_2*(-p_affine_0_1 + p_affine_3_1), p_affine_0_2 + q_p_0_0*(-p_affine_0_2 + p_affine_1_2) + q_p_0_1*(-p_affine_0_2 + p_affine_2_2) + q_p_0_2*(-p_affine_0_2 + p_affine_3_2), &Blending_DF_Tetrahedron_0_0, &Blending_DF_Tetrahedron_0_1, &Blending_DF_Tetrahedron_0_2, &Blending_DF_Tetrahedron_0_3, &Blending_DF_Tetrahedron_0_4, &Blending_DF_Tetrahedron_0_5, &Blending_DF_Tetrahedron_0_6, &Blending_DF_Tetrahedron_0_7, &Blending_DF_Tetrahedron_0_8 );
      Blending_DF_Tetrahedron( p_affine_0_0 + q_p_1_0*(-p_affine_0_0 + p_affine_1_0) + q_p_1_1*(-p_affine_0_0 + p_affine_2_0) + q_p_1_2*(-p_affine_0_0 + p_affine_3_0), p_affine_0_1 + q_p_1_0*(-p_affine_0_1 + p_affine_1_1) + q_p_1_1*(-p_affine_0_1 + p_affine_2_1) + q_p_1_2*(-p_affine_0_1 + p_affine_3_1), p_affine_0_2 + q_p_1_0*(-p_affine_0_2 + p_affine_1_2) + q_p_1_1*(-p_affine_0_2 + p_affine_2_2) + q_p_1_2*(-p_affine_0_2 + p_affine_3_2), &Blending_DF_Tetrahedron_1_0, &Blending_DF_Tetrahedron_1_1, &Blending_DF_Tetrahedron_1_2, &Blending_DF_Tetrahedron_1_3, &Blending_DF_Tetrahedron_1_4, &Blending_DF_Tetrahedron_1_5, &Blending_DF_Tetrahedron_1_6, &Blending_DF_Tetrahedron_1_7, &Blending_DF_Tetrahedron_1_8 );
      Blending_DF_Tetrahedron( p_affine_0_0 + q_p_2_0*(-p_affine_0_0 + p_affine_1_0) + q_p_2_1*(-p_affine_0_0 + p_affine_2_0) + q_p_2_2*(-p_affine_0_0 + p_affine_3_0), p_affine_0_1 + q_p_2_0*(-p_affine_0_1 + p_affine_1_1) + q_p_2_1*(-p_affine_0_1 + p_affine_2_1) + q_p_2_2*(-p_affine_0_1 + p_affine_3_1), p_affine_0_2 + q_p_2_0*(-p_affine_0_2 + p_affine_1_2) + q_p_2_1*(-p_affine_0_2 + p_affine_2_2) + q_p_2_2*(-p_affine_0_2 + p_affine_3_2), &Blending_DF_Tetrahedron_2_0, &Blending_DF_Tetrahedron_2_1, &Blending_DF_Tetrahedron_2_2, &Blending_DF_Tetrahedron_2_3, &Blending_DF_Tetrahedron_2_4, &Blending_DF_Tetrahedron_2_5, &Blending_DF_Tetrahedron_2_6, &Blending_DF_Tetrahedron_2_7, &Blending_DF_Tetrahedron_2_8 );
      Blending_DF_Tetrahedron( p_affine_0_0 + q_p_3_0*(-p_affine_0_0 + p_affine_1_0) + q_p_3_1*(-p_affine_0_0 + p_affine_2_0) + q_p_3_2*(-p_affine_0_0 + p_affine_3_0), p_affine_0_1 + q_p_3_0*(-p_affine_0_1 + p_affine_1_1) + q_p_3_1*(-p_affine_0_1 + p_affine_2_1) + q_p_3_2*(-p_affine_0_1 + p_affine_3_1), p_affine_0_2 + q_p_3_0*(-p_affine_0_2 + p_affine_1_2) + q_p_3_1*(-p_affine_0_2 + p_affine_2_2) + q_p_3_2*(-p_affine_0_2 + p_affine_3_2), &Blending_DF_Tetrahedron_3_0, &Blending_DF_Tetrahedron_3_1, &Blending_DF_Tetrahedron_3_2, &Blending_DF_Tetrahedron_3_3, &Blending_DF_Tetrahedron_3_4, &Blending_DF_Tetrahedron_3_5, &Blending_DF_Tetrahedron_3_6, &Blending_DF_Tetrahedron_3_7, &Blending_DF_Tetrahedron_3_8 );
      Blending_DF_Tetrahedron( p_affine_0_0 + q_p_4_0*(-p_affine_0_0 + p_affine_1_0) + q_p_4_1*(-p_affine_0_0 + p_affine_2_0) + q_p_4_2*(-p_affine_0_0 + p_affine_3_0), p_affine_0_1 + q_p_4_0*(-p_affine_0_1 + p_affine_1_1) + q_p_4_1*(-p_affine_0_1 + p_affine_2_1) + q_p_4_2*(-p_affine_0_1 + p_affine_3_1), p_affine_0_2 + q_p_4_0*(-p_affine_0_2 + p_affine_1_2) + q_p_4_1*(-p_affine_0_2 + p_affine_2_2) + q_p_4_2*(-p_affine_0_2 + p_affine_3_2), &Blending_DF_Tetrahedron_4_0, &Blending_DF_Tetrahedron_4_1, &Blending_DF_Tetrahedron_4_2, &Blending_DF_Tetrahedron_4_3, &Blending_DF_Tetrahedron_4_4, &Blending_DF_Tetrahedron_4_5, &Blending_DF_Tetrahedron_4_6, &Blending_DF_Tetrahedron_4_7, &Blending_DF_Tetrahedron_4_8 );
      Blending_DF_Tetrahedron( p_affine_0_0 + q_p_5_0*(-p_affine_0_0 + p_affine_1_0) + q_p_5_1*(-p_affine_0_0 + p_affine_2_0) + q_p_5_2*(-p_affine_0_0 + p_affine_3_0), p_affine_0_1 + q_p_5_0*(-p_affine_0_1 + p_affine_1_1) + q_p_5_1*(-p_affine_0_1 + p_affine_2_1) + q_p_5_2*(-p_affine_0_1 + p_affine_3_1), p_affine_0_2 + q_p_5_0*(-p_affine_0_2 + p_affine_1_2) + q_p_5_1*(-p_affine_0_2 + p_affine_2_2) + q_p_5_2*(-p_affine_0_2 + p_affine_3_2), &Blending_DF_Tetrahedron_5_0, &Blending_DF_Tetrahedron_5_1, &Blending_DF_Tetrahedron_5_2, &Blending_DF_Tetrahedron_5_3, &Blending_DF_Tetrahedron_5_4, &Blending_DF_Tetrahedron_5_5, &Blending_DF_Tetrahedron_5_6, &Blending_DF_Tetrahedron_5_7, &Blending_DF_Tetrahedron_5_8 );
      real_t tmp_0 = -p_affine_0_0;
      real_t tmp_1 = p_affine_1_0 + tmp_0;
      real_t tmp_2 = -p_affine_0_1;
      real_t tmp_3 = p_affine_2_1 + tmp_2;
      real_t tmp_4 = tmp_1*tmp_3;
      real_t tmp_5 = p_affine_2_0 + tmp_0;
      real_t tmp_6 = p_affine_1_1 + tmp_2;
      real_t tmp_7 = tmp_5*tmp_6;
      real_t tmp_8 = tmp_4 - tmp_7;
      real_t tmp_9 = Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_4;
      real_t tmp_10 = Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_3;
      real_t tmp_11 = Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_5;
      real_t tmp_12 = Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_3;
      real_t tmp_13 = Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_5;
      real_t tmp_14 = Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_4;
      real_t tmp_15 = Blending_DF_Tetrahedron_0_6*tmp_11 - Blending_DF_Tetrahedron_0_6*tmp_14 + Blending_DF_Tetrahedron_0_7*tmp_12 - Blending_DF_Tetrahedron_0_7*tmp_13 - Blending_DF_Tetrahedron_0_8*tmp_10 + Blending_DF_Tetrahedron_0_8*tmp_9;
      real_t tmp_16 = -p_affine_0_2;
      real_t tmp_17 = p_affine_3_2 + tmp_16;
      real_t tmp_18 = p_affine_1_2 + tmp_16;
      real_t tmp_19 = p_affine_3_1 + tmp_2;
      real_t tmp_20 = tmp_19*tmp_5;
      real_t tmp_21 = p_affine_2_2 + tmp_16;
      real_t tmp_22 = p_affine_3_0 + tmp_0;
      real_t tmp_23 = tmp_22*tmp_6;
      real_t tmp_24 = tmp_1*tmp_19;
      real_t tmp_25 = tmp_22*tmp_3;
      real_t tmp_26 = 1.0 / (tmp_17*tmp_4 - tmp_17*tmp_7 + tmp_18*tmp_20 - tmp_18*tmp_25 + tmp_21*tmp_23 - tmp_21*tmp_24);
      real_t tmp_27 = tmp_26/tmp_15;
      real_t tmp_28 = tmp_27*(-tmp_10 + tmp_9);
      real_t tmp_29 = tmp_28*tmp_8;
      real_t tmp_30 = tmp_23 - tmp_24;
      real_t tmp_31 = tmp_28*tmp_30;
      real_t tmp_32 = tmp_20 - tmp_25;
      real_t tmp_33 = tmp_28*tmp_32;
      real_t tmp_34 = -tmp_1*tmp_21 + tmp_18*tmp_5;
      real_t tmp_35 = tmp_27*(tmp_12 - tmp_13);
      real_t tmp_36 = tmp_34*tmp_35;
      real_t tmp_37 = tmp_1*tmp_17 - tmp_18*tmp_22;
      real_t tmp_38 = tmp_35*tmp_37;
      real_t tmp_39 = -tmp_17*tmp_5 + tmp_21*tmp_22;
      real_t tmp_40 = tmp_35*tmp_39;
      real_t tmp_41 = -tmp_18*tmp_3 + tmp_21*tmp_6;
      real_t tmp_42 = tmp_27*(tmp_11 - tmp_14);
      real_t tmp_43 = tmp_41*tmp_42;
      real_t tmp_44 = -tmp_17*tmp_6 + tmp_18*tmp_19;
      real_t tmp_45 = tmp_42*tmp_44;
      real_t tmp_46 = tmp_17*tmp_3 - tmp_19*tmp_21;
      real_t tmp_47 = tmp_42*tmp_46;
      real_t tmp_48 = -tmp_29 - tmp_31 - tmp_33 - tmp_36 - tmp_38 - tmp_40 - tmp_43 - tmp_45 - tmp_47;
      real_t tmp_49 = tmp_27*(-Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_7 + Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_6);
      real_t tmp_50 = tmp_49*tmp_8;
      real_t tmp_51 = tmp_30*tmp_49;
      real_t tmp_52 = tmp_32*tmp_49;
      real_t tmp_53 = tmp_27*(Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_8 - Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_6);
      real_t tmp_54 = tmp_34*tmp_53;
      real_t tmp_55 = tmp_37*tmp_53;
      real_t tmp_56 = tmp_39*tmp_53;
      real_t tmp_57 = tmp_27*(-Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_8 + Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_7);
      real_t tmp_58 = tmp_41*tmp_57;
      real_t tmp_59 = tmp_44*tmp_57;
      real_t tmp_60 = tmp_46*tmp_57;
      real_t tmp_61 = -tmp_50 - tmp_51 - tmp_52 - tmp_54 - tmp_55 - tmp_56 - tmp_58 - tmp_59 - tmp_60;
      real_t tmp_62 = tmp_27*(Blending_DF_Tetrahedron_0_3*Blending_DF_Tetrahedron_0_7 - Blending_DF_Tetrahedron_0_4*Blending_DF_Tetrahedron_0_6);
      real_t tmp_63 = tmp_62*tmp_8;
      real_t tmp_64 = tmp_30*tmp_62;
      real_t tmp_65 = tmp_32*tmp_62;
      real_t tmp_66 = tmp_27*(-Blending_DF_Tetrahedron_0_3*Blending_DF_Tetrahedron_0_8 + Blending_DF_Tetrahedron_0_5*Blending_DF_Tetrahedron_0_6);
      real_t tmp_67 = tmp_34*tmp_66;
      real_t tmp_68 = tmp_37*tmp_66;
      real_t tmp_69 = tmp_39*tmp_66;
      real_t tmp_70 = tmp_27*(Blending_DF_Tetrahedron_0_4*Blending_DF_Tetrahedron_0_8 - Blending_DF_Tetrahedron_0_5*Blending_DF_Tetrahedron_0_7);
      real_t tmp_71 = tmp_41*tmp_70;
      real_t tmp_72 = tmp_44*tmp_70;
      real_t tmp_73 = tmp_46*tmp_70;
      real_t tmp_74 = -tmp_63 - tmp_64 - tmp_65 - tmp_67 - tmp_68 - tmp_69 - tmp_71 - tmp_72 - tmp_73;
      real_t tmp_75 = p_affine_0_0*p_affine_1_1;
      real_t tmp_76 = p_affine_0_0*p_affine_1_2;
      real_t tmp_77 = p_affine_2_1*p_affine_3_2;
      real_t tmp_78 = p_affine_0_1*p_affine_1_0;
      real_t tmp_79 = p_affine_0_1*p_affine_1_2;
      real_t tmp_80 = p_affine_2_2*p_affine_3_0;
      real_t tmp_81 = p_affine_0_2*p_affine_1_0;
      real_t tmp_82 = p_affine_0_2*p_affine_1_1;
      real_t tmp_83 = p_affine_2_0*p_affine_3_1;
      real_t tmp_84 = p_affine_2_2*p_affine_3_1;
      real_t tmp_85 = p_affine_2_0*p_affine_3_2;
      real_t tmp_86 = p_affine_2_1*p_affine_3_0;
      real_t tmp_87 = std::abs(p_affine_0_0*tmp_77 - p_affine_0_0*tmp_84 + p_affine_0_1*tmp_80 - p_affine_0_1*tmp_85 + p_affine_0_2*tmp_83 - p_affine_0_2*tmp_86 - p_affine_1_0*tmp_77 + p_affine_1_0*tmp_84 - p_affine_1_1*tmp_80 + p_affine_1_1*tmp_85 - p_affine_1_2*tmp_83 + p_affine_1_2*tmp_86 + p_affine_2_0*tmp_79 - p_affine_2_0*tmp_82 - p_affine_2_1*tmp_76 + p_affine_2_1*tmp_81 + p_affine_2_2*tmp_75 - p_affine_2_2*tmp_78 - p_affine_3_0*tmp_79 + p_affine_3_0*tmp_82 + p_affine_3_1*tmp_76 - p_affine_3_1*tmp_81 - p_affine_3_2*tmp_75 + p_affine_3_2*tmp_78);
      real_t tmp_88 = tmp_87*w_p_0*std::abs(tmp_15);
      real_t tmp_89 = Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_4;
      real_t tmp_90 = Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_3;
      real_t tmp_91 = Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_5;
      real_t tmp_92 = Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_3;
      real_t tmp_93 = Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_5;
      real_t tmp_94 = Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_4;
      real_t tmp_95 = Blending_DF_Tetrahedron_1_6*tmp_91 - Blending_DF_Tetrahedron_1_6*tmp_94 + Blending_DF_Tetrahedron_1_7*tmp_92 - Blending_DF_Tetrahedron_1_7*tmp_93 + Blending_DF_Tetrahedron_1_8*tmp_89 - Blending_DF_Tetrahedron_1_8*tmp_90;
      real_t tmp_96 = tmp_26/tmp_95;
      real_t tmp_97 = tmp_96*(tmp_89 - tmp_90);
      real_t tmp_98 = tmp_8*tmp_97;
      real_t tmp_99 = tmp_30*tmp_97;
      real_t tmp_100 = tmp_32*tmp_97;
      real_t tmp_101 = tmp_96*(tmp_92 - tmp_93);
      real_t tmp_102 = tmp_101*tmp_34;
      real_t tmp_103 = tmp_101*tmp_37;
      real_t tmp_104 = tmp_101*tmp_39;
      real_t tmp_105 = tmp_96*(tmp_91 - tmp_94);
      real_t tmp_106 = tmp_105*tmp_41;
      real_t tmp_107 = tmp_105*tmp_44;
      real_t tmp_108 = tmp_105*tmp_46;
      real_t tmp_109 = -tmp_100 - tmp_102 - tmp_103 - tmp_104 - tmp_106 - tmp_107 - tmp_108 - tmp_98 - tmp_99;
      real_t tmp_110 = tmp_96*(-Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_7 + Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_6);
      real_t tmp_111 = tmp_110*tmp_8;
      real_t tmp_112 = tmp_110*tmp_30;
      real_t tmp_113 = tmp_110*tmp_32;
      real_t tmp_114 = tmp_96*(Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_8 - Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_6);
      real_t tmp_115 = tmp_114*tmp_34;
      real_t tmp_116 = tmp_114*tmp_37;
      real_t tmp_117 = tmp_114*tmp_39;
      real_t tmp_118 = tmp_96*(-Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_8 + Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_7);
      real_t tmp_119 = tmp_118*tmp_41;
      real_t tmp_120 = tmp_118*tmp_44;
      real_t tmp_121 = tmp_118*tmp_46;
      real_t tmp_122 = -tmp_111 - tmp_112 - tmp_113 - tmp_115 - tmp_116 - tmp_117 - tmp_119 - tmp_120 - tmp_121;
      real_t tmp_123 = tmp_96*(Blending_DF_Tetrahedron_1_3*Blending_DF_Tetrahedron_1_7 - Blending_DF_Tetrahedron_1_4*Blending_DF_Tetrahedron_1_6);
      real_t tmp_124 = tmp_123*tmp_8;
      real_t tmp_125 = tmp_123*tmp_30;
      real_t tmp_126 = tmp_123*tmp_32;
      real_t tmp_127 = tmp_96*(-Blending_DF_Tetrahedron_1_3*Blending_DF_Tetrahedron_1_8 + Blending_DF_Tetrahedron_1_5*Blending_DF_Tetrahedron_1_6);
      real_t tmp_128 = tmp_127*tmp_34;
      real_t tmp_129 = tmp_127*tmp_37;
      real_t tmp_130 = tmp_127*tmp_39;
      real_t tmp_131 = tmp_96*(Blending_DF_Tetrahedron_1_4*Blending_DF_Tetrahedron_1_8 - Blending_DF_Tetrahedron_1_5*Blending_DF_Tetrahedron_1_7);
      real_t tmp_132 = tmp_131*tmp_41;
      real_t tmp_133 = tmp_131*tmp_44;
      real_t tmp_134 = tmp_131*tmp_46;
      real_t tmp_135 = -tmp_124 - tmp_125 - tmp_126 - tmp_128 - tmp_129 - tmp_130 - tmp_132 - tmp_133 - tmp_134;
      real_t tmp_136 = tmp_87*w_p_1*std::abs(tmp_95);
      real_t tmp_137 = Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_4;
      real_t tmp_138 = Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_3;
      real_t tmp_139 = Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_5;
      real_t tmp_140 = Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_3;
      real_t tmp_141 = Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_5;
      real_t tmp_142 = Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_4;
      real_t tmp_143 = Blending_DF_Tetrahedron_2_6*tmp_139 - Blending_DF_Tetrahedron_2_6*tmp_142 + Blending_DF_Tetrahedron_2_7*tmp_140 - Blending_DF_Tetrahedron_2_7*tmp_141 + Blending_DF_Tetrahedron_2_8*tmp_137 - Blending_DF_Tetrahedron_2_8*tmp_138;
      real_t tmp_144 = tmp_26/tmp_143;
      real_t tmp_145 = tmp_144*(tmp_137 - tmp_138);
      real_t tmp_146 = tmp_145*tmp_8;
      real_t tmp_147 = tmp_145*tmp_30;
      real_t tmp_148 = tmp_145*tmp_32;
      real_t tmp_149 = tmp_144*(tmp_140 - tmp_141);
      real_t tmp_150 = tmp_149*tmp_34;
      real_t tmp_151 = tmp_149*tmp_37;
      real_t tmp_152 = tmp_149*tmp_39;
      real_t tmp_153 = tmp_144*(tmp_139 - tmp_142);
      real_t tmp_154 = tmp_153*tmp_41;
      real_t tmp_155 = tmp_153*tmp_44;
      real_t tmp_156 = tmp_153*tmp_46;
      real_t tmp_157 = -tmp_146 - tmp_147 - tmp_148 - tmp_150 - tmp_151 - tmp_152 - tmp_154 - tmp_155 - tmp_156;
      real_t tmp_158 = tmp_144*(-Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_7 + Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_6);
      real_t tmp_159 = tmp_158*tmp_8;
      real_t tmp_160 = tmp_158*tmp_30;
      real_t tmp_161 = tmp_158*tmp_32;
      real_t tmp_162 = tmp_144*(Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_8 - Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_6);
      real_t tmp_163 = tmp_162*tmp_34;
      real_t tmp_164 = tmp_162*tmp_37;
      real_t tmp_165 = tmp_162*tmp_39;
      real_t tmp_166 = tmp_144*(-Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_8 + Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_7);
      real_t tmp_167 = tmp_166*tmp_41;
      real_t tmp_168 = tmp_166*tmp_44;
      real_t tmp_169 = tmp_166*tmp_46;
      real_t tmp_170 = -tmp_159 - tmp_160 - tmp_161 - tmp_163 - tmp_164 - tmp_165 - tmp_167 - tmp_168 - tmp_169;
      real_t tmp_171 = tmp_144*(Blending_DF_Tetrahedron_2_3*Blending_DF_Tetrahedron_2_7 - Blending_DF_Tetrahedron_2_4*Blending_DF_Tetrahedron_2_6);
      real_t tmp_172 = tmp_171*tmp_8;
      real_t tmp_173 = tmp_171*tmp_30;
      real_t tmp_174 = tmp_171*tmp_32;
      real_t tmp_175 = tmp_144*(-Blending_DF_Tetrahedron_2_3*Blending_DF_Tetrahedron_2_8 + Blending_DF_Tetrahedron_2_5*Blending_DF_Tetrahedron_2_6);
      real_t tmp_176 = tmp_175*tmp_34;
      real_t tmp_177 = tmp_175*tmp_37;
      real_t tmp_178 = tmp_175*tmp_39;
      real_t tmp_179 = tmp_144*(Blending_DF_Tetrahedron_2_4*Blending_DF_Tetrahedron_2_8 - Blending_DF_Tetrahedron_2_5*Blending_DF_Tetrahedron_2_7);
      real_t tmp_180 = tmp_179*tmp_41;
      real_t tmp_181 = tmp_179*tmp_44;
      real_t tmp_182 = tmp_179*tmp_46;
      real_t tmp_183 = -tmp_172 - tmp_173 - tmp_174 - tmp_176 - tmp_177 - tmp_178 - tmp_180 - tmp_181 - tmp_182;
      real_t tmp_184 = tmp_87*w_p_2*std::abs(tmp_143);
      real_t tmp_185 = Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_4;
      real_t tmp_186 = Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_3;
      real_t tmp_187 = Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_5;
      real_t tmp_188 = Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_3;
      real_t tmp_189 = Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_5;
      real_t tmp_190 = Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_4;
      real_t tmp_191 = Blending_DF_Tetrahedron_3_6*tmp_187 - Blending_DF_Tetrahedron_3_6*tmp_190 + Blending_DF_Tetrahedron_3_7*tmp_188 - Blending_DF_Tetrahedron_3_7*tmp_189 + Blending_DF_Tetrahedron_3_8*tmp_185 - Blending_DF_Tetrahedron_3_8*tmp_186;
      real_t tmp_192 = tmp_26/tmp_191;
      real_t tmp_193 = tmp_192*(tmp_185 - tmp_186);
      real_t tmp_194 = tmp_193*tmp_8;
      real_t tmp_195 = tmp_193*tmp_30;
      real_t tmp_196 = tmp_193*tmp_32;
      real_t tmp_197 = tmp_192*(tmp_188 - tmp_189);
      real_t tmp_198 = tmp_197*tmp_34;
      real_t tmp_199 = tmp_197*tmp_37;
      real_t tmp_200 = tmp_197*tmp_39;
      real_t tmp_201 = tmp_192*(tmp_187 - tmp_190);
      real_t tmp_202 = tmp_201*tmp_41;
      real_t tmp_203 = tmp_201*tmp_44;
      real_t tmp_204 = tmp_201*tmp_46;
      real_t tmp_205 = -tmp_194 - tmp_195 - tmp_196 - tmp_198 - tmp_199 - tmp_200 - tmp_202 - tmp_203 - tmp_204;
      real_t tmp_206 = tmp_192*(-Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_7 + Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_6);
      real_t tmp_207 = tmp_206*tmp_8;
      real_t tmp_208 = tmp_206*tmp_30;
      real_t tmp_209 = tmp_206*tmp_32;
      real_t tmp_210 = tmp_192*(Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_8 - Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_6);
      real_t tmp_211 = tmp_210*tmp_34;
      real_t tmp_212 = tmp_210*tmp_37;
      real_t tmp_213 = tmp_210*tmp_39;
      real_t tmp_214 = tmp_192*(-Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_8 + Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_7);
      real_t tmp_215 = tmp_214*tmp_41;
      real_t tmp_216 = tmp_214*tmp_44;
      real_t tmp_217 = tmp_214*tmp_46;
      real_t tmp_218 = -tmp_207 - tmp_208 - tmp_209 - tmp_211 - tmp_212 - tmp_213 - tmp_215 - tmp_216 - tmp_217;
      real_t tmp_219 = tmp_192*(Blending_DF_Tetrahedron_3_3*Blending_DF_Tetrahedron_3_7 - Blending_DF_Tetrahedron_3_4*Blending_DF_Tetrahedron_3_6);
      real_t tmp_220 = tmp_219*tmp_8;
      real_t tmp_221 = tmp_219*tmp_30;
      real_t tmp_222 = tmp_219*tmp_32;
      real_t tmp_223 = tmp_192*(-Blending_DF_Tetrahedron_3_3*Blending_DF_Tetrahedron_3_8 + Blending_DF_Tetrahedron_3_5*Blending_DF_Tetrahedron_3_6);
      real_t tmp_224 = tmp_223*tmp_34;
      real_t tmp_225 = tmp_223*tmp_37;
      real_t tmp_226 = tmp_223*tmp_39;
      real_t tmp_227 = tmp_192*(Blending_DF_Tetrahedron_3_4*Blending_DF_Tetrahedron_3_8 - Blending_DF_Tetrahedron_3_5*Blending_DF_Tetrahedron_3_7);
      real_t tmp_228 = tmp_227*tmp_41;
      real_t tmp_229 = tmp_227*tmp_44;
      real_t tmp_230 = tmp_227*tmp_46;
      real_t tmp_231 = -tmp_220 - tmp_221 - tmp_222 - tmp_224 - tmp_225 - tmp_226 - tmp_228 - tmp_229 - tmp_230;
      real_t tmp_232 = tmp_87*w_p_3*std::abs(tmp_191);
      real_t tmp_233 = Blending_DF_Tetrahedron_4_0*Blending_DF_Tetrahedron_4_4;
      real_t tmp_234 = Blending_DF_Tetrahedron_4_1*Blending_DF_Tetrahedron_4_3;
      real_t tmp_235 = Blending_DF_Tetrahedron_4_1*Blending_DF_Tetrahedron_4_5;
      real_t tmp_236 = Blending_DF_Tetrahedron_4_2*Blending_DF_Tetrahedron_4_3;
      real_t tmp_237 = Blending_DF_Tetrahedron_4_0*Blending_DF_Tetrahedron_4_5;
      real_t tmp_238 = Blending_DF_Tetrahedron_4_2*Blending_DF_Tetrahedron_4_4;
      real_t tmp_239 = Blending_DF_Tetrahedron_4_6*tmp_235 - Blending_DF_Tetrahedron_4_6*tmp_238 + Blending_DF_Tetrahedron_4_7*tmp_236 - Blending_DF_Tetrahedron_4_7*tmp_237 + Blending_DF_Tetrahedron_4_8*tmp_233 - Blending_DF_Tetrahedron_4_8*tmp_234;
      real_t tmp_240 = tmp_26/tmp_239;
      real_t tmp_241 = tmp_240*(tmp_233 - tmp_234);
      real_t tmp_242 = tmp_241*tmp_8;
      real_t tmp_243 = tmp_241*tmp_30;
      real_t tmp_244 = tmp_241*tmp_32;
      real_t tmp_245 = tmp_240*(tmp_236 - tmp_237);
      real_t tmp_246 = tmp_245*tmp_34;
      real_t tmp_247 = tmp_245*tmp_37;
      real_t tmp_248 = tmp_245*tmp_39;
      real_t tmp_249 = tmp_240*(tmp_235 - tmp_238);
      real_t tmp_250 = tmp_249*tmp_41;
      real_t tmp_251 = tmp_249*tmp_44;
      real_t tmp_252 = tmp_249*tmp_46;
      real_t tmp_253 = -tmp_242 - tmp_243 - tmp_244 - tmp_246 - tmp_247 - tmp_248 - tmp_250 - tmp_251 - tmp_252;
      real_t tmp_254 = tmp_240*(-Blending_DF_Tetrahedron_4_0*Blending_DF_Tetrahedron_4_7 + Blending_DF_Tetrahedron_4_1*Blending_DF_Tetrahedron_4_6);
      real_t tmp_255 = tmp_254*tmp_8;
      real_t tmp_256 = tmp_254*tmp_30;
      real_t tmp_257 = tmp_254*tmp_32;
      real_t tmp_258 = tmp_240*(Blending_DF_Tetrahedron_4_0*Blending_DF_Tetrahedron_4_8 - Blending_DF_Tetrahedron_4_2*Blending_DF_Tetrahedron_4_6);
      real_t tmp_259 = tmp_258*tmp_34;
      real_t tmp_260 = tmp_258*tmp_37;
      real_t tmp_261 = tmp_258*tmp_39;
      real_t tmp_262 = tmp_240*(-Blending_DF_Tetrahedron_4_1*Blending_DF_Tetrahedron_4_8 + Blending_DF_Tetrahedron_4_2*Blending_DF_Tetrahedron_4_7);
      real_t tmp_263 = tmp_262*tmp_41;
      real_t tmp_264 = tmp_262*tmp_44;
      real_t tmp_265 = tmp_262*tmp_46;
      real_t tmp_266 = -tmp_255 - tmp_256 - tmp_257 - tmp_259 - tmp_260 - tmp_261 - tmp_263 - tmp_264 - tmp_265;
      real_t tmp_267 = tmp_240*(Blending_DF_Tetrahedron_4_3*Blending_DF_Tetrahedron_4_7 - Blending_DF_Tetrahedron_4_4*Blending_DF_Tetrahedron_4_6);
      real_t tmp_268 = tmp_267*tmp_8;
      real_t tmp_269 = tmp_267*tmp_30;
      real_t tmp_270 = tmp_267*tmp_32;
      real_t tmp_271 = tmp_240*(-Blending_DF_Tetrahedron_4_3*Blending_DF_Tetrahedron_4_8 + Blending_DF_Tetrahedron_4_5*Blending_DF_Tetrahedron_4_6);
      real_t tmp_272 = tmp_271*tmp_34;
      real_t tmp_273 = tmp_271*tmp_37;
      real_t tmp_274 = tmp_271*tmp_39;
      real_t tmp_275 = tmp_240*(Blending_DF_Tetrahedron_4_4*Blending_DF_Tetrahedron_4_8 - Blending_DF_Tetrahedron_4_5*Blending_DF_Tetrahedron_4_7);
      real_t tmp_276 = tmp_275*tmp_41;
      real_t tmp_277 = tmp_275*tmp_44;
      real_t tmp_278 = tmp_275*tmp_46;
      real_t tmp_279 = -tmp_268 - tmp_269 - tmp_270 - tmp_272 - tmp_273 - tmp_274 - tmp_276 - tmp_277 - tmp_278;
      real_t tmp_280 = tmp_87*w_p_4*std::abs(tmp_239);
      real_t tmp_281 = Blending_DF_Tetrahedron_5_0*Blending_DF_Tetrahedron_5_4;
      real_t tmp_282 = Blending_DF_Tetrahedron_5_1*Blending_DF_Tetrahedron_5_3;
      real_t tmp_283 = Blending_DF_Tetrahedron_5_1*Blending_DF_Tetrahedron_5_5;
      real_t tmp_284 = Blending_DF_Tetrahedron_5_2*Blending_DF_Tetrahedron_5_3;
      real_t tmp_285 = Blending_DF_Tetrahedron_5_0*Blending_DF_Tetrahedron_5_5;
      real_t tmp_286 = Blending_DF_Tetrahedron_5_2*Blending_DF_Tetrahedron_5_4;
      real_t tmp_287 = Blending_DF_Tetrahedron_5_6*tmp_283 - Blending_DF_Tetrahedron_5_6*tmp_286 + Blending_DF_Tetrahedron_5_7*tmp_284 - Blending_DF_Tetrahedron_5_7*tmp_285 + Blending_DF_Tetrahedron_5_8*tmp_281 - Blending_DF_Tetrahedron_5_8*tmp_282;
      real_t tmp_288 = tmp_26/tmp_287;
      real_t tmp_289 = tmp_288*(tmp_281 - tmp_282);
      real_t tmp_290 = tmp_289*tmp_8;
      real_t tmp_291 = tmp_289*tmp_30;
      real_t tmp_292 = tmp_289*tmp_32;
      real_t tmp_293 = tmp_288*(tmp_284 - tmp_285);
      real_t tmp_294 = tmp_293*tmp_34;
      real_t tmp_295 = tmp_293*tmp_37;
      real_t tmp_296 = tmp_293*tmp_39;
      real_t tmp_297 = tmp_288*(tmp_283 - tmp_286);
      real_t tmp_298 = tmp_297*tmp_41;
      real_t tmp_299 = tmp_297*tmp_44;
      real_t tmp_300 = tmp_297*tmp_46;
      real_t tmp_301 = -tmp_290 - tmp_291 - tmp_292 - tmp_294 - tmp_295 - tmp_296 - tmp_298 - tmp_299 - tmp_300;
      real_t tmp_302 = tmp_288*(-Blending_DF_Tetrahedron_5_0*Blending_DF_Tetrahedron_5_7 + Blending_DF_Tetrahedron_5_1*Blending_DF_Tetrahedron_5_6);
      real_t tmp_303 = tmp_302*tmp_8;
      real_t tmp_304 = tmp_30*tmp_302;
      real_t tmp_305 = tmp_302*tmp_32;
      real_t tmp_306 = tmp_288*(Blending_DF_Tetrahedron_5_0*Blending_DF_Tetrahedron_5_8 - Blending_DF_Tetrahedron_5_2*Blending_DF_Tetrahedron_5_6);
      real_t tmp_307 = tmp_306*tmp_34;
      real_t tmp_308 = tmp_306*tmp_37;
      real_t tmp_309 = tmp_306*tmp_39;
      real_t tmp_310 = tmp_288*(-Blending_DF_Tetrahedron_5_1*Blending_DF_Tetrahedron_5_8 + Blending_DF_Tetrahedron_5_2*Blending_DF_Tetrahedron_5_7);
      real_t tmp_311 = tmp_310*tmp_41;
      real_t tmp_312 = tmp_310*tmp_44;
      real_t tmp_313 = tmp_310*tmp_46;
      real_t tmp_314 = -tmp_303 - tmp_304 - tmp_305 - tmp_307 - tmp_308 - tmp_309 - tmp_311 - tmp_312 - tmp_313;
      real_t tmp_315 = tmp_288*(Blending_DF_Tetrahedron_5_3*Blending_DF_Tetrahedron_5_7 - Blending_DF_Tetrahedron_5_4*Blending_DF_Tetrahedron_5_6);
      real_t tmp_316 = tmp_315*tmp_8;
      real_t tmp_317 = tmp_30*tmp_315;
      real_t tmp_318 = tmp_315*tmp_32;
      real_t tmp_319 = tmp_288*(-Blending_DF_Tetrahedron_5_3*Blending_DF_Tetrahedron_5_8 + Blending_DF_Tetrahedron_5_5*Blending_DF_Tetrahedron_5_6);
      real_t tmp_320 = tmp_319*tmp_34;
      real_t tmp_321 = tmp_319*tmp_37;
      real_t tmp_322 = tmp_319*tmp_39;
      real_t tmp_323 = tmp_288*(Blending_DF_Tetrahedron_5_4*Blending_DF_Tetrahedron_5_8 - Blending_DF_Tetrahedron_5_5*Blending_DF_Tetrahedron_5_7);
      real_t tmp_324 = tmp_323*tmp_41;
      real_t tmp_325 = tmp_323*tmp_44;
      real_t tmp_326 = tmp_323*tmp_46;
      real_t tmp_327 = -tmp_316 - tmp_317 - tmp_318 - tmp_320 - tmp_321 - tmp_322 - tmp_324 - tmp_325 - tmp_326;
      real_t tmp_328 = tmp_87*w_p_5*std::abs(tmp_287);
      real_t tmp_329 = tmp_33 + tmp_40 + tmp_47;
      real_t tmp_330 = tmp_52 + tmp_56 + tmp_60;
      real_t tmp_331 = tmp_65 + tmp_69 + tmp_73;
      real_t tmp_332 = tmp_100 + tmp_104 + tmp_108;
      real_t tmp_333 = tmp_113 + tmp_117 + tmp_121;
      real_t tmp_334 = tmp_126 + tmp_130 + tmp_134;
      real_t tmp_335 = tmp_148 + tmp_152 + tmp_156;
      real_t tmp_336 = tmp_161 + tmp_165 + tmp_169;
      real_t tmp_337 = tmp_174 + tmp_178 + tmp_182;
      real_t tmp_338 = tmp_196 + tmp_200 + tmp_204;
      real_t tmp_339 = tmp_209 + tmp_213 + tmp_217;
      real_t tmp_340 = tmp_222 + tmp_226 + tmp_230;
      real_t tmp_341 = tmp_244 + tmp_248 + tmp_252;
      real_t tmp_342 = tmp_257 + tmp_261 + tmp_265;
      real_t tmp_343 = tmp_270 + tmp_274 + tmp_278;
      real_t tmp_344 = tmp_292 + tmp_296 + tmp_300;
      real_t tmp_345 = tmp_305 + tmp_309 + tmp_313;
      real_t tmp_346 = tmp_318 + tmp_322 + tmp_326;
      real_t tmp_347 = tmp_136*(tmp_109*tmp_332 + tmp_122*tmp_333 + tmp_135*tmp_334) + tmp_184*(tmp_157*tmp_335 + tmp_170*tmp_336 + tmp_183*tmp_337) + tmp_232*(tmp_205*tmp_338 + tmp_218*tmp_339 + tmp_231*tmp_340) + tmp_280*(tmp_253*tmp_341 + tmp_266*tmp_342 + tmp_279*tmp_343) + tmp_328*(tmp_301*tmp_344 + tmp_314*tmp_345 + tmp_327*tmp_346) + tmp_88*(tmp_329*tmp_48 + tmp_330*tmp_61 + tmp_331*tmp_74);
      real_t tmp_348 = tmp_31 + tmp_38 + tmp_45;
      real_t tmp_349 = tmp_51 + tmp_55 + tmp_59;
      real_t tmp_350 = tmp_64 + tmp_68 + tmp_72;
      real_t tmp_351 = tmp_103 + tmp_107 + tmp_99;
      real_t tmp_352 = tmp_112 + tmp_116 + tmp_120;
      real_t tmp_353 = tmp_125 + tmp_129 + tmp_133;
      real_t tmp_354 = tmp_147 + tmp_151 + tmp_155;
      real_t tmp_355 = tmp_160 + tmp_164 + tmp_168;
      real_t tmp_356 = tmp_173 + tmp_177 + tmp_181;
      real_t tmp_357 = tmp_195 + tmp_199 + tmp_203;
      real_t tmp_358 = tmp_208 + tmp_212 + tmp_216;
      real_t tmp_359 = tmp_221 + tmp_225 + tmp_229;
      real_t tmp_360 = tmp_243 + tmp_247 + tmp_251;
      real_t tmp_361 = tmp_256 + tmp_260 + tmp_264;
      real_t tmp_362 = tmp_269 + tmp_273 + tmp_277;
      real_t tmp_363 = tmp_291 + tmp_295 + tmp_299;
      real_t tmp_364 = tmp_304 + tmp_308 + tmp_312;
      real_t tmp_365 = tmp_317 + tmp_321 + tmp_325;
      real_t tmp_366 = tmp_136*(tmp_109*tmp_351 + tmp_122*tmp_352 + tmp_135*tmp_353) + tmp_184*(tmp_157*tmp_354 + tmp_170*tmp_355 + tmp_183*tmp_356) + tmp_232*(tmp_205*tmp_357 + tmp_218*tmp_358 + tmp_231*tmp_359) + tmp_280*(tmp_253*tmp_360 + tmp_266*tmp_361 + tmp_279*tmp_362) + tmp_328*(tmp_301*tmp_363 + tmp_314*tmp_364 + tmp_327*tmp_365) + tmp_88*(tmp_348*tmp_48 + tmp_349*tmp_61 + tmp_350*tmp_74);
      real_t tmp_367 = tmp_29 + tmp_36 + tmp_43;
      real_t tmp_368 = tmp_50 + tmp_54 + tmp_58;
      real_t tmp_369 = tmp_63 + tmp_67 + tmp_71;
      real_t tmp_370 = tmp_102 + tmp_106 + tmp_98;
      real_t tmp_371 = tmp_111 + tmp_115 + tmp_119;
      real_t tmp_372 = tmp_124 + tmp_128 + tmp_132;
      real_t tmp_373 = tmp_146 + tmp_150 + tmp_154;
      real_t tmp_374 = tmp_159 + tmp_163 + tmp_167;
      real_t tmp_375 = tmp_172 + tmp_176 + tmp_180;
      real_t tmp_376 = tmp_194 + tmp_198 + tmp_202;
      real_t tmp_377 = tmp_207 + tmp_211 + tmp_215;
      real_t tmp_378 = tmp_220 + tmp_224 + tmp_228;
      real_t tmp_379 = tmp_242 + tmp_246 + tmp_250;
      real_t tmp_380 = tmp_255 + tmp_259 + tmp_263;
      real_t tmp_381 = tmp_268 + tmp_272 + tmp_276;
      real_t tmp_382 = tmp_290 + tmp_294 + tmp_298;
      real_t tmp_383 = tmp_303 + tmp_307 + tmp_311;
      real_t tmp_384 = tmp_316 + tmp_320 + tmp_324;
      real_t tmp_385 = tmp_136*(tmp_109*tmp_370 + tmp_122*tmp_371 + tmp_135*tmp_372) + tmp_184*(tmp_157*tmp_373 + tmp_170*tmp_374 + tmp_183*tmp_375) + tmp_232*(tmp_205*tmp_376 + tmp_218*tmp_377 + tmp_231*tmp_378) + tmp_280*(tmp_253*tmp_379 + tmp_266*tmp_380 + tmp_279*tmp_381) + tmp_328*(tmp_301*tmp_382 + tmp_314*tmp_383 + tmp_327*tmp_384) + tmp_88*(tmp_367*tmp_48 + tmp_368*tmp_61 + tmp_369*tmp_74);
      real_t tmp_386 = tmp_136*(tmp_332*tmp_351 + tmp_333*tmp_352 + tmp_334*tmp_353) + tmp_184*(tmp_335*tmp_354 + tmp_336*tmp_355 + tmp_337*tmp_356) + tmp_232*(tmp_338*tmp_357 + tmp_339*tmp_358 + tmp_340*tmp_359) + tmp_280*(tmp_341*tmp_360 + tmp_342*tmp_361 + tmp_343*tmp_362) + tmp_328*(tmp_344*tmp_363 + tmp_345*tmp_364 + tmp_346*tmp_365) + tmp_88*(tmp_329*tmp_348 + tmp_330*tmp_349 + tmp_331*tmp_350);
      real_t tmp_387 = tmp_136*(tmp_332*tmp_370 + tmp_333*tmp_371 + tmp_334*tmp_372) + tmp_184*(tmp_335*tmp_373 + tmp_336*tmp_374 + tmp_337*tmp_375) + tmp_232*(tmp_338*tmp_376 + tmp_339*tmp_377 + tmp_340*tmp_378) + tmp_280*(tmp_341*tmp_379 + tmp_342*tmp_380 + tmp_343*tmp_381) + tmp_328*(tmp_344*tmp_382 + tmp_345*tmp_383 + tmp_346*tmp_384) + tmp_88*(tmp_329*tmp_367 + tmp_330*tmp_368 + tmp_331*tmp_369);
      real_t tmp_388 = tmp_136*(tmp_351*tmp_370 + tmp_352*tmp_371 + tmp_353*tmp_372) + tmp_184*(tmp_354*tmp_373 + tmp_355*tmp_374 + tmp_356*tmp_375) + tmp_232*(tmp_357*tmp_376 + tmp_358*tmp_377 + tmp_359*tmp_378) + tmp_280*(tmp_360*tmp_379 + tmp_361*tmp_380 + tmp_362*tmp_381) + tmp_328*(tmp_363*tmp_382 + tmp_364*tmp_383 + tmp_365*tmp_384) + tmp_88*(tmp_348*tmp_367 + tmp_349*tmp_368 + tmp_350*tmp_369);
      real_t a_0_0 = tmp_136*((tmp_109*tmp_109) + (tmp_122*tmp_122) + (tmp_135*tmp_135)) + tmp_184*((tmp_157*tmp_157) + (tmp_170*tmp_170) + (tmp_183*tmp_183)) + tmp_232*((tmp_205*tmp_205) + (tmp_218*tmp_218) + (tmp_231*tmp_231)) + tmp_280*((tmp_253*tmp_253) + (tmp_266*tmp_266) + (tmp_279*tmp_279)) + tmp_328*((tmp_301*tmp_301) + (tmp_314*tmp_314) + (tmp_327*tmp_327)) + tmp_88*((tmp_48*tmp_48) + (tmp_61*tmp_61) + (tmp_74*tmp_74));
      real_t a_0_1 = tmp_347;
      real_t a_0_2 = tmp_366;
      real_t a_0_3 = tmp_385;
      real_t a_1_0 = tmp_347;
      real_t a_1_1 = tmp_136*((tmp_332*tmp_332) + (tmp_333*tmp_333) + (tmp_334*tmp_334)) + tmp_184*((tmp_335*tmp_335) + (tmp_336*tmp_336) + (tmp_337*tmp_337)) + tmp_232*((tmp_338*tmp_338) + (tmp_339*tmp_339) + (tmp_340*tmp_340)) + tmp_280*((tmp_341*tmp_341) + (tmp_342*tmp_342) + (tmp_343*tmp_343)) + tmp_328*((tmp_344*tmp_344) + (tmp_345*tmp_345) + (tmp_346*tmp_346)) + tmp_88*((tmp_329*tmp_329) + (tmp_330*tmp_330) + (tmp_331*tmp_331));
      real_t a_1_2 = tmp_386;
      real_t a_1_3 = tmp_387;
      real_t a_2_0 = tmp_366;
      real_t a_2_1 = tmp_386;
      real_t a_2_2 = tmp_136*((tmp_351*tmp_351) + (tmp_352*tmp_352) + (tmp_353*tmp_353)) + tmp_184*((tmp_354*tmp_354) + (tmp_355*tmp_355) + (tmp_356*tmp_356)) + tmp_232*((tmp_357*tmp_357) + (tmp_358*tmp_358) + (tmp_359*tmp_359)) + tmp_280*((tmp_360*tmp_360) + (tmp_361*tmp_361) + (tmp_362*tmp_362)) + tmp_328*((tmp_363*tmp_363) + (tmp_364*tmp_364) + (tmp_365*tmp_365)) + tmp_88*((tmp_348*tmp_348) + (tmp_349*tmp_349) + (tmp_350*tmp_350));
      real_t a_2_3 = tmp_388;
      real_t a_3_0 = tmp_385;
      real_t a_3_1 = tmp_387;
      real_t a_3_2 = tmp_388;
      real_t a_3_3 = tmp_136*((tmp_370*tmp_370) + (tmp_371*tmp_371) + (tmp_372*tmp_372)) + tmp_184*((tmp_373*tmp_373) + (tmp_374*tmp_374) + (tmp_375*tmp_375)) + tmp_232*((tmp_376*tmp_376) + (tmp_377*tmp_377) + (tmp_378*tmp_378)) + tmp_280*((tmp_379*tmp_379) + (tmp_380*tmp_380) + (tmp_381*tmp_381)) + tmp_328*((tmp_382*tmp_382) + (tmp_383*tmp_383) + (tmp_384*tmp_384)) + tmp_88*((tmp_367*tmp_367) + (tmp_368*tmp_368) + (tmp_369*tmp_369));
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
      (elMat(0, 3)) = a_0_3;
      (elMat(1, 0)) = a_1_0;
      (elMat(1, 1)) = a_1_1;
      (elMat(1, 2)) = a_1_2;
      (elMat(1, 3)) = a_1_3;
      (elMat(2, 0)) = a_2_0;
      (elMat(2, 1)) = a_2_1;
      (elMat(2, 2)) = a_2_2;
      (elMat(2, 3)) = a_2_3;
      (elMat(3, 0)) = a_3_0;
      (elMat(3, 1)) = a_3_1;
      (elMat(3, 2)) = a_3_2;
      (elMat(3, 3)) = a_3_3;
   }

 private:

   void Blending_DF_Triangle( real_t in_0, real_t in_1, real_t * out_0, real_t * out_1, real_t * out_2, real_t * out_3 ) const
   {
      Point3D  mappedPt( {in_0, in_1, 0} );
      Matrix2r DPsi;
      geometryMap_->evalDF( mappedPt, DPsi );
      *out_0 = DPsi( 0, 0 );
      *out_1 = DPsi( 0, 1 );
      *out_2 = DPsi( 1, 0 );
      *out_3 = DPsi( 1, 1 );
   }

   void Blending_DF_Tetrahedron( real_t in_0, real_t in_1, real_t in_2, real_t * out_0, real_t * out_1, real_t * out_2, real_t * out_3, real_t * out_4, real_t * out_5, real_t * out_6, real_t * out_7, real_t * out_8 ) const
   {
      Point3D  mappedPt( {in_0, in_1, in_2} );
      Matrix3r DPsi;
      geometryMap_->evalDF( mappedPt, DPsi );
      *out_0 = DPsi( 0, 0 );
      *out_1 = DPsi( 0, 1 );
      *out_2 = DPsi( 0, 2 );
      *out_3 = DPsi( 1, 0 );
      *out_4 = DPsi( 1, 1 );
      *out_5 = DPsi( 1, 2 );
      *out_6 = DPsi( 2, 0 );
      *out_7 = DPsi( 2, 1 );
      *out_8 = DPsi( 2, 2 );
   }

};

} // namespace hyteg
