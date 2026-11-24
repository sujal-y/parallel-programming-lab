// Launch: multiplyKernel_rowwise<<<1, numRowsA>>>(
//              d_matrixA, d_matrixB, d_matrixC,
//              numColsA, numColsB);

__global__ void multiplyKernel_rowwise(
    int* matrixA, int* matrixB, int* matrixC,
    int numColsA, int numColsB)
{
    int rowA = threadIdx.x;  // Each thread handles one row of A and C

    int sum;

    // Iterate through every column of matrix B
    for (int colB = 0; colB < numColsB; colB++) {

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