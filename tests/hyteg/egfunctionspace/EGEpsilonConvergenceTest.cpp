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

#include "hyteg/MeshQuality.hpp"
#include "hyteg/composites/P1DGEP0StokesOperator.hpp"
#include "hyteg/egfunctionspace/EGConvTestUtils.hpp"
#include "hyteg/egfunctionspace/EGOperators.hpp"
#include "hyteg/functions/FunctionTraits.hpp"
#include "hyteg/mesh/MeshInfo.hpp"
#include "hyteg/p1functionspace/P1ConstantOperator.cpp"
#include "hyteg/petsc/PETScManager.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"
#include "hyteg/solvers/MinresSolver.hpp"

using walberla::real_t;
using walberla::uint_t;

using hyteg::Point3D;
using hyteg::dg::eg::EGMassOperator;
using hyteg::dg::eg::EGP0EpsilonStokesOperator;
using hyteg::dg::eg::EGP0StokesOperator;
using hyteg::dg::eg::EGSIPGLaplaceOperator;

namespace hyteg {
    namespace dg {
        namespace eg {

            void
            Epsilon2D(const uint_t minLevel, const uint_t maxLevel, const std::shared_ptr<PrimitiveStorage> &storage);

            void SmoothViscosityTest2D(const uint_t minLevel, const uint_t maxLevel,
                                       const std::shared_ptr<PrimitiveStorage> &storage);

            void IncreasingSteepnessTest(const uint_t minLevel, const uint_t maxLevel);

            void Epsilon3D(const uint_t minLevel, const uint_t maxLevel);

            void SmoothViscosityTest3D(const uint_t minLevel, const uint_t maxLevel);

            void StraightJump3D(const uint_t minLevel, const uint_t maxLevel);

            void IncreasingJump3D(const uint_t minLevel, const uint_t maxLevel);
        } // namespace eg
    } // namespace dg
} // namespace hyteg

int main(int argc, char *argv[]) {
    walberla::MPIManager::instance()->initializeMPI(&argc, &argv);
    walberla::MPIManager::instance()->useWorldComm();
    hyteg::PETScManager petscManager(&argc, &argv);

    /* commandline arguments for petsc solver:
   -ksp_monitor -ksp_rtol 1e-7 -ksp_type minres  -pc_type fieldsplit -pc_fieldsplit_type schur -pc_fieldsplit_schur_fact_type diag  -fieldsplit_0_ksp_type cg -fieldsplit_1_ksp_type cg -pc_fieldsplit_detect_saddle_point -fieldsplit_1_ksp_constant_null_space
   */

    uint_t minLevel = 3;

    if constexpr (false) {
        WALBERLA_LOG_INFO_ON_ROOT("### Testing const Epsilon 2D ###")
        auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/quad_4el.msh");

        hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                  walberla::uint_c(
                                                          walberla::mpi::MPIManager::instance()->numProcesses()));
        setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
        auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

        uint_t maxLevel = 3;

        hyteg::dg::eg::Epsilon2D(minLevel, maxLevel, storage);
    }

    if constexpr (false) {
        WALBERLA_LOG_INFO_ON_ROOT("### Testing const. Epsilon 3D ###")
        hyteg::dg::eg::Epsilon3D(minLevel, 5);
    }


    if constexpr (true) {
        WALBERLA_LOG_INFO_ON_ROOT("### Testing varying viscosity Epsilon 2D ###")
        auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/quad_4el.msh");

        hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                  walberla::uint_c(
                                                          walberla::mpi::MPIManager::instance()->numProcesses()));
        setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
        auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

        uint_t maxLevel = 4;

        hyteg::dg::eg::SmoothViscosityTest2D(minLevel, maxLevel, storage);
    }



    if constexpr (true) {
        WALBERLA_LOG_INFO_ON_ROOT("### Testing varying viscosity Epsilon 3D ###")
        hyteg::dg::eg::SmoothViscosityTest3D(minLevel, 4);
    }

    if constexpr (false) {
        WALBERLA_LOG_INFO_ON_ROOT("### Testing Straight jumps Epsilon 3D ###")
        hyteg::dg::eg::StraightJump3D(minLevel, 5);
    }


    if constexpr (false) {
        WALBERLA_LOG_INFO_ON_ROOT("### Testing Increasing Jump Epsilon 3D ###")
        hyteg::dg::eg::IncreasingJump3D(minLevel, 5);
    }
    return 0;
}

namespace hyteg {
    namespace dg {
        namespace eg {


            void
            Epsilon2D(const uint_t minLevel, const uint_t maxLevel, const std::shared_ptr<PrimitiveStorage> &storage) {
                EGP0EpsilonStokesOperator EGP0EpsilonOp_mu_1(storage, minLevel, maxLevel,
                                                             [](const hyteg::Point3D &) { return 1; });
                P2P1ElementwiseAffineEpsilonStokesOperator P2P1EpsilonOp_mu_1(
                        storage, minLevel, maxLevel, [](const hyteg::Point3D &) { return 1; });

                auto dummyLambda = [](const Point3D &) -> real_t { return 0; };

                hyteg::dg::eg::StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                        "P2P1ConstEpsilonOp2D_hom_asym",
                        std::make_tuple(
                                [](const Point3D &xx) -> real_t {
                                    return std::sin(M_PI * (xx[0] + 1.0) / 2.0) * std::sin(M_PI * (xx[1] + 1.0) / 2.0) *
                                           std::exp(xx[1]);
                                },
                                [](const Point3D &xx) -> real_t {
                                    return std::sin(M_PI * (xx[0] + 1.0) / 2.0) * std::sin(M_PI * (xx[1] + 1.0) / 2.0) *
                                           std::exp(xx[1]);
                                },
                                dummyLambda,
                                [](const Point3D &xx) -> real_t { return xx[0] + xx[1]; }),
                        std::make_tuple(
                                [](const Point3D &p) -> real_t {
                                    const real_t x = p[0];
                                    const real_t y = p[1];
                                    const real_t x0 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                    const real_t x1 = std::sin(x0);
                                    const real_t x2 = std::exp(y);
                                    const real_t x3 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                    const real_t x4 = std::sin(x3);
                                    const real_t x5 = x2 * x4;
                                    const real_t x6 = x2 * std::cos(x3);
                                    const real_t x7 = std::cos(x0);
                                    const real_t x8 = std::pow(M_PI, 2);
                                    return 0.75 * x1 * x2 * x4 * x8 - 1.0 * x1 * x5 - 1.0 * M_PI * x1 * x6 -
                                           0.5 * M_PI * x5 * x7 -
                                           0.25 * x6 * x7 * x8 + 1;
                                },
                                [](const Point3D &p) -> real_t {
                                    const real_t x = p[0];
                                    const real_t y = p[1];
                                    const real_t x0 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                    const real_t x1 = std::sin(x0);
                                    const real_t x2 = std::exp(y);
                                    const real_t x3 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                    const real_t x4 = std::sin(x3);
                                    const real_t x5 = x2 * x4;
                                    const real_t x6 = x2 * std::cos(x3);
                                    const real_t x7 = std::cos(x0);
                                    const real_t x8 = std::pow(M_PI, 2);
                                    return 0.75 * x1 * x2 * x4 * x8 - 2.0 * x1 * x5 - 2.0 * M_PI * x1 * x6 -
                                           0.5 * M_PI * x5 * x7 -
                                           0.25 * x6 * x7 * x8 + 1;
                                },
                                dummyLambda,
                                [](const Point3D &p) -> real_t {
                                    const real_t x = p[0];
                                    const real_t y = p[1];
                                    const real_t x0 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                    const real_t x1 = std::sin(x0);
                                    const real_t x2 = std::exp(y);
                                    const real_t x3 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                    const real_t x4 = x2 * std::sin(x3);
                                    const real_t x5 = M_PI_2;
                                    return -x1 * x2 * x5 * std::cos(x3) - x1 * x4 - x4 * x5 * std::cos(x0);
                                }),
                        std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                storage, minLevel, maxLevel, [](const hyteg::Point3D &) { return 1; }),
                        storage,
                        minLevel,
                        maxLevel);

                hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                        "EGP0ConstEpsilonOp2D_hom_asym",
                        std::make_tuple(
                                [](const Point3D &xx) -> real_t {
                                    return std::sin(M_PI * (xx[0] + 1.0) / 2.0) * std::sin(M_PI * (xx[1] + 1.0) / 2.0) *
                                           std::exp(xx[1]);
                                },
                                [](const Point3D &xx) -> real_t {
                                    return std::sin(M_PI * (xx[0] + 1.0) / 2.0) * std::sin(M_PI * (xx[1] + 1.0) / 2.0) *
                                           std::exp(xx[1]);
                                },
                                dummyLambda,
                                [](const Point3D &xx) -> real_t { return xx[0] + xx[1]; }),
                        std::make_tuple(
                                [](const Point3D &p) -> real_t {
                                    const real_t x = p[0];
                                    const real_t y = p[1];
                                    const real_t x0 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                    const real_t x1 = std::sin(x0);
                                    const real_t x2 = std::exp(y);
                                    const real_t x3 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                    const real_t x4 = std::sin(x3);
                                    const real_t x5 = x2 * x4;
                                    const real_t x6 = x2 * std::cos(x3);
                                    const real_t x7 = std::cos(x0);
                                    const real_t x8 = std::pow(M_PI, 2);
                                    return 0.75 * x1 * x2 * x4 * x8 - 1.0 * x1 * x5 - 1.0 * M_PI * x1 * x6 -
                                           0.5 * M_PI * x5 * x7 -
                                           0.25 * x6 * x7 * x8 + 1;
                                },
                                [](const Point3D &p) -> real_t {
                                    const real_t x = p[0];
                                    const real_t y = p[1];
                                    const real_t x0 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                    const real_t x1 = std::sin(x0);
                                    const real_t x2 = std::exp(y);
                                    const real_t x3 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                    const real_t x4 = std::sin(x3);
                                    const real_t x5 = x2 * x4;
                                    const real_t x6 = x2 * std::cos(x3);
                                    const real_t x7 = std::cos(x0);
                                    const real_t x8 = std::pow(M_PI, 2);
                                    return 0.75 * x1 * x2 * x4 * x8 - 2.0 * x1 * x5 - 2.0 * M_PI * x1 * x6 -
                                           0.5 * M_PI * x5 * x7 -
                                           0.25 * x6 * x7 * x8 + 1;
                                },
                                dummyLambda,
                                [](const Point3D &p) -> real_t {
                                    const real_t x = p[0];
                                    const real_t y = p[1];
                                    const real_t x0 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                    const real_t x1 = std::sin(x0);
                                    const real_t x2 = std::exp(y);
                                    const real_t x3 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                    const real_t x4 = x2 * std::sin(x3);
                                    const real_t x5 = M_PI_2;
                                    return -x1 * x2 * x5 * std::cos(x3) - x1 * x4 - x4 * x5 * std::cos(x0);
                                }),
                        std::make_shared<EGP0EpsilonStokesOperator>(storage, minLevel, maxLevel,
                                                                    [](const hyteg::Point3D &) { return 1; }),
                        storage,
                        minLevel,
                        maxLevel);

