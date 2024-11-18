#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 3 // Dimension of the matrix
#define NUM_SAMPLES 1000000 // Number of Monte Carlo samples

// Function to generate a random vector
void generate_random_vector(double *vec, int size) {
    for (int i = 0; i < size; i++) {
        vec[i] = (double)rand() / RAND_MAX;
    }
}

// Function to compute the dot product
double dot_product(double *a, double *b, int size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// Monte Carlo matrix inversion
void monte_carlo_inverse(double matrix[N][N], double inverse[N][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;

            for (int k = 0; k < NUM_SAMPLES; k++) {
                double rand_vec[N];
                generate_random_vector(rand_vec, N);

                double dot_prod = dot_product(matrix[i], rand_vec, N);
                sum += rand_vec[j] / dot_prod;
            }

            inverse[i][j] = sum / NUM_SAMPLES;
        }
    }
}

// Main function
int main() {
    double matrix[N][N] = {
        {4, 1, 2},
        {1, 3, 0},
        {0, 2, 5}
    };
    double inverse[N][N];

    monte_carlo_inverse(matrix, inverse);

    printf("Inverse Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.5f ", inverse[i][j]);
        }
        printf("\n");
    }

    return 0;
}
