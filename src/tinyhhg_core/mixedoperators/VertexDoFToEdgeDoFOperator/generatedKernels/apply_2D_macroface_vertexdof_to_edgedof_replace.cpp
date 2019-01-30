
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "GeneratedKernelsVertexToEdgeMacroFace2D.hpp"

namespace hhg {
namespace VertexDoFToEdgeDoF {
namespace generated {

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_2(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_16*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 7];
      }
      for (int ctr_1 = 1; ctr_1 < 3; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_34*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 7];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5] + xi_37*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_39*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 3; ctr_1 < 4; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5] + xi_21*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_23*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 3; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_54*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 5] + xi_55*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_58*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 7];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 3; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_2*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 5] + xi_3*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_6*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 7];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_11*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5] + xi_9*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 3; ctr_1 < -ctr_2 + 4; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_44*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 5] + xi_45*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5] + xi_47*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_49*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 3; ctr_2 < 4; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 6] + xi_28*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 5] + xi_29*_data_vertexFaceSrc[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_3(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_16*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 11];
      }
      for (int ctr_1 = 1; ctr_1 < 7; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_34*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 11];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9] + xi_37*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_39*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 7; ctr_1 < 8; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9] + xi_21*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_23*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 7; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_54*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 9] + xi_55*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_58*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 11];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 7; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_2*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 9] + xi_3*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_6*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 11];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_11*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9] + xi_9*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 7; ctr_1 < -ctr_2 + 8; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_44*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 9] + xi_45*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9] + xi_47*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_49*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 7; ctr_2 < 8; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 10] + xi_28*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 9] + xi_29*_data_vertexFaceSrc[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_4(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_16*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 19];
      }
      for (int ctr_1 = 1; ctr_1 < 15; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_34*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 19];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17] + xi_37*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_39*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 15; ctr_1 < 16; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17] + xi_21*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_23*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 15; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_54*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 17] + xi_55*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_58*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 19];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 15; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_2*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 17] + xi_3*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_6*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 19];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_11*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17] + xi_9*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 15; ctr_1 < -ctr_2 + 16; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_44*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 17] + xi_45*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17] + xi_47*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_49*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 15; ctr_2 < 16; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 18] + xi_28*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 17] + xi_29*_data_vertexFaceSrc[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_5(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_16*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 35];
      }
      for (int ctr_1 = 1; ctr_1 < 31; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_34*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 35];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33] + xi_37*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_39*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 31; ctr_1 < 32; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33] + xi_21*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_23*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 31; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_54*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 33] + xi_55*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_58*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 35];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 31; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_2*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 33] + xi_3*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_6*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 35];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_11*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33] + xi_9*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 31; ctr_1 < -ctr_2 + 32; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_44*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 33] + xi_45*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33] + xi_47*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_49*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 31; ctr_2 < 32; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 34] + xi_28*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 33] + xi_29*_data_vertexFaceSrc[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_6(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_16*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 67];
      }
      for (int ctr_1 = 1; ctr_1 < 63; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_34*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 67];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65] + xi_37*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_39*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 63; ctr_1 < 64; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65] + xi_21*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_23*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 63; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_54*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 65] + xi_55*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_58*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 67];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 63; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_2*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 65] + xi_3*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_6*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 67];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_11*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65] + xi_9*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 63; ctr_1 < -ctr_2 + 64; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_44*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 65] + xi_45*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65] + xi_47*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_49*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 63; ctr_2 < 64; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 66] + xi_28*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 65] + xi_29*_data_vertexFaceSrc[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_7(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_16*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 131];
      }
      for (int ctr_1 = 1; ctr_1 < 127; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_34*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 131];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129] + xi_37*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_39*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 127; ctr_1 < 128; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129] + xi_21*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_23*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 127; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_54*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 129] + xi_55*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_58*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 131];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 127; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_2*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 129] + xi_3*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_6*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 131];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_11*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129] + xi_9*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 127; ctr_1 < -ctr_2 + 128; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_44*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 129] + xi_45*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129] + xi_47*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_49*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 127; ctr_2 < 128; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 130] + xi_28*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 129] + xi_29*_data_vertexFaceSrc[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_8(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_16*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 259];
      }
      for (int ctr_1 = 1; ctr_1 < 255; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_34*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 259];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257] + xi_37*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_39*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 255; ctr_1 < 256; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257] + xi_21*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_23*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 255; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_54*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 257] + xi_55*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_58*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 259];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 255; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_2*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 257] + xi_3*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_6*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 259];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_11*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257] + xi_9*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 255; ctr_1 < -ctr_2 + 256; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_44*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 257] + xi_45*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257] + xi_47*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_49*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 255; ctr_2 < 256; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 258] + xi_28*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 257] + xi_29*_data_vertexFaceSrc[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_9(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_16*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 515];
      }
      for (int ctr_1 = 1; ctr_1 < 511; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_34*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 515];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513] + xi_37*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_39*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 511; ctr_1 < 512; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513] + xi_21*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_23*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 511; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_54*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 513] + xi_55*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_58*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 515];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 511; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_2*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 513] + xi_3*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_6*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 515];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_11*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513] + xi_9*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 511; ctr_1 < -ctr_2 + 512; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_44*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 513] + xi_45*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513] + xi_47*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_49*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 511; ctr_2 < 512; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 514] + xi_28*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 513] + xi_29*_data_vertexFaceSrc[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_10(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_16*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1027];
      }
      for (int ctr_1 = 1; ctr_1 < 1023; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_34*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1027];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025] + xi_37*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_39*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 1023; ctr_1 < 1024; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025] + xi_21*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_23*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 1023; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_54*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025] + xi_55*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_58*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1027];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 1023; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_2*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025] + xi_3*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_6*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1027];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_11*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025] + xi_9*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 1023; ctr_1 < -ctr_2 + 1024; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_44*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025] + xi_45*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025] + xi_47*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_49*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1023; ctr_2 < 1024; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1026] + xi_28*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025] + xi_29*_data_vertexFaceSrc[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_11(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_16*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2051];
      }
      for (int ctr_1 = 1; ctr_1 < 2047; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_34*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2051];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049] + xi_37*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_39*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 2047; ctr_1 < 2048; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049] + xi_21*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_23*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 2047; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_54*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049] + xi_55*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_58*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2051];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 2047; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_2*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049] + xi_3*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_6*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2051];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_11*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049] + xi_9*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 2047; ctr_1 < -ctr_2 + 2048; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_44*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049] + xi_45*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049] + xi_47*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_49*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 2047; ctr_2 < 2048; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2050] + xi_28*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049] + xi_29*_data_vertexFaceSrc[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_12(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_16*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4099];
      }
      for (int ctr_1 = 1; ctr_1 < 4095; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_34*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4099];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097] + xi_37*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_39*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 4095; ctr_1 < 4096; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097] + xi_21*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_23*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 4095; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_54*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097] + xi_55*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_58*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4099];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 4095; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_2*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097] + xi_3*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_6*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4099];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_11*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097] + xi_9*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 4095; ctr_1 < -ctr_2 + 4096; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_44*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097] + xi_45*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097] + xi_47*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_49*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 4095; ctr_2 < 4096; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4098] + xi_28*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097] + xi_29*_data_vertexFaceSrc[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_13(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_16*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8195];
      }
      for (int ctr_1 = 1; ctr_1 < 8191; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_34*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8195];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193] + xi_37*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_39*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 8191; ctr_1 < 8192; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193] + xi_21*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_23*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 8191; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_54*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193] + xi_55*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_58*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8195];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 8191; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_2*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193] + xi_3*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_6*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8195];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_11*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193] + xi_9*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 8191; ctr_1 < -ctr_2 + 8192; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_44*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193] + xi_45*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193] + xi_47*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_49*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 8191; ctr_2 < 8192; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8194] + xi_28*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193] + xi_29*_data_vertexFaceSrc[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_14(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_16*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16387];
      }
      for (int ctr_1 = 1; ctr_1 < 16383; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_34*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16387];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385] + xi_37*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_39*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = 16383; ctr_1 < 16384; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385] + xi_21*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_23*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < 16383; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_54*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385] + xi_55*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_58*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16387];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 16383; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_2*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385] + xi_3*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_6*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16387];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_11*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385] + xi_9*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + 16383; ctr_1 < -ctr_2 + 16384; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_44*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385] + xi_45*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385] + xi_47*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_49*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 16383; ctr_2 < 16384; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16386] + xi_28*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385] + xi_29*_data_vertexFaceSrc[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}

