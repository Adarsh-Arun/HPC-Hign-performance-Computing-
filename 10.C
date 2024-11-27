#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    long long N = 10000;  // Total number of integers to sum
    long long local_sum = 0, total_sum = 0;
    long long start, end;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
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

    // Ring topology communication
    int prev = (rank - 1 + size) % size;  // Previous process in the ring
    int next = (rank + 1) % size;          // Next process in the ring

    // Start the sum collection in a ring manner
    if (rank == 0) {
        // Process 0 sends its local sum to the next process
        MPI_Send(&local_sum, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);

        // Process 0 receives the sum from the previous process
        MPI_Recv(&total_sum, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Add its own local sum to the total sum
        total_sum += local_sum;

        // Print the final result (sum of all N integers)
        printf("The total sum of the first %lld integers is: %lld\n", N, total_sum);
    }
    else {
        // Non-root processes: send their local sum to the next process
        MPI_Send(&local_sum, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);

        // Non-root processes: receive the total sum from the previous process
        MPI_Recv(&total_sum, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Add its own local sum to the total sum
        total_sum += local_sum;

        // Send the updated total sum to the next process
        if (rank != size - 1) {
            MPI_Send(&total_sum, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);
        }
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}
