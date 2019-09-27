/*
 * Copyright (c) 2017-2019 Dominik Thoennes.
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
#include "hyteg/FunctionProperties.hpp"
#include "hyteg/VTKWriter.hpp"
#include "hyteg/composites/P2P1TaylorHoodFunction.hpp"
#include "hyteg/composites/P2P1TaylorHoodStokesOperator.hpp"
#include "hyteg/mesh/MeshInfo.hpp"
#include "hyteg/primitivestorage/PrimitiveStorage.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "hyteg/solvers/MinresSolver.hpp"

using walberla::real_t;
using walberla::real_c;

int main( int argc, char* argv[] )
{
   walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
   walberla::MPIManager::instance()->useWorldComm();

   std::string meshFileName = "../../data/meshes/quad_4el_neumann.msh";

   hyteg::MeshInfo              meshInfo = hyteg::MeshInfo::fromGmshFile( meshFileName );
   hyteg::SetupPrimitiveStorage setupStorage( meshInfo, walberla::uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );

   hyteg::loadbalancing::roundRobin( setupStorage );

   size_t level   = 2;
   size_t maxiter = 100;

   std::shared_ptr< hyteg::PrimitiveStorage > storage = std::make_shared< hyteg::PrimitiveStorage >( setupStorage );

   hyteg::P2P1TaylorHoodFunction< real_t > r( "r", storage, level, level );
   hyteg::P2P1TaylorHoodFunction< real_t > f( "f", storage, level, level );
   hyteg::P2P1TaylorHoodFunction< real_t > u( "u", storage, level, level );

   hyteg::P2P1TaylorHoodStokesOperator L( storage, level, level );

   std::function< real_t( const hyteg::Point3D& ) > bc_x = []( const hyteg::Point3D& x ) { return 4.0 * ( 1.0 - x[1] ) * x[1]; };
   std::function< real_t( const hyteg::Point3D& ) > rhs  = []( const hyteg::Point3D& ) { return 0.0; };
   std::function< real_t( const hyteg::Point3D& ) > zero = []( const hyteg::Point3D& ) { return 0.0; };
   std::function< real_t( const hyteg::Point3D& ) > ones = []( const hyteg::Point3D& ) { return 1.0; };

   u.u.interpolate( zero, level );
   u.u.interpolate( bc_x, level, hyteg::DirichletBoundary );
   u.v.interpolate( zero, level, hyteg::DirichletBoundary );

   auto solver = hyteg::MinResSolver< hyteg::P2P1TaylorHoodStokesOperator >( storage, level, level, maxiter );
   solver.solve( L, u, f, level );

   L.apply( u, r, level, hyteg::Inner | hyteg::NeumannBoundary );
   real_t final_residuum = std::sqrt( r.dotGlobal( r, level, hyteg::Inner ) ) /
                           real_c( hyteg::numberOfGlobalDoFs< hyteg::P1StokesFunctionTag >( *storage, level ) );

   WALBERLA_LOG_INFO_ON_ROOT( "Residuum: " << final_residuum )

   WALBERLA_CHECK_LESS( final_residuum, 2.6e-05 );
   return EXIT_SUCCESS;
}