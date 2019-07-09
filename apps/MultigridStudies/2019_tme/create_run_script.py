import numpy as np

##################
# Omega Sampling #
##################

def omega_sampling():

    base_config = """
Parameters
{
    equation stokes;
    dim 3;
    numFacesPerSide 1;
    discretization P1;
    meshLayout CRISSCROSS;
    symmetricCuboidMesh true;
    numCycles 1;
    cycleType V;
    fmgInnerCycles 1; // 0 == no fmg

    // CRISSCROSS: ~0.4
    // CRISS:    : P1: ? , P2: ~0.72
    sorRelax 0.3;

    symmGSVelocity true;
    numGSVelocity 1;
    symmGSPressure false;
    numGSPressure 1;

    preSmoothingSteps 2;
    postSmoothingSteps 2;
    smoothingIncrement 2;
    minLevel 2;
    maxLevel 5; // P1 level, P2 level is automatically reduced by 1
    skipCyclesForAvgConvRate 0;
    L2residualTolerance 1e-16;
    projectPressureAfterRestriction true;
    calculateDiscretizationError false;
    coarseGridMaxIterations 100000;
    coarseGridResidualTolerance 1e-16;

    outputVTK false;
    outputTiming false;
    outputTimingJSON true;
    outputTimingJSONFile timing.json;
    outputSQL true;
    outputSQLFile omega_sampling.db;
}
"""

    with open("omega_sampling_base_config.prm", "w") as f:
        f.write(base_config)

    discretizations = ["P1", "P2"]
    num_processes = 8
    omegas = {"P1": list(np.arange(0.05, 0.5, 0.05)), "P2": list(np.arange(0.05, 0.5, 0.05))}

    with open("run_omega_sampling.sh", "w") as f:
        f.write("echo\n")
        f.write("echo OMEGA SAMPLING\n")
        f.write("echo\n")
        for discretization in discretizations:
            for omega in omegas[discretization]:
                for symm_gs_velocity in ["true", "false"]:
                    for smooth in range(1, 4):
                        for max_level in range(4, 6):
                            cmd = "mpirun --allow-run-as-root -np {} --map-by core --bind-to core --report-bindings ./MultigridStudies 2019_tme/omega_sampling_base_config.prm " \
                                  "-Parameters.sorRelax={} " \
                                  "-Parameters.discretization={} " \
                                  "-Parameters.symmGSVelocity={} " \
                                  "-Parameters.preSmoothingSteps={} " \
                                  "-Parameters.postSmoothingSteps={} " \
                                  "-Parameters.smoothingIncrement={} " \
                                  "-Parameters.maxLevel={}".format(num_processes, omega, discretization, symm_gs_velocity, smooth, smooth, smooth, max_level)
                            f.write("echo \"{}\"\n".format(cmd))
                            f.write(cmd + "\n")



