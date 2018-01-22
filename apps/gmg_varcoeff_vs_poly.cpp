#include <core/timing/Timer.h>
#include <tinyhhg_core/tinyhhg.hpp>
#include <fmt/format.h>
#include <core/Environment.h>

using walberla::real_t;
using walberla::uint_t;
using walberla::uint_c;

using namespace hhg;

int main(int argc, char* argv[])
{

  walberla::Environment walberlaEnv(argc, argv);
  walberla::logging::Logging::instance()->setLogLevel( walberla::logging::Logging::PROGRESS );
  walberla::MPIManager::instance()->useWorldComm();

  const uint_t level_H = 0;
  const uint_t level_h = 11;
  const uint_t minLevel = 2;
  const uint_t maxLevel = level_h - level_H;
  const uint_t maxPolyDegree = 2;
  const uint_t interpolationLevel = maxLevel-1;
  const uint_t max_outer_iter = 50;
  const uint_t max_cg_iter = 50;
  const real_t mg_tolerance = 1e-14;
  const real_t coarse_tolerance = 1e-3;
  const bool polynomialOperator = true;

  MeshInfo meshInfo = MeshInfo::unitSquareMesh(0);
  SetupPrimitiveStorage setupStorage( meshInfo, uint_c ( walberla::mpi::MPIManager::instance()->numProcesses() ) );

  hhg::loadbalancing::roundRobin( setupStorage );

  if (polynomialOperator) {
    WALBERLA_LOG_INFO_ON_ROOT("Polynomial Operator enabled");
  } else {
    WALBERLA_LOG_INFO_ON_ROOT("Polynomial Operator disabled");
  }

  std::shared_ptr<PrimitiveStorage> storage = std::make_shared<PrimitiveStorage>(setupStorage);

  hhg::P1Function< real_t > r("r", storage, minLevel, maxLevel);
  hhg::P1Function< real_t > f("f", storage, minLevel, maxLevel);
  hhg::P1Function< real_t > u("u", storage, minLevel, maxLevel);
  hhg::P1Function< real_t > Lu("Lu", storage, minLevel, maxLevel);
  hhg::P1Function< real_t > u_exact("u_exact", storage, minLevel, maxLevel);
  hhg::P1Function< real_t > err("err", storage, minLevel, maxLevel);
  hhg::P1Function< real_t > npoints_helper("npoints_helper", storage, minLevel, maxLevel);
  std::shared_ptr<P1Function< real_t >> coefficient = std::make_shared<P1Function< real_t >>("coeff", storage, minLevel, maxLevel);

  hhg::P1MassOperator M(storage, minLevel, maxLevel);

  typedef hhg::P1VariableCoefficientLaplaceOperator SolveOperatorNodal;
  typedef hhg::P1PolynomialLaplaceOperator<maxPolyDegree> SolveOperatorPoly;
  typedef Operator< P1Function< real_t >, P1Function< real_t > > GeneralOperator;
  typedef std::shared_ptr<GeneralOperator> SolveOperator;

  std::function<real_t(const hhg::Point3D&)> coeff = [](const hhg::Point3D& x) { return 3*x[0] + 4*x[1] + 1; };
  std::function<real_t(const hhg::Point3D&)> exact = [](const hhg::Point3D& x) { return sin(x[0])*sinh(x[1]); };
  std::function<real_t(const hhg::Point3D&)> rhs = [](const hhg::Point3D& x) { return -4*sin(x[0])*cosh(x[1]) - 3*cos(x[0])*sinh(x[1]); };
  std::function<real_t(const hhg::Point3D&)> ones  = [](const hhg::Point3D&) { return 1.0; };

  u.interpolate(exact, maxLevel, hhg::DirichletBoundary);

  for (uint_t level = minLevel; level <= maxLevel; ++level) {
    coefficient->interpolate(coeff, level);
  }

  u_exact.interpolate(exact, maxLevel);
  npoints_helper.interpolate(rhs, maxLevel);
  M.apply(npoints_helper, f, maxLevel, hhg::All);

  SolveOperator L;

  auto start = walberla::timing::getWcTime();
  if (polynomialOperator) {
    L = std::make_shared<SolveOperatorPoly>(storage, coefficient, coeff, minLevel, maxLevel, interpolationLevel);
  } else {
    L = std::make_shared<SolveOperatorNodal>(storage, coefficient, coeff, minLevel, maxLevel);
  }
  auto end = walberla::timing::getWcTime();
  real_t setupTime = end - start;

  npoints_helper.interpolate(ones, maxLevel);
  real_t npoints = npoints_helper.dot(npoints_helper, maxLevel);

  typedef hhg::CGSolver<hhg::P1Function<real_t>, GeneralOperator> CoarseSolver;
  auto coarseLaplaceSolver = std::make_shared<CoarseSolver>(storage, minLevel, minLevel);
  typedef GMultigridSolver<hhg::P1Function<real_t>, GeneralOperator, CoarseSolver> LaplaceSover;
  LaplaceSover laplaceSolver(storage, coarseLaplaceSolver, minLevel, maxLevel);

  WALBERLA_LOG_INFO_ON_ROOT("Starting V cycles");
  WALBERLA_LOG_INFO_ON_ROOT("iter  abs_res       rel_res       conv          L2-error      Time");

  real_t rel_res = 1.0;

  L->apply(u, Lu, maxLevel, hhg::Inner);
  r.assign({1.0, -1.0}, {&f, &Lu}, maxLevel, hhg::Inner);

  real_t begin_res = std::sqrt(r.dot(r, maxLevel, hhg::Inner));
  real_t abs_res_old = begin_res;

  err.assign({1.0, -1.0}, {&u, &u_exact}, maxLevel);
  real_t discr_l2_err = std::sqrt(err.dot(err, maxLevel) / npoints);

  WALBERLA_LOG_INFO_ON_ROOT(fmt::format("{:3d}   {:e}  {:e}  {:e}  {:e}  -", 0, begin_res, rel_res, begin_res/abs_res_old, discr_l2_err));

  real_t totalTime = real_c(0.0);
  real_t averageConvergenceRate = real_c(0.0);
  const uint_t convergenceStartIter = 3;

  uint_t i = 0;
  for (; i < max_outer_iter; ++i)
  {
    start = walberla::timing::getWcTime();
    laplaceSolver.solve(*L, u, f, r, maxLevel, coarse_tolerance, max_cg_iter, hhg::Inner, LaplaceSover::CycleType::VCYCLE, false);
    end = walberla::timing::getWcTime();
    L->apply(u, Lu, maxLevel, hhg::Inner);
    r.assign({1.0, -1.0}, { &f, &Lu }, maxLevel, hhg::Inner);
    real_t abs_res = std::sqrt(r.dot(r, maxLevel, hhg::Inner));
    rel_res = abs_res / begin_res;
    err.assign({1.0, -1.0}, { &u, &u_exact }, maxLevel);
    discr_l2_err = std::sqrt(err.dot(err, maxLevel) / npoints);

    WALBERLA_LOG_INFO_ON_ROOT(fmt::format("{:3d}   {:e}  {:e}  {:e}  {:e}  {:e}", i+1, abs_res, rel_res, abs_res/abs_res_old, discr_l2_err, end-start));
    totalTime += end-start;

    if (i >= convergenceStartIter) {
      averageConvergenceRate += abs_res/abs_res_old;
    }

    abs_res_old = abs_res;

    if (rel_res < mg_tolerance)
    {
      break;
    }
  }

  WALBERLA_LOG_INFO_ON_ROOT("L(H): " << level_H);
  WALBERLA_LOG_INFO_ON_ROOT("L(h): " << level_h);
  WALBERLA_LOG_INFO_ON_ROOT("interpolationLevel: " << interpolationLevel);
  WALBERLA_LOG_INFO_ON_ROOT("Setup time: " << std::defaultfloat << setupTime);
  WALBERLA_LOG_INFO_ON_ROOT("Time to solution: " << std::defaultfloat << totalTime);
  WALBERLA_LOG_INFO_ON_ROOT("Avg. convergence rate: " << std::scientific << averageConvergenceRate / real_c(i-convergenceStartIter));
  WALBERLA_LOG_INFO_ON_ROOT("L^2 error: " << std::scientific << discr_l2_err);
  WALBERLA_LOG_INFO_ON_ROOT("DoFs: " << (uint_t) npoints);

  return 0;
}
