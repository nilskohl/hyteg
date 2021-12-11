/*
 * Copyright (c) 2017-2019 Daniel Drzisga, Dominik Thoennes, Marcus Mohr, Nils Kohl.
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

#include <core/Environment.h>
#include <core/Format.hpp>
#include <core/config/Create.h>
#include <core/mpi/Broadcast.h>
#include <core/timing/Timer.h>

#include "hyteg/dataexport/VTKOutput.hpp"
#include "hyteg/mesh/adaptiverefinement/mesh.hpp"
#include "hyteg/p1functionspace/P1VariableOperator.hpp"
#include "hyteg/primitivestorage/PrimitiveStorage.hpp"
#include "hyteg/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "hyteg/solvers/CGSolver.hpp"

using namespace hyteg;
using walberla::real_t;
using walberla::uint_t;

#define PI 3.14159265359

// solve problem with current refinement and return sorted list of elementwise squared errors
std::vector< std::pair< real_t, hyteg::PrimitiveID > >
    solve( std::shared_ptr< PrimitiveStorage > storage, uint_t lvl, uint_t iter, real_t tol, int vtk )
{
   uint_t l_min = lvl;
   uint_t l_max = lvl;

   uint_t dim = storage->hasGlobalCells() ? 3 : 2;

   // continuous functions
   // auto coeff = [=]( const hyteg::Point3D& ) { return 1; };
   auto exact = [=]( const hyteg::Point3D& x ) { return sin( 1.0 / x.normSq() ); };

   std::function< real_t( const hyteg::Point3D& ) > rhs;
   if ( storage->hasGlobalCells() )
   {
      rhs = [=]( const hyteg::Point3D& x ) {
         auto x0 = x.normSq();
         auto x1 = 1.0 / x0;
         return 2 * ( -x0 * cos( x1 ) + 2 * sin( x1 ) ) / pow( x0, 3 );
      };
   }
   else
   {
      rhs = [=]( const hyteg::Point3D& x ) {
         auto x0 = x.normSq();
         auto x1 = 1.0 / x0;
         return 4 * ( -x0 * cos( x1 ) + sin( x1 ) ) / pow( x0, 3 );
      };
   }

   // operators
   P1BlendingMassOperator    M( storage, l_min, l_max );
   P1BlendingLaplaceOperator A( storage, l_min, l_max );

   // FE functions
   P1Function< real_t > b( "b", storage, l_min, l_max );
   P1Function< real_t > u( "u", storage, l_min, l_max );
   P1Function< real_t > u_exact( "u_exact", storage, l_min, l_max );
   P1Function< real_t > err( "err", storage, l_min, l_max );
   P1Function< real_t > tmp( "err*M*err", storage, l_min, l_max );

   // global DoF
   tmp.interpolate( []( const hyteg::Point3D& ) { return 1.0; }, l_max, hyteg::Inner );
   auto n_dof = uint_t( tmp.dotGlobal( tmp, l_max ) );
   WALBERLA_LOG_INFO_ON_ROOT( " -> number of global DoF: " << n_dof );

   // rhs
   tmp.interpolate( rhs, l_max );
   M.apply( tmp, b, l_max, hyteg::All );
   // exact solution
   u_exact.interpolate( exact, l_max );
   // initialize u
   u.interpolate( exact, l_max, hyteg::DirichletBoundary );
   u.interpolate( []( const hyteg::Point3D& ) { return 0.0; }, l_max, hyteg::Inner );

   // solve
   hyteg::CGSolver< P1BlendingLaplaceOperator > solver( storage, l_min, l_min, iter, tol );
   solver.solve( A, u, b, l_max );

   // compute total error
   err.assign( { 1.0, -1.0 }, { u, u_exact }, l_max );
   M.apply( err, tmp, l_max, hyteg::All, Replace );
   real_t l2err = std::sqrt( err.dotGlobal( tmp, l_max ) );

   WALBERLA_LOG_INFO_ON_ROOT( "L2-error = " << l2err );

   // compute elementwise error
   std::vector< std::pair< real_t, hyteg::PrimitiveID > > err_2_elwise_loc;

   if ( dim == 3 )
   {
      for ( auto& [id, cell] : storage->getCells() )
      {
         real_t err_2_cell = vertexdof::macrocell::dot< real_t >( l_max, *cell, err.getCellDataID(), err.getCellDataID(), 0 );

         // scale squared error by cell-volume
         std::array< Point3D, 3 + 1 > vertices;
         uint_t                       i = 0;
         for ( auto& vid : cell->neighborVertices() )
         {
            vertices[i] = storage->getVertex( vid )->getCoordinates();
            ++i;
         }
         err_2_cell *= adaptiveRefinement::Simplex3::volume( vertices );

         err_2_elwise_loc.push_back( { err_2_cell, id } );
      }
   }
   else // dim == 2
   {
      for ( auto& [id, face] : storage->getFaces() )
      {
         real_t err_2_face = vertexdof::macroface::dot< real_t >( l_max, *face, err.getFaceDataID(), err.getFaceDataID(), 0 );

         // scale squared error by face-volume
         std::array< Point3D, 2 + 1 > vertices;
         uint_t                       i = 0;
         for ( auto& vid : face->neighborVertices() )
         {
            vertices[i] = storage->getVertex( vid )->getCoordinates();
            ++i;
         }
         err_2_face *= adaptiveRefinement::Simplex2::volume( vertices );

         err_2_elwise_loc.push_back( { err_2_face, id } );
      }
   }

   // communication
   std::vector< std::pair< real_t, hyteg::PrimitiveID > > err_2_elwise;
   std::vector< std::pair< real_t, hyteg::PrimitiveID > > err_2_elwise_other;

   walberla::mpi::SendBuffer send;
   walberla::mpi::RecvBuffer recv;

   send << err_2_elwise_loc;
   walberla::mpi::allGathervBuffer( send, recv );
   for ( int rnk = 0; rnk < walberla::mpi::MPIManager::instance()->numProcesses(); ++rnk )
   {
      recv >> err_2_elwise_other;
      err_2_elwise.insert( err_2_elwise.end(), err_2_elwise_other.begin(), err_2_elwise_other.end() );
   }

   // sort by errors
   std::sort( err_2_elwise.begin(), err_2_elwise.end() );

   // export to vtk
   if ( vtk >= 0 )
   {
      // compute L2 error contribution of each DoF, i.e. tmp_i=err_i*[M*err]_i
      tmp.multElementwise( { err, tmp }, l_max );
      // sanity check
      auto check = std::sqrt( tmp.sumGlobal( l_max ) );
      if ( std::abs( check - l2err ) > 1e-15 )
      {
         WALBERLA_LOG_WARNING_ON_ROOT( "sanity check failed: l2err" );
      }

      VTKOutput vtkOutput( "output", "adaptive_" + std::to_string( dim ) + "d", storage );
      vtkOutput.setVTKDataFormat( vtk::DataFormat::BINARY );
      vtkOutput.add( u );
      vtkOutput.add( err );
      vtkOutput.add( tmp );
      vtkOutput.add( u_exact );
      vtkOutput.add( b );
      vtkOutput.write( l_max, uint_t( vtk ) );
   }

   return err_2_elwise;
}

void solve_for_each_refinement( uint_t dim, uint_t n, real_t p, uint_t lvl, uint_t iter, real_t tol, bool vtk )
{
   MeshInfo meshInfo = MeshInfo::emptyMeshInfo();

   // setup domain
   double min = 1.0 / std::sqrt( 4 * PI );
   double max = 5;
   uint_t N   = 2;
   if ( dim == 3 )
   {
      meshInfo = MeshInfo::meshCuboid( Point3D( { min, min, min } ), Point3D( { max, max, max } ), N, N, N );
   }
   else if ( dim == 2 )
   {
      meshInfo = MeshInfo::meshRectangle( Point2D( { min, min } ), Point2D( { max, max } ), MeshInfo::CRISS, N, N );
   }
   else
   {
      WALBERLA_ABORT( "Dimension must be either 2 or 3!" );
   }

   // construct initial setupStorage
   SetupPrimitiveStorage  initialStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   SetupPrimitiveStorage& setupStorage = initialStorage;
   // todo: apply Geometrymap

   // construct adaptive mesh and update setup storage
   adaptiveRefinement::Mesh mesh( setupStorage );
   setupStorage = mesh.setupStorage();

   std::vector< std::pair< real_t, hyteg::PrimitiveID > > local_errors;

   for ( uint_t refinement = 0; refinement <= n; ++refinement )
   {
      if ( refinement > 0 )
      {
         WALBERLA_LOG_INFO_ON_ROOT( "* refinement " << refinement );

         uint_t N_tot = local_errors.size();
         uint_t N_ref = uint_t( std::ceil( real_t( N_tot ) * p ) );

         WALBERLA_LOG_INFO_ON_ROOT( " -> " << N_ref << " of " << N_tot << " elements are being refined ..." );

         // collect elements to refine
         std::vector< PrimitiveID > R( N_ref );
         for ( uint_t i = 0; i < N_ref; ++i )
         {
            R[i] = local_errors[N_tot - 1 - i].second;
         }

         // apply refinement and update setupStorage
         setupStorage = mesh.refineRG( R );
      }

      WALBERLA_LOG_INFO_ON_ROOT( "* solving system with " << mesh.n_elements() << " macro elements ..." );

      // apply boundary conditions and load balancing
      setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
      loadbalancing::roundRobin( setupStorage );
      // construct PrimitiveStorage from setupStorage corresponding to current refinement
      auto storage = std::make_shared< PrimitiveStorage >( setupStorage );

      int vtkname  = ( vtk ) ? int( refinement ) : -1;
      local_errors = solve( storage, lvl, iter, tol, vtkname );
   }
}

int main( int argc, char* argv[] )
{
   walberla::Environment walberlaEnv( argc, argv );
   walberla::logging::Logging::instance()->setLogLevel( walberla::logging::Logging::PROGRESS );
   walberla::MPIManager::instance()->useWorldComm();

   walberla::shared_ptr< walberla::config::Config > cfg;

   if ( argc == 1 )
   {
      walberla::shared_ptr< walberla::config::Config > cfg_( new walberla::config::Config );
      cfg_->readParameterFile( "../../hyteg/data/param/adaptiveRefinement.prm" );
      cfg = cfg_;
   }
   else
   {
      cfg = walberla::config::create( argc, argv );
   }

   // read parameters
   WALBERLA_LOG_INFO_ON_ROOT( "config = " << *cfg );
   walberla::Config::BlockHandle parameters = cfg->getOneBlock( "Parameters" );

   const uint_t dim           = parameters.getParameter< uint_t >( "dim" );
   const uint_t n_refinements = parameters.getParameter< uint_t >( "n_refinements" );
   const uint_t lvl           = parameters.getParameter< uint_t >( "microlevel" );
   const real_t p_refinement  = parameters.getParameter< real_t >( "proportion_of_elements_refined_per_step" );
   const uint_t iter          = parameters.getParameter< uint_t >( "n_iterations" );
   const real_t tol           = parameters.getParameter< real_t >( "tolerance" );
   const bool   vtkoutput     = parameters.getParameter< bool >( "vtkOutput" );

   solve_for_each_refinement( dim, n_refinements, p_refinement, lvl, iter, tol, vtkoutput );

   return 0;
}
