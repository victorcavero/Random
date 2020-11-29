#!/bin/bash

# ---- Compilation
mpic++ -o ./random_mpi.out -g random_mpi.c

# ---- Execution
for i in {1..100}
do
   echo $i
    mpirun -np 4 ./random_mpi.out
# mpirun -np 4 ./main_mpi.out
# mpirun -np 8 ./main_mpi.out
done 
# ---- Cleanup
#rm *.out