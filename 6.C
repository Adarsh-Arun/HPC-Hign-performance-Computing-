#include <omp.h>
#include <stdio.h>

int main() {
    // Parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); // Get thread ID

        // Thread 0 prints the series of 2
        if (thread_id == 0) {
            printf("Thread %d: Series of 2: ", thread_id);
            for (int i = 1; i <= 5; i++) {
                printf("%d ", 2 * i);  // Printing multiples of 2
            }
            printf("\n");
        }

        // Thread 1 prints the series of 4
        if (thread_id == 1) {
            printf("Thread %d: Series of 4: ", thread_id);
            for (int i = 1; i <= 5; i++) {
                printf("%d ", 4 * i);  // Printing multiples of 4
            }
            printf("\n");
        }
    }

    return 0;
}
