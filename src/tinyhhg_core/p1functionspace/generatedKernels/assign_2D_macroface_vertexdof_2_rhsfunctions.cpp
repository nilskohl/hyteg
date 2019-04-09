
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "GeneratedKernelsVertexToVertexMacroFace2D.hpp"

namespace hhg {
namespace vertexdof {
namespace macroface {
namespace generated {

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_2(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 4; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 4; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 6*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_3(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 8; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 8; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 10*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_4(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 16; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 16; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 18*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_5(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 32; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 32; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 34*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_6(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 64; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 64; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 66*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_7(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 128; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 128; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 130*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_8(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 256; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 256; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 258*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_9(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 512; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 512; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 514*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_10(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 1024; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 1024; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 1026*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_11(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 2048; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 2048; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 2050*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_12(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 4096; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 4096; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 4098*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_13(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 8192; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 8192; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 8194*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_14(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1)
{
   for (int ctr_2 = 1; ctr_2 < 16384; ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 16384; ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + 16386*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}

static void assign_2D_macroface_vertexdof_2_rhs_functions_level_any(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1, int64_t level)
{
   for (int ctr_2 = 1; ctr_2 < (1 << (level)); ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + (1 << (level)); ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4;
      }
   }
}


void assign_2D_macroface_vertexdof_2_rhs_functions(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1, int64_t level)
{
    switch( level )
    {
    case 2:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_2(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 3:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_3(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 4:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_4(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 5:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_5(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 6:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_6(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 7:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_7(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 8:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_8(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 9:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_9(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 10:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_10(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 11:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_11(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 12:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_12(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 13:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_13(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    case 14:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_14(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1);
        break;
    default:
        assign_2D_macroface_vertexdof_2_rhs_functions_level_any(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1, level);
        break;
    }
}
    

} // namespace generated
} // namespace macroface
} // namespace vertexdof
} // namespace hhg