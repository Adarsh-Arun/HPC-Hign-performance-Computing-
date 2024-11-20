#include <omp.h>
#include <stdio.h>

int main() {
    int i, private_var = 0; // Declare and initialize a variable

    printf("Initial value of private_var: %d\n", private_var);

    // Parallel region with private clause
    #pragma omp parallel private(private_var)
    {
        int thread_id = omp_get_thread_num(); // Get thread ID
        private_var = thread_id + 10;         // Assign a value based on thread ID
        printf("Thread %d: private_var = %d\n", thread_id, private_var);
    }

    // Outside the parallel region
    printf("Value of private_var after parallel region: %d\n", private_var);

    return 0;
}
