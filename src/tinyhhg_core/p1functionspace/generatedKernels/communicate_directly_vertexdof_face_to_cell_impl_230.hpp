
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "all.hpp"
#include "core/DataTypes.h"
#include "core/Macros.h"
#include "tinyhhg_core/edgedofspace/EdgeDoFIndexing.hpp"
#include <map>
#define RESTRICT WALBERLA_RESTRICT

namespace hhg {
namespace vertexdof {
namespace comm {
namespace generated {

void communicate_directly_vertexdof_face_to_cell_impl_230(double * RESTRICT _data_p1_cell_dst, double const * RESTRICT const _data_p1_face_src, int32_t level);

} // namespace generated
} // namespace comm
} // namespace vertexdof
} // namespace hhg