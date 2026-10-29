
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d: Before barrier\n", rank);
    fflush(stdout);

    // Each process waits for rank * 0.1 seconds
    usleep(rank * 100000);

    // Every process must reach this point
    MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d: After barrier\n", rank);
    fflush(stdout);

    MPI_Finalize();
    return 0;
}
