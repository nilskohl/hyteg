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

#include "p2_to_p1_div_2_affine_q2.hpp"

namespace hyteg {
namespace forms {

   void p2_to_p1_div_2_affine_q2::integrateAll( const std::array< Point3D, 3 >& , Matrix< real_t, 3, 6 >&  ) const
   {
      
   }

   void p2_to_p1_div_2_affine_q2::integrateRow0( const std::array< Point3D, 3 >& , Matrix< real_t, 1, 6 >&  ) const
   {
      
   }

   void p2_to_p1_div_2_affine_q2::integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 4, 10 >& elMat ) const
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
      real_t tmp_0 = -p_affine_0_0;
      real_t tmp_1 = p_affine_1_0 + tmp_0;
      real_t tmp_2 = -p_affine_0_1;
      real_t tmp_3 = p_affine_2_1 + tmp_2;
      real_t tmp_4 = tmp_1*tmp_3;
      real_t tmp_5 = p_affine_2_0 + tmp_0;
      real_t tmp_6 = p_affine_1_1 + tmp_2;
      real_t tmp_7 = tmp_5*tmp_6;
      real_t tmp_8 = tmp_4 - tmp_7;
      real_t tmp_9 = -p_affine_0_2;
      real_t tmp_10 = p_affine_3_2 + tmp_9;
      real_t tmp_11 = p_affine_1_2 + tmp_9;
      real_t tmp_12 = p_affine_3_1 + tmp_2;
      real_t tmp_13 = tmp_12*tmp_5;
      real_t tmp_14 = p_affine_2_2 + tmp_9;
      real_t tmp_15 = p_affine_3_0 + tmp_0;
      real_t tmp_16 = tmp_15*tmp_6;
      real_t tmp_17 = tmp_1*tmp_12;
      real_t tmp_18 = tmp_15*tmp_3;
      real_t tmp_19 = 1.0 / (tmp_10*tmp_4 - tmp_10*tmp_7 + tmp_11*tmp_13 - tmp_11*tmp_18 + tmp_14*tmp_16 - tmp_14*tmp_17);
      real_t tmp_20 = 0.55278640450004235;
      real_t tmp_21 = 0.55278640450004235;
      real_t tmp_22 = 2.3416407864998732;
      real_t tmp_23 = tmp_19*(tmp_20 + tmp_21 + tmp_22 - 3.0);
      real_t tmp_24 = tmp_16 - tmp_17;
      real_t tmp_25 = tmp_13 - tmp_18;
      real_t tmp_26 = -tmp_23*tmp_24 - tmp_23*tmp_25 - tmp_23*tmp_8;
      real_t tmp_27 = p_affine_0_0*p_affine_1_1;
      real_t tmp_28 = p_affine_0_0*p_affine_1_2;
      real_t tmp_29 = p_affine_2_1*p_affine_3_2;
      real_t tmp_30 = p_affine_0_1*p_affine_1_0;
      real_t tmp_31 = p_affine_0_1*p_affine_1_2;
      real_t tmp_32 = p_affine_2_2*p_affine_3_0;
      real_t tmp_33 = p_affine_0_2*p_affine_1_0;
      real_t tmp_34 = p_affine_0_2*p_affine_1_1;
      real_t tmp_35 = p_affine_2_0*p_affine_3_1;
      real_t tmp_36 = p_affine_2_2*p_affine_3_1;
      real_t tmp_37 = p_affine_2_0*p_affine_3_2;
      real_t tmp_38 = p_affine_2_1*p_affine_3_0;
      real_t tmp_39 = std::abs(p_affine_0_0*tmp_29 - p_affine_0_0*tmp_36 + p_affine_0_1*tmp_32 - p_affine_0_1*tmp_37 + p_affine_0_2*tmp_35 - p_affine_0_2*tmp_38 - p_affine_1_0*tmp_29 + p_affine_1_0*tmp_36 - p_affine_1_1*tmp_32 + p_affine_1_1*tmp_37 - p_affine_1_2*tmp_35 + p_affine_1_2*tmp_38 + p_affine_2_0*tmp_31 - p_affine_2_0*tmp_34 - p_affine_2_1*tmp_28 + p_affine_2_1*tmp_33 + p_affine_2_2*tmp_27 - p_affine_2_2*tmp_30 - p_affine_3_0*tmp_31 + p_affine_3_0*tmp_34 + p_affine_3_1*tmp_28 - p_affine_3_1*tmp_33 - p_affine_3_2*tmp_27 + p_affine_3_2*tmp_30);
      real_t tmp_40 = 0.041666666666666657*tmp_39;
      real_t tmp_41 = 0.13819660112501042*tmp_40;
      real_t tmp_42 = 0.55278640450004235;
      real_t tmp_43 = 2.3416407864998732;
      real_t tmp_44 = 0.55278640450004235;
      real_t tmp_45 = tmp_19*(tmp_42 + tmp_43 + tmp_44 - 3.0);
      real_t tmp_46 = -tmp_24*tmp_45 - tmp_25*tmp_45 - tmp_45*tmp_8;
      real_t tmp_47 = 0.041666666666666657*tmp_39;
      real_t tmp_48 = 0.13819660112501048*tmp_47;
      real_t tmp_49 = 2.3416407864998732;
      real_t tmp_50 = 0.55278640450004235;
      real_t tmp_51 = 0.55278640450004235;
      real_t tmp_52 = tmp_19*(tmp_49 + tmp_50 + tmp_51 - 3.0);
      real_t tmp_53 = -tmp_24*tmp_52 - tmp_25*tmp_52 - tmp_52*tmp_8;
      real_t tmp_54 = 0.041666666666666657*tmp_39;
      real_t tmp_55 = 0.13819660112501053*tmp_54;
      real_t tmp_56 = 0.55278640450004235;
      real_t tmp_57 = 0.55278640450004235;
      real_t tmp_58 = 0.55278640450004235;
      real_t tmp_59 = tmp_19*(tmp_56 + tmp_57 + tmp_58 - 3.0);
      real_t tmp_60 = -tmp_24*tmp_59 - tmp_25*tmp_59 - tmp_59*tmp_8;
      real_t tmp_61 = 0.041666666666666657*tmp_39;
      real_t tmp_62 = 0.58541019662496807*tmp_61;
      real_t tmp_63 = tmp_19*tmp_25;
      real_t tmp_64 = tmp_63*(tmp_20 - 1.0);
      real_t tmp_65 = tmp_63*(tmp_42 - 1.0);
      real_t tmp_66 = tmp_63*(tmp_49 - 1.0);
      real_t tmp_67 = tmp_63*(tmp_56 - 1.0);
      real_t tmp_68 = tmp_19*tmp_24;
      real_t tmp_69 = tmp_68*(tmp_21 - 1.0);
      real_t tmp_70 = tmp_68*(tmp_43 - 1.0);
      real_t tmp_71 = tmp_68*(tmp_50 - 1.0);
      real_t tmp_72 = tmp_68*(tmp_57 - 1.0);
      real_t tmp_73 = tmp_19*tmp_8;
      real_t tmp_74 = tmp_73*(tmp_22 - 1.0);
      real_t tmp_75 = tmp_73*(tmp_44 - 1.0);
      real_t tmp_76 = tmp_73*(tmp_51 - 1.0);
      real_t tmp_77 = tmp_73*(tmp_58 - 1.0);
      real_t tmp_78 = tmp_21*tmp_73;
      real_t tmp_79 = tmp_22*tmp_68;
      real_t tmp_80 = -tmp_78 - tmp_79;
      real_t tmp_81 = tmp_43*tmp_73;
      real_t tmp_82 = tmp_44*tmp_68;
      real_t tmp_83 = -tmp_81 - tmp_82;
      real_t tmp_84 = tmp_50*tmp_73;
      real_t tmp_85 = tmp_51*tmp_68;
      real_t tmp_86 = -tmp_84 - tmp_85;
      real_t tmp_87 = tmp_57*tmp_73;
      real_t tmp_88 = tmp_58*tmp_68;
      real_t tmp_89 = -tmp_87 - tmp_88;
      real_t tmp_90 = tmp_20*tmp_73;
      real_t tmp_91 = tmp_22*tmp_63;
      real_t tmp_92 = -tmp_90 - tmp_91;
      real_t tmp_93 = tmp_42*tmp_73;
      real_t tmp_94 = tmp_44*tmp_63;
      real_t tmp_95 = -tmp_93 - tmp_94;
      real_t tmp_96 = tmp_49*tmp_73;
      real_t tmp_97 = tmp_51*tmp_63;
      real_t tmp_98 = -tmp_96 - tmp_97;
      real_t tmp_99 = tmp_56*tmp_73;
      real_t tmp_100 = tmp_58*tmp_63;
      real_t tmp_101 = -tmp_100 - tmp_99;
      real_t tmp_102 = tmp_20*tmp_68;
      real_t tmp_103 = tmp_21*tmp_63;
      real_t tmp_104 = -tmp_102 - tmp_103;
      real_t tmp_105 = tmp_42*tmp_68;
      real_t tmp_106 = tmp_43*tmp_63;
      real_t tmp_107 = -tmp_105 - tmp_106;
      real_t tmp_108 = tmp_49*tmp_68;
      real_t tmp_109 = tmp_50*tmp_63;
      real_t tmp_110 = -tmp_108 - tmp_109;
      real_t tmp_111 = tmp_56*tmp_68;
      real_t tmp_112 = tmp_57*tmp_63;
      real_t tmp_113 = -tmp_111 - tmp_112;
      real_t tmp_114 = -tmp_21;
      real_t tmp_115 = 4.0 - tmp_20;
      real_t tmp_116 = -tmp_73*(tmp_114 + tmp_115 - 4.6832815729997463) + tmp_79 + tmp_91;
      real_t tmp_117 = -tmp_43;
      real_t tmp_118 = 4.0 - tmp_42;
      real_t tmp_119 = -tmp_73*(tmp_117 + tmp_118 - 1.1055728090000847) + tmp_82 + tmp_94;
      real_t tmp_120 = -tmp_50;
      real_t tmp_121 = 4.0 - tmp_49;
      real_t tmp_122 = -tmp_73*(tmp_120 + tmp_121 - 1.1055728090000847) + tmp_85 + tmp_97;
      real_t tmp_123 = -tmp_57;
      real_t tmp_124 = 4.0 - tmp_56;
      real_t tmp_125 = tmp_100 - tmp_73*(tmp_123 + tmp_124 - 1.1055728090000847) + tmp_88;
      real_t tmp_126 = -tmp_22;
      real_t tmp_127 = tmp_103 - tmp_68*(tmp_115 + tmp_126 - 1.1055728090000847) + tmp_78;
      real_t tmp_128 = -tmp_44;
      real_t tmp_129 = tmp_106 - tmp_68*(tmp_118 + tmp_128 - 4.6832815729997463) + tmp_81;
      real_t tmp_130 = -tmp_51;
      real_t tmp_131 = tmp_109 - tmp_68*(tmp_121 + tmp_130 - 1.1055728090000847) + tmp_84;
      real_t tmp_132 = -tmp_58;
      real_t tmp_133 = tmp_112 - tmp_68*(tmp_124 + tmp_132 - 1.1055728090000847) + tmp_87;
      real_t tmp_134 = tmp_102 - tmp_63*(tmp_114 + tmp_126 + 2.8944271909999153) + tmp_90;
      real_t tmp_135 = tmp_105 - tmp_63*(tmp_117 + tmp_128 + 2.8944271909999153) + tmp_93;
      real_t tmp_136 = tmp_108 - tmp_63*(tmp_120 + tmp_130 - 0.68328157299974634) + tmp_96;
      real_t tmp_137 = tmp_111 - tmp_63*(tmp_123 + tmp_132 + 2.8944271909999153) + tmp_99;
      real_t tmp_138 = 0.13819660112501059*tmp_40;
      real_t tmp_139 = 0.13819660112501059*tmp_47;
      real_t tmp_140 = 0.58541019662496829*tmp_54;
      real_t tmp_141 = 0.13819660112501059*tmp_61;
      real_t tmp_142 = 0.13819660112501059*tmp_40;
      real_t tmp_143 = 0.58541019662496829*tmp_47;
      real_t tmp_144 = 0.13819660112501059*tmp_54;
      real_t tmp_145 = 0.13819660112501059*tmp_61;
      real_t tmp_146 = 0.58541019662496829*tmp_40;
      real_t tmp_147 = 0.13819660112501059*tmp_47;
      real_t tmp_148 = 0.13819660112501059*tmp_54;
      real_t tmp_149 = 0.13819660112501059*tmp_61;
      real_t a_0_0 = tmp_26*tmp_41 + tmp_46*tmp_48 + tmp_53*tmp_55 + tmp_60*tmp_62;
      real_t a_0_1 = -tmp_41*tmp_64 - tmp_48*tmp_65 - tmp_55*tmp_66 - tmp_62*tmp_67;
      real_t a_0_2 = -tmp_41*tmp_69 - tmp_48*tmp_70 - tmp_55*tmp_71 - tmp_62*tmp_72;
      real_t a_0_3 = -tmp_41*tmp_74 - tmp_48*tmp_75 - tmp_55*tmp_76 - tmp_62*tmp_77;
      real_t a_0_4 = tmp_41*tmp_80 + tmp_48*tmp_83 + tmp_55*tmp_86 + tmp_62*tmp_89;
      real_t a_0_5 = tmp_101*tmp_62 + tmp_41*tmp_92 + tmp_48*tmp_95 + tmp_55*tmp_98;
      real_t a_0_6 = tmp_104*tmp_41 + tmp_107*tmp_48 + tmp_110*tmp_55 + tmp_113*tmp_62;
      real_t a_0_7 = tmp_116*tmp_41 + tmp_119*tmp_48 + tmp_122*tmp_55 + tmp_125*tmp_62;
      real_t a_0_8 = tmp_127*tmp_41 + tmp_129*tmp_48 + tmp_131*tmp_55 + tmp_133*tmp_62;
      real_t a_0_9 = tmp_134*tmp_41 + tmp_135*tmp_48 + tmp_136*tmp_55 + tmp_137*tmp_62;
      real_t a_1_0 = tmp_138*tmp_26 + tmp_139*tmp_46 + tmp_140*tmp_53 + tmp_141*tmp_60;
      real_t a_1_1 = -tmp_138*tmp_64 - tmp_139*tmp_65 - tmp_140*tmp_66 - tmp_141*tmp_67;
      real_t a_1_2 = -tmp_138*tmp_69 - tmp_139*tmp_70 - tmp_140*tmp_71 - tmp_141*tmp_72;
      real_t a_1_3 = -tmp_138*tmp_74 - tmp_139*tmp_75 - tmp_140*tmp_76 - tmp_141*tmp_77;
      real_t a_1_4 = tmp_138*tmp_80 + tmp_139*tmp_83 + tmp_140*tmp_86 + tmp_141*tmp_89;
      real_t a_1_5 = tmp_101*tmp_141 + tmp_138*tmp_92 + tmp_139*tmp_95 + tmp_140*tmp_98;
      real_t a_1_6 = tmp_104*tmp_138 + tmp_107*tmp_139 + tmp_110*tmp_140 + tmp_113*tmp_141;
      real_t a_1_7 = tmp_116*tmp_138 + tmp_119*tmp_139 + tmp_122*tmp_140 + tmp_125*tmp_141;
      real_t a_1_8 = tmp_127*tmp_138 + tmp_129*tmp_139 + tmp_131*tmp_140 + tmp_133*tmp_141;
      real_t a_1_9 = tmp_134*tmp_138 + tmp_135*tmp_139 + tmp_136*tmp_140 + tmp_137*tmp_141;
      real_t a_2_0 = tmp_142*tmp_26 + tmp_143*tmp_46 + tmp_144*tmp_53 + tmp_145*tmp_60;
      real_t a_2_1 = -tmp_142*tmp_64 - tmp_143*tmp_65 - tmp_144*tmp_66 - tmp_145*tmp_67;
      real_t a_2_2 = -tmp_142*tmp_69 - tmp_143*tmp_70 - tmp_144*tmp_71 - tmp_145*tmp_72;
      real_t a_2_3 = -tmp_142*tmp_74 - tmp_143*tmp_75 - tmp_144*tmp_76 - tmp_145*tmp_77;
      real_t a_2_4 = tmp_142*tmp_80 + tmp_143*tmp_83 + tmp_144*tmp_86 + tmp_145*tmp_89;
      real_t a_2_5 = tmp_101*tmp_145 + tmp_142*tmp_92 + tmp_143*tmp_95 + tmp_144*tmp_98;
      real_t a_2_6 = tmp_104*tmp_142 + tmp_107*tmp_143 + tmp_110*tmp_144 + tmp_113*tmp_145;
      real_t a_2_7 = tmp_116*tmp_142 + tmp_119*tmp_143 + tmp_122*tmp_144 + tmp_125*tmp_145;
      real_t a_2_8 = tmp_127*tmp_142 + tmp_129*tmp_143 + tmp_131*tmp_144 + tmp_133*tmp_145;
      real_t a_2_9 = tmp_134*tmp_142 + tmp_135*tmp_143 + tmp_136*tmp_144 + tmp_137*tmp_145;
      real_t a_3_0 = tmp_146*tmp_26 + tmp_147*tmp_46 + tmp_148*tmp_53 + tmp_149*tmp_60;
      real_t a_3_1 = -tmp_146*tmp_64 - tmp_147*tmp_65 - tmp_148*tmp_66 - tmp_149*tmp_67;
      real_t a_3_2 = -tmp_146*tmp_69 - tmp_147*tmp_70 - tmp_148*tmp_71 - tmp_149*tmp_72;
      real_t a_3_3 = -tmp_146*tmp_74 - tmp_147*tmp_75 - tmp_148*tmp_76 - tmp_149*tmp_77;
      real_t a_3_4 = tmp_146*tmp_80 + tmp_147*tmp_83 + tmp_148*tmp_86 + tmp_149*tmp_89;
      real_t a_3_5 = tmp_101*tmp_149 + tmp_146*tmp_92 + tmp_147*tmp_95 + tmp_148*tmp_98;
      real_t a_3_6 = tmp_104*tmp_146 + tmp_107*tmp_147 + tmp_110*tmp_148 + tmp_113*tmp_149;
      real_t a_3_7 = tmp_116*tmp_146 + tmp_119*tmp_147 + tmp_122*tmp_148 + tmp_125*tmp_149;
      real_t a_3_8 = tmp_127*tmp_146 + tmp_129*tmp_147 + tmp_131*tmp_148 + tmp_133*tmp_149;
      real_t a_3_9 = tmp_134*tmp_146 + tmp_135*tmp_147 + tmp_136*tmp_148 + tmp_137*tmp_149;
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
      (elMat(0, 3)) = a_0_3;
      (elMat(0, 4)) = a_0_4;
      (elMat(0, 5)) = a_0_5;
      (elMat(0, 6)) = a_0_6;
      (elMat(0, 7)) = a_0_7;
      (elMat(0, 8)) = a_0_8;
      (elMat(0, 9)) = a_0_9;
      (elMat(1, 0)) = a_1_0;
      (elMat(1, 1)) = a_1_1;
      (elMat(1, 2)) = a_1_2;
      (elMat(1, 3)) = a_1_3;
      (elMat(1, 4)) = a_1_4;
      (elMat(1, 5)) = a_1_5;
      (elMat(1, 6)) = a_1_6;
      (elMat(1, 7)) = a_1_7;
      (elMat(1, 8)) = a_1_8;
      (elMat(1, 9)) = a_1_9;
      (elMat(2, 0)) = a_2_0;
      (elMat(2, 1)) = a_2_1;
      (elMat(2, 2)) = a_2_2;
      (elMat(2, 3)) = a_2_3;
      (elMat(2, 4)) = a_2_4;
      (elMat(2, 5)) = a_2_5;
      (elMat(2, 6)) = a_2_6;
      (elMat(2, 7)) = a_2_7;
      (elMat(2, 8)) = a_2_8;
      (elMat(2, 9)) = a_2_9;
      (elMat(3, 0)) = a_3_0;
      (elMat(3, 1)) = a_3_1;
      (elMat(3, 2)) = a_3_2;
      (elMat(3, 3)) = a_3_3;
      (elMat(3, 4)) = a_3_4;
      (elMat(3, 5)) = a_3_5;
      (elMat(3, 6)) = a_3_6;
      (elMat(3, 7)) = a_3_7;
      (elMat(3, 8)) = a_3_8;
      (elMat(3, 9)) = a_3_9;
   }

   void p2_to_p1_div_2_affine_q2::integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const
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
      real_t tmp_0 = -p_affine_0_0;
      real_t tmp_1 = p_affine_1_0 + tmp_0;
      real_t tmp_2 = -p_affine_0_1;
      real_t tmp_3 = p_affine_2_1 + tmp_2;
      real_t tmp_4 = tmp_1*tmp_3;
      real_t tmp_5 = p_affine_2_0 + tmp_0;
      real_t tmp_6 = p_affine_1_1 + tmp_2;
      real_t tmp_7 = tmp_5*tmp_6;
      real_t tmp_8 = tmp_4 - tmp_7;
      real_t tmp_9 = -p_affine_0_2;
      real_t tmp_10 = p_affine_3_2 + tmp_9;
      real_t tmp_11 = p_affine_1_2 + tmp_9;
      real_t tmp_12 = p_affine_3_1 + tmp_2;
      real_t tmp_13 = tmp_12*tmp_5;
      real_t tmp_14 = p_affine_2_2 + tmp_9;
      real_t tmp_15 = p_affine_3_0 + tmp_0;
      real_t tmp_16 = tmp_15*tmp_6;
      real_t tmp_17 = tmp_1*tmp_12;
      real_t tmp_18 = tmp_15*tmp_3;
      real_t tmp_19 = 1.0 / (tmp_10*tmp_4 - tmp_10*tmp_7 + tmp_11*tmp_13 - tmp_11*tmp_18 + tmp_14*tmp_16 - tmp_14*tmp_17);
      real_t tmp_20 = 0.55278640450004235;
      real_t tmp_21 = 0.55278640450004235;
      real_t tmp_22 = 2.3416407864998732;
      real_t tmp_23 = tmp_19*(tmp_20 + tmp_21 + tmp_22 - 3.0);
      real_t tmp_24 = tmp_16 - tmp_17;
      real_t tmp_25 = tmp_13 - tmp_18;
      real_t tmp_26 = p_affine_0_0*p_affine_1_1;
      real_t tmp_27 = p_affine_0_0*p_affine_1_2;
      real_t tmp_28 = p_affine_2_1*p_affine_3_2;
      real_t tmp_29 = p_affine_0_1*p_affine_1_0;
      real_t tmp_30 = p_affine_0_1*p_affine_1_2;
      real_t tmp_31 = p_affine_2_2*p_affine_3_0;
      real_t tmp_32 = p_affine_0_2*p_affine_1_0;
      real_t tmp_33 = p_affine_0_2*p_affine_1_1;
      real_t tmp_34 = p_affine_2_0*p_affine_3_1;
      real_t tmp_35 = p_affine_2_2*p_affine_3_1;
      real_t tmp_36 = p_affine_2_0*p_affine_3_2;
      real_t tmp_37 = p_affine_2_1*p_affine_3_0;
      real_t tmp_38 = std::abs(p_affine_0_0*tmp_28 - p_affine_0_0*tmp_35 + p_affine_0_1*tmp_31 - p_affine_0_1*tmp_36 + p_affine_0_2*tmp_34 - p_affine_0_2*tmp_37 - p_affine_1_0*tmp_28 + p_affine_1_0*tmp_35 - p_affine_1_1*tmp_31 + p_affine_1_1*tmp_36 - p_affine_1_2*tmp_34 + p_affine_1_2*tmp_37 + p_affine_2_0*tmp_30 - p_affine_2_0*tmp_33 - p_affine_2_1*tmp_27 + p_affine_2_1*tmp_32 + p_affine_2_2*tmp_26 - p_affine_2_2*tmp_29 - p_affine_3_0*tmp_30 + p_affine_3_0*tmp_33 + p_affine_3_1*tmp_27 - p_affine_3_1*tmp_32 - p_affine_3_2*tmp_26 + p_affine_3_2*tmp_29);
      real_t tmp_39 = 0.0057581917135420997*tmp_38;
      real_t tmp_40 = 0.55278640450004235;
      real_t tmp_41 = 2.3416407864998732;
      real_t tmp_42 = 0.55278640450004235;
      real_t tmp_43 = tmp_19*(tmp_40 + tmp_41 + tmp_42 - 3.0);
      real_t tmp_44 = 0.0057581917135421023*tmp_38;
      real_t tmp_45 = 2.3416407864998732;
      real_t tmp_46 = 0.55278640450004235;
      real_t tmp_47 = 0.55278640450004235;
      real_t tmp_48 = tmp_19*(tmp_45 + tmp_46 + tmp_47 - 3.0);
      real_t tmp_49 = 0.0057581917135421041*tmp_38;
      real_t tmp_50 = 0.55278640450004235;
      real_t tmp_51 = 0.55278640450004235;
      real_t tmp_52 = 0.55278640450004235;
      real_t tmp_53 = tmp_19*(tmp_50 + tmp_51 + tmp_52 - 3.0);
      real_t tmp_54 = 0.024392091526040331*tmp_38;
      real_t tmp_55 = tmp_19*tmp_25;
      real_t tmp_56 = tmp_19*tmp_24;
      real_t tmp_57 = tmp_19*tmp_8;
      real_t tmp_58 = tmp_21*tmp_57;
      real_t tmp_59 = tmp_22*tmp_56;
      real_t tmp_60 = tmp_41*tmp_57;
      real_t tmp_61 = tmp_42*tmp_56;
      real_t tmp_62 = tmp_46*tmp_57;
      real_t tmp_63 = tmp_47*tmp_56;
      real_t tmp_64 = tmp_51*tmp_57;
      real_t tmp_65 = tmp_52*tmp_56;
      real_t tmp_66 = tmp_20*tmp_57;
      real_t tmp_67 = tmp_22*tmp_55;
      real_t tmp_68 = tmp_40*tmp_57;
      real_t tmp_69 = tmp_42*tmp_55;
      real_t tmp_70 = tmp_45*tmp_57;
      real_t tmp_71 = tmp_47*tmp_55;
      real_t tmp_72 = tmp_50*tmp_57;
      real_t tmp_73 = tmp_52*tmp_55;
      real_t tmp_74 = tmp_20*tmp_56;
      real_t tmp_75 = tmp_21*tmp_55;
      real_t tmp_76 = tmp_40*tmp_56;
      real_t tmp_77 = tmp_41*tmp_55;
      real_t tmp_78 = tmp_45*tmp_56;
      real_t tmp_79 = tmp_46*tmp_55;
      real_t tmp_80 = tmp_50*tmp_56;
      real_t tmp_81 = tmp_51*tmp_55;
      real_t tmp_82 = -tmp_21;
      real_t tmp_83 = 4.0 - tmp_20;
      real_t tmp_84 = -tmp_41;
      real_t tmp_85 = 4.0 - tmp_40;
      real_t tmp_86 = -tmp_46;
      real_t tmp_87 = 4.0 - tmp_45;
      real_t tmp_88 = -tmp_51;
      real_t tmp_89 = 4.0 - tmp_50;
      real_t tmp_90 = -tmp_22;
      real_t tmp_91 = -tmp_42;
      real_t tmp_92 = -tmp_47;
      real_t tmp_93 = -tmp_52;
      real_t a_0_0 = tmp_39*(-tmp_23*tmp_24 - tmp_23*tmp_25 - tmp_23*tmp_8) + tmp_44*(-tmp_24*tmp_43 - tmp_25*tmp_43 - tmp_43*tmp_8) + tmp_49*(-tmp_24*tmp_48 - tmp_25*tmp_48 - tmp_48*tmp_8) + tmp_54*(-tmp_24*tmp_53 - tmp_25*tmp_53 - tmp_53*tmp_8);
      real_t a_0_1 = -tmp_39*tmp_55*(tmp_20 - 1.0) - tmp_44*tmp_55*(tmp_40 - 1.0) - tmp_49*tmp_55*(tmp_45 - 1.0) - tmp_54*tmp_55*(tmp_50 - 1.0);
      real_t a_0_2 = -tmp_39*tmp_56*(tmp_21 - 1.0) - tmp_44*tmp_56*(tmp_41 - 1.0) - tmp_49*tmp_56*(tmp_46 - 1.0) - tmp_54*tmp_56*(tmp_51 - 1.0);
      real_t a_0_3 = -tmp_39*tmp_57*(tmp_22 - 1.0) - tmp_44*tmp_57*(tmp_42 - 1.0) - tmp_49*tmp_57*(tmp_47 - 1.0) - tmp_54*tmp_57*(tmp_52 - 1.0);
      real_t a_0_4 = tmp_39*(-tmp_58 - tmp_59) + tmp_44*(-tmp_60 - tmp_61) + tmp_49*(-tmp_62 - tmp_63) + tmp_54*(-tmp_64 - tmp_65);
      real_t a_0_5 = tmp_39*(-tmp_66 - tmp_67) + tmp_44*(-tmp_68 - tmp_69) + tmp_49*(-tmp_70 - tmp_71) + tmp_54*(-tmp_72 - tmp_73);
      real_t a_0_6 = tmp_39*(-tmp_74 - tmp_75) + tmp_44*(-tmp_76 - tmp_77) + tmp_49*(-tmp_78 - tmp_79) + tmp_54*(-tmp_80 - tmp_81);
      real_t a_0_7 = tmp_39*(-tmp_57*(tmp_82 + tmp_83 - 4.6832815729997463) + tmp_59 + tmp_67) + tmp_44*(-tmp_57*(tmp_84 + tmp_85 - 1.1055728090000847) + tmp_61 + tmp_69) + tmp_49*(-tmp_57*(tmp_86 + tmp_87 - 1.1055728090000847) + tmp_63 + tmp_71) + tmp_54*(-tmp_57*(tmp_88 + tmp_89 - 1.1055728090000847) + tmp_65 + tmp_73);
      real_t a_0_8 = tmp_39*(-tmp_56*(tmp_83 + tmp_90 - 1.1055728090000847) + tmp_58 + tmp_75) + tmp_44*(-tmp_56*(tmp_85 + tmp_91 - 4.6832815729997463) + tmp_60 + tmp_77) + tmp_49*(-tmp_56*(tmp_87 + tmp_92 - 1.1055728090000847) + tmp_62 + tmp_79) + tmp_54*(-tmp_56*(tmp_89 + tmp_93 - 1.1055728090000847) + tmp_64 + tmp_81);
      real_t a_0_9 = tmp_39*(-tmp_55*(tmp_82 + tmp_90 + 2.8944271909999153) + tmp_66 + tmp_74) + tmp_44*(-tmp_55*(tmp_84 + tmp_91 + 2.8944271909999153) + tmp_68 + tmp_76) + tmp_49*(-tmp_55*(tmp_86 + tmp_92 - 0.68328157299974634) + tmp_70 + tmp_78) + tmp_54*(-tmp_55*(tmp_88 + tmp_93 + 2.8944271909999153) + tmp_72 + tmp_80);
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
      (elMat(0, 3)) = a_0_3;
      (elMat(0, 4)) = a_0_4;
      (elMat(0, 5)) = a_0_5;
      (elMat(0, 6)) = a_0_6;
      (elMat(0, 7)) = a_0_7;
      (elMat(0, 8)) = a_0_8;
      (elMat(0, 9)) = a_0_9;
   }

} // namespace forms
} // namespace hyteg
