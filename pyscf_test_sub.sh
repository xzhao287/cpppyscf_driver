#!/bin/bash
#SBATCH --partition=shared
#SBATCH --time=7-00:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --mem-per-cpu=3000


module load gcc cmake openmpi
export LD_LIBRARY_PATH=$OPENMPI_ROOT/lib:$LD_LIBRARY_PATH


ulimit -s unlimited
export OMP_NUM_THREADS=4
export OMP_STACKSIZE=256M



g++ $(python3.10-config --cflags) -I/home/xzhao287/miniconda3/lib/python3.10/site-packages/numpy/core/include gmxdummy.cpp -o gmxdummy $(python3.10-config --ldflags --embed)
#use this to tell the compiler where to find API libraries for C++/Python, NumPy librabry needs to be individually located

LD_LIBRARY_PATH=$HOME/miniconda3/lib:$LD_LIBRARY_PATH ./gmxdummy
#tell the terminal where to find dynamic/shared library when running the executable