static void apply_2D_macroface_vertexdof_to_edgedof_replace_level_any(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil, int64_t level)
{
   const double xi_14 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_15 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_16 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_17 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_32 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_33 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_34 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_36 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_37 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_38 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_39 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_20 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_21 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_22 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_23 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_52 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_53 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_54 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_55 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_56 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_57 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_58 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_59 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_0 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_2 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_3 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_4 = _data_vertexToDiagonalEdgeFaceStencil[3];
   const double xi_5 = _data_vertexToDiagonalEdgeFaceStencil[2];
   const double xi_6 = _data_vertexToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_vertexToDiagonalEdgeFaceStencil[1];
   const double xi_8 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_9 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_10 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_11 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_42 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_43 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_44 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_45 = _data_vertexToHorizontalEdgeFaceStencil[0];
   const double xi_46 = _data_vertexToVerticalEdgeFaceStencil[3];
   const double xi_47 = _data_vertexToVerticalEdgeFaceStencil[0];
   const double xi_48 = _data_vertexToVerticalEdgeFaceStencil[2];
   const double xi_49 = _data_vertexToVerticalEdgeFaceStencil[1];
   const double xi_26 = _data_vertexToHorizontalEdgeFaceStencil[1];
   const double xi_27 = _data_vertexToHorizontalEdgeFaceStencil[3];
   const double xi_28 = _data_vertexToHorizontalEdgeFaceStencil[2];
   const double xi_29 = _data_vertexToHorizontalEdgeFaceStencil[0];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_14*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_15*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_16*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_17*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1];
      }
      for (int ctr_1 = 1; ctr_1 < (1 << (level)) - 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_32*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_33*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_34*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_35*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_36*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1] + xi_37*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_38*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_39*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
      for (int ctr_1 = (1 << (level)) - 1; ctr_1 < (1 << (level)); ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_20*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1] + xi_21*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_22*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_23*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = 1; ctr_2 < (1 << (level)) - 1; ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_52*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_53*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_54*_data_vertexFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + 1] + xi_55*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_56*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_57*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_58*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_59*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1];
      }
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + (1 << (level)) - 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_0*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_1*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_2*_data_vertexFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + 1] + xi_3*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_4*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_5*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_6*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_7*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_10*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_11*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1] + xi_8*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1] + xi_9*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
      }
      for (int ctr_1 = -ctr_2 + (1 << (level)) - 1; ctr_1 < -ctr_2 + (1 << (level)); ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_42*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_43*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_44*_data_vertexFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + 1] + xi_45*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_46*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1] + xi_47*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_48*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_49*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   for (int ctr_2 = (1 << (level)) - 1; ctr_2 < (1 << (level)); ctr_2 += 1)
   {
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_26*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] + xi_27*_data_vertexFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))] + xi_28*_data_vertexFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + 1] + xi_29*_data_vertexFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
      }
   }
   {
      
   }
}


void apply_2D_macroface_vertexdof_to_edgedof_replace(double * _data_edgeFaceDst, double * _data_vertexFaceSrc, double * const _data_vertexToDiagonalEdgeFaceStencil, double * const _data_vertexToHorizontalEdgeFaceStencil, double * const _data_vertexToVerticalEdgeFaceStencil, int64_t level)
{
    switch( level )
    {
    case 2:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_2(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 3:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_3(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 4:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_4(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 5:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_5(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 6:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_6(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 7:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_7(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 8:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_8(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 9:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_9(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 10:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_10(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 11:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_11(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 12:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_12(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 13:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_13(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    case 14:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_14(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil);
        break;
    default:
        apply_2D_macroface_vertexdof_to_edgedof_replace_level_any(_data_edgeFaceDst, _data_vertexFaceSrc, _data_vertexToDiagonalEdgeFaceStencil, _data_vertexToHorizontalEdgeFaceStencil, _data_vertexToVerticalEdgeFaceStencil, level);
        break;
    }
}
    

} // namespace generated
} // namespace VertexDoFToEdgeDoF
} // namespace hhg