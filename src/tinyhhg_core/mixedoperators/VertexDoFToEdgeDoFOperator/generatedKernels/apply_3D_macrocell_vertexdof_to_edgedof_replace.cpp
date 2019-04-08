
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "GeneratedKernelsVertexToEdgeMacroCell3D.hpp"

namespace hhg {
namespace VertexDoFToEdgeDoF {
namespace generated {

static void apply_3D_macrocell_vertexdof_to_edgedof_replace_level_2(double * _data_edgeCellDst_X, double * _data_edgeCellDst_XY, double * _data_edgeCellDst_XYZ, double * _data_edgeCellDst_XZ, double * _data_edgeCellDst_Y, double * _data_edgeCellDst_YZ, double * _data_edgeCellDst_Z, double * _data_vertexCellSrc, std::map< hhg::edgedof::EdgeDoFOrientation, std::map< hhg::indexing::IndexIncrement, double > > v2eStencilMap)
{
   const double xi_105 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 0, 0, 1 }];
   const double xi_106 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 0, 1, 0 }];
   const double xi_107 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 0, 1, 1 }];
   const double xi_108 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 1, 0, 0 }];
   const double xi_109 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 1, 0, 1 }];
   const double xi_110 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 1, 1, 0 }];
   const double xi_133 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ -1, 1, 0 }];
   const double xi_134 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ -1, 1, 1 }];
   const double xi_135 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 0, 0 }];
   const double xi_136 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 0, 1 }];
   const double xi_137 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 1, 0 }];
   const double xi_138 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 1, 1 }];
   const double xi_139 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 1, 0, 0 }];
   const double xi_140 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 1, 0, 1 }];
   const double xi_165 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 0, 0, 0 }];
   const double xi_166 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 0, 0, 1 }];
   const double xi_167 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 0, 1, 0 }];
   const double xi_168 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 1, -1, 1 }];
   const double xi_169 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 1, 0, 0 }];
   const double xi_170 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 1, 0, 1 }];
   const double xi_281 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ -1, 0, 1 }];
   const double xi_282 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ -1, 1, 0 }];
   const double xi_283 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, -1, 1 }];
   const double xi_284 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, 0, 0 }];
   const double xi_285 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, 0, 1 }];
   const double xi_286 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, 1, 0 }];
   const double xi_287 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 1, -1, 1 }];
   const double xi_288 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 1, 0, 0 }];
   const double xi_213 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 0, 0 }];
   const double xi_214 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 0, 1 }];
   const double xi_215 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 1, -1 }];
   const double xi_216 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 1, 0 }];
   const double xi_217 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 0, 0 }];
   const double xi_218 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 0, 1 }];
   const double xi_219 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 1, -1 }];
   const double xi_220 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 1, 0 }];
   const double xi_341 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ -1, 1, 0 }];
   const double xi_342 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 0, 0 }];
   const double xi_343 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 0, 1 }];
   const double xi_344 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 1, -1 }];
   const double xi_345 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 1, 0 }];
   const double xi_346 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 1, 0, 0 }];
   const double xi_401 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 0, 0 }];
   const double xi_402 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 0, 1 }];
   const double xi_403 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 1, -1 }];
   const double xi_404 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 1, 0 }];
   const double xi_405 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, -1, 0 }];
   const double xi_406 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, -1, 1 }];
   const double xi_407 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, 0, -1 }];
   const double xi_408 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, 0, 0 }];
   for (int ctr_3 = 0; ctr_3 < 1; ctr_3 += 1)
   {
      for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
      {
         // vertex 0
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_113 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_114 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_115 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_116 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_117 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_118 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_113 + xi_114 + xi_115 + xi_116 + xi_117 + xi_118;
         }
         // edge 0
         for (int ctr_1 = 1; ctr_1 < 3; ctr_1 += 1)
         {
            const double xi_149 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_150 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_151 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_152 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_153 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_154 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_155 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_156 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_157 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_158 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_159 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_160 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_161 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_162 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_149 + xi_150 + xi_151 + xi_152 + xi_153 + xi_154 + xi_155 + xi_156;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_157 + xi_158 + xi_159 + xi_160 + xi_161 + xi_162;
         }
      }
      for (int ctr_2 = 1; ctr_2 < -ctr_3 + 3; ctr_2 += 1)
      {
         // edge 1
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_179 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_180 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_181 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_182 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_183 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_184 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_185 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_186 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_187 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_188 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_189 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_190 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_179 + xi_180 + xi_181 + xi_182 + xi_183 + xi_184;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_185 + xi_186 + xi_187 + xi_188 + xi_189 + xi_190;
         }
         // face 0
         for (int ctr_1 = 1; ctr_1 < -ctr_2 + 3; ctr_1 += 1)
         {
            const double xi_311 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_312 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_313 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_314 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_315 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_316 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_317 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_318 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_319 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_320 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_321 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_322 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_323 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_324 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_325 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_326 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_327 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_328 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_329 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_330 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_331 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_332 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_333 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_334 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_335 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_336 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_337 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_338 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_311 + xi_312 + xi_313 + xi_314 + xi_315 + xi_316 + xi_317 + xi_318;
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_319 + xi_320 + xi_321 + xi_322 + xi_323 + xi_324;
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_325 + xi_326 + xi_327 + xi_328 + xi_329 + xi_330 + xi_331 + xi_332;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_333 + xi_334 + xi_335 + xi_336 + xi_337 + xi_338;
         }
         // edge 2
         for (int ctr_1 = -ctr_2 + 3; ctr_1 < -ctr_2 + 4; ctr_1 += 1)
         {
            const double xi_203 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_204 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_205 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_206 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_207 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_208 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_209 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_210 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_203 + xi_204 + xi_205 + xi_206 + xi_207 + xi_208 + xi_209 + xi_210;
         }
      }
   }
   for (int ctr_3 = 1; ctr_3 < 3; ctr_3 += 1)
   {
      for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
      {
         // edge 3
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_229 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_230 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_231 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_232 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_233 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_234 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_235 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_236 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_237 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_238 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_239 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_240 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_241 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_242 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_229 + xi_230 + xi_231 + xi_232 + xi_233 + xi_234 + xi_235 + xi_236;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_237 + xi_238 + xi_239 + xi_240 + xi_241 + xi_242;
         }
         // face 1
         for (int ctr_1 = 1; ctr_1 < -ctr_3 + 3; ctr_1 += 1)
         {
            const double xi_371 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_372 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_373 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_374 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_375 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_376 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_377 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_378 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_379 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_380 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_381 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_382 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_383 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_384 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_385 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_386 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_387 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_388 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_389 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_390 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_391 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_392 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_393 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_394 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_395 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_396 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_397 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_398 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_371 + xi_372 + xi_373 + xi_374 + xi_375 + xi_376;
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_377 + xi_378 + xi_379 + xi_380 + xi_381 + xi_382 + xi_383 + xi_384;
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_385 + xi_386 + xi_387 + xi_388 + xi_389 + xi_390 + xi_391 + xi_392;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_393 + xi_394 + xi_395 + xi_396 + xi_397 + xi_398;
         }
         // edge 4
         for (int ctr_1 = -ctr_3 + 3; ctr_1 < -ctr_3 + 4; ctr_1 += 1)
         {
            const double xi_253 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_254 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_255 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_256 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_257 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_258 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_253 + xi_254 + xi_255 + xi_256 + xi_257 + xi_258;
         }
      }
      for (int ctr_2 = 1; ctr_2 < -ctr_3 + 3; ctr_2 += 1)
      {
         // face 2
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_431 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_432 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_433 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_434 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_435 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_436 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_437 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 7) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_438 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_439 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_440 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_441 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_442 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_443 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_444 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_445 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_446 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_447 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_448 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_449 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_450 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_451 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_452 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_453 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_454 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_455 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_456 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_457 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_458 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_431 + xi_432 + xi_433 + xi_434 + xi_435 + xi_436 + xi_437 + xi_438;
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_439 + xi_440 + xi_441 + xi_442 + xi_443 + xi_444 + xi_445 + xi_446;
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_447 + xi_448 + xi_449 + xi_450 + xi_451 + xi_452;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_453 + xi_454 + xi_455 + xi_456 + xi_457 + xi_458;
         }
         // cell (inner)
         for (int ctr_1 = 1; ctr_1 < -ctr_2 - ctr_3 + 3; ctr_1 += 1)
         {
            const double xi_53 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_54 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_55 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_56 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_57 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_58 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_59 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 7) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_60 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_66 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_61 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_62 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_63 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_64 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_65 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_67 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_68 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_69 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_70 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_71 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_72 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_73 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_74 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_75 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_76 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_77 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_78 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_79 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_80 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_81 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_82 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_83 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_84 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_85 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_86 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_87 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_88 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_89 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_90 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_91 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_92 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_93 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_94 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_95 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_96 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_97 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_98 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_99 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 5) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_100 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_101 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_102 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57 + xi_58 + xi_59 + xi_60;
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_61 + xi_62 + xi_63 + xi_64 + xi_65 + xi_66;
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_67 + xi_68 + xi_69 + xi_70 + xi_71 + xi_72 + xi_73 + xi_74;
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_75 + xi_76 + xi_77 + xi_78 + xi_79 + xi_80 + xi_81 + xi_82;
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_83 + xi_84 + xi_85 + xi_86 + xi_87 + xi_88;
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_89 + xi_90 + xi_91 + xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + 4) + ((60) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 3)*(-ctr_3 + 4)*(-ctr_3 + 5)) / (6))] = xi_100 + xi_101 + xi_102 + xi_97 + xi_98 + xi_99;
         }
         // face 3
         for (int ctr_1 = -ctr_2 - ctr_3 + 3; ctr_1 < -ctr_2 - ctr_3 + 4; ctr_1 += 1)
         {
            const double xi_485 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_486 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_487 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_488 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_489 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_490 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_491 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 7) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_492 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_493 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_494 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_495 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_496 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_497 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_498 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_499 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) - 1];
            const double xi_500 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) - 1];
            const double xi_501 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_502 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_503 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_504 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_505 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_506 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_485 + xi_486 + xi_487 + xi_488 + xi_489 + xi_490 + xi_491 + xi_492;
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_493 + xi_494 + xi_495 + xi_496 + xi_497 + xi_498;
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_499 + xi_500 + xi_501 + xi_502 + xi_503 + xi_504 + xi_505 + xi_506;
         }
      }
      for (int ctr_2 = -ctr_3 + 3; ctr_2 < -ctr_3 + 4; ctr_2 += 1)
      {
         // edge 5
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_271 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_272 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))];
            const double xi_273 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 7) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6))];
            const double xi_274 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + 6) + ((210) / (6)) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6))];
            const double xi_275 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            const double xi_276 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + 5) + ((210) / (6)) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6)) + 1];
            const double xi_277 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 7) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 6)*(-ctr_3 + 7)*(-ctr_3 + 8)) / (6)) + 1];
            const double xi_278 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + 6) + ((210) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 5)*(-ctr_3 + 6)*(-ctr_3 + 7)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + 5) + ((120) / (6)) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + 4)*(-ctr_3 + 5)*(-ctr_3 + 6)) / (6))] = xi_271 + xi_272 + xi_273 + xi_274 + xi_275 + xi_276 + xi_277 + xi_278;
         }
      }
   }
   {
      
   }
}

