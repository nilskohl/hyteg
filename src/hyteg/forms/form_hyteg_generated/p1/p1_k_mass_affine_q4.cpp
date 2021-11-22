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

#include "p1_k_mass_affine_q4.hpp"

namespace hyteg {
namespace forms {

   void p1_k_mass_affine_q4::integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 3, 3 >& elMat ) const
   {
      real_t p_affine_0_0 = coords[0][0];
      real_t p_affine_0_1 = coords[0][1];
      real_t p_affine_1_0 = coords[1][0];
      real_t p_affine_1_1 = coords[1][1];
      real_t p_affine_2_0 = coords[2][0];
      real_t p_affine_2_1 = coords[2][1];
      real_t Scalar_Variable_Coefficient_2D_0_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_1_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_2_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_3_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_4_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_5_0 = 0;
      Scalar_Variable_Coefficient_2D( 0.091576213509770743*p_affine_0_0 + 0.091576213509770743*p_affine_1_0 + 0.81684757298045851*p_affine_2_0, 0.091576213509770743*p_affine_0_1 + 0.091576213509770743*p_affine_1_1 + 0.81684757298045851*p_affine_2_1, &Scalar_Variable_Coefficient_2D_0_0 );
      Scalar_Variable_Coefficient_2D( 0.44594849091596489*p_affine_0_0 + 0.44594849091596489*p_affine_1_0 + 0.10810301816807022*p_affine_2_0, 0.44594849091596489*p_affine_0_1 + 0.44594849091596489*p_affine_1_1 + 0.10810301816807022*p_affine_2_1, &Scalar_Variable_Coefficient_2D_1_0 );
      Scalar_Variable_Coefficient_2D( 0.091576213509770743*p_affine_0_0 + 0.81684757298045851*p_affine_1_0 + 0.091576213509770743*p_affine_2_0, 0.091576213509770743*p_affine_0_1 + 0.81684757298045851*p_affine_1_1 + 0.091576213509770743*p_affine_2_1, &Scalar_Variable_Coefficient_2D_2_0 );
      Scalar_Variable_Coefficient_2D( 0.44594849091596489*p_affine_0_0 + 0.10810301816807022*p_affine_1_0 + 0.44594849091596489*p_affine_2_0, 0.44594849091596489*p_affine_0_1 + 0.10810301816807022*p_affine_1_1 + 0.44594849091596489*p_affine_2_1, &Scalar_Variable_Coefficient_2D_3_0 );
      Scalar_Variable_Coefficient_2D( 0.81684757298045851*p_affine_0_0 + 0.091576213509770743*p_affine_1_0 + 0.091576213509770743*p_affine_2_0, 0.81684757298045851*p_affine_0_1 + 0.091576213509770743*p_affine_1_1 + 0.091576213509770743*p_affine_2_1, &Scalar_Variable_Coefficient_2D_4_0 );
      Scalar_Variable_Coefficient_2D( 0.10810301816807022*p_affine_0_0 + 0.44594849091596489*p_affine_1_0 + 0.44594849091596489*p_affine_2_0, 0.10810301816807022*p_affine_0_1 + 0.44594849091596489*p_affine_1_1 + 0.44594849091596489*p_affine_2_1, &Scalar_Variable_Coefficient_2D_5_0 );
      real_t tmp_0 = 0.091576213509770743;
      real_t tmp_1 = std::abs(p_affine_0_0*p_affine_1_1 - p_affine_0_0*p_affine_2_1 - p_affine_0_1*p_affine_1_0 + p_affine_0_1*p_affine_2_0 + p_affine_1_0*p_affine_2_1 - p_affine_1_1*p_affine_2_0);
      real_t tmp_2 = 0.054975871827660928*Scalar_Variable_Coefficient_2D_0_0*tmp_1;
      real_t tmp_3 = 0.44594849091596489;
      real_t tmp_4 = 0.11169079483900572*Scalar_Variable_Coefficient_2D_1_0*tmp_1;
      real_t tmp_5 = 0.091576213509770743;
      real_t tmp_6 = 0.054975871827660928*Scalar_Variable_Coefficient_2D_2_0*tmp_1;
      real_t tmp_7 = 0.44594849091596489;
      real_t tmp_8 = 0.11169079483900572*Scalar_Variable_Coefficient_2D_3_0*tmp_1;
      real_t tmp_9 = 0.81684757298045851;
      real_t tmp_10 = 0.054975871827660928*Scalar_Variable_Coefficient_2D_4_0*tmp_1;
      real_t tmp_11 = 0.10810301816807022;
      real_t tmp_12 = 0.11169079483900572*Scalar_Variable_Coefficient_2D_5_0*tmp_1;
      real_t tmp_13 = tmp_0*tmp_2;
      real_t tmp_14 = tmp_3*tmp_4;
      real_t tmp_15 = tmp_5*tmp_6;
      real_t tmp_16 = tmp_7*tmp_8;
      real_t tmp_17 = tmp_10*tmp_9;
      real_t tmp_18 = tmp_11*tmp_12;
      real_t tmp_19 = 0.091576213509770743*tmp_13 + 0.44594849091596489*tmp_14 + 0.81684757298045851*tmp_15 + 0.10810301816807022*tmp_16 + 0.091576213509770743*tmp_17 + 0.44594849091596489*tmp_18;
      real_t tmp_20 = 0.81684757298045851*tmp_13 + 0.10810301816807022*tmp_14 + 0.091576213509770743*tmp_15 + 0.44594849091596489*tmp_16 + 0.091576213509770743*tmp_17 + 0.44594849091596489*tmp_18;
      real_t tmp_21 = 0.0083862028807871174*tmp_10 + 0.19887005655022641*tmp_12 + 0.074803807748196505*tmp_2 + 0.04820837781551205*tmp_4 + 0.074803807748196505*tmp_6 + 0.04820837781551205*tmp_8;
      real_t a_0_0 = (tmp_0*tmp_0)*tmp_2 + tmp_10*(tmp_9*tmp_9) + (tmp_11*tmp_11)*tmp_12 + (tmp_3*tmp_3)*tmp_4 + (tmp_5*tmp_5)*tmp_6 + (tmp_7*tmp_7)*tmp_8;
      real_t a_0_1 = tmp_19;
      real_t a_0_2 = tmp_20;
      real_t a_1_0 = tmp_19;
      real_t a_1_1 = 0.0083862028807871174*tmp_10 + 0.19887005655022641*tmp_12 + 0.0083862028807871174*tmp_2 + 0.19887005655022641*tmp_4 + 0.6672399574840655*tmp_6 + 0.01168626253704612*tmp_8;
      real_t a_1_2 = tmp_21;
      real_t a_2_0 = tmp_20;
      real_t a_2_1 = tmp_21;
      real_t a_2_2 = 0.0083862028807871174*tmp_10 + 0.19887005655022641*tmp_12 + 0.6672399574840655*tmp_2 + 0.01168626253704612*tmp_4 + 0.0083862028807871174*tmp_6 + 0.19887005655022641*tmp_8;
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

   void p1_k_mass_affine_q4::integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 3 >& elMat ) const
   {
      real_t p_affine_0_0 = coords[0][0];
      real_t p_affine_0_1 = coords[0][1];
      real_t p_affine_1_0 = coords[1][0];
      real_t p_affine_1_1 = coords[1][1];
      real_t p_affine_2_0 = coords[2][0];
      real_t p_affine_2_1 = coords[2][1];
      real_t Scalar_Variable_Coefficient_2D_0_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_1_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_2_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_3_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_4_0 = 0;
      real_t Scalar_Variable_Coefficient_2D_5_0 = 0;
      Scalar_Variable_Coefficient_2D( 0.091576213509770743*p_affine_0_0 + 0.091576213509770743*p_affine_1_0 + 0.81684757298045851*p_affine_2_0, 0.091576213509770743*p_affine_0_1 + 0.091576213509770743*p_affine_1_1 + 0.81684757298045851*p_affine_2_1, &Scalar_Variable_Coefficient_2D_0_0 );
      Scalar_Variable_Coefficient_2D( 0.44594849091596489*p_affine_0_0 + 0.44594849091596489*p_affine_1_0 + 0.10810301816807022*p_affine_2_0, 0.44594849091596489*p_affine_0_1 + 0.44594849091596489*p_affine_1_1 + 0.10810301816807022*p_affine_2_1, &Scalar_Variable_Coefficient_2D_1_0 );
      Scalar_Variable_Coefficient_2D( 0.091576213509770743*p_affine_0_0 + 0.81684757298045851*p_affine_1_0 + 0.091576213509770743*p_affine_2_0, 0.091576213509770743*p_affine_0_1 + 0.81684757298045851*p_affine_1_1 + 0.091576213509770743*p_affine_2_1, &Scalar_Variable_Coefficient_2D_2_0 );
      Scalar_Variable_Coefficient_2D( 0.44594849091596489*p_affine_0_0 + 0.10810301816807022*p_affine_1_0 + 0.44594849091596489*p_affine_2_0, 0.44594849091596489*p_affine_0_1 + 0.10810301816807022*p_affine_1_1 + 0.44594849091596489*p_affine_2_1, &Scalar_Variable_Coefficient_2D_3_0 );
      Scalar_Variable_Coefficient_2D( 0.81684757298045851*p_affine_0_0 + 0.091576213509770743*p_affine_1_0 + 0.091576213509770743*p_affine_2_0, 0.81684757298045851*p_affine_0_1 + 0.091576213509770743*p_affine_1_1 + 0.091576213509770743*p_affine_2_1, &Scalar_Variable_Coefficient_2D_4_0 );
      Scalar_Variable_Coefficient_2D( 0.10810301816807022*p_affine_0_0 + 0.44594849091596489*p_affine_1_0 + 0.44594849091596489*p_affine_2_0, 0.10810301816807022*p_affine_0_1 + 0.44594849091596489*p_affine_1_1 + 0.44594849091596489*p_affine_2_1, &Scalar_Variable_Coefficient_2D_5_0 );
      real_t tmp_0 = 0.091576213509770743;
      real_t tmp_1 = std::abs(p_affine_0_0*p_affine_1_1 - p_affine_0_0*p_affine_2_1 - p_affine_0_1*p_affine_1_0 + p_affine_0_1*p_affine_2_0 + p_affine_1_0*p_affine_2_1 - p_affine_1_1*p_affine_2_0);
      real_t tmp_2 = 0.054975871827660928*Scalar_Variable_Coefficient_2D_0_0*tmp_1;
      real_t tmp_3 = 0.44594849091596489;
      real_t tmp_4 = 0.11169079483900572*Scalar_Variable_Coefficient_2D_1_0*tmp_1;
      real_t tmp_5 = 0.091576213509770743;
      real_t tmp_6 = 0.054975871827660928*Scalar_Variable_Coefficient_2D_2_0*tmp_1;
      real_t tmp_7 = 0.44594849091596489;
      real_t tmp_8 = 0.11169079483900572*Scalar_Variable_Coefficient_2D_3_0*tmp_1;
      real_t tmp_9 = 0.81684757298045851;
      real_t tmp_10 = 0.054975871827660928*Scalar_Variable_Coefficient_2D_4_0*tmp_1;
      real_t tmp_11 = 0.10810301816807022;
      real_t tmp_12 = 0.11169079483900572*Scalar_Variable_Coefficient_2D_5_0*tmp_1;
      real_t tmp_13 = tmp_0*tmp_2;
      real_t tmp_14 = tmp_3*tmp_4;
      real_t tmp_15 = tmp_5*tmp_6;
      real_t tmp_16 = tmp_7*tmp_8;
      real_t tmp_17 = tmp_10*tmp_9;
      real_t tmp_18 = tmp_11*tmp_12;
      real_t a_0_0 = (tmp_0*tmp_0)*tmp_2 + tmp_10*(tmp_9*tmp_9) + (tmp_11*tmp_11)*tmp_12 + (tmp_3*tmp_3)*tmp_4 + (tmp_5*tmp_5)*tmp_6 + (tmp_7*tmp_7)*tmp_8;
      real_t a_0_1 = 0.091576213509770743*tmp_13 + 0.44594849091596489*tmp_14 + 0.81684757298045851*tmp_15 + 0.10810301816807022*tmp_16 + 0.091576213509770743*tmp_17 + 0.44594849091596489*tmp_18;
      real_t a_0_2 = 0.81684757298045851*tmp_13 + 0.10810301816807022*tmp_14 + 0.091576213509770743*tmp_15 + 0.44594849091596489*tmp_16 + 0.091576213509770743*tmp_17 + 0.44594849091596489*tmp_18;
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
   }

