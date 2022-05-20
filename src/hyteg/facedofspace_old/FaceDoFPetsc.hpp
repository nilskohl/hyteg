/*
 * Copyright (c) 2021-2022 Marcus Mohr, Nils Kohl.
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

#include "hyteg/petsc/PETScWrapper.hpp"
#include "hyteg/sparseassembly/SparseMatrixProxy.hpp"
#include "hyteg/sparseassembly/VectorProxy.hpp"

namespace hyteg {

inline void createVectorFromFunction( const FaceDoFFunction_old< real_t >&  function,
                                      const FaceDoFFunction_old< idx_t >&   numerator,
                                      const std::shared_ptr< VectorProxy >& vec,
                                      uint_t                                level,
                                      DoFType                               flag )
{
   WALBERLA_ABORT( "Congrats :( You have detected another unimplemented feature of FaceDoFFunction" );
}

inline void createFunctionFromVector( const FaceDoFFunction_old< real_t >&  function,
                                      const FaceDoFFunction_old< idx_t >&   numerator,
                                      const std::shared_ptr< VectorProxy >& vec,
                                      uint_t                                level,
                                      DoFType                               flag )
{
   WALBERLA_ABORT( "Congrats :( You have detected another unimplemented feature of FaceDoFFunction" );
}

} // namespace hyteg