static void apply_3D_macrocell_vertexdof_to_edgedof_replace_level_any(double * _data_edgeCellDst_X, double * _data_edgeCellDst_XY, double * _data_edgeCellDst_XYZ, double * _data_edgeCellDst_XZ, double * _data_edgeCellDst_Y, double * _data_edgeCellDst_YZ, double * _data_edgeCellDst_Z, double * _data_vertexCellSrc, int64_t level, std::map< hhg::edgedof::EdgeDoFOrientation, std::map< hhg::indexing::IndexIncrement, double > > v2eStencilMap)
{
   const double xi_105 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 0, 0, 1 }];
   const double xi_106 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 0, 1, 0 }];
   const double xi_107 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 0, 1, 1 }];
   const double xi_108 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 1, 0, 0 }];
   const double xi_109 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 1, 0, 1 }];
   const double xi_110 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XYZ][{ 1, 1, 0 }];
   const double xi_133 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ -1, 1, 0 }];
   const double xi_134 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ -1, 1, 1 }];
   const double xi_135 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 0, 0 }];
   const double xi_136 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 0, 1 }];
   const double xi_137 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 1, 0 }];
   const double xi_138 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 0, 1, 1 }];
   const double xi_139 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 1, 0, 0 }];
   const double xi_140 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::YZ][{ 1, 0, 1 }];
   const double xi_165 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 0, 0, 0 }];
   const double xi_166 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 0, 0, 1 }];
   const double xi_167 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 0, 1, 0 }];
   const double xi_168 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 1, -1, 1 }];
   const double xi_169 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 1, 0, 0 }];
   const double xi_170 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XZ][{ 1, 0, 1 }];
   const double xi_281 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ -1, 0, 1 }];
   const double xi_282 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ -1, 1, 0 }];
   const double xi_283 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, -1, 1 }];
   const double xi_284 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, 0, 0 }];
   const double xi_285 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, 0, 1 }];
   const double xi_286 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 0, 1, 0 }];
   const double xi_287 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 1, -1, 1 }];
   const double xi_288 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Z][{ 1, 0, 0 }];
   const double xi_213 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 0, 0 }];
   const double xi_214 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 0, 1 }];
   const double xi_215 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 1, -1 }];
   const double xi_216 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 0, 1, 0 }];
   const double xi_217 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 0, 0 }];
   const double xi_218 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 0, 1 }];
   const double xi_219 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 1, -1 }];
   const double xi_220 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::XY][{ 1, 1, 0 }];
   const double xi_341 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ -1, 1, 0 }];
   const double xi_342 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 0, 0 }];
   const double xi_343 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 0, 1 }];
   const double xi_344 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 1, -1 }];
   const double xi_345 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 0, 1, 0 }];
   const double xi_346 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::Y][{ 1, 0, 0 }];
   const double xi_401 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 0, 0 }];
   const double xi_402 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 0, 1 }];
   const double xi_403 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 1, -1 }];
   const double xi_404 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 0, 1, 0 }];
   const double xi_405 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, -1, 0 }];
   const double xi_406 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, -1, 1 }];
   const double xi_407 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, 0, -1 }];
   const double xi_408 = v2eStencilMap[hhg::edgedof::EdgeDoFOrientation::X][{ 1, 0, 0 }];
   for (int ctr_3 = 0; ctr_3 < 1; ctr_3 += 1)
   {
      for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
      {
         // vertex 0
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_113 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_114 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_115 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_116 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_117 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_118 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_113 + xi_114 + xi_115 + xi_116 + xi_117 + xi_118;
         }
         // edge 0
         for (int ctr_1 = 1; ctr_1 < (1 << (level)) - 1; ctr_1 += 1)
         {
            const double xi_149 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_150 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_151 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_152 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_153 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_154 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_155 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_156 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_157 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_158 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_159 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_160 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_161 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_162 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_149 + xi_150 + xi_151 + xi_152 + xi_153 + xi_154 + xi_155 + xi_156;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_157 + xi_158 + xi_159 + xi_160 + xi_161 + xi_162;
         }
      }
      for (int ctr_2 = 1; ctr_2 < -ctr_3 + (1 << (level)) - 1; ctr_2 += 1)
      {
         // edge 1
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_179 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_180 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_181 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_182 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_183 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_184 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_185 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_186 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_187 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_188 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_189 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_190 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_179 + xi_180 + xi_181 + xi_182 + xi_183 + xi_184;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_185 + xi_186 + xi_187 + xi_188 + xi_189 + xi_190;
         }
         // face 0
         for (int ctr_1 = 1; ctr_1 < -ctr_2 + (1 << (level)) - 1; ctr_1 += 1)
         {
            const double xi_311 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_312 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_313 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_314 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_315 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_316 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_317 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_318 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_319 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_320 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_321 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_322 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_323 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_324 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_325 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_326 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_327 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_328 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_329 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_330 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_331 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_332 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_333 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_334 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_335 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_336 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_337 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_338 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_311 + xi_312 + xi_313 + xi_314 + xi_315 + xi_316 + xi_317 + xi_318;
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_319 + xi_320 + xi_321 + xi_322 + xi_323 + xi_324;
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_325 + xi_326 + xi_327 + xi_328 + xi_329 + xi_330 + xi_331 + xi_332;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_333 + xi_334 + xi_335 + xi_336 + xi_337 + xi_338;
         }
         // edge 2
         for (int ctr_1 = -ctr_2 + (1 << (level)) - 1; ctr_1 < -ctr_2 + (1 << (level)); ctr_1 += 1)
         {
            const double xi_203 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_204 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_205 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_206 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_207 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_208 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_209 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_210 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_203 + xi_204 + xi_205 + xi_206 + xi_207 + xi_208 + xi_209 + xi_210;
         }
      }
   }
   for (int ctr_3 = 1; ctr_3 < (1 << (level)) - 1; ctr_3 += 1)
   {
      for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
      {
         // edge 3
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_229 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_230 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_231 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_232 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_233 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_234 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_235 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_236 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_237 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_238 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_239 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_240 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_241 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_242 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_229 + xi_230 + xi_231 + xi_232 + xi_233 + xi_234 + xi_235 + xi_236;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_237 + xi_238 + xi_239 + xi_240 + xi_241 + xi_242;
         }
         // face 1
         for (int ctr_1 = 1; ctr_1 < -ctr_3 + (1 << (level)) - 1; ctr_1 += 1)
         {
            const double xi_371 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_372 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_373 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_374 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_375 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_376 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_377 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_378 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_379 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_380 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_381 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_382 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_383 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_384 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_385 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_386 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_387 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_388 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_389 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_390 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_391 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_392 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_393 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_394 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_395 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_396 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_397 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_398 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_371 + xi_372 + xi_373 + xi_374 + xi_375 + xi_376;
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_377 + xi_378 + xi_379 + xi_380 + xi_381 + xi_382 + xi_383 + xi_384;
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_385 + xi_386 + xi_387 + xi_388 + xi_389 + xi_390 + xi_391 + xi_392;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_393 + xi_394 + xi_395 + xi_396 + xi_397 + xi_398;
         }
         // edge 4
         for (int ctr_1 = -ctr_3 + (1 << (level)) - 1; ctr_1 < -ctr_3 + (1 << (level)); ctr_1 += 1)
         {
            const double xi_253 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_254 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_255 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_256 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_257 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_258 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_253 + xi_254 + xi_255 + xi_256 + xi_257 + xi_258;
         }
      }
      for (int ctr_2 = 1; ctr_2 < -ctr_3 + (1 << (level)) - 1; ctr_2 += 1)
      {
         // face 2
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_431 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_432 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_433 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_434 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_435 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_436 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_437 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 3) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_438 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_439 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_440 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_441 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_442 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_443 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_444 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_445 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_446 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_447 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_448 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_449 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_450 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_451 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_452 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_453 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_454 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_455 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_456 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_457 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_458 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_431 + xi_432 + xi_433 + xi_434 + xi_435 + xi_436 + xi_437 + xi_438;
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_439 + xi_440 + xi_441 + xi_442 + xi_443 + xi_444 + xi_445 + xi_446;
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_447 + xi_448 + xi_449 + xi_450 + xi_451 + xi_452;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_453 + xi_454 + xi_455 + xi_456 + xi_457 + xi_458;
         }
         // cell (inner)
         for (int ctr_1 = 1; ctr_1 < -ctr_2 - ctr_3 + (1 << (level)) - 1; ctr_1 += 1)
         {
            const double xi_53 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_54 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_55 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_56 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_57 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_58 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_59 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 3) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_60 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_66 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_61 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_62 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_63 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_64 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_65 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_67 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_68 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_69 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_70 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_71 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_72 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_73 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_74 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_75 = xi_213*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_76 = xi_214*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_77 = xi_215*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_78 = xi_216*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_79 = xi_217*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_80 = xi_218*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_81 = xi_219*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_82 = xi_220*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_83 = xi_165*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_84 = xi_166*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_85 = xi_167*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_86 = xi_168*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_87 = xi_169*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_88 = xi_170*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_89 = xi_133*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_90 = xi_134*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_91 = xi_135*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_92 = xi_136*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_93 = xi_137*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_94 = xi_138*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_95 = xi_139*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_96 = xi_140*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_97 = xi_105*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_98 = xi_106*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_99 = xi_107*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_100 = xi_108*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_101 = xi_109*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_102 = xi_110*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57 + xi_58 + xi_59 + xi_60;
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_61 + xi_62 + xi_63 + xi_64 + xi_65 + xi_66;
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_67 + xi_68 + xi_69 + xi_70 + xi_71 + xi_72 + xi_73 + xi_74;
            _data_edgeCellDst_XY[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_75 + xi_76 + xi_77 + xi_78 + xi_79 + xi_80 + xi_81 + xi_82;
            _data_edgeCellDst_XZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_83 + xi_84 + xi_85 + xi_86 + xi_87 + xi_88;
            _data_edgeCellDst_YZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_89 + xi_90 + xi_91 + xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
            _data_edgeCellDst_XYZ[ctr_1 + ctr_2*(-ctr_3 + (1 << (level))) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) - 1)*(-ctr_3 + (1 << (level)) + 1)) / (6)) + ((((1 << (level)) - 1)*((1 << (level)) + 1)*(1 << (level))) / (6))] = xi_100 + xi_101 + xi_102 + xi_97 + xi_98 + xi_99;
         }
         // face 3
         for (int ctr_1 = -ctr_2 - ctr_3 + (1 << (level)) - 1; ctr_1 < -ctr_2 - ctr_3 + (1 << (level)); ctr_1 += 1)
         {
            const double xi_485 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_486 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_487 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_488 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_489 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_490 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_491 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 3) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_492 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_493 = xi_341*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_494 = xi_342*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_495 = xi_343*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_496 = xi_344*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_497 = xi_345*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_498 = xi_346*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_499 = xi_281*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_500 = xi_282*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_501 = xi_283*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_502 = xi_284*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_503 = xi_285*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_504 = xi_286*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_505 = xi_287*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_506 = xi_288*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_485 + xi_486 + xi_487 + xi_488 + xi_489 + xi_490 + xi_491 + xi_492;
            _data_edgeCellDst_Y[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_493 + xi_494 + xi_495 + xi_496 + xi_497 + xi_498;
            _data_edgeCellDst_Z[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_499 + xi_500 + xi_501 + xi_502 + xi_503 + xi_504 + xi_505 + xi_506;
         }
      }
      for (int ctr_2 = -ctr_3 + (1 << (level)) - 1; ctr_2 < -ctr_3 + (1 << (level)); ctr_2 += 1)
      {
         // edge 5
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            const double xi_271 = xi_401*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_272 = xi_402*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_273 = xi_403*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_274 = xi_404*_data_vertexCellSrc[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_275 = xi_405*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_276 = xi_406*_data_vertexCellSrc[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_277 = xi_407*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 3) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_278 = xi_408*_data_vertexCellSrc[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_edgeCellDst_X[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6))] = xi_271 + xi_272 + xi_273 + xi_274 + xi_275 + xi_276 + xi_277 + xi_278;
         }
      }
   }
   {
      
   }
}


