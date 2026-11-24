// Launch: multiplyKernel_rowwise<<<(1,1), (wb,ha)>>>(
//              d_matrixA, d_matrixB, d_matrixC,
//              numColsA, numColsB);

__global__ void multiplyKernel_rowwise(
    int* matrixA, int* matrixB, int* matrixC,
    int numColsA, int numColsB)
{
    int rowA = threadIdx.y;  
    int colb = threadIdx.x;
    int numColsB =blockDim.x//wb

    int sum =0,k;

    
        // Calculate the dot product of row A and column B
        for (int k = 0; k < numColsA; k++) {

            sum += matrixA[rowA * numColsA + k]
                 * matrixB[k * numColsB + colB];
        }

        // Store the result in matrix C
        matrixC[rowA * numColsB + colB] = sum;
    
}