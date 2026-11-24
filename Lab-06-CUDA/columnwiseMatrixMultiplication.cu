// Launch: multiplyKernel_colwise<<<1, numColsB>>>(
//              d_matrixA, d_matrixB, d_matrixC,
//              numRowsA, numColsA, numColsB);

__global__ void multiplyKernel_colwise(
    int* matrixA, int* matrixB, int* matrixC,
    int numRowsA, int numColsA, int numColsB)
{
    int colB = threadIdx.x;  // Each thread handles one column of B and C
    int numColsB = blockDim.x;
    int sum;

    // Iterate over every row of matrix A
    for (int rowA = 0; rowA < numRowsA; rowA++) {

        sum = 0;

        // Calculate the dot product of row A and column B
        for (int k = 0; k < numColsA; k++) {

            sum += matrixA[rowA * numColsA + k]
                 * matrixB[k * numColsB + colB];
        }

        // Store the result in matrix C
        matrixC[rowA * numColsB + colB] = sum;
    }
}