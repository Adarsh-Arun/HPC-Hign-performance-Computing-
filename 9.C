#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    long long N = 10000;  // Total number of integers to sum
    long long local_sum = 0, global_sum = 0;
    long long start, end;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divide the work among processes
    long long range_per_process = N / size;
    start = rank * range_per_process + 1;
    end = (rank + 1) * range_per_process;

    // Handle the case for the last process if N is not perfectly divisible
    if (rank == size - 1) {
        end = N;  // Last process handles the remaining numbers
    }

    // Calculate the partial sum for this process
    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    // Use MPI_Reduce to sum all the local sums into the global sum at root process
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the final result
    if (rank == 0) {
        printf("The sum of the first %lld integers is: %lld\n", N, global_sum);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
