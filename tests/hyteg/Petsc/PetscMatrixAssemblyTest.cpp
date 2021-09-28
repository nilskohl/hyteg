/*
 * Copyright (c) 2021 Marcus Mohr.
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

#include "core/DataTypes.h"
#include "core/math/Random.h"
#include "core/mpi/MPIManager.h"

#include "hyteg/composites/P1BlendingStokesOperator.hpp"
#include "hyteg/composites/P1EpsilonStokesOperator.hpp"
#include "hyteg/composites/P1P1UzawaDampingFactorEstimationOperator.hpp"
#include "hyteg/dataexport/VTKOutput.hpp"
#include "hyteg/elementwiseoperators/DiagonalNonConstantOperator.hpp"
#include "hyteg/elementwiseoperators/ElementwiseOperatorPetsc.hpp"
#include "hyteg/elementwiseoperators/P1ElementwiseOperator.hpp"
#include "hyteg/elementwiseoperators/P2ElementwiseOperator.hpp"
#include "hyteg/functions/FunctionTraits.hpp"
#include "hyteg/geometry/AnnulusMap.hpp"
#include "hyteg/mesh/MeshInfo.hpp"
#include "hyteg/p1functionspace/P1ConstantOperator_new.hpp"
#include "hyteg/p1functionspace/P1PolynomialBlendingOperator.hpp"
#include "hyteg/p1functionspace/P1ProjectNormalOperator.hpp"
#include "hyteg/p1functionspace/P1SurrogateOperator.hpp"
#include "hyteg/p1functionspace/P1VariableOperator.hpp"
#include "hyteg/p1functionspace/P1VariableOperator_new.hpp"
#include "hyteg/p2functionspace/P2ConstantOperator.hpp"
#include "hyteg/p2functionspace/P2EpsilonOperator.hpp"
#include "hyteg/p2functionspace/P2Function.hpp"
#include "hyteg/p2functionspace/P2SurrogateOperator.hpp"
#include "hyteg/p2functionspace/P2VariableOperator.hpp"
// #include "hyteg/composites/P1PolynomialBlendingStokesOperator.hpp"   <-- see issue 159
#include "hyteg/composites/P1StokesBlockLaplaceOperator.hpp"
#include "hyteg/composites/P1StokesOperator.hpp"
#include "hyteg/composites/P2P1BlendingTaylorHoodStokesOperator.hpp"
#include "hyteg/composites/P2P1SurrogateTaylorHoodStokesOperator.hpp"
#include "hyteg/composites/P2P1TaylorHoodBlockFunction.hpp"
#include "hyteg/composites/P2P1TaylorHoodStokesOperator.hpp"
#include "hyteg/composites/P2P1UzawaDampingFactorEstimationOperator.hpp"
#include "hyteg/composites/P2P2StabilizedStokesOperator.hpp"
#include "hyteg/composites/P2P2UnstableStokesOperator.hpp"
#include "hyteg/composites/UnsteadyDiffusion.hpp"
#include "hyteg/operators/BlockOperator.hpp"
#include "hyteg/operators/VectorMassOperator.hpp"
#include "hyteg/petsc/PETScExportOperatorMatrix.hpp"
#include "hyteg/petsc/PETScManager.hpp"
#include "hyteg/petsc/PETScSparseMatrix.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/primitivestorage/loadbalancing/SimpleBalancer.hpp"

/// This test checks whether we can assemble a sparse matrix
/// (for/with PETSc) for the given operators. It is mostly a
/// compile time check.

#ifndef HYTEG_BUILD_WITH_PETSC
#error "This test only works with PETSc enabled. Please enable it via -DHYTEG_BUILD_WITH_PETSC=ON"
#endif

using walberla::real_t;
using namespace hyteg;

void printTestHdr( std::string msg )
{
   std::string sep = "------------------------------------------------------";
   WALBERLA_LOG_INFO_ON_ROOT( "" << sep << "\n" << msg << ":\n" << sep );
}

template < class operType >
void testAssembly_newAPI( std::shared_ptr< PrimitiveStorage >& storage, uint_t level, std::string tag )
{
   WALBERLA_LOG_INFO_ON_ROOT( " * " << tag );

   typename operType::srcType::template FunctionType< PetscInt > enumerator( "enumerator", storage, level, level );
   enumerator.enumerate( level );

   PETScManager                                                            petscManager;
   PETScSparseMatrix< operType, operType::srcType::template FunctionType > matrix( enumerator, level, tag.c_str() );

   operType oper( storage, level, level );
   matrix.createMatrixFromOperator_newAPI( oper, level, enumerator, All );
}

template < template < class > class fKind >
void testAssembly_newAPI( BlockOperator< fKind< real_t >, fKind< real_t > >& oper,
                          std::shared_ptr< PrimitiveStorage >&               storage,
                          uint_t                                             level,
                          std::string                                        tag )
{
   WALBERLA_LOG_INFO_ON_ROOT( " * " << tag );

   typedef BlockOperator< fKind< real_t >, fKind< real_t > > operType;
   fKind< PetscInt >                                         enumerator( "enumerator", storage, level, level );
   enumerator.enumerate( level );

   PETScManager                         petscManager;
   PETScSparseMatrix< operType, fKind > matrix( enumerator, level, tag.c_str() );

   matrix.createMatrixFromOperator_newAPI( oper, level, enumerator, All );
}

template < class operType >

void testAssembly( std::shared_ptr< PrimitiveStorage >& storage, uint_t level, std::string tag )
{
   WALBERLA_LOG_INFO_ON_ROOT( " * " << tag );

   PETScManager                                                            petscManager;
   PETScSparseMatrix< operType, operType::srcType::template FunctionType > matrix( storage, level, tag.c_str() );

   typename operType::srcType::template FunctionType< PetscInt > enumerator( "enumerator", storage, level, level );
   enumerator.enumerate( level );

   operType oper( storage, level, level );
   matrix.createMatrixFromOperator( oper, level, enumerator, All );
}

// Version for operators the require a form in their ctors
template < class operType, class formType >
void testAssembly( std::shared_ptr< PrimitiveStorage >& storage,
                   uint_t                               level,
                   std::shared_ptr< formType >&         form,
                   std::string                          tag )
{
   WALBERLA_LOG_INFO_ON_ROOT( " * " << tag );

   PETScManager                                                            petscManager;
   PETScSparseMatrix< operType, operType::srcType::template FunctionType > matrix( storage, level, tag.c_str() );

   typename operType::srcType::template FunctionType< PetscInt > enumerator( "enumerator", storage, level, level );
   enumerator.enumerate( level );

   operType oper( storage, level, level, form );
   matrix.createMatrixFromOperator( oper, level, enumerator, All );
}

// Version for (some?) Surrogate Operators (need an interpolation level in ctor)
template < class operType >
void testAssembly( std::shared_ptr< PrimitiveStorage >& storage, uint_t level, uint_t ipLevel, std::string tag )
{
   WALBERLA_LOG_INFO_ON_ROOT( " * " << tag );

   PETScManager                                                            petscManager;
   PETScSparseMatrix< operType, operType::srcType::template FunctionType > matrix( storage, level, tag.c_str() );

   typename operType::srcType::template FunctionType< PetscInt > enumerator( "enumerator", storage, level, level );
   enumerator.enumerate( level );

   operType oper( storage, level, level, ipLevel );
   matrix.createMatrixFromOperator( oper, level, enumerator, All );
}

// Version for ProjectNormalOperators
template < class operType >
void testAssembly( uint_t level, std::string tag )
{
   WALBERLA_LOG_INFO_ON_ROOT( " * " << tag );

   // blended annulus mesh
   auto                  meshInfo = MeshInfo::meshAnnulus( 0.5, 1.0, MeshInfo::CRISS, 6, 6 );
   SetupPrimitiveStorage annulusStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   annulusStorage.setMeshBoundaryFlagsOnBoundary( 3, 0, true );
   AnnulusMap::setMap( annulusStorage );
   const auto storage = std::make_shared< PrimitiveStorage >( annulusStorage );

   // normal computation
   auto normalInterpolant = []( const Point3D& p ) {
      real_t norm = p.norm();
      real_t sign = ( norm > 0.75 ) ? 1.0 : -1.0;
      return sign / norm * p;
   };

   auto normalFunction = [=]( const Point3D& p, Point3D& n ) -> void { n = normalInterpolant( p ); };

   // standard assemble check
   PETScManager                                                            petscManager;
   PETScSparseMatrix< operType, operType::srcType::template FunctionType > matrix( storage, level, tag.c_str() );

   typename operType::srcType::template FunctionType< PetscInt > enumerator( "enumerator", storage, level, level );
   enumerator.enumerate( level );

   operType projectNormalOperator( storage, level, level, normalFunction );
   matrix.createMatrixFromOperator( projectNormalOperator, level, enumerator, All );
}

// -------------------------------
//  Specialised one case versions
// -------------------------------
template <>
void testAssembly< P1ConstantUnsteadyDiffusionOperator >( std::shared_ptr< PrimitiveStorage >& storage,
                                                          uint_t                               level,
                                                          std::string                          tag )
{
   WALBERLA_LOG_INFO_ON_ROOT( " * " << tag );

   PETScManager petscManager;
   PETScSparseMatrix< P1ConstantUnsteadyDiffusionOperator, P1ConstantUnsteadyDiffusionOperator::srcType::template FunctionType >
       matrix( storage, level, tag.c_str() );

   typename P1ConstantUnsteadyDiffusionOperator::srcType::template FunctionType< PetscInt > enumerator(
       "enumerator", storage, level, level );
   enumerator.enumerate( level );

   P1ConstantUnsteadyDiffusionOperator oper( storage, level, level, 0.1, 1.0, DiffusionTimeIntegrator::ImplicitEuler );
   matrix.createMatrixFromOperator( oper, level, enumerator, All );
}

int main( int argc, char* argv[] )
{
   // General setup stuff
   walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
   walberla::MPIManager::instance()->useWorldComm();

   // ----------------------------
   //  Prepare setup for 2D tests
   // ----------------------------
   std::string           meshFileName = "../../data/meshes/quad_16el.msh";
   MeshInfo              meshInfo     = MeshInfo::fromGmshFile( meshFileName );
   SetupPrimitiveStorage setupStorage( meshInfo, walberla::uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   loadbalancing::roundRobin( setupStorage );
   std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );

   uint_t      level = 2;
   std::string rule  = "==============================";

   // ------------------
   //  Scalar Operators
   // ------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n  SCALAR TO SCALAR OPERATORS\n" << rule );

   std::shared_ptr< Form > form = nullptr;

   printTestHdr( "Testing P1 Operators" );

   testAssembly_newAPI< P1ConstantMassOperator >( storage, level, "P1ConstantOperator" );
   testAssembly< P1ConstantMassOperator_new >( storage, level, "P1ConstantOperator_new" );
   testAssembly< P1SurrogateMassOperator >( storage, level, "P1SurrogateOperator" );
   testAssembly< P1BlendingMassOperator_new >( storage, level, "P1VariableOperator_new" );

   WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1PolynomialBlendingOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1VariableOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1ProjectNormalOperator" );
   // testAssembly< P1PolynomialBlendingMassOperator >( storage, level, level, "P1PolynomialBlendingOperator" );
   // testAssembly< P1BlendingMassOperator >( storage, level, "P1VariableOperator" );
   // testAssembly< P1ProjectNormalOperator >( level, "P1ProjectNormalOperator" );

   printTestHdr( "Testing P2 Operators" );

   testAssembly_newAPI< P2ConstantMassOperator >( storage, level, "P2ConstantOperator" );

   WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2SurrogateVariableOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2VariableOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2ProjectNormalOperator" );
   // testAssembly< P2BlendingMassOperator >( storage, level, "P2VariableOperator" );
   // testAssembly< P2SurrogateMassOperator >( storage, level, level, "P2SurrogateOperator" );
   // testAssembly< P2ProjectNormalOperator >( level, "P2ProjectNormalOperator" );

   // ---------------------
   //  Low-level Operators
   // ---------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n  LOW-LEVEL OPERATORS\n" << rule );
   typedef EdgeDoFOperator< P2FenicsForm< p2_mass_cell_integral_0_otherwise, p2_tet_mass_cell_integral_0_otherwise > >
       E2EMassOperator;
   testAssembly< E2EMassOperator >( storage, level, "EdgeDoFOperator" );

   WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   WALBERLA_LOG_INFO_ON_ROOT( " * VertexDoFToEdgeDoFOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * EdgeDoFToVertexDoFOperator" );
   // typedef EdgeDoFToVertexDoFOperator< P2FenicsForm< p2_mass_cell_integral_0_otherwise, p2_tet_mass_cell_integral_0_otherwise > > E2VMassOperator;
   // testAssembly< E2VMassOperator >( storage, level, "EdgeDoFToVertexDoFOperator" );
   // typedef VertexDoFToEdgeDoFOperator< P2FenicsForm< p2_mass_cell_integral_0_otherwise, p2_tet_mass_cell_integral_0_otherwise > > V2EMassOperator;
   // testAssembly< V2EMassOperator >( storage, level, "VertexDoFToEdgeDoFOperator" );

   // -----------------------
   //  Elementwise Operators
   // -----------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n  ELEMENTWISE OPERATORS\n" << rule );

   testAssembly_newAPI< P1ElementwiseMassOperator >( storage, level, "P1ElementwiseOperator" );
   testAssembly_newAPI< P2ElementwiseMassOperator >( storage, level, "P2ElementwiseOperator" );

   auto                            p2MassFormHyTeG       = std::make_shared< P2Form_mass >();
   std::shared_ptr< P2RowSumForm > lumpedMassFormP2HyTeG = std::make_shared< P2RowSumForm >( p2MassFormHyTeG );
   testAssembly< P2BlendingLumpedDiagonalOperator, P2RowSumForm >(
       storage, level, lumpedMassFormP2HyTeG, "DiagonalNonConstantOperator" );

   testAssembly< P2P1ElementwiseBlendingStokesOperator >( storage, level, "P2P1ElementwiseBlendingStokesOperator" );

   WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2ToP1ElementwiseOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1ToP2ElementwiseOperator" );
   // testAssembly< P2ToP1ElementwiseBlendingDivxOperator >( storage, level, "P2ToP1ElementwiseOperator" );
   // testAssembly< P1ToP2ElementwiseBlendingDivTxOperator >( storage, level, "P1ToP2ElementwiseOperator" );

   // ---------------------
   //  Composite Operators
   // ---------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n  COMPOSITE OPERATORS\n" << rule );

   // cannot construct operator:
   // testAssembly< P1P1UzawaDampingFactorEstimationOperator >( storage, level, "P1P1UzawaDampingFactorEstimationOperator" );
   // testAssembly< P2P1UzawaDampingFactorEstimationOperator >( storage, level, "P2P1UzawaDampingFactorEstimationOperator" );

   testAssembly< P1ConstantUnsteadyDiffusionOperator >( storage, level, "P1ConstantUnsteadyDiffusionOperator" );

   testAssembly< P1StokesOperator >( storage, level, "P1StokesOperator" );
   testAssembly< P2P1TaylorHoodStokesOperator >( storage, level, "P2P1TaylorHoodStokesOperator" );
   testAssembly< P2P2StabilizedStokesOperator >( storage, level, "P2P2StabilizedStokesOperator" );

   testAssembly< P2P1TaylorHoodStokesOperator >( storage, level, "P2P1TaylorHoodStokesOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1PolynomialBlendingStokesOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1BlendingStokesOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1StokesBlockLaplaceOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1EpsilonStokesOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2P2UnstableStokesOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2P1BlendingTaylorHoodStokesOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2P1SurrogateTaylorHoodStokesOperator" );
   // testAssembly< P1StokesBlockLaplaceOperator >( storage, level, "P1StokesBlockLaplaceOperator" );
   // testAssembly< P1BlendingStokesOperator >( storage, level, "P1BlendingStokesOperator" );
   // testAssembly< P1EpsilonStokesOperator >( storage, level, "P1EpsilonStokesOperator" );
   // testAssembly< P2P2UnstableStokesOperator >( storage, level, "P2P2UnstableStokesOperator" );
   // testAssembly< P2P1BlendingTaylorHoodStokesOperator >( storage, level, "P2P1BlendingTaylorHoodStokesOperator" );
   // testAssembly< P2P1SurrogateTaylorHoodStokesOperator >( storage, level, level, "P2P1SurrogateTaylorHoodStokesOperator" );

   // ----------------------------
   //  Scalar To Vector Operators
   // ----------------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n  SCALAR TO VECTOR OPERATORS\n" << rule );

   WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1ScalarToP2VectorOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P1ToP2ConstantOperator" );
   // testAssembly< P1ToP2ElementwiseBlendingDivTOperator >( storage, level, "P1ScalarToP2VectorOperator" );
   // testAssembly< P1ToP2ConstantDivTxOperator >( storage, level, "P1ToP2ConstantOperator" );

   // ----------------------------
   //  Vector To Scalar Operators
   // ----------------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n  VECTOR TO SCALAR OPERATORS\n" << rule );

   WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2ScalarToP1VectorOperator" );
   WALBERLA_LOG_INFO_ON_ROOT( " * P2ToP1ConstantOperator" );
   // testAssembly< P2ToP1ElementwiseBlendingDivOperator >( storage, level, "P2ScalarToP1VectorOperator" );
   // testAssembly< P2ToP1ConstantDivxOperator >( storage, level, "P2ToP1ConstantOperator" );

   // ------------------
   //  Vector Operators
   // ------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n  VECTOR TO VECTOR OPERATORS\n" << rule );
   testAssembly_newAPI< P1ConstantVectorMassOperator >( storage, level, "P1ConstantVectorMassOperator" );
   testAssembly_newAPI< P2ConstantVectorMassOperator >( storage, level, "P2ConstantVectorMassOperator" );
   testAssembly_newAPI< P2ElementwiseBlendingVectorMassOperator >( storage, level, "P2ElementwiseBlendingVectorMassOperator" );

   // WALBERLA_LOG_INFO_ON_ROOT( "Skipping: (since assembly doesn't compile)" );
   // WALBERLA_LOG_INFO_ON_ROOT( " * [all of this kind]" );

   // ------------------
   //  Block Operators
   // ------------------
   WALBERLA_LOG_INFO_ON_ROOT( "" << rule << "\n BLOCK OPERATORS\n" << rule );

   // setup an artificial block operator
   typedef BlockOperator< P2P1TaylorHoodBlockFunction< real_t >, P2P1TaylorHoodBlockFunction< real_t > > myBlockOper;
   myBlockOper oper( storage, level, level, 2, 2 );
   oper.setSubOperator( 0, 0, std::make_shared< OperatorWrapper< P2ConstantVectorLaplaceOperator > >( storage, level, level ) );
   oper.setSubOperator( 1, 0, nullptr );
   oper.setSubOperator( 0, 1, nullptr );
   oper.setSubOperator( 1, 1, std::make_shared< OperatorWrapper< P1ConstantMassOperator > >( storage, level, level ) );

   testAssembly_newAPI< P2P1TaylorHoodBlockFunction >( oper, storage, level, "artificial diagonal BlockOperator" );

   return 0;
}
