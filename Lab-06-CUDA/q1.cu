// Write a program in CUDA which performs convolution operation on one-dimensional input array 
// N of size width using a mask array M of size mask_width to produce the resultant onedimensional 
// array P of size width

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

//kernel
__global__ void onedimensional_convolution(float* input_array,float* mask,float* result ,int input_size,int mask_width){
    int i = blockIdx.x*blockDim.x+threadIdx.x;

    float resultValue =0;
    if(i<input_size){

    //finding leftmost input
    int Input_starting_point = i-(mask_width/2);
    for(int j =0;j<mask_width;j++){
        //skip ghost elements
        if(Input_starting_point+j>=0 && Input_starting_point+j<mask_width)
        resultValue += input_array[Input_starting_point+j]*mask[j];
    }
    result[i] =resultValue;
}
}

int main() {
    int Width = 7;
    int Mask_Width = 5;

    float h_N[7] = {1, 2, 3, 4, 5, 6, 7};
    float h_M[5] = {3, 4, 5, 4, 3};
    float h_P[7] = {0};

    int size_N = Width * sizeof(float);
    int size_M = Mask_Width * sizeof(float);

    float *d_N, *d_M, *d_P;

    // 1. Allocate device global memory
    cudaMalloc((void**)&d_N, size_N);
    cudaMalloc((void**)&d_M, size_M);
    cudaMalloc((void**)&d_P, size_N);

    // 2. Copy input array and mask from Host (CPU) to Device (GPU)
    cudaMemcpy(d_N, h_N, size_N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, size_M, cudaMemcpyHostToDevice);

    // 3. Launch kernel (using 256 threads per block)
    int threadsPerBlock = 256;
    int blocksPerGrid = (Width + threadsPerBlock - 1) / threadsPerBlock;
    onedimensional_convolution<<<blocksPerGrid, threadsPerBlock>>>(d_N, d_M, d_P,Width, Mask_Width);

    // 4. Copy output array P back from Device to Host
    cudaMemcpy(h_P, d_P, size_N, cudaMemcpyDeviceToHost);

    // Print results (P[1] should be 38, P[2] should be 57)
    for (int i = 0; i < Width; i++) {
        printf("P[%d] = %.1f\n", i, h_P[i]);
    }

    // 5. Free device memory
    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    return 0;
}