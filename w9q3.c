
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int local_value;
    int global_max, global_min;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Give each process a different random seed
    srand((unsigned int)time(NULL) + rank);

    // Each process generates one random number
    local_value = rand() % 1000;

    // Find the global maximum on every process
    MPI_Allreduce(
        &local_value, &global_max,
        1, MPI_INT, MPI_MAX, MPI_COMM_WORLD
    );

    // Find the global minimum on every process
    MPI_Allreduce(
        &local_value, &global_min,
        1, MPI_INT, MPI_MIN, MPI_COMM_WORLD
    );

    printf(
        "Process %d generated %d. Global Max: %d, Global Min: %d\n",
        rank, local_value, global_max, global_min
    );

    MPI_Finalize();
    return 0;
}
