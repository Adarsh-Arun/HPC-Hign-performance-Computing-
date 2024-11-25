#include <mpi.h>
#include <stdio.h>

#define NUM_ELEMENTS 2  // Number of elements per process

int main(int argc, char** argv) {
    int rank, size;
    int data[NUM_ELEMENTS];  // Array to store data for each process

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize the data array with two numbers per process
    data[0] = rank * 10 + 1;  // First number (example: 1, 11, 21, ...)
    data[1] = rank * 10 + 2;  // Second number (example: 2, 12, 22, ...)

    // Root process (rank 0) receives messages from all other processes
    if (rank == 0) {
        printf("Root process %d: Receiving messages:\n", rank);

        // Receive data from all other processes
        for (int i = 1; i < size; i++) {
            MPI_Recv(data, NUM_ELEMENTS, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Received from process %d: %d, %d\n", i, data[0], data[1]);
        }

        // The root process also prints its own data
        printf("Received from process %d: %d, %d\n", rank, data[0], data[1]);
    }
    else {
        // Non-root processes send their data to the root process
        MPI_Send(data, NUM_ELEMENTS, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