def fmg_tests():

    base_config = """
Parameters
{
    equation stokes;
    dim 3;
    numFacesPerSide 1;
    discretization P1;
    meshLayout CRISSCROSS;
    symmetricCuboidMesh true;
    numCycles 5;
    cycleType V;
    fmgInnerCycles 1; // 0 == no fmg

    // CRISSCROSS: ~0.4
    // CRISS:    : P1: ? , P2: ~0.72
    sorRelax 0.3;

    symmGSVelocity true;
    numGSVelocity 1;
    symmGSPressure false;
    numGSPressure 1;

    preSmoothingSteps 2;
    postSmoothingSteps 2;
    smoothingIncrement 2;
    minLevel 2;
    maxLevel 8; // P1 level, P2 level is automatically reduced by 1
    skipCyclesForAvgConvRate 0;
    L2residualTolerance 1e-16;
    projectPressureAfterRestriction true;
    calculateDiscretizationError false;
    coarseGridMaxIterations 500;
    coarseGridResidualTolerance 1e-14;

    outputVTK false;
    outputTiming false;
    outputTimingJSON true;
    outputTimingJSONFile timing.json;
    outputSQL true;
    outputSQLFile fmg_benchmark.db;
}
"""

    with open("fmg_tests_base_config.prm", "w") as f:
        f.write(base_config)

    discretizations = ["P1", "P2"]
    num_processes = 8
    sor_omega = {"P1": 0.3, "P2": 0.3}
    symm_gs = ["true", "false"]
    num_pre_post_inc = [(1, 1, 2), (2, 2, 2), (3, 3, 2)]
    inner_cycles = [1, 2]

    with open("run_fmg.sh", "w") as f:
        f.write("echo\n")
        f.write("echo FMG TESTS\n")
        f.write("echo\n")
        for discretization in discretizations:
            for symm in symm_gs:
                    for smooth in num_pre_post_inc:
                        for r in inner_cycles:
                            cmd = "mpirun --allow-run-as-root -np {} --map-by core --bind-to core --report-bindings ./MultigridStudies 2019_tme/fmg_tests_base_config.prm " \
                                  "-Parameters.preSmoothingSteps={} " \
                                  "-Parameters.postSmoothingSteps={} " \
                                  "-Parameters.smoothingIncrement={} " \
                                  "-Parameters.sorRelax={} " \
                                  "-Parameters.symmGSVelocity={} " \
                                  "-Parameters.fmgInnerCycles={} " \
                                  "-Parameters.discretization={} ".format(num_processes, smooth[0], smooth[1], smooth[2], sor_omega[discretization], symm, r, discretization)
                            f.write("echo \"{}\"\n".format(cmd))
                            f.write(cmd + "\n")


def discretization_error():

    base_config = """
Parameters
{
    equation stokes;
    dim 3;
    numFacesPerSide 1;
    discretization P1;
    meshLayout CRISSCROSS;
    symmetricCuboidMesh true;
    numCycles 20;
    cycleType V;
    fmgInnerCycles 0; // 0 == no fmg

    // CRISSCROSS: ~0.4
    // CRISS:    : P1: ? , P2: ~0.72
    sorRelax 0.3;

    symmGSVelocity true;
    numGSVelocity 1;
    symmGSPressure false;
    numGSPressure 1;

    preSmoothingSteps 2;
    postSmoothingSteps 2;
    smoothingIncrement 2;
    minLevel 2;
    maxLevel 8; // P1 level, P2 level is automatically reduced by 1
    skipCyclesForAvgConvRate 0;
    L2residualTolerance 1e-16;
    projectPressureAfterRestriction true;
    calculateDiscretizationError false;
    coarseGridMaxIterations 500;
    coarseGridResidualTolerance 1e-14;

    outputVTK false;
    outputTiming false;
    outputTimingJSON true;
    outputTimingJSONFile timing.json;
    outputSQL true;
    outputSQLFile discretization_error.db;
}
"""

    with open("discretization_error_base_config.prm", "w") as f:
        f.write(base_config)

    max_levels = list(range(2, 9))
    discretizations = ["P1", "P2"]
    num_processes = 8
    sor_omega = {"P1": 0.3, "P2": 0.3}

    with open("run_discretization_error.sh", "w") as f:
        f.write("echo\n")
        f.write("echo DISCRETIZATION ERROR\n")
        f.write("echo\n")
        for discretization in discretizations:
            for level in max_levels:
                cmd = "mpirun --allow-run-as-root -np {} --map-by core --bind-to core --report-bindings ./MultigridStudies 2019_tme/discretization_error_base_config.prm " \
                      "-Parameters.maxLevel={} " \
                      "-Parameters.sorRelax={} " \
                      "-Parameters.discretization={} ".format(num_processes, level, sor_omega[discretization], discretization)
                f.write("echo \"{}\"\n".format(cmd))
                f.write(cmd + "\n")


if __name__ == "__main__":
    omega_sampling()
    fmg_tests()
    discretization_error()