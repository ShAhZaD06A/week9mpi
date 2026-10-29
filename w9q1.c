#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int local_data[3];
    int gathered_data[300];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (int i = 0; i < 3; i++)
    {
        local_data[i] = rank * 10 + i;
    }
    MPI_Gather(local_data, 3, MPI_INT, gathered_data, 3, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for (int i = 0; i < size * 3; i++)
        {
            printf("Gathered data[%d]: %d\n", i, gathered_data[i]);
        }
    }
    MPI_Finalize();
    return 0;
}