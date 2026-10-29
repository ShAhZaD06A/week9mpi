
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define POINTS_PER_PROCESS 100000

int main(int argc, char *argv[])
{
    int rank, size;
    long long local_hits = 0;
    long long global_hits = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random generator separately for each process
    srand((unsigned int)time(NULL) + rank);

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    // Each process generates its own random points
    for (int i = 0; i < POINTS_PER_PROCESS; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1.0)
        {
            local_hits++;
        }
    }

    printf("Process %d local hits: %lld\n", rank, local_hits);

    // Add all local hit counts at root
    MPI_Reduce(
        &local_hits, &global_hits,
        1, MPI_LONG_LONG_INT, MPI_SUM,
        0, MPI_COMM_WORLD
    );

    double local_elapsed = MPI_Wtime() - start_time;
    double execution_time = 0.0;

    // Use the slowest process time as the overall elapsed time
    MPI_Reduce(
        &local_elapsed, &execution_time,
        1, MPI_DOUBLE, MPI_MAX,
        0, MPI_COMM_WORLD
    );

    if (rank == 0)
    {
        long long total_points =
            (long long)POINTS_PER_PROCESS * size;

        double pi_estimate =
            4.0 * (double)global_hits / total_points;

        printf("Total points: %lld\n", total_points);
        printf("Estimated Pi: %.6f\n", pi_estimate);
        printf("Execution Time: %.6f seconds\n", execution_time);
    }

    MPI_Finalize();
    return 0;
}
