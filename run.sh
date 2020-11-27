#!/bin/bash

# ---- Compilation
mpic++ -o ./random_mpi.out -g random_mpi.c

# ---- Execution
mpirun -np 4 ./random_mpi.out
# mpirun -np 4 ./main_mpi.out
# mpirun -np 8 ./main_mpi.out

# ---- Cleanup
rm *.out