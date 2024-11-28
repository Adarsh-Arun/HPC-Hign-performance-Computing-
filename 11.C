#include <stdio.h>
#include <cuda_runtime.h>

// Define matrix dimensions
#define N 1024  // Size of the matrix

// CUDA kernel function to add two matrices A and B, store the result in C
__global__ void matrixAdd(float *A, float *B, float *C, int width) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int idy = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (idx < width && idy < width) {
        int index = idy * width + idx;
        C[index] = A[index] + B[index];
    }
}

int main() {
    int size = N * N * sizeof(float);  // Size of the matrices in bytes

    // Host matrices
    float *h_A, *h_B, *h_C, *h_D, *h_E;

    // Allocate memory for matrices on the host
    h_A = (float*)malloc(size);
    h_B = (float*)malloc(size);
    h_C = (float*)malloc(size);
    h_D = (float*)malloc(size);
    h_E = (float*)malloc(size);

    // Initialize matrices A, B, and D with random values
    for (int i = 0; i < N * N; i++) {
        h_A[i] = rand() % 10;
        h_B[i] = rand() % 10;
        h_D[i] = rand() % 10;
    }

    // Device matrices
    float *d_A, *d_B, *d_C, *d_D, *d_E;

    // Allocate memory for matrices on the device
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);
    cudaMalloc(&d_D, size);
    cudaMalloc(&d_E, size);

    // Copy matrices A, B, and D from host to device
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_D, h_D, size, cudaMemcpyHostToDevice);

    // Define grid and block size
    dim3 threadsPerBlock(16, 16);  // 16x16 block
    dim3 numBlocks((N + 15) / 16, (N + 15) / 16);  // Grid size

    // Step 1: Perform A + B = C
    matrixAdd<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, N);
    
    // Wait for kernel to finish
    cudaDeviceSynchronize();

    // Step 2: Perform C + D = E
    matrixAdd<<<numBlocks, threadsPerBlock>>>(d_C, d_D, d_E, N);

    // Wait for kernel to finish
    cudaDeviceSynchronize();

    // Copy result matrix E from device to host
    cudaMemcpy(h_E, d_E, size, cudaMemcpyDeviceToHost);

    // Print the result (optional)
    // You can print a few elements of the result to verify
    printf("Result matrix E (a few elements):\n");
    for (int i = 0; i < 5; i++) {
        printf("%f ", h_E[i]);
    }
    printf("\n");

    // Free memory
    free(h_A);
    free(h_B);
    free(h_C);
    free(h_D);
    free(h_E);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaFree(d_D);
    cudaFree(d_E);

    return 0;
}
