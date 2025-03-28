/*
 * Copyright (c) 2021-2023 Benjamin Mann.
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
#include <core/math/Constants.h>
#include <core/mpi/Broadcast.h>
#include <core/timing/Timer.h>
#include <iomanip>

#include "hyteg/adaptiverefinement/error_estimator.hpp"
#include "hyteg/adaptiverefinement/mesh.hpp"
#include "hyteg/dataexport/VTKOutput/VTKOutput.hpp"
#include "hyteg/elementwiseoperators/P1ElementwiseOperator.hpp"
#include "hyteg/geometry/AnnulusMap.hpp"
#include "hyteg/geometry/IcosahedralShellMap.hpp"
#include "hyteg/gridtransferoperators/P1toP1LinearProlongation.hpp"
#include "hyteg/gridtransferoperators/P1toP1LinearRestriction.hpp"
#include "hyteg/memory/MemoryAllocation.hpp"
#include "hyteg/numerictools/L2Space.hpp"
#include "hyteg/p1functionspace/P1VariableOperator.hpp"
#include "hyteg/petsc/PETScCGSolver.hpp"
#include "hyteg/petsc/PETScManager.hpp"
#include "hyteg/petsc/PETScSparseMatrix.hpp"
#include "hyteg/petsc/PETScVector.hpp"
#include "hyteg/primitivestorage/PrimitiveStorage.hpp"
#include "hyteg/primitivestorage/Visualization.hpp"
#include "hyteg/primitivestorage/loadbalancing/DistributedBalancer.hpp"
#include "hyteg/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "hyteg/solvers/CGSolver.hpp"
#include "hyteg/solvers/FullMultigridSolver.hpp"
#include "hyteg/solvers/GaussSeidelSmoother.hpp"
#include "hyteg/solvers/GeometricMultigridSolver.hpp"
#include "hyteg/solvers/WeightedJacobiSmoother.hpp"
#include "hyteg/solvers/controlflow/AgglomerationWrapper.hpp"

#include "constant_stencil_operator/P1ConstantOperator.hpp"

using namespace hyteg;
using walberla::real_t;
using walberla::uint_t;

// using Mass = P1ConstantMassOperator;
// using Mass    = P1ElementwiseMassOperator;
using Mass    = operatorgeneration::P1ElementwiseMass;
using Laplace = P1ConstantLaplaceOperator;
// using Laplace      = P1ElementwiseLaplaceOperator;
using DivkGradForm = forms::p1_div_k_grad_affine_q3;
using DivkGrad     = P1VariableOperator< DivkGradForm >;

// representation of a model problem
struct ModelProblem
{
   enum Type
   {
      // constant coefficient
      DIRAC,
      DIRAC_REGULARIZED,
      SLIT,
      REENTRANT_CORNER,
      WAVES,
      __VARIABLE_COEFFICIENT,
      // variable coefficient
      WAVES_K,
      JUMP_COEFF,
      JUMP_COEFF_REGULARIZED,
      __NOT_AVAILABLE
   };

   ModelProblem( uint_t mp_type, uint_t spacial_dim )
   : type( Type( mp_type ) )
   , dim( spacial_dim )
   , sigma( 0.0 )
   , n_w( 1.0 )
   , p_w( 1.0 )
   , k_lo( 1.0 )
   , k_hi( 1.0 )
   {
      if ( mp_type >= Type::__NOT_AVAILABLE )
      {
         WALBERLA_ABORT( "Invalid argument for model problem: Must be less than " << Type::__NOT_AVAILABLE );
      }
      if ( mp_type == Type::__VARIABLE_COEFFICIENT )
      {
         WALBERLA_ABORT( "Invalid argument for model problem: " << Type::__VARIABLE_COEFFICIENT << " undefined!" );
      }
      if ( spacial_dim < 2 || 3 < spacial_dim )
      {
         WALBERLA_ABORT( "Invalid argument for spatial dimension: Must be either 2 or 3" );
      }
   }

   std::string name() const
   {
      std::stringstream ss;

      switch ( type )
      {
      case DIRAC:
         ss << "dirac";
         break;

      case DIRAC_REGULARIZED:
         ss << "dirac_regularized"; // << "_" << sigma;
         break;

      case SLIT:
         ss << "slit";
         break;

      case REENTRANT_CORNER:
         ss << "reentrant_corner";
         break;

      case WAVES:
         ss << "waves";
         break;

      case WAVES_K:
         ss << "waves_k";
         break;

      case JUMP_COEFF:
         ss << "jump_coeff";
         break;

      case JUMP_COEFF_REGULARIZED:
         ss << "jump_coeff_regularized";
         break;

      default:
         break;
      }

      ss << "_" << dim << "D";

      return ss.str();
   }

   void set_params( real_t sig, uint_t n_waves, uint_t squeeze_waves, real_t kLo, real_t kHi )
   {
      if ( type == DIRAC_REGULARIZED || type == JUMP_COEFF_REGULARIZED )
      {
         sigma = sig;
      }
      if ( type == WAVES || type == WAVES_K )
      {
         n_w = real_c( n_waves );
         p_w = real_c( squeeze_waves );
      }
      if ( type == JUMP_COEFF )
      {
         k_lo = kLo;
         k_hi = kHi;
      }
      // todo: add parameters when adding new problems
   }

   bool constant_coefficient() const { return type < __VARIABLE_COEFFICIENT; }

   auto coeff() const
   {
      using walberla::math::pi;

      std::function< real_t( const Point3D& ) > k;

      if ( constant_coefficient() )
      {
         k = []( const Point3D& ) { return 1.0; };
      }
      if ( type == JUMP_COEFF )
      {
         k = [*this]( const hyteg::Point3D& x ) {
            // jump at { (x,y) | x + (x_jump_0 - x_jump_1)y = x_jump_0 }
            real_t x_jump_y = x_jump_0 * ( real_c( 1.0 ) - x[1] ) + x_jump_1 * x[1];
            return ( x[0] < x_jump_y ) ? k_lo : k_hi;
         };
      }
      if ( type == JUMP_COEFF_REGULARIZED )
      {
         k = [*this]( const hyteg::Point3D& x ) {
            return ( 2 * exp( sigma * ( x[0] - 0.5 ) ) + 1 ) / ( exp( sigma * ( x[0] - 0.5 ) ) + 1 );
         };
      }
      if ( type == WAVES_K )
      {
         auto v = [*this]( const real_t& t ) {
            const auto c1 = n_w * p_w * 2 * pi;
            const auto c2 = log( c1 );
            const auto c3 = c1 * c2 / p_w;
            const auto c4 = pow( c1, t ) / p_w;
            const auto c5 = -sin( c4 ) * c4 * c2 + c3;
            return 1. / c5;
         };
         if ( dim == 3 )
         {
            k = [=]( const hyteg::Point3D& x ) { return v( x[0] * x[1] * x[2] ); };
         }
         else
         {
            k = [=]( const hyteg::Point3D& x ) { return v( x[0] * x[1] ); };
         }
      }
      // todo: add required coefficients

      return k;
   }

   void init( std::shared_ptr< PrimitiveStorage >        storage,
              std::function< real_t( const Point3D& ) >& u,
              P1Function< real_t >&                      f,
              P1Function< real_t >&                      u_h,
              P1Function< real_t >&                      b,
              uint_t                                     l_min,
              uint_t                                     l_max ) const
   {
      using walberla::math::one_div_root_two;
      using walberla::math::pi;

      // setup rhs function f and analytic solution u of pde
      std::function< real_t( const Point3D& ) > _f;
      std::function< real_t( const Point3D& ) > _u;

      if ( type == DIRAC_REGULARIZED )
      {
         const real_t sqrt_2pi_pow_3 = std::pow( 2.0 * pi, 3.0 / 2.0 ); //sqrt(2π)^3
         const real_t sig2           = sigma * sigma;
         const real_t sig3           = sig2 * sigma;

         if ( dim == 2 )
         {
            WALBERLA_ABORT( "regularized dirac not implemented for 2d" );
         }
         else
         {
            _f = [=]( const Point3D& x ) -> real_t {
               return std::exp( -0.5 * x.squaredNorm() / sig2 ) / ( sqrt_2pi_pow_3 * sig3 );
            };

            _u = [*this, sqrt_2pi_pow_3]( const Point3D& x ) -> real_t {
               real_t r = x.norm();
               if ( r <= 0.0 )
                  return 1.0 / ( sqrt_2pi_pow_3 * sigma );
               else
                  return std::erf( one_div_root_two * r / sigma ) / ( 4.0 * pi * r );
            };
         }
      }

      if ( type == DIRAC )
      {
         _f = []( const Point3D& x ) -> real_t { return ( x.norm() < 1e-10 ) ? std::numeric_limits< real_t >::infinity() : 0.0; };

         if ( dim == 2 )
         {
            _u = []( const Point3D& x ) -> real_t { return -std::log( x.norm() ) / ( 2.0 * pi ); };
         }
         else
         {
            _u = []( const Point3D& x ) -> real_t { return 1.0 / ( 4.0 * pi * x.norm() ); };
         }
      }

      if ( type == SLIT || type == REENTRANT_CORNER )
      {
         const real_t alpha = ( type == SLIT ) ? 1.0 / 2.0 : 2.0 / 3.0;

         if ( type == REENTRANT_CORNER && dim == 3 )
         {
            WALBERLA_ABORT( "" << name() << " not implemented for 3d" );
         }

         _f = []( const Point3D& ) -> real_t { return 0.0; };
         _u = [=]( const Point3D& x ) -> real_t {
            auto r   = x.norm();
            auto phi = std::atan2( x[1], x[0] ); // only valid in 2D!
            if ( phi < 0 )
               phi += 2 * pi;

            return std::pow( r, alpha ) * std::sin( alpha * phi );
         };
      }

      if ( type == WAVES )
      {
         auto omega = 2.0 * pi * n_w;
         auto alpha = p_w;
         // v(t) = 1 - cos(φ(t)), φ(t) = ωte^(α(t-1))
         auto v = [=]( const real_t& t ) { return 1 - std::cos( omega * t * std::exp( alpha * ( t - 1.0 ) ) ); };
         // v''(t) = sin(φ)φ'' + cos(φ)φ'φ'
         auto d2v = [=]( const real_t& t ) {
            auto weat1 = omega * std::exp( alpha * ( t - 1.0 ) );     // ωe^(α(t-1))
            auto phi   = t * weat1;                                   // φ = ωte^(α(t-1))
            auto dphi  = weat1 * ( 1.0 + alpha * t );                 // φ' = ωe^(α(t-1))(1+αt)
            auto d2phi = weat1 * ( 2.0 * alpha + alpha * alpha * t ); // φ'' = ωe^(α(t-1))(2α+α^2t)
            return std::sin( phi ) * d2phi + std::cos( phi ) * dphi * dphi;
         };

         if ( dim == 3 )
         {
            _u = [=]( const hyteg::Point3D& x ) { return v( x[0] ) * v( x[1] ) * v( x[2] ); };
            _f = [=]( const hyteg::Point3D& x ) {
               auto vx   = v( x[0] );
               auto vy   = v( x[1] );
               auto vz   = v( x[2] );
               auto d2vx = d2v( x[0] );
               auto d2vy = d2v( x[1] );
               auto d2vz = d2v( x[2] );
               return -d2vx * vy * vz - vx * d2vy * vz - vx * vy * d2vz;
            };
         }
         else
         {
            _u = [=]( const hyteg::Point3D& x ) { return v( x[0] ) * v( x[1] ); };
            _f = [=]( const hyteg::Point3D& x ) {
               auto vx   = v( x[0] );
               auto vy   = v( x[1] );
               auto d2vx = d2v( x[0] );
               auto d2vy = d2v( x[1] );
               return -d2vx * vy - vx * d2vy;
            };
         }
      }

      if ( type == WAVES_K )
      {
         auto v = [*this]( const real_t& t ) {
            const auto c1 = n_w * p_w * 2 * pi;
            const auto c2 = log( c1 );
            const auto c3 = c1 * c2 / p_w;
            const auto c4 = pow( c1, t ) / p_w;
            return cos( c4 ) + c3 * t;
         };
         if ( dim == 3 )
         {
            _u = [=]( const hyteg::Point3D& x ) { return v( x[0] * x[1] * x[2] ); };
         }
         else
         {
            _u = [=]( const hyteg::Point3D& x ) { return v( x[0] * x[1] ); };
         }

         _f = [=]( const hyteg::Point3D& ) { return 0; };
      }

      if ( type == JUMP_COEFF )
      {
         if ( dim == 3 )
         {
            WALBERLA_ABORT( "" << name() << " not implemented for 3d" );
         }

         real_t du_dx_min = real_c( 1.0 ) / k_lo;
         real_t du_dx_max = real_c( 1.0 ) / k_hi;
         real_t du_dy_min = ( x_jump_0 - x_jump_1 ) / k_lo;
         real_t du_dy_max = ( x_jump_0 - x_jump_1 ) / k_hi;
         real_t u_jump    = du_dx_min * x_jump_0;

         _u = [=, *this]( const hyteg::Point3D& x ) {
            // kink at { (x,y) | x + (x_jump_0 - x_jump_1)y = x_jump_0 }
            real_t x_jump_y = x_jump_0 * ( real_c( 1.0 ) - x[1] ) + x_jump_1 * x[1];
            if ( x[0] < x_jump_y )
            {
               return du_dx_min * x[0] + du_dy_min * x[1];
            }
            else
            {
               return u_jump + du_dx_max * ( x[0] - x_jump_0 ) + du_dy_max * x[1];
            }
         };

         _f = []( const Point3D& ) -> real_t { return 0.0; };
      }
      if ( type == JUMP_COEFF_REGULARIZED )
      {
         if ( dim == 3 )
         {
            WALBERLA_ABORT( "" << name() << " not implemented for 3d" );
         }
         _u = [*this]( const hyteg::Point3D& x ) {
            return ( -2 * sigma * x[0] + log( 2 * exp( sigma * ( x[0] - 0.5 ) ) + 1 ) ) / sigma;
         };

         _f = []( const Point3D& ) -> real_t { return 0.0; };
      }

      // interpolate rhs of pde
      for ( uint_t lvl = l_min; lvl <= l_max; ++lvl )
         f.interpolate( _f, lvl );
      // construct rhs of linear system s.th. b_i = ∫fφ_i
      if ( type == DIRAC )
      {
         // ∫δ_0 φ_i = φ_i(0)
         auto _b = [=]( const Point3D& x ) -> real_t { return ( _f( x ) > 0.0 ) ? 1.0 : 0.0; };
         for ( uint_t lvl = l_min; lvl <= l_max; ++lvl )
            b.interpolate( _b, lvl );
      }
      else
      {
         // b_i = ∫f φ_i = (f,φ_i)_0
         L2Space< 5, P1Function< real_t > > L2( storage, l_max );
         for ( uint_t lvl = l_min; lvl <= l_max; ++lvl )
         {
            L2.setLvl( lvl );
            L2.dot( _f, b );
         }
      }

      // analytic solution
      u = _u;

      // initialize u_h
      for ( uint_t lvl = l_min; lvl <= l_max; ++lvl )
         u_h.interpolate( _u, lvl, DirichletBoundary );
   }

   // general setting
   const Type   type;
   const uint_t dim;
   // parameters
   real_t sigma;          // standard deviation
   real_t n_w;            // number of waves
   real_t p_w;            // 'squeeze' parameter of waves
   real_t k_lo, k_hi;     // values of jump coefficient
   real_t x_jump_0 = 0.4; // position of jump
   real_t x_jump_1 = 0.6;
};

SetupPrimitiveStorage domain( const ModelProblem& problem, uint_t N, const std::string& inputMsh )
{
   MeshInfo meshInfo = MeshInfo::emptyMeshInfo();

   if ( inputMsh != "" )
   {
      meshInfo = MeshInfo::fromGmshFile( inputMsh );
   }
   else if ( problem.dim == 2 )
   {
      if ( problem.type == ModelProblem::REENTRANT_CORNER )
      {
         if ( N % 2 != 0 || N < 2 || N > 10 )
         {
            WALBERLA_ABORT( "Initial resolution for reentrant corner must be an even number with 2 <= N <= 10!" );
         }
         uint_t n_el     = N * N * 3 / 2;
         auto   filename = "data/LShape_" + std::to_string( n_el ) + "el.msh";
         meshInfo        = MeshInfo::fromGmshFile( filename );
      }
      else if ( problem.type == ModelProblem::WAVES || problem.type == ModelProblem::WAVES_K ||
                problem.type == ModelProblem::JUMP_COEFF )
      {
         // (0,1)^2
         Point2D n( { 1, 1 } );
         meshInfo = MeshInfo::meshRectangle( { 0, 0 }, n, MeshInfo::CRISS, N, N );
      }
      else
      {
         // (-1,1)^2
         Point2D n( { 1, 1 } );
         meshInfo = MeshInfo::meshRectangle( -n, n, MeshInfo::CRISS, N, N );
      }
   }
   else
   {
      if ( problem.type == ModelProblem::SLIT )
      {
         if ( N % 2 != 0 )
         {
            WALBERLA_ABORT( "Initial resolution for slit domain must be an even number!" );
         }
         Point3D n( { 1, 1, 0.1 } );
         meshInfo = MeshInfo::meshCuboid( -n, n, N, N, 1 );
      }
      else if ( problem.type == ModelProblem::WAVES || problem.type == ModelProblem::WAVES_K )
      {
         Point3D n( { 1, 1, 1 } );
         meshInfo = MeshInfo::meshCuboid( 0 * n, n, N, N, N );
      }
      else
      {
         Point3D n( { 1, 1, 1 } );
         meshInfo = MeshInfo::meshCuboid( -n, n, N, N, N );
      }
   }

   SetupPrimitiveStorage setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );

   // setup boundary conditions

   // dirichlet boundary conditions on entire boundary
   setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );

   if ( problem.type == ModelProblem::SLIT )
   {
      if ( problem.dim == 3 )
      {
         // Neumann boundary on top and bottom of plate
         setupStorage.setMeshBoundaryFlagsOnBoundary( 2, 0, true );
         auto onBoundary = []( const Point3D& x ) -> bool {
            return std::abs( x[0] ) >= 1 - 1e-15 || //
                   std::abs( x[1] ) >= 1 - 1e-15;
         };
         setupStorage.setMeshBoundaryFlagsByCentroidLocation( 1, onBoundary, true );
      }
      // dirichlet boundary on slit
      auto onBoundary = []( const Point3D& x ) -> bool { return std::abs( x[1] ) < 1e-50 && x[0] >= 0.0; };
      setupStorage.setMeshBoundaryFlagsByVertexLocation( 1, onBoundary, true );
   }

   return setupStorage;
}

// solve problem with current refinement and return list of elementwise squared errors of local elements
template < class A_t >
adaptiveRefinement::ErrorVector solve( adaptiveRefinement::Mesh&                mesh,
                                       const ModelProblem&                      problem,
                                       uint_t                                   u0,
                                       std::shared_ptr< P1Function< real_t > >& u_old,
                                       uint_t                                   l_interpolate,
                                       uint_t                                   l_min,
                                       uint_t                                   l_max,
                                       uint_t                                   n_cycles,
                                       uint_t                                   max_iter,
                                       uint_t                                   n1,
                                       uint_t                                   n2,
                                       real_t                                   tol,
                                       real_t                                   cg_tol,
                                       std::string                              vtkname,
                                       bool                                     writePartitioning,
                                       bool                                     writeMeshfile,
                                       bool                                     printMeshData,
                                       uint_t                                   refinement_step,
                                       bool                                     error_indicator,
                                       bool                                     global_error_estimate,
                                       uint_t                                   error_freq,
                                       uint_t                                   error_lvl,
                                       bool                                     loadbalancing )
{
   // timing
   real_t t0, t1;
   real_t t_loadbalancing, t_primitivestorage, t_init, t_residual, t_error, t_interpolate, t_error_indicator, t_solve, t_callback;

   // load balancing
   auto lb_scheme = ( loadbalancing ) ? adaptiveRefinement::GREEDY : adaptiveRefinement::ROUND_ROBIN;
   if ( u0 == 0 || u_old == nullptr )
   {
      WALBERLA_LOG_INFO_ON_ROOT( "* apply load balancing ..." );
      // if u0 is initialized with zero, we apply load balancing before creating the storage.
      // else, we first interpolate u before applying load balancing
      t0 = walberla::timing::getWcTime();
      mesh.loadbalancing( lb_scheme, false, true, true );
      t1              = walberla::timing::getWcTime();
      t_loadbalancing = t1 - t0;
   }
   else
   {
      t_loadbalancing = 0;
   }

   WALBERLA_LOG_INFO_ON_ROOT( "* create PrimitiveStorage ..." );
   t0                 = walberla::timing::getWcTime();
   auto storage       = mesh.make_storage();
   t1                 = walberla::timing::getWcTime();
   t_primitivestorage = t1 - t0;
   WALBERLA_LOG_INFO_ON_ROOT( " -> number of macro elements: " << mesh.n_elements() );
   WALBERLA_LOG_INFO_ON_ROOT( "" );

   WALBERLA_LOG_INFO_ON_ROOT( "* setup system ..." );

   // operators
   t0 = walberla::timing::getWcTime();
   std::shared_ptr< A_t > A;
   auto                   P = std::make_shared< P1toP1LinearProlongation<> >();
   auto                   R = std::make_shared< P1toP1LinearRestriction<> >();

   if constexpr ( std::is_same_v< A_t, DivkGrad > )
   {
      auto k = problem.coeff();
      A      = std::make_shared< A_t >( storage, l_min, l_max, DivkGradForm( k, k ) );
   }
   else
   {
      A = std::make_shared< A_t >( storage, l_min, l_max );
   }
   // FE functions
   auto                 u = std::make_shared< P1Function< real_t > >( "u_h", storage, l_min, l_max ); // discrete solution
   P1Function< real_t > f( "f", storage, l_min, l_max );                                              // rhs of strong form
   P1Function< real_t > b( "b(f)", storage, l_min, l_max );                                           // rhs of weak form
   P1Function< real_t > r( "r", storage, l_min, l_max );                                              // residual
   P1Function< real_t > tmp( "tmp", storage, l_min, l_max );                                          // temporary vector

   std::function< real_t( const Point3D& ) > u_anal;

   // global DoF
   tmp.interpolate( 1.0, l_max, Inner | NeumannBoundary );
   auto n_dof = uint_t( tmp.dotGlobal( tmp, l_max ) );
   // cg-dof
   tmp.interpolate( 1.0, l_min, Inner | NeumannBoundary );
   auto n_dof_coarse = uint_t( tmp.dotGlobal( tmp, l_min ) );

   t1     = walberla::timing::getWcTime();
   t_init = t1 - t0;
   WALBERLA_LOG_INFO_ON_ROOT( " -> number of global DoF: " << n_dof );
   auto v_mean = mesh.volume() / real_t( mesh.n_elements() );
   auto h_mean = sqrt( 2 * v_mean );
   if ( problem.dim == 3 )
   {
      h_mean = pow( 6 * v_mean, 1.0 / 3.0 );
   }
   h_mean /= real_t( 1 << l_max );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> h_mean = %3.3e", h_mean ) );

   // computation of residual and L2 error
   t_residual = 0;
   t_error    = 0;

   L2Space< 5, P1Function< real_t > > L2( storage, std::max( l_max, error_lvl ) );
   std::map< PrimitiveID, real_t >    err_el;

   t0 = walberla::timing::getWcTime();
   tmp.setToZero( l_max );

   auto compute_residual = [&]() -> real_t {
      auto my_t0 = walberla::timing::getWcTime();
      A->apply( *u, tmp, l_max, Inner | NeumannBoundary, Replace );
      r.assign( { 1.0, -1.0 }, { b, tmp }, l_max, Inner | NeumannBoundary );
      auto norm_r = std::sqrt( r.dotGlobal( r, l_max, Inner | NeumannBoundary ) / real_t( n_dof ) );
      auto my_t1  = walberla::timing::getWcTime();
      t_residual += my_t1 - my_t0;
      return norm_r;
   };
   auto compute_L2error = [&]() -> real_t {
      auto my_t0 = walberla::timing::getWcTime();
      err_el.clear();
      auto err = [&]( const Point3D& x, const PrimitiveID& id ) {
         real_t ux;
         u->evaluate( x, l_max, ux, 1e-5, id );
         return u_anal( x ) - ux;
      };
      auto norm_e = L2.norm( err, err_el );
      auto my_t1  = walberla::timing::getWcTime();
      t_error += my_t1 - my_t0;
      return norm_e;
   };

   // initialize analytic solution, rhs and boundary values
   problem.init( storage, u_anal, f, *u, b, l_min, l_max );

   t1 = walberla::timing::getWcTime();
   t_init += t1 - t0;

   // initialize u_h
   if ( u0 == 1 && u_old != nullptr )
   {
      // todo: only interpolate on l_min (and apply load balancing before interpolation)
      // ! this requires implementing a version of migrate that allows having the same primitive on multiple processes
      // ! alternatively, we could use a separate storage for each process only keeping the local primitives
      // interpolate old solution to new mesh
      t0 = walberla::timing::getWcTime();
      WALBERLA_LOG_INFO_ON_ROOT( " -> initialize u=u_old" );
      u->interpolate( *u_old, l_max, l_interpolate );
      t1            = walberla::timing::getWcTime();
      t_interpolate = t1 - t0;
      // apply load balancing
      WALBERLA_LOG_INFO_ON_ROOT( " -> apply load balancing" );
      t0                 = walberla::timing::getWcTime();
      auto migrationInfo = mesh.loadbalancing( lb_scheme, true, false, true );
      storage->migratePrimitives( migrationInfo );
      t1 = walberla::timing::getWcTime();
      t_loadbalancing += t1 - t0;
   }
   else
   {
      t_interpolate = 0;
      WALBERLA_LOG_INFO_ON_ROOT( " -> initialize u=0" );
   }

   // solver
   t0 = walberla::timing::getWcTime();
   // smoother
   auto smoother = std::make_shared< GaussSeidelSmoother< A_t > >();
   // coarse grid solver
   auto cgIter = std::max( uint_t( 50 ), 2 * n_dof_coarse );
#ifdef HYTEG_BUILD_WITH_PETSC
   auto cgs = std::make_shared< PETScCGSolver< A_t > >( storage, l_min, 1e-30, cg_tol, cgIter );
#else
   auto cgs = std::make_shared< CGSolver< A_t > >( storage, l_min, l_min, cgIter, cg_tol );
#endif

   // error indicator
   t_error_indicator = 0.0;
   t_callback        = 0.0;
   std::unique_ptr< adaptiveRefinement::ErrorEstimator< P1Function< real_t > > > errorEstimator;
   uint_t j_max = global_error_estimate ? l_max - l_min - 1 : 0;
   if ( error_indicator || global_error_estimate )
   {
      errorEstimator = std::make_unique< adaptiveRefinement::ErrorEstimator< P1Function< real_t > > >( *u, j_max );
   }

   // multigrid
   auto gmg = std::make_shared< GeometricMultigridSolver< A_t > >( storage, smoother, cgs, R, P, l_min, l_max, n1, n2 );
   auto fmg = std::make_shared< FullMultigridSolver< A_t > >( storage, gmg, P, l_min, l_max, n_cycles );
   if ( error_indicator || global_error_estimate )
   {
      auto callback = [&]( uint_t lvl ) {
         real_t my_t0 = walberla::timing::getWcTime();
         errorEstimator->fmg_callback()( lvl );
         real_t my_t1 = walberla::timing::getWcTime();
         t_callback += my_t1 - my_t0;
      };
      fmg = std::make_shared< FullMultigridSolver< A_t > >( storage, gmg, P, l_min, l_max, n_cycles, []( uint_t ) {}, callback );
   };

   t1 = walberla::timing::getWcTime();
   t_init += t1 - t0;

   WALBERLA_LOG_INFO_ON_ROOT( " -> Time spent to ...  " );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "load balancing", t_loadbalancing ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "create primitives", t_primitivestorage ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "initialize problem", t_init ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "interpolate u0", t_interpolate ) );

   WALBERLA_LOG_INFO_ON_ROOT( "" );
   WALBERLA_LOG_INFO_ON_ROOT( "* solve system ..." );
   WALBERLA_LOG_INFO_ON_ROOT( " -> run multigrid solver" );
   WALBERLA_LOG_INFO_ON_ROOT(
       walberla::format( " ->  %10s |%17s |%6s%d%5s", "iteration", "||r||/sqrt(N)", "||e_", l_max, "||_L2" ) );

   // initial residual
   real_t norm_r = compute_residual();
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " ->  %10d |%17.2e |", 0, norm_r ) );

   // solve system
   t_solve = 0;
   for ( uint_t iter = 1; iter <= max_iter; ++iter )
   {
      t0 = walberla::timing::getWcTime();
      if ( iter == 1 )
         fmg->solve( *A, *u, b, l_max );
      else
         gmg->solve( *A, *u, b, l_max );
      t1 = walberla::timing::getWcTime();
      t_solve += t1 - t0;
      norm_r = compute_residual();

      bool converged = norm_r <= tol;

      if ( error_freq > 0 && ( converged || iter % error_freq == 0 ) )
      {
         auto eL2 = compute_L2error();
         WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " ->  %10d |%17.2e |%12.2e", iter, norm_r, eL2 ) );
      }
      else
      {
         WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " ->  %10d |%17.2e |", iter, norm_r ) );
      }

      if ( converged )
         break;
   }

   // apply error indicator
   adaptiveRefinement::ErrorVector err_2_elwise_loc;
   if ( error_indicator || global_error_estimate )
   {
      t0 = walberla::timing::getWcTime();
      errorEstimator->estimate();
      if ( error_indicator )
      {
         err_2_elwise_loc = errorEstimator->eta_T_sq();
      }
      t1 = walberla::timing::getWcTime();
      t_error_indicator += t1 - t0;
   }
   if ( !error_indicator )
   {
      // use actual local L2 error
      for ( auto& [id, err] : err_el )
      {
         err_2_elwise_loc.push_back( { err, id } );
      }
   }
   // print error estimate
   if ( global_error_estimate )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " ->  global error estimate for lvl L: ||e_%d||_L2 ≈ η_j", l_max ) );
      real_t theta_min = 1.0, theta_max = 0.0;
      for ( uint_t j = 1; j <= j_max; ++j )
      {
         auto eta   = errorEstimator->eta( j );
         auto theta = errorEstimator->theta( j );
         auto q     = -log( theta ) / log( 2.0 );

         if ( j > 1 ) // for j=1, the estimates tend to be inaccurate
         {
            theta_min = std::min( theta, theta_min );
            theta_max = std::max( theta, theta_max );
         }

         WALBERLA_LOG_INFO_ON_ROOT(
             walberla::format( " ->  j=%d: η_j = %1.2e, θ_j ≈ %1.2f ⇒ ||e||_L2 ≈ O(h^%1.2f)", j, eta, theta, q ) );
      }
      auto rho = ( j_max < 3 ) ? 0.0 : theta_min / theta_max;
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " ->  reliability: ϱ = %1.2f", rho ) );
      if ( rho < 0.9 )
      {
         WALBERLA_LOG_WARNING_ON_ROOT( " ->  Low reliability! Above estimates may be inaccurate!" )
      }
   }

   t_error_indicator += t_callback;
   t_solve -= t_callback;

   WALBERLA_LOG_INFO_ON_ROOT( " -> Time spent to ...  " );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "system solve", t_solve ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "compute residual", t_residual ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "compute error", t_error ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> %20s: %12.3e", "error indicator", t_error_indicator ) );

   printCurrentMemoryUsage();

   // export to vtk
   if ( vtkname != "" )
   {
      // coefficient
      P1Function< real_t > k( "k", storage, l_max, l_max );
      k.interpolate( problem.coeff(), l_max );

      // error
      P1Function< real_t > err( "err", storage, l_max, l_max );
      P1Function< real_t > err_abs( "err_abs", storage, l_max, l_max );

      auto _err = [&]( const Point3D& x ) {
         real_t ux;
         u->evaluate( x, l_max, ux, 1e-5 );
         return u_anal( x ) - ux;
      };
      auto _err_abs = [&]( const Point3D& x ) { return std::abs( _err( x ) ); };

      err.interpolate( _err, l_max );
      err_abs.interpolate( _err_abs, l_max );

      // write vtk file
      VTKOutput vtkOutput( "output", vtkname, storage );
      vtkOutput.setVTKDataFormat( vtk::DataFormat::BINARY );
      vtkOutput.add( k );
      vtkOutput.add( f );
      vtkOutput.add( *u );
      vtkOutput.add( b );
      vtkOutput.add( err );
      vtkOutput.add( err_abs );
      vtkOutput.write( l_max, refinement_step );
   }

   if ( writePartitioning )
   {
      std::map< std::string, std::map< PrimitiveID, real_t > > realData;
      std::map< std::string, std::map< PrimitiveID, real_t > > errData;
      errData["estL2error"] = err_el;

      writeDomainPartitioningVTK(
          *storage, "output", vtkname + "_partitioning_vertices_ts" + std::to_string( refinement_step ), VTK_VERTEX, realData );
      writeDomainPartitioningVTK(
          *storage, "output", vtkname + "_partitioning_edges_ts" + std::to_string( refinement_step ), VTK_LINE, realData );
      if ( storage->hasGlobalCells() )
      {
         writeDomainPartitioningVTK(
             *storage, "output", vtkname + "_partitioning_faces_ts" + std::to_string( refinement_step ), VTK_TRIANGLE, realData );
         writeDomainPartitioningVTK(
             *storage, "output", vtkname + "_partitioning_cells_ts" + std::to_string( refinement_step ), VTK_TETRA, errData );
      }
      else
      {
         writeDomainPartitioningVTK(
             *storage, "output", vtkname + "_partitioning_faces_ts" + std::to_string( refinement_step ), VTK_TRIANGLE, errData );
      }
   }

   if ( writeMeshfile )
   {
      mesh.exportMesh( "output/" + vtkname + "_mesh_" + std::to_string( refinement_step ) + ".msh" );
   }

   if ( printMeshData )
   {
      WALBERLA_ROOT_SECTION()
      {
         std::ofstream file( "output/" + vtkname + "_mesh_" + std::to_string( refinement_step ) + ".dat" );

         file << std::setw( 13 ) << "#||centroid||" << std::setw( 13 ) << "R" << std::setw( 13 ) << "V"
              << "\n";

         if ( mesh.dim() == 2 )
         {
            for ( auto& el : mesh.get_elements2d() )
            {
               file << std::setw( 13 ) << el->barycenter( mesh.get_vertices() ).norm() //
                    << std::setw( 13 ) << el->radius( mesh.get_vertices() )            //
                    << std::setw( 13 ) << el->volume( mesh.get_vertices() ) << "\n";
            }
         }
         if ( mesh.dim() == 3 )
         {
            for ( auto& el : mesh.get_elements3d() )
            {
               file << std::setw( 13 ) << el->barycenter( mesh.get_vertices() ).norm() //
                    << std::setw( 13 ) << el->radius( mesh.get_vertices() )            //
                    << std::setw( 13 ) << el->volume( mesh.get_vertices() ) << "\n";
            }
         }
      }
   }

   // update u_old
   u_old.swap( u );

   return err_2_elwise_loc;
}

void solve_for_each_refinement( const SetupPrimitiveStorage&        setupStorage,
                                const ModelProblem&                 problem,
                                uint_t                              n_ref,
                                const adaptiveRefinement::Strategy& ref_strat,
                                uint_t                              l_min,
                                uint_t                              l_max,
                                uint_t                              l_final,
                                uint_t                              u0,
                                uint_t                              n_cycles,
                                uint_t                              max_iter,
                                uint_t                              n1,
                                uint_t                              n2,
                                real_t                              tol,
                                uint_t                              max_iter_final,
                                real_t                              tol_final,
                                real_t                              cg_tol,
                                std::string                         vtkname,
                                bool                                writePartitioning,
                                bool                                writeMeshfile,
                                bool                                printMeshData,
                                bool                                error_indicator,
                                bool                                global_error_estimate,
                                uint_t                              error_freq,
                                uint_t                              error_lvl,
                                bool                                loadbalancing )
{
   // construct adaptive mesh
   adaptiveRefinement::Mesh mesh( setupStorage );
   // store solution from previous refinement as initial guess
   std::shared_ptr< P1Function< real_t > > u_old = nullptr;

   uint_t refinement = 0;
   while ( 1 )
   {
      adaptiveRefinement::ErrorVector local_errors;
      if ( problem.constant_coefficient() )
         local_errors = solve< Laplace >( mesh,
                                          problem,
                                          u0,
                                          u_old,
                                          l_max,
                                          l_min,
                                          l_max,
                                          n_cycles,
                                          max_iter,
                                          n1,
                                          n2,
                                          tol,
                                          cg_tol,
                                          vtkname,
                                          writePartitioning,
                                          writeMeshfile,
                                          printMeshData,
                                          refinement,
                                          error_indicator,
                                          global_error_estimate,
                                          error_freq,
                                          error_lvl,
                                          loadbalancing );
      else
         local_errors = solve< DivkGrad >( mesh,
                                           problem,
                                           u0,
                                           u_old,
                                           l_max,
                                           l_min,
                                           l_max,
                                           n_cycles,
                                           max_iter,
                                           n1,
                                           n2,
                                           tol,
                                           cg_tol,
                                           vtkname,
                                           writePartitioning,
                                           writeMeshfile,
                                           printMeshData,
                                           refinement,
                                           error_indicator,
                                           global_error_estimate,
                                           error_freq,
                                           error_lvl,
                                           loadbalancing );

      if ( refinement >= n_ref )
      {
         WALBERLA_LOG_INFO_ON_ROOT( "" );
         WALBERLA_LOG_INFO_ON_ROOT( "* maximum number of refinements!" );
         break;
      }

      auto n_el_old = mesh.n_elements();
      ++refinement;
      WALBERLA_LOG_INFO_ON_ROOT( "" );
      WALBERLA_LOG_INFO_ON_ROOT( "* apply refinement " << refinement );
      WALBERLA_LOG_INFO_ON_ROOT( " -> n_el_old = " << n_el_old );

      // apply refinement
      auto t0 = walberla::timing::getWcTime();
      mesh.refineRG( local_errors, ref_strat, adaptiveRefinement::Strategy::none(), true );
      auto t1 = walberla::timing::getWcTime();
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " -> Time spent for refinement: %12.3e", t1 - t0 ) );
      WALBERLA_LOG_INFO_ON_ROOT( " -> n_el_new = " << mesh.n_elements() );
      // compute mesh quality
      auto v_mean       = mesh.volume() / real_t( mesh.n_elements() );
      auto v_minmax     = mesh.min_max_volume();
      auto a_minmax     = mesh.min_max_angle();
      auto a_meanminmax = mesh.mean_min_max_angle();
      WALBERLA_LOG_INFO_ON_ROOT( " -> el volume (min, max, mean): " << v_minmax.first << ", " << v_minmax.second << ", "
                                                                    << v_mean );
      WALBERLA_LOG_INFO_ON_ROOT( " -> angle (min, max) over all elements: " << a_minmax.first << ", " << a_minmax.second );
      WALBERLA_LOG_INFO_ON_ROOT( " -> angle (min, max) mean over all elements: " << a_meanminmax.first << ", "
                                                                                 << a_meanminmax.second );
   }

   if ( l_final > l_max || max_iter_final > max_iter || tol_final < tol )
   {
      WALBERLA_LOG_INFO_ON_ROOT( "" );
      WALBERLA_LOG_INFO_ON_ROOT( "* final solve with " );
      if ( l_final > l_max )
         WALBERLA_LOG_INFO_ON_ROOT( "    higher micro-level" );
      if ( max_iter_final > max_iter )
         WALBERLA_LOG_INFO_ON_ROOT( "    greater number of iterations" );
      if ( tol_final < tol )
         WALBERLA_LOG_INFO_ON_ROOT( "    smaller tolerance for residual" );

      if ( problem.constant_coefficient() )
      {
         solve< Laplace >( mesh,
                           problem,
                           u0,
                           u_old,
                           l_max,
                           l_min,
                           l_final,
                           n_cycles,
                           max_iter_final,
                           n1,
                           n2,
                           tol_final,
                           cg_tol,
                           vtkname,
                           writePartitioning,
                           writeMeshfile,
                           printMeshData,
                           refinement,
                           error_indicator,
                           global_error_estimate,
                           error_freq,
                           error_lvl,
                           loadbalancing );
      }
      else
      {
         solve< DivkGrad >( mesh,
                            problem,
                            u0,
                            u_old,
                            l_max,
                            l_min,
                            l_final,
                            n_cycles,
                            max_iter_final,
                            n1,
                            n2,
                            tol_final,
                            cg_tol,
                            vtkname,
                            writePartitioning,
                            writeMeshfile,
                            printMeshData,
                            refinement,
                            error_indicator,
                            global_error_estimate,
                            error_freq,
                            error_lvl,
                            loadbalancing );
      }
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
      cfg_->readParameterFile( "data/adaptiveRefinement.prm" );
      cfg = cfg_;
   }
   else
   {
      cfg = walberla::config::create( argc, argv );
   }

   // read parameters
   walberla::Config::BlockHandle parameters = cfg->getOneBlock( "Parameters" );

   const uint_t mp            = parameters.getParameter< uint_t >( "modelProblem" );
   const uint_t dim           = parameters.getParameter< uint_t >( "dim" );
   const real_t sigma         = parameters.getParameter< real_t >( "sigma", 0.0 );
   const uint_t n_waves       = parameters.getParameter< uint_t >( "n_waves", 1u );
   const uint_t squeeze_waves = parameters.getParameter< uint_t >( "squeeze_waves", 1u );
   const real_t kLo           = parameters.getParameter< real_t >( "k_low", 1.0 );
   const real_t kHi           = parameters.getParameter< real_t >( "k_high", 1.0 );

   // todo: add parameters when adding new problems

   const uint_t N_default =
       ( ModelProblem::Type( mp ) == ModelProblem::SLIT || ModelProblem::Type( mp ) == ModelProblem::REENTRANT_CORNER ) ? 2 : 1;
   const uint_t N             = parameters.getParameter< uint_t >( "initial_resolution", N_default );
   const uint_t n_refinements = parameters.getParameter< uint_t >( "n_refinements" );
   const uint_t ref_type =
       parameters.getParameter< uint_t >( "refinement_strategy", adaptiveRefinement::Strategy::WEIGHTED_MEAN );
   const real_t p_refinement          = parameters.getParameter< real_t >( "p_refinement", 0.0 );
   const bool   error_indicator       = parameters.getParameter< bool >( "error_indicator", false );
   bool         global_error_estimate = parameters.getParameter< bool >( "global_error_estimate", false );

   const uint_t l_min   = parameters.getParameter< uint_t >( "cg_level", 0 );
   const uint_t l_max   = parameters.getParameter< uint_t >( "microlevel" );
   const uint_t l_final = parameters.getParameter< uint_t >( "microlevel_final", l_max );

   const uint_t u0             = parameters.getParameter< uint_t >( "initial_guess", 0 );
   const uint_t n_cycles       = parameters.getParameter< uint_t >( "n_cycles" );
   const uint_t max_iter       = parameters.getParameter< uint_t >( "n_iterations" );
   const uint_t max_iter_final = parameters.getParameter< uint_t >( "n_iterations_final", max_iter );
   const uint_t n1             = parameters.getParameter< uint_t >( "presmooth", 2 );
   const uint_t n2             = parameters.getParameter< uint_t >( "postsmooth", 2 );
   const real_t tol            = parameters.getParameter< real_t >( "tolerance" );
   const real_t tol_final      = parameters.getParameter< real_t >( "tolerance_final", tol );
   const real_t cg_tol         = parameters.getParameter< real_t >( "cg_tolerance", tol );

   const bool   loadbalancing = parameters.getParameter< bool >( "loadbalancing", false );
   uint_t       l2error       = parameters.getParameter< uint_t >( "l2error", 0 );
   const uint_t l2_err_lvl    = parameters.getParameter< uint_t >( "l2error_lvl", l_max );

   std::string vtkname           = parameters.getParameter< std::string >( "vtkName", "" );
   std::string inputmesh         = parameters.getParameter< std::string >( "initialMesh", "" );
   const bool  writePartitioning = parameters.getParameter< bool >( "writeDomainPartitioning", false );
   const bool  writeMeshfile     = parameters.getParameter< bool >( "writeMeshfile", false );
   const bool  printMeshData     = parameters.getParameter< bool >( "printMeshData", false );

   const adaptiveRefinement::Strategy ref_strat{ adaptiveRefinement::Strategy::Type( ref_type ), p_refinement };

#ifdef HYTEG_BUILD_WITH_PETSC
   PETScManager petscManager( &argc, &argv );
#endif

   if ( error_indicator && l_max - l_min < 1 )
   {
      WALBERLA_LOG_WARNING_ON_ROOT(
          "Local error indicator requires at least 2 multigrid levels, i.e., microlevel - cg_level >= 1." )
      WALBERLA_LOG_WARNING_ON_ROOT( "Resetting --Parameters.error_indicator=0" );
      global_error_estimate = 0;
   }
   if ( global_error_estimate && l_max - l_min < 3 )
   {
      WALBERLA_LOG_WARNING_ON_ROOT(
          "Global error estimation requires at least 2 multigrid levels, i.e., microlevel - cg_level >= 3." )
      WALBERLA_LOG_WARNING_ON_ROOT( "Resetting --Parameters.global_error_estimate=0" );
      global_error_estimate = 0;
   }
   if ( l2error == 0 && !error_indicator )
   {
      WALBERLA_LOG_WARNING_ON_ROOT( "Running without error indicator requires computation of exact error." )
      WALBERLA_LOG_WARNING_ON_ROOT( "Resetting --Parameters.l2error=max_iter!" )
      l2error = max_iter;
   }

   // setup model problem
   ModelProblem problem( mp, dim );
   if ( vtkname == "auto" )
   {
      vtkname = problem.name();
   }
   problem.set_params( sigma, n_waves, squeeze_waves, kLo, kHi );

   // setup domain
   auto setupStorage = domain( problem, N, inputmesh );

   // print parameters
   WALBERLA_LOG_INFO_ON_ROOT( "Parameters:" )
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d (%s)", "model problem", mp, problem.name().c_str() ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "spatial dimensions", dim ) );
   if ( ModelProblem::Type( mp ) == ModelProblem::DIRAC_REGULARIZED )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2.1e", "sigma", sigma ) );
      if ( sigma <= real_t( 0.0 ) )
      {
         WALBERLA_LOG_WARNING_ON_ROOT( "Sigma should be greater than zero to prevent singularity in the solution at (0,0,0)!" )
      }
   }
   if ( ModelProblem::Type( mp ) == ModelProblem::WAVES || ModelProblem::Type( mp ) == ModelProblem::WAVES_K )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2d", "n_waves", n_waves ) );
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2d", "squeeze", squeeze_waves ) );
   }
   if ( ModelProblem::Type( mp ) == ModelProblem::JUMP_COEFF )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2.1e", "k_low", kLo ) );
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2.1e", "k_high", kHi ) );
   }
   if ( ModelProblem::Type( mp ) == ModelProblem::JUMP_COEFF_REGULARIZED )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2.1e", "sigma", sigma ) );
   }
   // todo: add output for new parameters when adding problems
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "initial resolution", N ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "number of refinements", n_refinements ) );
   if ( ref_strat.t == adaptiveRefinement::Strategy::WEIGHTED_MEAN )
   {
      WALBERLA_LOG_INFO_ON_ROOT( " mark all elements for refinement where ||e_T||^2 > mean_T ||e_T||^2" );
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format(
          "    with weighted mean μ(x) = (∑_i i^%1.1f x_i)/(∑_i i^%1.1f) for x_1 <= x_2 <= ...", p_refinement, p_refinement ) );
   }
   if ( ref_strat.t == adaptiveRefinement::Strategy::PERCENTILE )
   {
      WALBERLA_LOG_INFO_ON_ROOT(
          walberla::format( " %30s: %3.1f%%", "proportion of elements marked for refinement", p_refinement * 100.0 ) );
   }
   if ( error_indicator )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: u_%d - u_%d", "error estimate for refinement", l_max - 1, l_max ) );
   }
   else
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: u_%d - u", "error for refinement", l_max ) );
   }
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %s", "initial guess", ( u0 ) ? "interpolated" : "zero" ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d / %d", "level (min/max)", l_min, l_max ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "max iterations", max_iter ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "V-cycles in FMG", n_cycles ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d/%d", "number of (gs) smoothing steps", n1, n2 ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2.1e / %2.1e", "tolerance (CG/MG)", cg_tol, tol ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format(
       " %30s: %d", "additional final step", ( l_final > l_max || max_iter_final > max_iter || tol_final < tol ) ) );
   if ( l_final > l_max || max_iter_final > max_iter || tol_final < tol )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "level (final solve)", l_final ) );
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "max iterations (final solve)", max_iter_final ) );
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %2.1e", "tolerance (final solve)", tol_final ) );
   }
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "write vtk output", ( vtkname != "" ) ) );
   if ( vtkname != "" )
   {
      WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %s", "vtk name", vtkname.c_str() ) );
   }
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "write domain partitioning", writePartitioning ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "write  mesh to file", writeMeshfile ) );
   WALBERLA_LOG_INFO_ON_ROOT( walberla::format( " %30s: %d", "export mesh data", printMeshData ) );

   // solve/refine iteratively
   solve_for_each_refinement( setupStorage,
                              problem,
                              n_refinements,
                              ref_strat,
                              l_min,
                              l_max,
                              l_final,
                              u0,
                              n_cycles,
                              max_iter,
                              n1,
                              n2,
                              tol,
                              max_iter_final,
                              tol_final,
                              cg_tol,
                              vtkname,
                              writePartitioning,
                              writeMeshfile,
                              printMeshData,
                              error_indicator,
                              global_error_estimate,
                              l2error,
                              l2_err_lvl,
                              loadbalancing );

   return 0;
}
