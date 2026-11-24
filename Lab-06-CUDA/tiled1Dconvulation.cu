//1d tiled

__global__ void convolution_1D_basic_kernel(float *N, float *P, 
                                            int Mask_Width, int Width) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    // Shared memory holds the block's tile PLUS left and right halo elements
    __shared__ float N_ds[TILE_SIZE + MAX_MASK_WIDTH - 1];
    int n = Mask_Width / 2; // Halo radius on each side

    // 1. Load left halo elements (using the last 'n' threads of the block)
    int halo_index_left = (blockIdx.x - 1) * blockDim.x + threadIdx.x;
    if (threadIdx.x >= blockDim.x - n) {
        N_ds[threadIdx.x - (blockDim.x - n)] = 
            (halo_index_left < 0) ? 0 : N[halo_index_left];
    }

    // 2. Load center (internal) tile elements (all threads participate)
    N_ds[n + threadIdx.x] = N[blockIdx.x * blockDim.x + threadIdx.x];

    // 3. Load right halo elements (using the first 'n' threads of the block)
    int halo_index_right = (blockIdx.x + 1) * blockDim.x + threadIdx.x;
    if (threadIdx.x < n) {
        N_ds[n + blockDim.x + threadIdx.x] = 
            (halo_index_right >= Width) ? 0 : N[halo_index_right];
    }

    // Wait until ALL threads in the block finish loading N_ds!
    __syncthreads();

    // 4. Compute convolution using fast shared memory N_ds and constant memory M
    float Pvalue = 0;
    for (int j = 0; j < Mask_Width; j++) {
        Pvalue += N_ds[threadIdx.x + j] * M[j];
    }
    P[i] = Pvalue;
}