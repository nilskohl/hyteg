
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "core/DataTypes.h"

namespace hhg {
namespace EdgeDoFToVertexDoF {
namespace generated {

void apply_2D_macroface_edgedof_to_vertexdof_replace(double * _data_edgeFaceSrc, double * const _data_edgeToVertexFaceStencil, double * _data_p1FaceDst, int64_t level);

void apply_2D_macroface_edgedof_to_vertexdof_add(double * _data_edgeFaceSrc, double * const _data_edgeToVertexFaceStencil, double * _data_p1FaceDst, int64_t level);

} // namespace generated
} // namespace EdgeDoFToVertexDoF
} // namespace hhg