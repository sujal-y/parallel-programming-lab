__global__ void work_inefficient_scan_kernel(float *X, float *Y, int InputSize) {
    __shared__ float XY[SECTION_SIZE];
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    // 1. Load input element from global memory into shared memory
    if (i < InputSize) {
        XY[threadIdx.x] = X[i];
    }

    //for exclusive scan
    // if (i < InputSize && threadIdx.x != 0) {
    // XY[threadIdx.x] = X[i - 1]; // Shift every input right by 1 position
    // } else {
    // XY[threadIdx.x] = 0;        // Put 0 in XY[0] (and pad out-of-bounds slots with 0)
    // }

    // 2. Iteratively double the stride (1, 2, 4, 8...)
    for (unsigned int stride = 1; stride <= threadIdx.x; stride *= 2) {
        __syncthreads();
        XY[threadIdx.x] += XY[threadIdx.x - stride];
    }

    // 3. Write final prefix sum back to global output array Y
    Y[i] = XY[threadIdx.x];
}