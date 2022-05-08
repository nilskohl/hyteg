/*
* Copyright (c) 2017-2022 Nils Kohl.
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

#include "hyteg/composites/P1DGEP1StokesFunction.hpp"
#include "hyteg/composites/P1DGEP1StokesOperator.hpp"
#include "hyteg/dataexport/VTKOutput.hpp"
#include "hyteg/dgfunctionspace/DGBasisLinearLagrange_Example.hpp"
#include "hyteg/dgfunctionspace/DGDiffusionForm_Example.hpp"
#include "hyteg/functions/FunctionTraits.hpp"
#include "hyteg/mesh/MeshInfo.hpp"
#include "hyteg/p1dgefunctionspace/P1DGEOperators.hpp"
#include "hyteg/petsc/PETScCGSolver.hpp"
#include "hyteg/petsc/PETScManager.hpp"
#include "hyteg/petsc/PETScSparseMatrix.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/solvers/CGSolver.hpp"

using walberla::real_t;
using walberla::uint_t;

namespace hyteg {

/// Manufactured solution for u = (sin(pi x) * sin(pi y) * sin(pi (x+y)), (sin(2 pi x) * sin(2 pi y) * sin(2 pi (x+y))
/// which has homogeneous dirichlet boundary conditions on a rectangular unit triangle.
real_t testHomogeneousDirichlet( const std::string& meshFile, const uint_t& level, bool writeVTK = false )
{
   MeshInfo              mesh = MeshInfo::fromGmshFile( meshFile );
   SetupPrimitiveStorage setupStorage( mesh, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
   auto storage = std::make_shared< PrimitiveStorage >( setupStorage, 1 );

   P1DGEFunction< idx_t > numerator( "numerator", storage, level, level );
   P1DGELaplaceOperator   L( storage, level, level );
   P1DGEMassOperator      M( storage, level, level );

   numerator.enumerate( level );

   // solution as a lambda function
   std::function< real_t( const Point3D& p ) > u_x_expr = []( const Point3D& p ) -> real_t {
      const real_t x = p[0];
      const real_t y = p[1];
      return std::sin( M_PI * x ) * std::sin( M_PI * y ) * std::sin( M_PI * ( x + y ) );
   };

   std::function< real_t( const Point3D& p ) > u_y_expr = []( const Point3D& p ) -> real_t {
      const real_t x  = p[0];
      const real_t y  = p[1];
      const real_t x0 = 2 * x;
      const real_t x1 = 2 * y;
      return std::sin( M_PI * x0 ) * std::sin( M_PI * x1 ) * std::sin( M_PI * ( x0 + x1 ) );
   };

   // rhs as a lambda function
   std::function< real_t( const Point3D& p ) > f_x_expr = []( const Point3D& p ) -> real_t {
      const real_t x  = p[0];
      const real_t y  = p[1];
      const real_t x0 = M_PI * x;
      const real_t x1 = std::sin( x0 );
      const real_t x2 = M_PI * ( x + y );
      const real_t x3 = std::pow( M_PI, 2 );
      const real_t x4 = M_PI * y;
      const real_t x5 = x3 * std::sin( x4 );
      const real_t x6 = 2 * std::cos( x2 );
      return -( x1 * x3 * x6 * std::cos( x4 ) - 4 * x1 * x5 * std::sin( x2 ) + x5 * x6 * std::cos( x0 ) );
   };
   std::function< real_t( const Point3D& p ) > f_y_expr = []( const Point3D& p ) -> real_t {
      const real_t x  = p[0];
      const real_t y  = p[1];
      const real_t x0 = 2 * x;
      const real_t x1 = 2 * y;
      const real_t x2 = M_PI * ( x0 + x1 );
      const real_t x3 = M_PI * x0;
      const real_t x4 = std::sin( x3 );
      const real_t x5 = std::pow( M_PI, 2 );
      const real_t x6 = M_PI * x1;
      const real_t x7 = x5 * std::sin( x6 );
      const real_t x8 = 8 * std::cos( x2 );
      return -( x4 * x5 * x8 * std::cos( x6 ) - 16 * x4 * x7 * std::sin( x2 ) + x7 * x8 * std::cos( x3 ) );
   };

   P1DGEFunction< real_t > u( "u", storage, level, level );
   P1DGEFunction< real_t > f( "f", storage, level, level );
   P1DGEFunction< real_t > rhs( "rhs", storage, level, level );
   P1DGEFunction< real_t > sol( "sol", storage, level, level );
   P1DGEFunction< real_t > err( "err", storage, level, level );
   P1DGEFunction< real_t > Merr( "Merr", storage, level, level );

   sol.interpolate( { u_x_expr, u_y_expr }, level, All );
   f.interpolate( { f_x_expr, f_y_expr }, level, All );

   // Why do I need this?
   f.interpolate( { u_x_expr, u_y_expr }, level, DirichletBoundary );

   M.apply( f, rhs, level, All, Replace );

   rhs.interpolate( 0, level, DirichletBoundary );
   u.getConformingPart()->interpolate( 0, level, DirichletBoundary );

   PETScCGSolver< P1DGELaplaceOperator > solver( storage, level, numerator );
   solver.solve( L, u, rhs, level );

   err.assign( { 1.0, -1.0 }, { u, sol }, level );

   // calculate the error in the L2 norm
   M.apply( err, Merr, level, All, Replace );
   auto discrL2 = sqrt( err.dotGlobal( Merr, level, Inner ) );

   if ( writeVTK )
   {
      VTKOutput vtk( "../../", "P1DGEPoisson2DHomogeneousDirichletConvergenceTest", storage );
      vtk.add( u );
      vtk.add( sol );
      vtk.add( err );
      vtk.add( f );
      vtk.add( *u.getConformingPart() );
      vtk.add( *u.getDiscontinuousPart() );
      vtk.add( *numerator.getConformingPart() );
      vtk.add( *numerator.getDiscontinuousPart() );
      vtk.write( level );
   }

   return discrL2;
}

real_t testStokesHomogeneousDirichlet( const std::string& meshFile, const uint_t& level, bool writeVTK = false )
{
   MeshInfo              mesh = MeshInfo::fromGmshFile( meshFile );
   SetupPrimitiveStorage setupStorage( mesh, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
   auto storage = std::make_shared< PrimitiveStorage >( setupStorage, 1 );

   P1DGEMassOperator M( storage, level, level );

   P1DGEP1StokesFunction< idx_t > numerator( "numerator", storage, level, level );

   P1DGEP1StokesOperator K( storage, level, level );

   numerator.enumerate( level );

   // solution as a lambda function
   std::function< real_t( const Point3D& p ) > u_x_expr = []( const Point3D& p ) -> real_t {
      const real_t x = p[0];
      const real_t y = p[1];
      return y + 2 * std::sin( x + y ) + 4;
   };

   std::function< real_t( const Point3D& p ) > u_y_expr = []( const Point3D& p ) -> real_t {
      const real_t x = p[0];
      const real_t y = p[1];
      return -x - 2 * std::sin( x + y ) + 3;
   };

   std::function< real_t( const Point3D& p ) > p_expr = []( const Point3D& p ) -> real_t {
      const real_t x = p[0];
      const real_t y = p[1];
      return 2 * x - y + 1;
   };

   // rhs as a lambda function
   std::function< real_t( const Point3D& p ) > f_x_expr = []( const Point3D& p ) -> real_t {
      const real_t x = p[0];
      const real_t y = p[1];
      return 2 - 4 * std::sin( x + y );
   };
   std::function< real_t( const Point3D& p ) > f_y_expr = []( const Point3D& p ) -> real_t {
      const real_t x = p[0];
      const real_t y = p[1];
      return 4 * std::sin( x + y ) - 1;
   };

   P1DGEP1StokesFunction< real_t > u( "u", storage, level, level );
   P1DGEP1StokesFunction< real_t > f( "f", storage, level, level );
   P1DGEP1StokesFunction< real_t > rhs( "rhs", storage, level, level );
   P1DGEP1StokesFunction< real_t > sol( "sol", storage, level, level );
   P1DGEP1StokesFunction< real_t > err( "err", storage, level, level );
   P1DGEP1StokesFunction< real_t > Merr( "Merr", storage, level, level );

   {
      WALBERLA_LOG_WARNING(
          "P1DGEConvergenceTest2D checks convergence in stokes by copying the velocity boundary conditions to the pressure. "
          "This is just a temporary workaround for testing things! " );

      numerator.p().setBoundaryCondition( numerator.uvw().getBoundaryCondition() );
      u.p().setBoundaryCondition( u.uvw().getBoundaryCondition() );
      f.p().setBoundaryCondition( f.uvw().getBoundaryCondition() );
      rhs.p().setBoundaryCondition( rhs.uvw().getBoundaryCondition() );
      sol.p().setBoundaryCondition( sol.uvw().getBoundaryCondition() );
      err.p().setBoundaryCondition( err.uvw().getBoundaryCondition() );
      Merr.p().setBoundaryCondition( Merr.uvw().getBoundaryCondition() );
   }

   sol.uvw().interpolate( { u_x_expr, u_y_expr }, level, All );
   sol.p().interpolate( p_expr, level, All );
   f.uvw().interpolate( { f_x_expr, f_y_expr }, level, All );
   f.p().interpolate( 0, level, All );

   // Why do I need this?
   f.uvw().interpolate( { u_x_expr, u_y_expr }, level, DirichletBoundary );
   f.p().interpolate( p_expr, level, DirichletBoundary );

   M.apply( f.uvw(), rhs.uvw(), level, All, Replace );
   rhs.p().interpolate( 0, level, All );

   rhs.assign( { 1. }, { sol }, level, DirichletBoundary );
   u.assign( { 1 }, { sol }, level, DirichletBoundary );

   // TODO: replace by minres
   PETScCGSolver< P1DGEP1StokesOperator > solver( storage, level, numerator );
   solver.solve( K, u, rhs, level );

   err.assign( { 1.0, -1.0 }, { u, sol }, level );

   // calculate the error in the L2 norm
   M.apply( err.uvw(), Merr.uvw(), level, All, Replace );
   auto discrL2_velocity = sqrt( err.uvw().dotGlobal( Merr.uvw(), level, Inner ) );

   if ( writeVTK )
   {
      VTKOutput vtk( "../../", "P1DGEStokes2DHomogeneousDirichletConvergenceTest", storage );
      vtk.add( u );
      vtk.add( sol );
      vtk.add( err );
      vtk.add( f );
      vtk.add( *u.uvw().getConformingPart() );
      vtk.add( *u.uvw().getDiscontinuousPart() );
      vtk.add( *numerator.uvw().getConformingPart() );
      vtk.add( *numerator.uvw().getDiscontinuousPart() );
      vtk.write( level );
   }

   return discrL2_velocity;
}

void runLaplace()
{
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( "%6s|%15s|%15s", "level", "error", "rate" ) );
   real_t lastError    = std::nan( "" );
   real_t currentError = std::nan( "" );
   real_t currentRate  = std::nan( "" );
   for ( uint_t level = 6; level <= 7; level++ )
   {
      lastError    = currentError;
      currentError = hyteg::testHomogeneousDirichlet( "../../data/meshes/tri_1el.msh", level, false );
      currentRate  = lastError / currentError;
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( "%6d|%15.2e|%15.2e", level, currentError, currentRate ) );
   }

   const real_t expectedRate = 4.;
   WALBERLA_CHECK_LESS( 0.9 * expectedRate, currentRate, "unexpected rate!" );
   WALBERLA_CHECK_GREATER( 1.1 * expectedRate, currentRate, "unexpected rate!" );
}

void runStokes()
{
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( "%6s|%15s|%15s", "level", "error", "rate" ) );
   real_t lastError    = std::nan( "" );
   real_t currentError = std::nan( "" );
   real_t currentRate  = std::nan( "" );
   for ( uint_t level = 3; level <= 6; level++ )
   {
      lastError    = currentError;
      currentError = hyteg::testStokesHomogeneousDirichlet( "../../data/meshes/tri_1el.msh", level, true );
      currentRate  = lastError / currentError;
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( "%6d|%15.2e|%15.2e", level, currentError, currentRate ) );
   }

   const real_t expectedRate = 4.;
   WALBERLA_CHECK_LESS( 0.9 * expectedRate, currentRate, "unexpected rate!" );
   WALBERLA_CHECK_GREATER( 1.1 * expectedRate, currentRate, "unexpected rate!" );
}

} // namespace hyteg

int main( int argc, char* argv[] )
{
   walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
   walberla::MPIManager::instance()->useWorldComm();
   hyteg::PETScManager petscManager( &argc, &argv );

   // hyteg::runLaplace();
   hyteg::runStokes();

   return 0;
}
