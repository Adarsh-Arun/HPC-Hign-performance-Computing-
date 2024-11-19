#include <omp.h>
#include <stdio.h>

int main() {
    // Set the number of threads
    omp_set_num_threads(4);

    // Parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); // Get the thread ID
        printf("Hello from thread %d: My name is [Your Name]\n", thread_id);
    }

    return 0;
}
