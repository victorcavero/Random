#!/bin/bash

# ---- Compilation
mpic++ -o ./main_mpi.out -g random_mpi.c

# ---- Execution


# echo "1 Proceso"
# for i in {0..100}
# do
#     mpirun -np 1 ./main_mpi.out
# done 

# echo "2 Procesos"
# for i in {0..100}
# do
#     mpirun -np 2 ./main_mpi.out
# done 

# echo "4 Procesos"
# for i in {0..100}
# do
#     mpirun -np 4 ./main_mpi.out
# done 

# echo "8 Procesos"
# for i in {0..100}
# do
#     mpirun -np 8 ./main_mpi.out
# done 

echo "16 Procesos"
for i in {0..100}
do
    mpirun -np 12 ./main_mpi.out
done 