/*
 * Copyright (c) 2017-2019 Dominik Thoennes, Marcus Mohr.
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

#include <fstream>

#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "hyteg/primitivestorage/PrimitiveStorage.hpp"

#include "hyteg/petsc/PETScManager.hpp"
#include "hyteg/petsc/PETScSparseMatrix.hpp"
#include "hyteg/petsc/PETScVector.hpp"

#ifdef HYTEG_BUILD_WITH_PETSC

namespace hyteg {

  /// \brief Exports matrix associated wit given operator to an ASCII file
  ///
  /// Uses PETSc functionality to generate the matrix associated with the given operator
  /// and export if to a file in ASCII forma which can be executed as a Matlab function.
  ///
  /// \param op               the operator to export
  /// \param fName            name of file to write matrix to
  /// \param mName            name of matrix, must be different from base part of fName;
  ///                         when the script is executed in Matlab this will be the final
  ///                         name of the sparse matrix
  /// \param storage          primitive storage
  /// \param level            refinement level on which the operator matrix should be generated
  /// \param elimDirichletBC  whether to zero row/columns for Dirichlet boundary values
  /// \param beVerbose        should function be talkative or not
  ///
  template <class OperatorType, template <class> class FunctionType, class FunctionTag>
  void exportOperator( OperatorType op,
                       std::string fName,
                       std::string matrixName,
                       std::shared_ptr< PrimitiveStorage > storage,
                       uint_t level,
                       bool elimDirichletBC,
                       bool beVerbose = false ) {

    // Get dimension of function space
    uint_t localDoFs  = hyteg::numberOfLocalDoFs < FunctionTag >( *storage, level );
    uint_t globalDoFs = hyteg::numberOfGlobalDoFs< FunctionTag >( *storage, level );
    if(  localDoFs != globalDoFs ) {
      WALBERLA_ABORT( "localDoFs and globalDoFs must agree for this app!" );
    }
    if( beVerbose ) {
      WALBERLA_LOG_INFO_ON_ROOT( " * Dimension of function space is " << globalDoFs );
    }

    // Fire up PETSc
    if( beVerbose ) {
      WALBERLA_LOG_INFO_ON_ROOT( " * Firing up PETSc" );
    }
    PETScManager pmgr;

    // Create PETSc matrix
    if( beVerbose ) {
      WALBERLA_LOG_INFO_ON_ROOT( " * Converting Operator to PETSc matrix" );
    }
    PETScSparseMatrix< OperatorType, FunctionType > petscMatrix( localDoFs, globalDoFs, matrixName.c_str() );
    FunctionType< PetscInt > numerator( "numerator", storage, level, level );
    numerator.enumerate( level );
    petscMatrix.createMatrixFromOperator( op, level, numerator );

    // Zero rows and columns of "Dirichlet DoFs"
    std::vector< PetscInt > indices;
    if( elimDirichletBC ) {
      indices = petscMatrix.applyDirichletBCSymmetrically( numerator, level );
    }

    // Write out matrix
    if( beVerbose ) {
      WALBERLA_LOG_INFO_ON_ROOT( " * Exporting Operator to file '" << fName << "'" );
    }
    petscMatrix.print( fName.c_str() );

    // Now make Matlab be a little talkative
    std::ofstream ofs;
    ofs.open( fName.c_str(), std::ofstream::out | std::ofstream::app );
    ofs << "fprintf( 'Constructed matrix %s\\n', '" << matrixName << "' );\n";

    // Export indices of DoFs fixed by Dirichlet boundary conditions and add
    // code to Matlab script to truly eliminate them from the final matrix
    if( elimDirichletBC ) {
       hyteg::petsc::applyDirichletBC( numerator, indices, level );
      ofs << "DirichletDoFs = [" << indices[0] + 1;
      for( auto k = indices.begin() + 1; k != indices.end(); ++k ) {
        ofs << ", " << *k + 1;
      }
      ofs << "];\n"
          << "tmpIndices = ~ismember( 1:size(" << matrixName << ",1), DirichletDoFs );\n"
          << matrixName << " = " << matrixName << "( tmpIndices, tmpIndices );\n"
          << "clear tmpIndices;\n"
          << "fprintf( 'Eliminated DoFs fixed by Dirichlet BCs from matrix\\n' );\n";
    }

    // Close file explicitely
    ofs.close();
  }

} // hyteg

#endif
