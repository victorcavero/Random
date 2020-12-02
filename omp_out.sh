#!/bin/bash
#SBATCH -J CPD-test-16:27:24-12/01/20
#SBATCH -p investigacion
#SBATCH -N 1
#SBATCH --tasks-per-node=8

echo " OMP Test"

module load gcc/5.5.0

echo "1 Proceso"
for i in {1..100}
do
        ./random_openmp.out 1
done

echo "2 Procesos"
for i in {1..100}
do
        ./random_openmp.out 2
done

echo "4 Procesos"
for i in {1..100}
do
        ./random_openmp.out 4
done

echo "8 Procesos"
for i in {1..100}
do
        ./random_openmp.out 8
done

#echo "12 Procesos"
#for i in {1..100}
#do
 #       ./random_openmp.out 12
#done



module unload gcc/5.5.0