   void p1_k_mass_affine_q4::integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 4, 4 >& elMat ) const
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
      real_t Scalar_Variable_Coefficient_3D_0_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_1_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_2_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_3_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_4_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_5_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_6_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_7_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_8_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_9_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_10_0 = 0;
      Scalar_Variable_Coefficient_3D( 0.17469405869723054*p_affine_0_0 + 0.040490506727590428*p_affine_1_0 + 0.01356070187980288*p_affine_2_0 + 0.77125473269537614*p_affine_3_0, 0.17469405869723054*p_affine_0_1 + 0.040490506727590428*p_affine_1_1 + 0.01356070187980288*p_affine_2_1 + 0.77125473269537614*p_affine_3_1, 0.17469405869723054*p_affine_0_2 + 0.040490506727590428*p_affine_1_2 + 0.01356070187980288*p_affine_2_2 + 0.77125473269537614*p_affine_3_2, &Scalar_Variable_Coefficient_3D_0_0 );
      Scalar_Variable_Coefficient_3D( 0.081404918402859225*p_affine_0_0 + 0.75250850700965499*p_affine_1_0 + 0.068099370938206658*p_affine_2_0 + 0.097987203649279112*p_affine_3_0, 0.081404918402859225*p_affine_0_1 + 0.75250850700965499*p_affine_1_1 + 0.068099370938206658*p_affine_2_1 + 0.097987203649279112*p_affine_3_1, 0.081404918402859225*p_affine_0_2 + 0.75250850700965499*p_affine_1_2 + 0.068099370938206658*p_affine_2_2 + 0.097987203649279112*p_affine_3_2, &Scalar_Variable_Coefficient_3D_1_0 );
      Scalar_Variable_Coefficient_3D( 0.30444840243449711*p_affine_0_0 + 0.24027666492807259*p_affine_1_0 + 0.12680172591539199*p_affine_2_0 + 0.32847320672203839*p_affine_3_0, 0.30444840243449711*p_affine_0_1 + 0.24027666492807259*p_affine_1_1 + 0.12680172591539199*p_affine_2_1 + 0.32847320672203839*p_affine_3_1, 0.30444840243449711*p_affine_0_2 + 0.24027666492807259*p_affine_1_2 + 0.12680172591539199*p_affine_2_2 + 0.32847320672203839*p_affine_3_2, &Scalar_Variable_Coefficient_3D_2_0 );
      Scalar_Variable_Coefficient_3D( 0.74122888209362259*p_affine_0_0 + 0.067223294893383398*p_affine_1_0 + 0.035183929773598722*p_affine_2_0 + 0.15636389323939531*p_affine_3_0, 0.74122888209362259*p_affine_0_1 + 0.067223294893383398*p_affine_1_1 + 0.035183929773598722*p_affine_2_1 + 0.15636389323939531*p_affine_3_1, 0.74122888209362259*p_affine_0_2 + 0.067223294893383398*p_affine_1_2 + 0.035183929773598722*p_affine_2_2 + 0.15636389323939531*p_affine_3_2, &Scalar_Variable_Coefficient_3D_3_0 );
      Scalar_Variable_Coefficient_3D( 0.053341239535745266*p_affine_0_0 + 0.41926631387951302*p_affine_1_0 + 0.047781435559086663*p_affine_2_0 + 0.47961101102565512*p_affine_3_0, 0.053341239535745266*p_affine_0_1 + 0.41926631387951302*p_affine_1_1 + 0.047781435559086663*p_affine_2_1 + 0.47961101102565512*p_affine_3_1, 0.053341239535745266*p_affine_0_2 + 0.41926631387951302*p_affine_1_2 + 0.047781435559086663*p_affine_2_2 + 0.47961101102565512*p_affine_3_2, &Scalar_Variable_Coefficient_3D_4_0 );
      Scalar_Variable_Coefficient_3D( 0.43295349048135578*p_affine_0_0 + 0.45076587609127677*p_affine_1_0 + 0.059456616299433829*p_affine_2_0 + 0.056824017127933668*p_affine_3_0, 0.43295349048135578*p_affine_0_1 + 0.45076587609127677*p_affine_1_1 + 0.059456616299433829*p_affine_2_1 + 0.056824017127933668*p_affine_3_1, 0.43295349048135578*p_affine_0_2 + 0.45076587609127677*p_affine_1_2 + 0.059456616299433829*p_affine_2_2 + 0.056824017127933668*p_affine_3_2, &Scalar_Variable_Coefficient_3D_5_0 );
      Scalar_Variable_Coefficient_3D( 0.53800720391618573*p_affine_0_0 + 0.12941137378891041*p_affine_1_0 + 0.33019041483746447*p_affine_2_0 + 0.0023910074574393651*p_affine_3_0, 0.53800720391618573*p_affine_0_1 + 0.12941137378891041*p_affine_1_1 + 0.33019041483746447*p_affine_2_1 + 0.0023910074574393651*p_affine_3_1, 0.53800720391618573*p_affine_0_2 + 0.12941137378891041*p_affine_1_2 + 0.33019041483746447*p_affine_2_2 + 0.0023910074574393651*p_affine_3_2, &Scalar_Variable_Coefficient_3D_6_0 );
      Scalar_Variable_Coefficient_3D( 0.008991260093335729*p_affine_0_0 + 0.1215419913339278*p_affine_1_0 + 0.30649398842969028*p_affine_2_0 + 0.56297276014304609*p_affine_3_0, 0.008991260093335729*p_affine_0_1 + 0.1215419913339278*p_affine_1_1 + 0.30649398842969028*p_affine_2_1 + 0.56297276014304609*p_affine_3_1, 0.008991260093335729*p_affine_0_2 + 0.1215419913339278*p_affine_1_2 + 0.30649398842969028*p_affine_2_2 + 0.56297276014304609*p_affine_3_2, &Scalar_Variable_Coefficient_3D_7_0 );
      Scalar_Variable_Coefficient_3D( 0.10660417256199362*p_affine_0_0 + 0.097204644587583267*p_affine_1_0 + 0.68439041545304002*p_affine_2_0 + 0.11180076739738309*p_affine_3_0, 0.10660417256199362*p_affine_0_1 + 0.097204644587583267*p_affine_1_1 + 0.68439041545304002*p_affine_2_1 + 0.11180076739738309*p_affine_3_1, 0.10660417256199362*p_affine_0_2 + 0.097204644587583267*p_affine_1_2 + 0.68439041545304002*p_affine_2_2 + 0.11180076739738309*p_affine_3_2, &Scalar_Variable_Coefficient_3D_8_0 );
      Scalar_Variable_Coefficient_3D( 0.32923295974264682*p_affine_0_0 + 0.029569495206479609*p_affine_1_0 + 0.31790356021339461*p_affine_2_0 + 0.32329398483747901*p_affine_3_0, 0.32923295974264682*p_affine_0_1 + 0.029569495206479609*p_affine_1_1 + 0.31790356021339461*p_affine_2_1 + 0.32329398483747901*p_affine_3_1, 0.32923295974264682*p_affine_0_2 + 0.029569495206479609*p_affine_1_2 + 0.31790356021339461*p_affine_2_2 + 0.32329398483747901*p_affine_3_2, &Scalar_Variable_Coefficient_3D_9_0 );
      Scalar_Variable_Coefficient_3D( 0.10384411641099309*p_affine_0_0 + 0.43271023904776862*p_affine_1_0 + 0.35382323920929709*p_affine_2_0 + 0.1096224053319412*p_affine_3_0, 0.10384411641099309*p_affine_0_1 + 0.43271023904776862*p_affine_1_1 + 0.35382323920929709*p_affine_2_1 + 0.1096224053319412*p_affine_3_1, 0.10384411641099309*p_affine_0_2 + 0.43271023904776862*p_affine_1_2 + 0.35382323920929709*p_affine_2_2 + 0.1096224053319412*p_affine_3_2, &Scalar_Variable_Coefficient_3D_10_0 );
      real_t tmp_0 = 0.17469405869723054;
      real_t tmp_1 = p_affine_0_0*p_affine_1_1;
      real_t tmp_2 = p_affine_0_0*p_affine_1_2;
      real_t tmp_3 = p_affine_2_1*p_affine_3_2;
      real_t tmp_4 = p_affine_0_1*p_affine_1_0;
      real_t tmp_5 = p_affine_0_1*p_affine_1_2;
      real_t tmp_6 = p_affine_2_2*p_affine_3_0;
      real_t tmp_7 = p_affine_0_2*p_affine_1_0;
      real_t tmp_8 = p_affine_0_2*p_affine_1_1;
      real_t tmp_9 = p_affine_2_0*p_affine_3_1;
      real_t tmp_10 = p_affine_2_2*p_affine_3_1;
      real_t tmp_11 = p_affine_2_0*p_affine_3_2;
      real_t tmp_12 = p_affine_2_1*p_affine_3_0;
      real_t tmp_13 = std::abs(p_affine_0_0*tmp_10 - p_affine_0_0*tmp_3 + p_affine_0_1*tmp_11 - p_affine_0_1*tmp_6 + p_affine_0_2*tmp_12 - p_affine_0_2*tmp_9 - p_affine_1_0*tmp_10 + p_affine_1_0*tmp_3 - p_affine_1_1*tmp_11 + p_affine_1_1*tmp_6 - p_affine_1_2*tmp_12 + p_affine_1_2*tmp_9 - p_affine_2_0*tmp_5 + p_affine_2_0*tmp_8 + p_affine_2_1*tmp_2 - p_affine_2_1*tmp_7 - p_affine_2_2*tmp_1 + p_affine_2_2*tmp_4 + p_affine_3_0*tmp_5 - p_affine_3_0*tmp_8 - p_affine_3_1*tmp_2 + p_affine_3_1*tmp_7 + p_affine_3_2*tmp_1 - p_affine_3_2*tmp_4);
      real_t tmp_14 = 0.006541848487473325*Scalar_Variable_Coefficient_3D_0_0*tmp_13;
      real_t tmp_15 = 0.10384411641099309;
      real_t tmp_16 = 0.025829352669374347*Scalar_Variable_Coefficient_3D_10_0*tmp_13;
      real_t tmp_17 = 0.081404918402859225;
      real_t tmp_18 = 0.0092122281926561474*Scalar_Variable_Coefficient_3D_1_0*tmp_13;
      real_t tmp_19 = 0.30444840243449711;
      real_t tmp_20 = 0.032235135341605742*Scalar_Variable_Coefficient_3D_2_0*tmp_13;
      real_t tmp_21 = 0.74122888209362259;
      real_t tmp_22 = 0.0092322998119293929*Scalar_Variable_Coefficient_3D_3_0*tmp_13;
      real_t tmp_23 = 0.053341239535745266;
      real_t tmp_24 = 0.0099888641910932524*Scalar_Variable_Coefficient_3D_4_0*tmp_13;
      real_t tmp_25 = 0.43295349048135578;
      real_t tmp_26 = 0.011578327656272558*Scalar_Variable_Coefficient_3D_5_0*tmp_13;
      real_t tmp_27 = 0.53800720391618573;
      real_t tmp_28 = 0.012693785874259723*Scalar_Variable_Coefficient_3D_6_0*tmp_13;
      real_t tmp_29 = 0.008991260093335729;
      real_t tmp_30 = 0.013237780011337548*Scalar_Variable_Coefficient_3D_7_0*tmp_13;
      real_t tmp_31 = 0.10660417256199362;
      real_t tmp_32 = 0.017744672359248346*Scalar_Variable_Coefficient_3D_8_0*tmp_13;
      real_t tmp_33 = 0.32923295974264682;
      real_t tmp_34 = 0.018372372071416277*Scalar_Variable_Coefficient_3D_9_0*tmp_13;
      real_t tmp_35 = tmp_0*tmp_14;
      real_t tmp_36 = tmp_15*tmp_16;
      real_t tmp_37 = tmp_17*tmp_18;
      real_t tmp_38 = tmp_19*tmp_20;
      real_t tmp_39 = tmp_21*tmp_22;
      real_t tmp_40 = tmp_23*tmp_24;
      real_t tmp_41 = tmp_25*tmp_26;
      real_t tmp_42 = tmp_27*tmp_28;
      real_t tmp_43 = tmp_29*tmp_30;
      real_t tmp_44 = tmp_31*tmp_32;
      real_t tmp_45 = tmp_33*tmp_34;
      real_t tmp_46 = 0.040490506727590428*tmp_35 + 0.43271023904776862*tmp_36 + 0.75250850700965499*tmp_37 + 0.24027666492807259*tmp_38 + 0.067223294893383398*tmp_39 + 0.41926631387951302*tmp_40 + 0.45076587609127677*tmp_41 + 0.12941137378891041*tmp_42 + 0.1215419913339278*tmp_43 + 0.097204644587583267*tmp_44 + 0.029569495206479609*tmp_45;
      real_t tmp_47 = 0.01356070187980288*tmp_35 + 0.35382323920929709*tmp_36 + 0.068099370938206658*tmp_37 + 0.12680172591539199*tmp_38 + 0.035183929773598722*tmp_39 + 0.047781435559086663*tmp_40 + 0.059456616299433829*tmp_41 + 0.33019041483746447*tmp_42 + 0.30649398842969028*tmp_43 + 0.68439041545304002*tmp_44 + 0.31790356021339461*tmp_45;
      real_t tmp_48 = 0.77125473269537614*tmp_35 + 0.1096224053319412*tmp_36 + 0.097987203649279112*tmp_37 + 0.32847320672203839*tmp_38 + 0.15636389323939531*tmp_39 + 0.47961101102565512*tmp_40 + 0.056824017127933668*tmp_41 + 0.0023910074574393651*tmp_42 + 0.56297276014304609*tmp_43 + 0.11180076739738309*tmp_44 + 0.32329398483747901*tmp_45;
      real_t tmp_49 = 0.040490506727590428*tmp_14;
      real_t tmp_50 = 0.43271023904776862*tmp_16;
      real_t tmp_51 = 0.75250850700965499*tmp_18;
      real_t tmp_52 = 0.24027666492807259*tmp_20;
      real_t tmp_53 = 0.067223294893383398*tmp_22;
      real_t tmp_54 = 0.41926631387951302*tmp_24;
      real_t tmp_55 = 0.45076587609127677*tmp_26;
      real_t tmp_56 = 0.12941137378891041*tmp_28;
      real_t tmp_57 = 0.1215419913339278*tmp_30;
      real_t tmp_58 = 0.097204644587583267*tmp_32;
      real_t tmp_59 = 0.029569495206479609*tmp_34;
      real_t tmp_60 = 0.01356070187980288*tmp_49 + 0.35382323920929709*tmp_50 + 0.068099370938206658*tmp_51 + 0.12680172591539199*tmp_52 + 0.035183929773598722*tmp_53 + 0.047781435559086663*tmp_54 + 0.059456616299433829*tmp_55 + 0.33019041483746447*tmp_56 + 0.30649398842969028*tmp_57 + 0.68439041545304002*tmp_58 + 0.31790356021339461*tmp_59;
      real_t tmp_61 = 0.77125473269537614*tmp_49 + 0.1096224053319412*tmp_50 + 0.097987203649279112*tmp_51 + 0.32847320672203839*tmp_52 + 0.15636389323939531*tmp_53 + 0.47961101102565512*tmp_54 + 0.056824017127933668*tmp_55 + 0.0023910074574393651*tmp_56 + 0.56297276014304609*tmp_57 + 0.11180076739738309*tmp_58 + 0.32329398483747901*tmp_59;
      real_t tmp_62 = 0.010458755503469055*tmp_14 + 0.03878695454446196*tmp_16 + 0.0066728669285098553*tmp_18 + 0.041650969529317808*tmp_20 + 0.0055014962388613723*tmp_22 + 0.022916502616750743*tmp_24 + 0.0033785637829680079*tmp_26 + 0.00078948774425137511*tmp_28 + 0.17254776663351357*tmp_30 + 0.076515373647063706*tmp_32 + 0.10277630877540979*tmp_34;
      real_t a_0_0 = (tmp_0*tmp_0)*tmp_14 + (tmp_15*tmp_15)*tmp_16 + (tmp_17*tmp_17)*tmp_18 + (tmp_19*tmp_19)*tmp_20 + (tmp_21*tmp_21)*tmp_22 + (tmp_23*tmp_23)*tmp_24 + (tmp_25*tmp_25)*tmp_26 + (tmp_27*tmp_27)*tmp_28 + (tmp_29*tmp_29)*tmp_30 + (tmp_31*tmp_31)*tmp_32 + (tmp_33*tmp_33)*tmp_34;
      real_t a_0_1 = tmp_46;
      real_t a_0_2 = tmp_47;
      real_t a_0_3 = tmp_48;
      real_t a_1_0 = tmp_46;
      real_t a_1_1 = 0.0016394811350570458*tmp_14 + 0.18723815097677707*tmp_16 + 0.56626905312190001*tmp_18 + 0.057732875708957271*tmp_20 + 0.0045189713763227864*tmp_22 + 0.17578424195411432*tmp_24 + 0.2031898750483363*tmp_26 + 0.016747303665933088*tmp_28 + 0.014772455657416582*tmp_30 + 0.0094487429293983807*tmp_32 + 0.00087435504676602058*tmp_34;
      real_t a_1_2 = tmp_60;
      real_t a_1_3 = tmp_61;
      real_t a_2_0 = tmp_47;
      real_t a_2_1 = tmp_60;
      real_t a_2_2 = 0.00018389263547288935*tmp_14 + 0.12519088460455946*tmp_16 + 0.0046375243221794659*tmp_18 + 0.016078677695122192*tmp_20 + 0.0012379089143135266*tmp_22 + 0.0022830655840871514*tmp_24 + 0.0035350892217781006*tmp_26 + 0.10902571005053688*tmp_28 + 0.093938564943539124*tmp_30 + 0.46839024076398472*tmp_32 + 0.10106267359635142*tmp_34;
      real_t a_2_3 = tmp_62;
      real_t a_3_0 = tmp_48;
      real_t a_3_1 = tmp_61;
      real_t a_3_2 = tmp_62;
      real_t a_3_3 = 0.59483386270501615*tmp_14 + 0.012017071750760411*tmp_16 + 0.0096014920790052985*tmp_18 + 0.10789464753425897*tmp_20 + 0.024449667108981017*tmp_22 + 0.23002672189705109*tmp_24 + 0.003228968922555699*tmp_26 + 5.7169166615306573e-6*tmp_28 + 0.31693832866307969*tmp_30 + 0.012499411590643758*tmp_32 + 0.10451900063209611*tmp_34;
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

   void p1_k_mass_affine_q4::integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 4 >& elMat ) const
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
      real_t Scalar_Variable_Coefficient_3D_0_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_1_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_2_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_3_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_4_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_5_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_6_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_7_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_8_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_9_0 = 0;
      real_t Scalar_Variable_Coefficient_3D_10_0 = 0;
      Scalar_Variable_Coefficient_3D( 0.17469405869723054*p_affine_0_0 + 0.040490506727590428*p_affine_1_0 + 0.01356070187980288*p_affine_2_0 + 0.77125473269537614*p_affine_3_0, 0.17469405869723054*p_affine_0_1 + 0.040490506727590428*p_affine_1_1 + 0.01356070187980288*p_affine_2_1 + 0.77125473269537614*p_affine_3_1, 0.17469405869723054*p_affine_0_2 + 0.040490506727590428*p_affine_1_2 + 0.01356070187980288*p_affine_2_2 + 0.77125473269537614*p_affine_3_2, &Scalar_Variable_Coefficient_3D_0_0 );
      Scalar_Variable_Coefficient_3D( 0.081404918402859225*p_affine_0_0 + 0.75250850700965499*p_affine_1_0 + 0.068099370938206658*p_affine_2_0 + 0.097987203649279112*p_affine_3_0, 0.081404918402859225*p_affine_0_1 + 0.75250850700965499*p_affine_1_1 + 0.068099370938206658*p_affine_2_1 + 0.097987203649279112*p_affine_3_1, 0.081404918402859225*p_affine_0_2 + 0.75250850700965499*p_affine_1_2 + 0.068099370938206658*p_affine_2_2 + 0.097987203649279112*p_affine_3_2, &Scalar_Variable_Coefficient_3D_1_0 );
      Scalar_Variable_Coefficient_3D( 0.30444840243449711*p_affine_0_0 + 0.24027666492807259*p_affine_1_0 + 0.12680172591539199*p_affine_2_0 + 0.32847320672203839*p_affine_3_0, 0.30444840243449711*p_affine_0_1 + 0.24027666492807259*p_affine_1_1 + 0.12680172591539199*p_affine_2_1 + 0.32847320672203839*p_affine_3_1, 0.30444840243449711*p_affine_0_2 + 0.24027666492807259*p_affine_1_2 + 0.12680172591539199*p_affine_2_2 + 0.32847320672203839*p_affine_3_2, &Scalar_Variable_Coefficient_3D_2_0 );
      Scalar_Variable_Coefficient_3D( 0.74122888209362259*p_affine_0_0 + 0.067223294893383398*p_affine_1_0 + 0.035183929773598722*p_affine_2_0 + 0.15636389323939531*p_affine_3_0, 0.74122888209362259*p_affine_0_1 + 0.067223294893383398*p_affine_1_1 + 0.035183929773598722*p_affine_2_1 + 0.15636389323939531*p_affine_3_1, 0.74122888209362259*p_affine_0_2 + 0.067223294893383398*p_affine_1_2 + 0.035183929773598722*p_affine_2_2 + 0.15636389323939531*p_affine_3_2, &Scalar_Variable_Coefficient_3D_3_0 );
      Scalar_Variable_Coefficient_3D( 0.053341239535745266*p_affine_0_0 + 0.41926631387951302*p_affine_1_0 + 0.047781435559086663*p_affine_2_0 + 0.47961101102565512*p_affine_3_0, 0.053341239535745266*p_affine_0_1 + 0.41926631387951302*p_affine_1_1 + 0.047781435559086663*p_affine_2_1 + 0.47961101102565512*p_affine_3_1, 0.053341239535745266*p_affine_0_2 + 0.41926631387951302*p_affine_1_2 + 0.047781435559086663*p_affine_2_2 + 0.47961101102565512*p_affine_3_2, &Scalar_Variable_Coefficient_3D_4_0 );
      Scalar_Variable_Coefficient_3D( 0.43295349048135578*p_affine_0_0 + 0.45076587609127677*p_affine_1_0 + 0.059456616299433829*p_affine_2_0 + 0.056824017127933668*p_affine_3_0, 0.43295349048135578*p_affine_0_1 + 0.45076587609127677*p_affine_1_1 + 0.059456616299433829*p_affine_2_1 + 0.056824017127933668*p_affine_3_1, 0.43295349048135578*p_affine_0_2 + 0.45076587609127677*p_affine_1_2 + 0.059456616299433829*p_affine_2_2 + 0.056824017127933668*p_affine_3_2, &Scalar_Variable_Coefficient_3D_5_0 );
      Scalar_Variable_Coefficient_3D( 0.53800720391618573*p_affine_0_0 + 0.12941137378891041*p_affine_1_0 + 0.33019041483746447*p_affine_2_0 + 0.0023910074574393651*p_affine_3_0, 0.53800720391618573*p_affine_0_1 + 0.12941137378891041*p_affine_1_1 + 0.33019041483746447*p_affine_2_1 + 0.0023910074574393651*p_affine_3_1, 0.53800720391618573*p_affine_0_2 + 0.12941137378891041*p_affine_1_2 + 0.33019041483746447*p_affine_2_2 + 0.0023910074574393651*p_affine_3_2, &Scalar_Variable_Coefficient_3D_6_0 );
      Scalar_Variable_Coefficient_3D( 0.008991260093335729*p_affine_0_0 + 0.1215419913339278*p_affine_1_0 + 0.30649398842969028*p_affine_2_0 + 0.56297276014304609*p_affine_3_0, 0.008991260093335729*p_affine_0_1 + 0.1215419913339278*p_affine_1_1 + 0.30649398842969028*p_affine_2_1 + 0.56297276014304609*p_affine_3_1, 0.008991260093335729*p_affine_0_2 + 0.1215419913339278*p_affine_1_2 + 0.30649398842969028*p_affine_2_2 + 0.56297276014304609*p_affine_3_2, &Scalar_Variable_Coefficient_3D_7_0 );
      Scalar_Variable_Coefficient_3D( 0.10660417256199362*p_affine_0_0 + 0.097204644587583267*p_affine_1_0 + 0.68439041545304002*p_affine_2_0 + 0.11180076739738309*p_affine_3_0, 0.10660417256199362*p_affine_0_1 + 0.097204644587583267*p_affine_1_1 + 0.68439041545304002*p_affine_2_1 + 0.11180076739738309*p_affine_3_1, 0.10660417256199362*p_affine_0_2 + 0.097204644587583267*p_affine_1_2 + 0.68439041545304002*p_affine_2_2 + 0.11180076739738309*p_affine_3_2, &Scalar_Variable_Coefficient_3D_8_0 );
      Scalar_Variable_Coefficient_3D( 0.32923295974264682*p_affine_0_0 + 0.029569495206479609*p_affine_1_0 + 0.31790356021339461*p_affine_2_0 + 0.32329398483747901*p_affine_3_0, 0.32923295974264682*p_affine_0_1 + 0.029569495206479609*p_affine_1_1 + 0.31790356021339461*p_affine_2_1 + 0.32329398483747901*p_affine_3_1, 0.32923295974264682*p_affine_0_2 + 0.029569495206479609*p_affine_1_2 + 0.31790356021339461*p_affine_2_2 + 0.32329398483747901*p_affine_3_2, &Scalar_Variable_Coefficient_3D_9_0 );
      Scalar_Variable_Coefficient_3D( 0.10384411641099309*p_affine_0_0 + 0.43271023904776862*p_affine_1_0 + 0.35382323920929709*p_affine_2_0 + 0.1096224053319412*p_affine_3_0, 0.10384411641099309*p_affine_0_1 + 0.43271023904776862*p_affine_1_1 + 0.35382323920929709*p_affine_2_1 + 0.1096224053319412*p_affine_3_1, 0.10384411641099309*p_affine_0_2 + 0.43271023904776862*p_affine_1_2 + 0.35382323920929709*p_affine_2_2 + 0.1096224053319412*p_affine_3_2, &Scalar_Variable_Coefficient_3D_10_0 );
      real_t tmp_0 = 0.17469405869723054;
      real_t tmp_1 = p_affine_0_0*p_affine_1_1;
      real_t tmp_2 = p_affine_0_0*p_affine_1_2;
      real_t tmp_3 = p_affine_2_1*p_affine_3_2;
      real_t tmp_4 = p_affine_0_1*p_affine_1_0;
      real_t tmp_5 = p_affine_0_1*p_affine_1_2;
      real_t tmp_6 = p_affine_2_2*p_affine_3_0;
      real_t tmp_7 = p_affine_0_2*p_affine_1_0;
      real_t tmp_8 = p_affine_0_2*p_affine_1_1;
      real_t tmp_9 = p_affine_2_0*p_affine_3_1;
      real_t tmp_10 = p_affine_2_2*p_affine_3_1;
      real_t tmp_11 = p_affine_2_0*p_affine_3_2;
      real_t tmp_12 = p_affine_2_1*p_affine_3_0;
      real_t tmp_13 = std::abs(p_affine_0_0*tmp_10 - p_affine_0_0*tmp_3 + p_affine_0_1*tmp_11 - p_affine_0_1*tmp_6 + p_affine_0_2*tmp_12 - p_affine_0_2*tmp_9 - p_affine_1_0*tmp_10 + p_affine_1_0*tmp_3 - p_affine_1_1*tmp_11 + p_affine_1_1*tmp_6 - p_affine_1_2*tmp_12 + p_affine_1_2*tmp_9 - p_affine_2_0*tmp_5 + p_affine_2_0*tmp_8 + p_affine_2_1*tmp_2 - p_affine_2_1*tmp_7 - p_affine_2_2*tmp_1 + p_affine_2_2*tmp_4 + p_affine_3_0*tmp_5 - p_affine_3_0*tmp_8 - p_affine_3_1*tmp_2 + p_affine_3_1*tmp_7 + p_affine_3_2*tmp_1 - p_affine_3_2*tmp_4);
      real_t tmp_14 = 0.006541848487473325*Scalar_Variable_Coefficient_3D_0_0*tmp_13;
      real_t tmp_15 = 0.10384411641099309;
      real_t tmp_16 = 0.025829352669374347*Scalar_Variable_Coefficient_3D_10_0*tmp_13;
      real_t tmp_17 = 0.081404918402859225;
      real_t tmp_18 = 0.0092122281926561474*Scalar_Variable_Coefficient_3D_1_0*tmp_13;
      real_t tmp_19 = 0.30444840243449711;
      real_t tmp_20 = 0.032235135341605742*Scalar_Variable_Coefficient_3D_2_0*tmp_13;
      real_t tmp_21 = 0.74122888209362259;
      real_t tmp_22 = 0.0092322998119293929*Scalar_Variable_Coefficient_3D_3_0*tmp_13;
      real_t tmp_23 = 0.053341239535745266;
      real_t tmp_24 = 0.0099888641910932524*Scalar_Variable_Coefficient_3D_4_0*tmp_13;
      real_t tmp_25 = 0.43295349048135578;
      real_t tmp_26 = 0.011578327656272558*Scalar_Variable_Coefficient_3D_5_0*tmp_13;
      real_t tmp_27 = 0.53800720391618573;
      real_t tmp_28 = 0.012693785874259723*Scalar_Variable_Coefficient_3D_6_0*tmp_13;
      real_t tmp_29 = 0.008991260093335729;
      real_t tmp_30 = 0.013237780011337548*Scalar_Variable_Coefficient_3D_7_0*tmp_13;
      real_t tmp_31 = 0.10660417256199362;
      real_t tmp_32 = 0.017744672359248346*Scalar_Variable_Coefficient_3D_8_0*tmp_13;
      real_t tmp_33 = 0.32923295974264682;
      real_t tmp_34 = 0.018372372071416277*Scalar_Variable_Coefficient_3D_9_0*tmp_13;
      real_t tmp_35 = tmp_0*tmp_14;
      real_t tmp_36 = tmp_15*tmp_16;
      real_t tmp_37 = tmp_17*tmp_18;
      real_t tmp_38 = tmp_19*tmp_20;
      real_t tmp_39 = tmp_21*tmp_22;
      real_t tmp_40 = tmp_23*tmp_24;
      real_t tmp_41 = tmp_25*tmp_26;
      real_t tmp_42 = tmp_27*tmp_28;
      real_t tmp_43 = tmp_29*tmp_30;
      real_t tmp_44 = tmp_31*tmp_32;
      real_t tmp_45 = tmp_33*tmp_34;
      real_t a_0_0 = (tmp_0*tmp_0)*tmp_14 + (tmp_15*tmp_15)*tmp_16 + (tmp_17*tmp_17)*tmp_18 + (tmp_19*tmp_19)*tmp_20 + (tmp_21*tmp_21)*tmp_22 + (tmp_23*tmp_23)*tmp_24 + (tmp_25*tmp_25)*tmp_26 + (tmp_27*tmp_27)*tmp_28 + (tmp_29*tmp_29)*tmp_30 + (tmp_31*tmp_31)*tmp_32 + (tmp_33*tmp_33)*tmp_34;
      real_t a_0_1 = 0.040490506727590428*tmp_35 + 0.43271023904776862*tmp_36 + 0.75250850700965499*tmp_37 + 0.24027666492807259*tmp_38 + 0.067223294893383398*tmp_39 + 0.41926631387951302*tmp_40 + 0.45076587609127677*tmp_41 + 0.12941137378891041*tmp_42 + 0.1215419913339278*tmp_43 + 0.097204644587583267*tmp_44 + 0.029569495206479609*tmp_45;
      real_t a_0_2 = 0.01356070187980288*tmp_35 + 0.35382323920929709*tmp_36 + 0.068099370938206658*tmp_37 + 0.12680172591539199*tmp_38 + 0.035183929773598722*tmp_39 + 0.047781435559086663*tmp_40 + 0.059456616299433829*tmp_41 + 0.33019041483746447*tmp_42 + 0.30649398842969028*tmp_43 + 0.68439041545304002*tmp_44 + 0.31790356021339461*tmp_45;
      real_t a_0_3 = 0.77125473269537614*tmp_35 + 0.1096224053319412*tmp_36 + 0.097987203649279112*tmp_37 + 0.32847320672203839*tmp_38 + 0.15636389323939531*tmp_39 + 0.47961101102565512*tmp_40 + 0.056824017127933668*tmp_41 + 0.0023910074574393651*tmp_42 + 0.56297276014304609*tmp_43 + 0.11180076739738309*tmp_44 + 0.32329398483747901*tmp_45;
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
      (elMat(0, 3)) = a_0_3;
   }

   void p1_k_mass_affine_q4::Scalar_Variable_Coefficient_2D( real_t in_0, real_t in_1, real_t * out_0 ) const
   {
      *out_0 = callback2D( Point3D( {in_0, in_1, 0} ) );
   }

   void p1_k_mass_affine_q4::Scalar_Variable_Coefficient_3D( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const
   {
      *out_0 = callback3D( Point3D( {in_0, in_1, in_2} ) );
   }

} // namespace forms
} // namespace hyteg
