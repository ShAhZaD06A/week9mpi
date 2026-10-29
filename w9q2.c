#include <stdio.h>
#include <mpi.h>
#define N 12

int main(int argc, char *argv[]) {
    int rank, size;
    int data[N];
    int local_data[N / 4]; // Assuming 4 processes for simplicity
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize data on the root process
    if (rank == 0) {
        for (i = 0; i < N; i++) {
            data[i] = i + 1; // Fill with values 1 to N
        }
    }

    // Scatter the data to all processes
    MPI_Scatter(data, N / size, MPI_INT, local_data, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints its received data
    printf("Process %d received: ", rank);
    for (i = 0; i < N / size; i++) {
        printf("%d ", local_data[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}