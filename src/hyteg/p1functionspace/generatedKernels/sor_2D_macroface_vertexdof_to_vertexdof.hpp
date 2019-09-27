
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "all.hpp"
#include "core/Macros.h"
#include "hyteg/edgedofspace/EdgeDoFOrientation.hpp"
#include "hyteg/indexing/Common.hpp"
#include <map>
#define RESTRICT WALBERLA_RESTRICT

namespace hyteg {
namespace vertexdof {
namespace macroface {
namespace generated {

void sor_2D_macroface_vertexdof_to_vertexdof(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceRhs, double const * RESTRICT const _data_p1FaceStencil, int32_t level, double relax);

} // namespace generated
} // namespace macroface
} // namespace vertexdof
} // namespace hyteg