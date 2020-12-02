#!/bin/bash
#SBATCH -J CPD-test-16:07:58-12/01/20
#SBATCH -p investigacion
#SBATCH -N 1
#SBATCH --tasks-per-node=8

echo "MPI Test"

module load openmpi/2.1.6

echo "1 Proceso"
for i in {0..100}
do
        mpirun -np 1 random_mpi.out
done

echo "2 Procesos"
for i in {0..100}
do
        mpirun -np 2 random_mpi.out
done

echo "4 Procesos"
for i in {0..100}
do
        mpirun -np 4 random_mpi.out
done

echo "8 Procesos"
for i in {0..100}
do
        mpirun -np 8 random_mpi.out
done

#echo "12 Procesos"
#for i in {0..100}
#do
#        mpirun -np 12 random_mpi.out
#done


module unload openmpi/2.1.6