                /*
   StokesConvergenceOrderTest< EGP0EpsilonStokesOperator >(
       "EGP0ConstEpsilonOp2D_hom_sym",
       std::make_tuple(
           []( const Point3D& xx ) -> real_t {
              return std::sin( M_PI * ( xx[0] + 1.0 ) / 2.0 ) * std::sin( M_PI * ( xx[1] + 1.0 ) / 2.0 );
           },
           []( const Point3D& xx ) -> real_t {
              return std::sin( M_PI * ( xx[0] + 1.0 ) / 2.0 ) * std::sin( M_PI * ( xx[1] + 1.0 ) / 2.0 );
           },
           dummyLambda,
           []( const Point3D& xx ) -> real_t { return xx[0] + xx[1]; } ),
       std::make_tuple(
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              const real_t x1 = M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 );
              const real_t x2 = M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 );
              return 0.75 * x0 * std::sin( x1 ) * std::sin( x2 ) - 0.25 * x0 * std::cos( x1 ) * std::cos( x2 ) + 1;
           },
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              const real_t x1 = M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 );
              const real_t x2 = M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 );
              return 0.75 * x0 * std::sin( x1 ) * std::sin( x2 ) - 0.25 * x0 * std::cos( x1 ) * std::cos( x2 ) + 1;
           },
           dummyLambda,
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 );
              const real_t x1 = M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 );
              const real_t x2 = M_PI_2;
              return -( x2 * std::sin( x0 ) * std::cos( x1 ) + x2 * std::sin( x1 ) * std::cos( x0 ) );
           } ),
       std::make_shared< EGP0EpsilonStokesOperator >( storage, minLevel, maxLevel, []( const hyteg::Point3D& ) { return 1; } ),
       storage,
       minLevel,
       maxLevel );

   StokesConvergenceOrderTest< EGP0EpsilonStokesOperator >(
       "EGP0ConstEpsilonOp2D_inhom_sym",
       std::make_tuple(
           []( const Point3D& p ) -> real_t {
              const real_t x = p[0];
              const real_t y = p[1];
              return std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) + std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           },
           []( const Point3D& p ) -> real_t {
              const real_t x = p[0];
              const real_t y = p[1];
              return std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) + std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           },
           dummyLambda,
           []( const Point3D& xx ) -> real_t { return xx[0] + xx[1]; } ),
       std::make_tuple(
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              return 0.5 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) +
                     0.25 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) ) + 1;
           },
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              return 0.25 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) +
                     0.5 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) ) + 1;
           },
           dummyLambda,
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = M_PI_2;
              return -x0 * std::cos( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) -
                     x0 * std::cos( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           } ),

       std::make_shared< EGP0EpsilonStokesOperator >( storage, minLevel, maxLevel, []( const hyteg::Point3D& ) { return 1; } ),
       storage,
       minLevel,
       maxLevel );

   StokesConvergenceOrderTest< EGP0EpsilonStokesOperator >(
       "EGP0EpsilonOp2D_inhom_constvisc",
       std::make_tuple(
           []( const Point3D& p ) -> real_t {
              const real_t x = p[0];
              const real_t y = p[1];
              return std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) + std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           },
           []( const Point3D& p ) -> real_t {
              const real_t x = p[0];
              const real_t y = p[1];
              return std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) + std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           },
           dummyLambda,
           []( const Point3D& xx ) -> real_t { return xx[0] + xx[1]; } ),
       std::make_tuple(
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              return 0.5 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) +
                     0.25 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) ) + 1;
           },
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              return 0.25 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) +
                     0.5 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) ) + 1;
           },
           dummyLambda,
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = M_PI_2;
              return -x0 * std::cos( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) -
                     x0 * std::cos( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           } ),
       std::make_shared< EGP0EpsilonStokesOperator >( storage, minLevel, maxLevel, []( const hyteg::Point3D& ) { return 1; } ),
       storage,
       minLevel,
       maxLevel );
       */
                /*

   StokesConvergenceOrderTest< P2P1ElementwiseAffineEpsilonStokesOperator >(
       "P2P1EpsilonOp2D_inhom_constvisc",
       std::make_tuple(
           []( const Point3D& p ) -> real_t {
              const real_t x = p[0];
              const real_t y = p[1];
              return std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) + std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           },
           []( const Point3D& p ) -> real_t {
              const real_t x = p[0];
              const real_t y = p[1];
              return std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) + std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           },
           dummyLambda,
           []( const Point3D& xx ) -> real_t { return xx[0] + xx[1]; } ),
       std::make_tuple(
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              return 0.5 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) +
                     0.25 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) ) + 1;
           },
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = std::pow( M_PI, 2 );
              return 0.25 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) +
                     0.5 * x0 * std::sin( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) ) + 1;
           },
           dummyLambda,
           []( const Point3D& p ) -> real_t {
              const real_t x  = p[0];
              const real_t y  = p[1];
              const real_t x0 = M_PI_2;
              return -x0 * std::cos( M_PI * ( ( 1.0 / 2.0 ) * x + 1.0 / 2.0 ) ) -
                     x0 * std::cos( M_PI * ( ( 1.0 / 2.0 ) * y + 1.0 / 2.0 ) );
           } ),
       std::make_shared< P2P1ElementwiseAffineEpsilonStokesOperator >(
           storage, minLevel, maxLevel, []( const hyteg::Point3D& ) { return 1; } ),
       storage,
       minLevel,
       maxLevel );*/
            }

            void SmoothViscosityTest2D(const uint_t minLevel, const uint_t maxLevel,
                                       const std::shared_ptr<PrimitiveStorage> &storage) {
                auto dummyLambda = [](const Point3D &) -> real_t { return 0; };

                auto resNormsEGP0 = {1e-5, 1e-5, 1e-5, 1e-5, 1e-6};
                auto resNormsP2P1 = {1e-5, 1e-6, 1e-7, 1e-8, 1e-9};

                if (true) {
                    hyteg::dg::eg::StokesConvergenceOrderTest<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(
                            "EGP0EpsilonOpNitscheBC2D_divFree_smoothVisc",
                            std::make_tuple(
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        return y + 2 * std::sin(M_PI * (x + y)) + 4;
                                    },
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        return -x - 2 * std::sin(M_PI * (x + y)) + 3;
                                    },
                                    dummyLambda,
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        return 2 * x - y + 1;
                                    }),
                            std::make_tuple(
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t x0 = M_PI * (x + y);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::exp(x) * std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x3 = x2 * std::sin(x1);
                                        return 4.0 * std::pow(M_PI, 2) * (x3 + 1) * std::sin(x0) -
                                               4.0 * M_PI * ((1.0 / 2.0) * M_PI * x2 * std::cos(x1) + x3) *
                                               std::cos(x0) +
                                               2;
                                    },
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::pow(M_PI, 2);
                                        const real_t x2 = M_PI * (x + y);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        return 2.0 * x0 * x1 * x3 * std::cos(x2) * std::cos(x4) -
                                               4.0 * x1 * (x0 * x3 * std::sin(x4) + 1) * std::sin(x2) -
                                               1;
                                    },
                                    dummyLambda,
                                    dummyLambda),
                            std::make_shared<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(storage,
                                                                                                minLevel,
                                                                                                maxLevel,
                                                                                                [](const hyteg::Point3D &p) {
                                                                                                    const real_t x = p[0];
                                                                                                    const real_t y = p[1];
                                                                                                    return std::exp(x) * std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0)) *
                                                                                                           std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0)) +
                                                                                                           1;
                                                                                                }),
                            storage,
                            minLevel,
                            maxLevel,
                            2, false, false, NULL, std::make_shared<std::vector<real_t>>(resNormsEGP0));
                }
                if (false) {
                    hyteg::dg::eg::StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                            "P2P1EpsilonOp2D_divFree_smoothVisc",
                            std::make_tuple(
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        return y + 2 * std::sin(M_PI * (x + y)) + 4;
                                    },
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        return -x - 2 * std::sin(M_PI * (x + y)) + 3;
                                    },
                                    dummyLambda,
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        return 2 * x - y + 1;
                                    }),
                            std::make_tuple(
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t x0 = M_PI * (x + y);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::exp(x) * std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x3 = x2 * std::sin(x1);
                                        return 4.0 * std::pow(M_PI, 2) * (x3 + 1) * std::sin(x0) -
                                               4.0 * M_PI * ((1.0 / 2.0) * M_PI * x2 * std::cos(x1) + x3) *
                                               std::cos(x0) +
                                               2;
                                    },
                                    [](const Point3D &p) -> real_t {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::pow(M_PI, 2);
                                        const real_t x2 = M_PI * (x + y);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        return 2.0 * x0 * x1 * x3 * std::cos(x2) * std::cos(x4) -
                                               4.0 * x1 * (x0 * x3 * std::sin(x4) + 1) * std::sin(x2) -
                                               1;
                                    },
                                    dummyLambda,
                                    dummyLambda),
                            std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                    storage,
                                    minLevel,
                                    maxLevel,
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        return std::exp(x) * std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0)) *
                                               std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0)) +
                                               1;
                                    }),
                            storage,
                            minLevel,
                            maxLevel,
                            2, false, false, NULL, std::make_shared<std::vector<real_t>>(resNormsP2P1));
                }

         }

            void Epsilon3D(const uint_t minLevel, const uint_t maxLevel) {
                if constexpr (false) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/tet_1el.msh");
                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // tet_1el, inhom.

                    WALBERLA_LOG_INFO_ON_ROOT("### tet_1el, inhom. ###");

                    hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                            "EGP0EpsilonOp3D_tet_1el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) { return -real_c(4) * std::cos(real_c(4) * xx[2]); },
                                    [](const hyteg::Point3D &xx) { return real_c(8) * std::cos(real_c(8) * xx[0]); },
                                    [](const hyteg::Point3D &xx) { return -real_c(2) * std::cos(real_c(2) * xx[1]); },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x) -
                                               64.0 * std::cos(4 * z);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y) +
                                               512.0 * std::cos(8 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z) -
                                               8.0 * std::cos(2 * y);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<EGP0EpsilonStokesOperator>(storage, minLevel, maxLevel,
                                                                        [](const hyteg::Point3D &) { return 1; }),
                            storage,
                            minLevel,
                            maxLevel,
                            5);
                }

                // cube_6el, inhom. solution
                if constexpr (true) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/cube_6el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // cube, hom. solution
                    if (false) {
                        WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, inhom. solution ###");
                        hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                                "EGP0ConstEpsilonOp3D_cube_6el_inhom",
                                std::make_tuple([](const hyteg::Point3D &xx) {
                                                    return -real_c(4) * std::cos(real_c(4) * xx[2]);
                                                },
                                                [](const hyteg::Point3D &xx) {
                                                    return real_c(8) * std::cos(real_c(8) * xx[0]);
                                                },
                                                [](const hyteg::Point3D &xx) {
                                                    return -real_c(2) * std::cos(real_c(2) * xx[1]);
                                                },
                                                [](const hyteg::Point3D &xx) {
                                                    return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) *
                                                           std::sin(2 * xx[2]);
                                                }),
                                std::make_tuple(
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x) -
                                                   64.0 * std::cos(4 * z);
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y) +
                                                   512.0 * std::cos(8 * x);
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z) -
                                                   8.0 * std::cos(2 * y);
                                        },
                                        [](const hyteg::Point3D &) { return 0; }),
                                std::make_shared<EGP0EpsilonStokesOperator>(
                                        storage, minLevel, maxLevel, [](const hyteg::Point3D &) { return 1; }),
                                storage,
                                minLevel,
                                maxLevel,
                                5);
                    }

                    // cube, hom. solution, Nitsche bcs
                    if (true) {
                        hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC EGP0ConstEpsilonOp(
                                storage, minLevel, maxLevel, [](const hyteg::Point3D &) { return 1; });

                        WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, inhom. solution, Nitsche BC ###");
                        hyteg::dg::eg::StokesConvergenceOrderTest<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(
                                "EGP0ConstEpsilonOp3DNitscheBC_cube_6el_inhom",
                                std::make_tuple([](const hyteg::Point3D &xx) {
                                                    return -real_c(4) * std::cos(real_c(4) * xx[2]);
                                                },
                                                [](const hyteg::Point3D &xx) {
                                                    return real_c(8) * std::cos(real_c(8) * xx[0]);
                                                },
                                                [](const hyteg::Point3D &xx) {
                                                    return -real_c(2) * std::cos(real_c(2) * xx[1]);
                                                },
                                                [](const hyteg::Point3D &xx) {
                                                    return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) *
                                                           std::sin(2 * xx[2]);
                                                }),
                                std::make_tuple(
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x) -
                                                   64.0 * std::cos(4 * z);
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y) +
                                                   512.0 * std::cos(8 * x);
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z) -
                                                   8.0 * std::cos(2 * y);
                                        },
                                        [](const hyteg::Point3D &) { return 0; }),
                                std::make_shared<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(
                                        storage, minLevel, maxLevel, [](const hyteg::Point3D &) { return 1; }),
                                storage,
                                minLevel,
                                maxLevel,
                                2);
                    }
                }

                // cube_24el, inhom. solution
                if constexpr (false) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/cube_24el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // cube, hom. solution
                    WALBERLA_LOG_INFO_ON_ROOT("### cube_24el, inhom. solution ###");
                    hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                            "EGP0ConstEpsilonOp3D_cube_24el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) { return -real_c(4) * std::cos(real_c(4) * xx[2]); },
                                    [](const hyteg::Point3D &xx) { return real_c(8) * std::cos(real_c(8) * xx[0]); },
                                    [](const hyteg::Point3D &xx) { return -real_c(2) * std::cos(real_c(2) * xx[1]); },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x) -
                                               64.0 * std::cos(4 * z);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y) +
                                               512.0 * std::cos(8 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z) -
                                               8.0 * std::cos(2 * y);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<EGP0EpsilonStokesOperator>(storage, minLevel, maxLevel,
                                                                        [](const hyteg::Point3D &) { return 1; }),
                            storage,
                            minLevel,
                            maxLevel,
                            5);
                }
            }

            void SmoothViscosityTest3D(const uint_t minLevel, const uint_t maxLevel) {
                auto mu = [](const hyteg::Point3D &p) {
                    const real_t x = p[0];
                    const real_t y = p[1];
                    const real_t z = p[2];
                    return std::exp(x) * std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0)) *
                           std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0)) *
                           std::sin(M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0)) + 1;
                };

                // tet_1el, inhom.
                if constexpr (false) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/tet_1el.msh");
                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // tet_1el, inhom.
                    WALBERLA_LOG_INFO_ON_ROOT("### tet_1el, inhom. ###");

                    hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                            "EGP0EpsilonOp3D_varvisc_tet_1el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) { return -real_c(4) * std::cos(real_c(4) * xx[2]); },
                                    [](const hyteg::Point3D &xx) { return real_c(8) * std::cos(real_c(8) * xx[0]); },
                                    [](const hyteg::Point3D &xx) { return -real_c(2) * std::cos(real_c(2) * xx[1]); },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x5 = 4 * z;
                                        const real_t x6 = 8.0 * std::sin(x4);
                                        return 32.0 * M_PI * x0 * x1 * x3 * std::sin(8 * x) * std::cos(x4) -
                                               M_PI * x0 * x1 * x6 * std::sin(x5) * std::cos(x2) -
                                               8 * (x0 * x1 * x3 * x6 + 8.0) * std::cos(x5) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::sin(x1);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x5 = 8 * x;
                                        const real_t x6 = x0 * x3 * std::sin(x4);
                                        const real_t x7 = 32.0 * x2 * x6;
                                        return -2.0 * M_PI * x0 * x2 * x3 * std::sin(2 * y) * std::cos(x4) -
                                               16 * (-x7 - 32.0) * std::cos(x5) -
                                               2 * (-16.0 * M_PI * x6 * std::cos(x1) - x7) * std::sin(x5) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = 2 * y;
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = std::sin(M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0));
                                        const real_t x5 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x6 = x0 * x4 * std::sin(x5);
                                        const real_t x7 = x3 * x6;
                                        return -2.0 * M_PI * x0 * x3 * x4 * std::sin(x1) * std::cos(x5) -
                                               4 * (2.0 * x7 + 2.0) * std::cos(x1) -
                                               2 * (4.0 * M_PI * x6 * std::cos(x2) + 8.0 * x7) * std::sin(4 * z) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<EGP0EpsilonStokesOperator>(storage, minLevel, maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel,
                            5);
                }

                // pyramid_2el, inhom. solution
                if constexpr (false) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/pyramid_2el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // cube, hom. solution
                    WALBERLA_LOG_INFO_ON_ROOT("### pyramid_2el, inhom. solution ###");
                    hyteg::dg::eg::StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                            "P2P1EpsilonOp3D_varvisc_pyramid_2el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) { return -real_c(4) * std::cos(real_c(4) * xx[2]); },
                                    [](const hyteg::Point3D &xx) { return real_c(8) * std::cos(real_c(8) * xx[0]); },
                                    [](const hyteg::Point3D &xx) { return -real_c(2) * std::cos(real_c(2) * xx[1]); },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x5 = 4 * z;
                                        const real_t x6 = 8.0 * std::sin(x4);
                                        return 32.0 * M_PI * x0 * x1 * x3 * std::sin(8 * x) * std::cos(x4) -
                                               M_PI * x0 * x1 * x6 * std::sin(x5) * std::cos(x2) -
                                               8 * (x0 * x1 * x3 * x6 + 8.0) * std::cos(x5) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::sin(x1);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x5 = 8 * x;
                                        const real_t x6 = x0 * x3 * std::sin(x4);
                                        const real_t x7 = 32.0 * x2 * x6;
                                        return -2.0 * M_PI * x0 * x2 * x3 * std::sin(2 * y) * std::cos(x4) -
                                               16 * (-x7 - 32.0) * std::cos(x5) -
                                               2 * (-16.0 * M_PI * x6 * std::cos(x1) - x7) * std::sin(x5) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = 2 * y;
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = std::sin(M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0));
                                        const real_t x5 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x6 = x0 * x4 * std::sin(x5);
                                        const real_t x7 = x3 * x6;
                                        return -2.0 * M_PI * x0 * x3 * x4 * std::sin(x1) * std::cos(x5) -
                                               4 * (2.0 * x7 + 2.0) * std::cos(x1) -
                                               2 * (4.0 * M_PI * x6 * std::cos(x2) + 8.0 * x7) * std::sin(4 * z) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(storage, minLevel, maxLevel,
                                                                                         mu),
                            storage,
                            minLevel,
                            maxLevel);

                    hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                            "EGP0EpsilonOp3D_varvisc_pyramid_2el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) { return -real_c(4) * std::cos(real_c(4) * xx[2]); },
                                    [](const hyteg::Point3D &xx) { return real_c(8) * std::cos(real_c(8) * xx[0]); },
                                    [](const hyteg::Point3D &xx) { return -real_c(2) * std::cos(real_c(2) * xx[1]); },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x5 = 4 * z;
                                        const real_t x6 = 8.0 * std::sin(x4);
                                        return 32.0 * M_PI * x0 * x1 * x3 * std::sin(8 * x) * std::cos(x4) -
                                               M_PI * x0 * x1 * x6 * std::sin(x5) * std::cos(x2) -
                                               8 * (x0 * x1 * x3 * x6 + 8.0) * std::cos(x5) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::sin(x1);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x5 = 8 * x;
                                        const real_t x6 = x0 * x3 * std::sin(x4);
                                        const real_t x7 = 32.0 * x2 * x6;
                                        return -2.0 * M_PI * x0 * x2 * x3 * std::sin(2 * y) * std::cos(x4) -
                                               16 * (-x7 - 32.0) * std::cos(x5) -
                                               2 * (-16.0 * M_PI * x6 * std::cos(x1) - x7) * std::sin(x5) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = 2 * y;
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = std::sin(M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0));
                                        const real_t x5 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x6 = x0 * x4 * std::sin(x5);
                                        const real_t x7 = x3 * x6;
                                        return -2.0 * M_PI * x0 * x3 * x4 * std::sin(x1) * std::cos(x5) -
                                               4 * (2.0 * x7 + 2.0) * std::cos(x1) -
                                               2 * (4.0 * M_PI * x6 * std::cos(x2) + 8.0 * x7) * std::sin(4 * z) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<EGP0EpsilonStokesOperator>(storage, minLevel, maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel);
                }

                // cube_6el, inhom. solution, EGP0
                if (false) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/cube_6el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // cube, hom. solution
                    WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, inhom. solution ###");

                    hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                            "EGP0EpsilonOp3D_varvisc_cube_6el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) { return -real_c(4) * std::cos(real_c(4) * xx[2]); },
                                    [](const hyteg::Point3D &xx) { return real_c(8) * std::cos(real_c(8) * xx[0]); },
                                    [](const hyteg::Point3D &xx) { return -real_c(2) * std::cos(real_c(2) * xx[1]); },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x5 = 4 * z;
                                        const real_t x6 = 8.0 * std::sin(x4);
                                        return 32.0 * M_PI * x0 * x1 * x3 * std::sin(8 * x) * std::cos(x4) -
                                               M_PI * x0 * x1 * x6 * std::sin(x5) * std::cos(x2) -
                                               8 * (x0 * x1 * x3 * x6 + 8.0) * std::cos(x5) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::sin(x1);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x5 = 8 * x;
                                        const real_t x6 = x0 * x3 * std::sin(x4);
                                        const real_t x7 = 32.0 * x2 * x6;
                                        return -2.0 * M_PI * x0 * x2 * x3 * std::sin(2 * y) * std::cos(x4) -
                                               16 * (-x7 - 32.0) * std::cos(x5) -
                                               2 * (-16.0 * M_PI * x6 * std::cos(x1) - x7) * std::sin(x5) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = 2 * y;
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = std::sin(M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0));
                                        const real_t x5 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x6 = x0 * x4 * std::sin(x5);
                                        const real_t x7 = x3 * x6;
                                        return -2.0 * M_PI * x0 * x3 * x4 * std::sin(x1) * std::cos(x5) -
                                               4 * (2.0 * x7 + 2.0) * std::cos(x1) -
                                               2 * (4.0 * M_PI * x6 * std::cos(x2) + 8.0 * x7) * std::sin(4 * z) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<EGP0EpsilonStokesOperator>(storage, minLevel, maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel,
                            2,
                            false,
                            true);
                }

                // cube_6el, inhom. solution, EGP0 Nitsche BCs
                if (true) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/cube_6el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, inhom. solution, Nitsche Bc ###");
                    auto resNormsEGP0 = {1e-5, 1e-5, 1e-5, 1e-6};
                    hyteg::dg::eg::StokesConvergenceOrderTest<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(
                            "EGP0EpsilonStokesOp3DNitscheBC_varvisc_cube_6el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) {
                                        return -real_c(4) * std::cos(real_c(4) * xx[2]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return real_c(8) * std::cos(real_c(8) * xx[0]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return -real_c(2) * std::cos(real_c(2) * xx[1]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x5 = 4 * z;
                                        const real_t x6 = 8.0 * std::sin(x4);
                                        return 32.0 * M_PI * x0 * x1 * x3 * std::sin(8 * x) * std::cos(x4) -
                                               M_PI * x0 * x1 * x6 * std::sin(x5) * std::cos(x2) -
                                               8 * (x0 * x1 * x3 * x6 + 8.0) * std::cos(x5) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::sin(x1);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x5 = 8 * x;
                                        const real_t x6 = x0 * x3 * std::sin(x4);
                                        const real_t x7 = 32.0 * x2 * x6;
                                        return -2.0 * M_PI * x0 * x2 * x3 * std::sin(2 * y) * std::cos(x4) -
                                               16 * (-x7 - 32.0) * std::cos(x5) -
                                               2 * (-16.0 * M_PI * x6 * std::cos(x1) - x7) * std::sin(x5) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = 2 * y;
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = std::sin(M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0));
                                        const real_t x5 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x6 = x0 * x4 * std::sin(x5);
                                        const real_t x7 = x3 * x6;
                                        return -2.0 * M_PI * x0 * x3 * x4 * std::sin(x1) * std::cos(x5) -
                                               4 * (2.0 * x7 + 2.0) * std::cos(x1) -
                                               2 * (4.0 * M_PI * x6 * std::cos(x2) + 8.0 * x7) * std::sin(4 * z) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(storage,
                                                                                                minLevel,
                                                                                                maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel,
                            2, false, false, NULL, std::make_shared<std::vector<real_t>>(
                                    resNormsEGP0));


                }

                // cube_6el, inhom. solution, P2P1
                if (false) {
                    auto resNormsP2P1 = {1e-5, 1e-6, 1e-6, 1e-5, 1e-6};

                    auto meshInfo = hyteg::MeshInfo::fromGmshFile(
                            "../../data/meshes/3D/cube_6el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // cube, hom. solution
                    WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, inhom. solution, P2P1 ###");

                    hyteg::dg::eg::StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                            "P2P1EpsilonStokesOp3D_varvisc_cube_6el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) {
                                        return -real_c(4) * std::cos(real_c(4) * xx[2]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return real_c(8) * std::cos(real_c(8) * xx[0]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return -real_c(2) * std::cos(real_c(2) * xx[1]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) * std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::sin(M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0));
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x5 = 4 * z;
                                        const real_t x6 = 8.0 * std::sin(x4);
                                        return 32.0 * M_PI * x0 * x1 * x3 * std::sin(8 * x) * std::cos(x4) -
                                               M_PI * x0 * x1 * x6 * std::sin(x5) * std::cos(x2) -
                                               8 * (x0 * x1 * x3 * x6 + 8.0) * std::cos(x5) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x2 = std::sin(x1);
                                        const real_t x3 = std::sin(M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0));
                                        const real_t x4 = M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0);
                                        const real_t x5 = 8 * x;
                                        const real_t x6 = x0 * x3 * std::sin(x4);
                                        const real_t x7 = 32.0 * x2 * x6;
                                        return -2.0 * M_PI * x0 * x2 * x3 * std::sin(2 * y) * std::cos(x4) -
                                               16 * (-x7 - 32.0) * std::cos(x5) -
                                               2 * (-16.0 * M_PI * x6 * std::cos(x1) - x7) * std::sin(x5) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = 2 * y;
                                        const real_t x2 = M_PI * ((1.0 / 2.0) * x + 1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = std::sin(M_PI * ((1.0 / 2.0) * z + 1.0 / 2.0));
                                        const real_t x5 = M_PI * ((1.0 / 2.0) * y + 1.0 / 2.0);
                                        const real_t x6 = x0 * x4 * std::sin(x5);
                                        const real_t x7 = x3 * x6;
                                        return -2.0 * M_PI * x0 * x3 * x4 * std::sin(x1) * std::cos(x5) -
                                               4 * (2.0 * x7 + 2.0) * std::cos(x1) -
                                               2 * (4.0 * M_PI * x6 * std::cos(x2) + 8.0 * x7) * std::sin(4 * z) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                    storage, minLevel, maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel,
                            2,
                            false,
                            false, NULL, std::make_shared<std::vector<real_t>>(
                                    resNormsP2P1));
                }

                // cube_24el, inhom. solution
                if (false) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile(
                            "../../data/meshes/3D/cube_24el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0,
                                                                true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(
                            setupStorage, 1);

                    EGP0EpsilonStokesOperator EGP0EpsilonOp(storage,
                                                            minLevel,
                                                            maxLevel,
                                                            mu);

                    // cube, hom. solution
                    WALBERLA_LOG_INFO_ON_ROOT(
                            "### cube_24el, inhom. solution ###");
                    hyteg::dg::eg::StokesConvergenceOrderTest<EGP0EpsilonStokesOperator>(
                            "EGP0EpsilonOp3D_varvisc_cube_24el_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &xx) {
                                        return -real_c(4) * std::cos(
                                                real_c(4) * xx[2]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return real_c(8) * std::cos(
                                                real_c(8) * xx[0]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return -real_c(2) * std::cos(
                                                real_c(2) * xx[1]);
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) *
                                               std::sin(8 * xx[1]) *
                                               std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = std::sin(
                                                M_PI *
                                                ((1.0 / 2.0) * x +
                                                 1.0 / 2.0));
                                        const real_t x2 = M_PI *
                                                          ((1.0 / 2.0) *
                                                           z +
                                                           1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = M_PI *
                                                          ((1.0 / 2.0) *
                                                           y +
                                                           1.0 / 2.0);
                                        const real_t x5 = 4 * z;
                                        const real_t x6 =
                                                8.0 * std::sin(x4);
                                        return 32.0 * M_PI * x0 * x1 *
                                               x3 * std::sin(8 * x) *
                                               std::cos(x4) -
                                               M_PI * x0 * x1 * x6 *
                                               std::sin(x5) *
                                               std::cos(x2) - 8 *
                                                              (x0 * x1 *
                                                               x3 * x6 +
                                                               8.0) *
                                                              std::cos(
                                                                      x5) +
                                               4 * std::sin(8 * y) *
                                               std::sin(2 * z) *
                                               std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = M_PI *
                                                          ((1.0 / 2.0) *
                                                           x +
                                                           1.0 / 2.0);
                                        const real_t x2 = std::sin(x1);
                                        const real_t x3 = std::sin(
                                                M_PI *
                                                ((1.0 / 2.0) * y +
                                                 1.0 / 2.0));
                                        const real_t x4 = M_PI *
                                                          ((1.0 / 2.0) *
                                                           z +
                                                           1.0 / 2.0);
                                        const real_t x5 = 8 * x;
                                        const real_t x6 =
                                                x0 * x3 * std::sin(x4);
                                        const real_t x7 =
                                                32.0 * x2 * x6;
                                        return -2.0 * M_PI * x0 * x2 *
                                               x3 * std::sin(2 * y) *
                                               std::cos(x4) -
                                               16 * (-x7 - 32.0) *
                                               std::cos(x5) -
                                               2 * (-16.0 * M_PI * x6 *
                                                    std::cos(x1) - x7) *
                                               std::sin(x5) +
                                               8 * std::sin(4 * x) *
                                               std::sin(2 * z) *
                                               std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        const real_t x0 = std::exp(x);
                                        const real_t x1 = 2 * y;
                                        const real_t x2 = M_PI *
                                                          ((1.0 / 2.0) *
                                                           x +
                                                           1.0 / 2.0);
                                        const real_t x3 = std::sin(x2);
                                        const real_t x4 = std::sin(
                                                M_PI *
                                                ((1.0 / 2.0) * z +
                                                 1.0 / 2.0));
                                        const real_t x5 = M_PI *
                                                          ((1.0 / 2.0) *
                                                           y +
                                                           1.0 / 2.0);
                                        const real_t x6 =
                                                x0 * x4 * std::sin(x5);
                                        const real_t x7 = x3 * x6;
                                        return -2.0 * M_PI * x0 * x3 *
                                               x4 * std::sin(x1) *
                                               std::cos(x5) -
                                               4 * (2.0 * x7 + 2.0) *
                                               std::cos(x1) -
                                               2 * (4.0 * M_PI * x6 *
                                                    std::cos(x2) +
                                                    8.0 * x7) *
                                               std::sin(4 * z) +
                                               2 * std::sin(4 * x) *
                                               std::sin(8 * y) *
                                               std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<EGP0EpsilonStokesOperator>(
                                    storage, minLevel, maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel,
                            5);
                }
            }

            void IncreasingJump3D(const uint_t minLevel, const uint_t maxLevel) {

                {
                    real_t alpha = 1;
                    auto mu = [&alpha](const hyteg::Point3D &p) {
                        const real_t x = p[0];
                        const real_t y = p[1];
                        const real_t z = p[2];
                        return std::tanh(alpha * (x + y + z) - 1.5) + 2;
                    };

                    if (true) {
                        auto resNormsP2P1 = {1e-5, 1e-7, 1e-7, 1e-5, 1e-6, 1e-7, 1e-5, 1e-6};

                        auto meshInfo = hyteg::MeshInfo::meshCuboid(Point3D({-1, -1, -1}), Point3D({1, 1, 1}), 1, 1, 1);

                        hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                                  walberla::uint_c(
                                                                          walberla::mpi::MPIManager::instance()->numProcesses()));
                        setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                        auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                        // cube, hom. solution
                        WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, IncreasingJump3D, alpha5 EGP0 ###");

                        StokesConvergenceOrderTest<EGP0EpsilonOperatorStokesNitscheBC>(
                                "EGP0EpsilonOperatorStokesNitscheBC_IncreasingJump3D_alpha5",
                                std::make_tuple(
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return y + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return z - 2 * std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return x + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 2 * x - 4 * y + 10 * z;
                                        }
                                ),
                                std::make_tuple(
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 2;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = std::cos(x1);
                                            const real_t x4 = 1 - std::pow(x2, 2);
                                            return 4.0 * M_PI * alpha * x3 * x4 -
                                                   4 * alpha * x4 * (-0.5 * M_PI * x3 + 0.5) -
                                                   6.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) - 4;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 10;
                                        },
                                        [](const hyteg::Point3D &) { return 0; }),
                                std::make_shared<EGP0EpsilonOperatorStokesNitscheBC>(
                                        storage, minLevel, maxLevel, mu),
                                storage,
                                minLevel,
                                maxLevel,
                                2,
                                true,
                                false, NULL, std::make_shared<std::vector<real_t>>(
                                        resNormsP2P1));
                    }

                    // cube_6el, inhom. solution, P2P1
                    if (false) {
                        auto resNormsP2P1 = {1e-5, 1e-7, 1e-7, 1e-5, 1e-6, 1e-7, 1e-5, 1e-6};

                        auto meshInfo = hyteg::MeshInfo::meshCuboid(Point3D({-1, -1, -1}), Point3D({1, 1, 1}), 1, 1, 1);

                        hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                                  walberla::uint_c(
                                                                          walberla::mpi::MPIManager::instance()->numProcesses()));
                        setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                        auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                        // cube, hom. solution
                        WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, IncreasingJump3D, alpha5 P2P1 ###");

                        StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                "P2P1EpsilonStokesOp3D_IncreasingJump3D_alpha5",
                                std::make_tuple(
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return y + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return z - 2 * std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return x + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 2 * x - 4 * y + 10 * z;
                                        }
                                ),
                                std::make_tuple(
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 2;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = std::cos(x1);
                                            const real_t x4 = 1 - std::pow(x2, 2);
                                            return 4.0 * M_PI * alpha * x3 * x4 -
                                                   4 * alpha * x4 * (-0.5 * M_PI * x3 + 0.5) -
                                                   6.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) - 4;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 10;
                                        },
                                        [](const hyteg::Point3D &) { return 0; }),
                                std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                        storage, minLevel, maxLevel, mu),
                                storage,
                                minLevel,
                                maxLevel,
                                2,
                                true,
                                false, NULL, std::make_shared<std::vector<real_t>>(
                                        resNormsP2P1));
                    }
                }

                {
                    real_t alpha = 10;
                    auto mu = [&alpha](const hyteg::Point3D &p) {
                        const real_t x = p[0];
                        const real_t y = p[1];
                        const real_t z = p[2];
                        return std::tanh(alpha * (x + y + z) - 1.5) + 2;
                    };

                    // cube_6el, inhom. solution, P2P1
                    if (true) {
                        auto resNormsP2P1 = {1e-5, 1e-7, 1e-7, 1e-5, 1e-6, 1e-7, 1e-5, 1e-6};

                        auto meshInfo = hyteg::MeshInfo::meshCuboid(Point3D({-1, -1, -1}), Point3D({1, 1, 1}), 1, 1, 1);

                        hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                                  walberla::uint_c(
                                                                          walberla::mpi::MPIManager::instance()->numProcesses()));
                        setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                        auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                        // cube, hom. solution
                        WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, IncreasingJump3D, alpha10 P2P1 ###");

                        StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                "P2P1EpsilonStokesOp3D_IncreasingJump3D_alpha10",
                                std::make_tuple(
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return y + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return z - 2 * std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return x + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 2 * x - 4 * y + 10 * z;
                                        }
                                ),
                                std::make_tuple(
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 2;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = std::cos(x1);
                                            const real_t x4 = 1 - std::pow(x2, 2);
                                            return 4.0 * M_PI * alpha * x3 * x4 -
                                                   4 * alpha * x4 * (-0.5 * M_PI * x3 + 0.5) -
                                                   6.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) - 4;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 10;
                                        },
                                        [](const hyteg::Point3D &) { return 0; }),
                                std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                        storage, minLevel, maxLevel, mu),
                                storage,
                                minLevel,
                                maxLevel,
                                2,
                                true,
                                false, NULL, std::make_shared<std::vector<real_t>>(
                                        resNormsP2P1));
                    }
                }

                {
                    real_t alpha = 20;
                    auto mu = [&alpha](const hyteg::Point3D &p) {
                        const real_t x = p[0];
                        const real_t y = p[1];
                        const real_t z = p[2];
                        return std::tanh(alpha * (x + y + z) - 1.5) + 2;
                    };

                    // cube_6el, inhom. solution, P2P1
                    if (true) {
                        auto resNormsP2P1 = {1e-5, 1e-7, 1e-7, 1e-5, 1e-6, 1e-7, 1e-5, 1e-6};

                        auto meshInfo = hyteg::MeshInfo::meshCuboid(Point3D({-1, -1, -1}), Point3D({1, 1, 1}), 1, 1, 1);

                        hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                                  walberla::uint_c(
                                                                          walberla::mpi::MPIManager::instance()->numProcesses()));
                        setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                        auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                        // cube, hom. solution
                        WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, IncreasingJump3D, alpha20 P2P1 ###");

                        StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                "P2P1EpsilonStokesOp3D_IncreasingJump3D_alpha20",
                                std::make_tuple(
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return y + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return z - 2 * std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];

                                            return x + std::sin(M_PI * (x + y + z));
                                        },
                                        [](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            return 2 * x - 4 * y + 10 * z;
                                        }
                                ),
                                std::make_tuple(
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 2;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = std::cos(x1);
                                            const real_t x4 = 1 - std::pow(x2, 2);
                                            return 4.0 * M_PI * alpha * x3 * x4 -
                                                   4 * alpha * x4 * (-0.5 * M_PI * x3 + 0.5) -
                                                   6.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) - 4;
                                        },
                                        [&alpha](const hyteg::Point3D &p) {
                                            const real_t x = p[0];
                                            const real_t y = p[1];
                                            const real_t z = p[2];
                                            const real_t x0 = x + y + z;
                                            const real_t x1 = M_PI * x0;
                                            const real_t x2 = std::tanh(alpha * x0 - 1.5);
                                            const real_t x3 = M_PI * std::cos(x1);
                                            const real_t x4 = alpha * (1 - std::pow(x2, 2));
                                            const real_t x5 = 2 * x4;
                                            return -2.0 * x3 * x4 - x5 * (0.5 - 0.5 * x3) - x5 * (1.0 * x3 + 0.5) +
                                                   3.0 * std::pow(M_PI, 2) * (x2 + 2) * std::sin(x1) + 10;
                                        },
                                        [](const hyteg::Point3D &) { return 0; }),
                                std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                        storage, minLevel, maxLevel, mu),
                                storage,
                                minLevel,
                                maxLevel,
                                2,
                                true,
                                false, NULL, std::make_shared<std::vector<real_t>>(
                                        resNormsP2P1));
                    }
                }


            }

            void StraightJump3D(const uint_t minLevel, const uint_t maxLevel) {
                auto mu = [](const hyteg::Point3D &p) {
                    const real_t z = p[2];
                    return ((z < 0.5) ? (
                            1
                    )
                                      : (
                                    100
                            ));
                };

                // cube_6el, inhom. solution, P2P1
                if (false) {
                    auto resNormsP2P1 = {1e-5, 1e-7, 1e-7, 1e-5, 1e-6};

                    auto meshInfo = hyteg::MeshInfo::fromGmshFile(
                            "../../data/meshes/3D/cube_6el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    // cube, hom. solution
                    WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, StraightJump3D, P2P1 ###");

                    hyteg::dg::eg::StokesConvergenceOrderTest<P2P1ElementwiseAffineEpsilonStokesOperator>(
                            "P2P1EpsilonStokesOp3D_StraightJump3D_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return z + 2 * std::sin(M_PI * (x + y + z)) + 4;
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return x - std::sin(M_PI * (x + y + z)) + 4;
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return y - std::sin(M_PI * (x + y + z)) + 4;
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) *
                                               std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 6.0 * std::pow(M_PI, 2) * ((z < 0.5) ? (
                                                1
                                        )
                                                                                    : (
                                                                                  100
                                                                          )) * std::sin(M_PI * (x + y + z)) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return -3.0 * std::pow(M_PI, 2) * ((z < 0.5) ? (
                                                1
                                        )
                                                                                     : (
                                                                                   100
                                                                           )) * std::sin(M_PI * (x + y + z)) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return -3.0 * std::pow(M_PI, 2) * ((z < 0.5) ? (
                                                1
                                        )
                                                                                     : (
                                                                                   100
                                                                           )) * std::sin(M_PI * (x + y + z)) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<P2P1ElementwiseAffineEpsilonStokesOperator>(
                                    storage, minLevel, maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel,
                            1,
                            true,
                            false, NULL, std::make_shared<std::vector<real_t>>(
                                    resNormsP2P1));
                }
                if (true) {
                    auto meshInfo = hyteg::MeshInfo::fromGmshFile("../../data/meshes/3D/cube_6el.msh");

                    hyteg::SetupPrimitiveStorage setupStorage(meshInfo,
                                                              walberla::uint_c(
                                                                      walberla::mpi::MPIManager::instance()->numProcesses()));
                    setupStorage.setMeshBoundaryFlagsOnBoundary(1, 0, true);
                    auto storage = std::make_shared<hyteg::PrimitiveStorage>(setupStorage, 1);

                    WALBERLA_LOG_INFO_ON_ROOT("### cube_6el, StraightJump3D, Nitsche Bc ###");
                    auto resNormsEGP0 = {1e-5, 1e-7, 1e-7, 1e-6};
                    hyteg::dg::eg::StokesConvergenceOrderTest<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(
                            "EGP0EpsilonStokesOp3DNitscheBC_StraightJump3D_inhom",
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return z + 2 * std::sin(M_PI * (x + y + z)) + 4;
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return x - std::sin(M_PI * (x + y + z)) + 4;
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return y - std::sin(M_PI * (x + y + z)) + 4;
                                    },
                                    [](const hyteg::Point3D &xx) {
                                        return std::sin(4 * xx[0]) * std::sin(8 * xx[1]) *
                                               std::sin(2 * xx[2]);
                                    }),
                            std::make_tuple(
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return 6.0 * std::pow(M_PI, 2) * ((z < 0.5) ? (
                                                1
                                        )
                                                                                    : (
                                                                                  100
                                                                          )) * std::sin(M_PI * (x + y + z)) +
                                               4 * std::sin(8 * y) * std::sin(2 * z) * std::cos(4 * x);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return -3.0 * std::pow(M_PI, 2) * ((z < 0.5) ? (
                                                1
                                        )
                                                                                     : (
                                                                                   100
                                                                           )) * std::sin(M_PI * (x + y + z)) +
                                               8 * std::sin(4 * x) * std::sin(2 * z) * std::cos(8 * y);
                                    },
                                    [](const hyteg::Point3D &p) {
                                        const real_t x = p[0];
                                        const real_t y = p[1];
                                        const real_t z = p[2];
                                        return -3.0 * std::pow(M_PI, 2) * ((z < 0.5) ? (
                                                1
                                        )
                                                                                     : (
                                                                                   100
                                                                           )) * std::sin(M_PI * (x + y + z)) +
                                               2 * std::sin(4 * x) * std::sin(8 * y) * std::cos(2 * z);
                                    },
                                    [](const hyteg::Point3D &) { return 0; }),
                            std::make_shared<hyteg::dg::eg::EGP0EpsilonOperatorStokesNitscheBC>(storage,
                                                                                                minLevel,
                                                                                                maxLevel, mu),
                            storage,
                            minLevel,
                            maxLevel,
                            1, false, false, NULL, std::make_shared<std::vector<real_t>>(
                                    resNormsEGP0));


                }


            }
        } // namespace eg
    } // namespace dg
} // namespace hyteg
