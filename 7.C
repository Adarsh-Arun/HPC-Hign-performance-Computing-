#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    char message[20];

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process creates its own message
    sprintf(message, "Hello from process %d", rank);

    // Root process (rank 0) receives messages from all other processes
    if (rank == 0) {
        printf("Root process %d: Receiving messages:\n", rank);

        // Receive messages from all other processes
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 20, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Received message: %s\n", message);
        }

        // The root process also prints its own message
        printf("Received message: Hello from process 0\n");
    }
    else {
        // Non-root processes send their message to the root process
        MPI_Send(message, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
