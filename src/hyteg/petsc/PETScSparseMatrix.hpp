/*
 * Copyright (c) 2017-2019 Boerge Struempfel, Daniel Drzisga, Dominik Thoennes, Marcus Mohr, Nils Kohl.
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
#include "hyteg/types/flags.hpp"

#ifdef HYTEG_BUILD_WITH_PETSC

#include "hyteg/p1functionspace/P1Petsc.hpp"

#include "hyteg/composites/petsc/P1StokesPetsc.hpp"

#include "hyteg/p2functionspace/P2Petsc.hpp"
#include "hyteg/composites/petsc/P2P1TaylorHoodPetsc.hpp"

#include "hyteg/petsc/PETScVector.hpp"

namespace hyteg {

template <class OperatorType, template <class> class FunctionType>
class PETScSparseMatrix {
protected:
  Mat mat;
  bool assembled;

public:
  PETScSparseMatrix() = delete;

  PETScSparseMatrix(uint_t localSize, uint_t globalSize, const char name[] = "Mat") {
    MatCreate(walberla::MPIManager::instance()->comm(),&mat);
    MatSetType(mat,MATMPIAIJ);
    MatSetSizes(mat,(PetscInt)localSize,(PetscInt)localSize,(PetscInt)globalSize,(PetscInt)globalSize);
    // Roughly overestimate number of non-zero entries for faster assembly of matrix
    MatMPIAIJSetPreallocation(mat, 1000, NULL, 1000, NULL);
    //MatSetUp(mat);
    //MatCreateAIJ(walberla::MPIManager::instance()->comm(),(PetscInt)localSize,(PetscInt)localSize,(PetscInt)globalSize,(PetscInt)globalSize,7, NULL, 0, NULL,&mat);
    setName(name);
    reset();
  }



  virtual ~PETScSparseMatrix() {
    MatDestroy(&mat);
  }

  inline void createMatrixFromFunction(const OperatorType& op, uint_t level,const FunctionType<PetscInt>& numerator,DoFType flag = All){
    //WALBERLA_LOG_INFO_ON_ROOT("Creating PETSc Matrix")
    hyteg::petsc::createMatrix<OperatorType>(op, numerator, numerator, mat, level, flag);

    MatAssemblyBegin(mat,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(mat, MAT_FINAL_ASSEMBLY);
  }

  inline bool createMatrixFromFunctionOnce(const OperatorType& op, uint_t level,const FunctionType<PetscInt>& numerator,DoFType flag = All){
    if(assembled)
      return false;
    createMatrixFromFunction(op,level,numerator,flag);
    assembled = true;
    return true;
  }

  inline void print(const std::string& name) {
    PetscViewer viewer;
    PetscViewerASCIIOpen(PETSC_COMM_WORLD,name.c_str(),&viewer);
    PetscViewerPushFormat(viewer,PETSC_VIEWER_ASCII_MATLAB );
    //PetscViewerMatlabOpen(PETSC_COMM_WORLD,name,FILE_MODE_WRITE,&viewer);
    MatView(mat,viewer);
    PetscViewerDestroy(&viewer);
  }

  void applyDirichletBC(const FunctionType<PetscInt>& numerator, uint_t level){
    //WALBERLA_LOG_INFO_ON_ROOT("")
    std::vector<PetscInt> ind;
    hyteg::petsc::applyDirichletBC(numerator,ind,level);

    MatZeroRows(mat,ind.size(),ind.data(),1.0,0,0);


    MatAssemblyBegin(mat,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(mat,MAT_FINAL_ASSEMBLY);

  }

    /// \brief Applies Dirichlet BCs to a linear system without losing symmetry.
    ///
    /// Uses the PETSc function MatZeroRowsColumns() which does that automatically.
    /// Still, we need to think how we can easily integrate this to use more efficient
    /// solvers in HyTeG, because the RHS is modified depending on the original system.
    ///
    /// So far I do not know any solution to this without re-assembling the system every time
    /// we solve it since we need to also rebuild the RHS.
    /// It should be possible to store a copy of the original system and circumvent re-assembling by
    /// copying it and applying only MatZeroRowsColumns() (without re-assembly) before calling the solver.
    /// If PETSc is only used as a coarse grid solver this might be a good solution.
    ///
    /// \param dirichletSolution a function that has the respective values interpolated on the Dirichlet boundary
    /// \param numerator an enumerated function
    /// \param rhsVec RHS of the system as PETSc vector - NOTE THAT THIS IS MODIFIED IN PLACE
    /// \param level the refinement level
    ///
    void applyDirichletBCSymmetrically( const FunctionType< real_t >&        dirichletSolution,
                                        const FunctionType< PetscInt >&      numerator,
                                        PETScVector< real_t, FunctionType >& rhsVec,
                                        const uint_t&                        level )
    {
       std::vector< PetscInt > bcIndices;
       hyteg::petsc::applyDirichletBC( numerator, bcIndices, level );

       PETScVector< real_t, FunctionType > dirichletSolutionVec( dirichletSolution, numerator, level );

       WALBERLA_ASSERT(
           isSymmetric(),
           "PETSc: Dirichlet boundary conditions can only be applied symmetrically if the original system is symmetric." );

       // This is required as the implementation of MatZeroRowsColumns() checks (for performance reasons?!)
       // if there are zero diagonals in the matrix. If there are, the function halts.
       // To disable that check, we need to allow setting MAT_NEW_NONZERO_LOCATIONS to true.
       MatSetOption( mat, MAT_NEW_NONZERO_LOCATIONS, PETSC_TRUE );

       MatZeroRowsColumns( mat, bcIndices.size(), bcIndices.data(), 1.0, dirichletSolutionVec.get(), rhsVec.get() );

       WALBERLA_ASSERT( isSymmetric() );
    }

    /// \brief Variant of applyDirichletBCSymmetrically() that only modifies the matrix itself
    ///
    /// \return Vector with global indices of the Dirichlet DoFs
   std::vector< PetscInt > applyDirichletBCSymmetrically( const FunctionType< PetscInt >& numerator,
                                                          const uint_t&                   level )
    {
       std::vector< PetscInt > bcIndices;
       hyteg::petsc::applyDirichletBC( numerator, bcIndices, level );

       WALBERLA_ASSERT(
           isSymmetric(),
           "PETSc: Dirichlet boundary conditions can only be applied symmetrically if the original system is symmetric." );

       // This is required as the implementation of MatZeroRowsColumns() checks (for performance reasons?!)
       // if there are zero diagonals in the matrix. If there are, the function halts.
       // To disable that check, we need to allow setting MAT_NEW_NONZERO_LOCATIONS to true.
       MatSetOption( mat, MAT_NEW_NONZERO_LOCATIONS, PETSC_TRUE );

       MatZeroRowsColumns( mat, bcIndices.size(), bcIndices.data(), 1.0, NULL, NULL );

       WALBERLA_ASSERT( isSymmetric() );

       return bcIndices;
    }

  inline void reset()  { assembled = false; }

  inline void setName(const char name[]){ PetscObjectSetName((PetscObject)mat,name); }

  inline Mat& get() { return mat; }

  bool isSymmetric(real_t tol = real_c(1e-13)) {
    Mat B;
    PetscReal norm;
    MatTranspose(mat, MAT_INITIAL_MATRIX, &B);
    MatAYPX(B, -1.0, mat, DIFFERENT_NONZERO_PATTERN);
    MatNorm(B, NORM_INFINITY, &norm);
    // WALBERLA_LOG_DEVEL_ON_ROOT( "PETSC_NORM = " << norm );
    MatDestroy( &B );
    return norm < tol;
  }

};

}

#endif