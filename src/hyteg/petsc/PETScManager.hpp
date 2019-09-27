/*
 * Copyright (c) 2017-2019 Boerge Struempfel, Daniel Drzisga, Nils Kohl.
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

#include "PETScWrapper.hpp"

#ifdef HYTEG_BUILD_WITH_PETSC

class PETScManager
{
 public:
   PETScManager() { PetscInitializeNoArguments(); }
   PETScManager( int* argc, char*** argv ) { PetscInitialize( argc, argv, NULL, NULL ); }

   ~PETScManager() { PetscFinalize(); }
};

#endif