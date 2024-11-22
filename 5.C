#include <omp.h>
#include <stdio.h>

#define N 20 // Total number of iterations
#define CHUNK 4 // Number of iterations per chunk

int main() {
    int i;

    // Parallel region with static scheduling and chunk size
    #pragma omp parallel for schedule(static, CHUNK)
    for (i = 0; i < N; i++) {
        int thread_id = omp_get_thread_num(); // Get the thread ID
        printf("Thread %d is processing iteration %d\n", thread_id, i);
    }

    return 0;
}
