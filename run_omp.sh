

gcc -o random_omp -fopenmp random_openmp.c

echo "1 Proceso"
export OMP_NUM_THREADS=1

for i in {1..100}
do
    ./random_omp         
done

echo "2 Procesos"
export OMP_NUM_THREADS=2

for i in {1..100}
do
    ./random_omp         
done

echo "4 Procesos"
export OMP_NUM_THREADS=4

for i in {1..100}
do
    ./random_omp         
done

echo "8 Procesos"
export OMP_NUM_THREADS=8

for i in {1..100}
do
    ./random_omp         
done

echo "16 Procesos"
export OMP_NUM_THREADS=16

for i in {1..100}
do
    ./random_omp         
done