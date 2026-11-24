__global__ void MatrixMulKernel(float* d_M, float* d_N, float* d_P, int Width) {
    // 1. Allocate 2D tiles in fast on-chip Shared Memory (shared across the block)
    __shared__ float Mds[TILE_WIDTH][TILE_WIDTH]; //
    __shared__ float Nds[TILE_WIDTH][TILE_WIDTH]; //

    int bx = blockIdx.x;  int by = blockIdx.y;  //
    int tx = threadIdx.x; int ty = threadIdx.y; //

    // 2. Identify the global Row and Col of d_P this thread will compute
    int Row = by * TILE_WIDTH + ty; //[cite: 57]
    int Col = bx * TILE_WIDTH + tx; //[cite: 57]

    float Pvalue = 0; // Stored in a fast private register[cite: 56, 57]

    // 3. Loop over all tiles (phases) required to compute d_P[Row][Col]
    for (int m = 0; m < Width / TILE_WIDTH; ++m) { //[cite: 57]
        // Collaboratively load one element of M and N into shared memory
        Mds[ty][tx] = d_M[Row * Width + (m * TILE_WIDTH + tx)]; //[cite: 57]
        Nds[ty][tx] = d_N[(m * TILE_WIDTH + ty) * Width + Col]; //[cite: 57]

        // BARRIER 1: Wait until the entire tile is loaded into shared memory[cite: 57]
        __syncthreads(); //[cite: 57]

        // Compute partial dot product using the loaded tile in shared memory[cite: 57]
        for (int k = 0; k < TILE_WIDTH; ++k) { //[cite: 57]
            Pvalue += Mds[ty][k] * Nds[k][tx]; //[cite: 57]
        }

        // BARRIER 2: Wait until all threads finish computing before loading next tile[cite: 57]
        __syncthreads(); //[cite: 57]
    }

    // 4. Write final accumulated result back to global memory
    d_P[Row * Width + Col] = Pvalue; //[cite: 57]
}