void apply_3D_macrocell_vertexdof_to_edgedof_replace(double * _data_edgeCellDst_X, double * _data_edgeCellDst_XY, double * _data_edgeCellDst_XYZ, double * _data_edgeCellDst_XZ, double * _data_edgeCellDst_Y, double * _data_edgeCellDst_YZ, double * _data_edgeCellDst_Z, double * _data_vertexCellSrc, int64_t level, std::map< hhg::edgedof::EdgeDoFOrientation, std::map< hhg::indexing::IndexIncrement, double > > v2eStencilMap)
{
    switch( level )
    {
    case 2:
        apply_3D_macrocell_vertexdof_to_edgedof_replace_level_2(_data_edgeCellDst_X, _data_edgeCellDst_XY, _data_edgeCellDst_XYZ, _data_edgeCellDst_XZ, _data_edgeCellDst_Y, _data_edgeCellDst_YZ, _data_edgeCellDst_Z, _data_vertexCellSrc, v2eStencilMap);
        break;
    default:
        apply_3D_macrocell_vertexdof_to_edgedof_replace_level_any(_data_edgeCellDst_X, _data_edgeCellDst_XY, _data_edgeCellDst_XYZ, _data_edgeCellDst_XZ, _data_edgeCellDst_Y, _data_edgeCellDst_YZ, _data_edgeCellDst_Z, _data_vertexCellSrc, level, v2eStencilMap);
        break;
    }
}
    

} // namespace generated
} // namespace VertexDoFToEdgeDoF
} // namespace hhg