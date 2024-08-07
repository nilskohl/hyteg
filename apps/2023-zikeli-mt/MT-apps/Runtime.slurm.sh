#!/bin/bash -l
#
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=5:00:00
#SBATCH --export=NONE
#SBATCH --partition spr1tb
#SBATCH --job-name=Runtime
#SBATCH --mail-user=michael.zikeli@fau.de
#SBATCH --mail-type=END

unset SLURM_EXPORT_ENV

cd $HOME/hyteg
rm -fr build-runtime

module load 000-all-spack-pkgs/0.19.1 gcc/13.2.0-gcc8.5.0-r5aeqqr cmake openmpi/4.1.3-gcc8.5.0

mkdir build-runtime
cd ./build-runtime

cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DHYTEG_BUILD_DOC=OFF ..
make -j 32 benchmarkRuntime

cd ./apps/2023-zikeli-mt/MT-apps

echo -e "Begin Program\n"

srun ./benchmarkRuntime

echo -e "\nFinish Program"

