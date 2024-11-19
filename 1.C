#include <omp.h>
#include <stdio.h>

int main() {
    // Initialize the OpenMP parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); // Get the thread ID
        int num_threads = omp_get_num_threads(); // Get the total number of threads

        // Print a message with thread ID
        printf("Hello, World from thread %d out of %d threads!\n", thread_id, num_threads);
    }

    return 0;
}
