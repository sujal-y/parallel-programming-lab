#include <stdio.h>
#include <cuda_runtime.h>

int main() {

    int dev_count;
    cudaGetDeviceCount(&dev_count);

    for (int i = 0; i < dev_count; i++) {

        cudaDeviceProp dev_prop;
        cudaGetDeviceProperties(&dev_prop, i);

        printf("\nGPU %d: %s\n", i, dev_prop.name);

        printf("Number of SMs: %d\n",
               dev_prop.multiProcessorCount);

        printf("Max threads per block: %d\n",
               dev_prop.maxThreadsPerBlock);

        printf("Max threads per SM: %d\n",
               dev_prop.maxThreadsPerMultiProcessor);

        printf("Max blocks per SM: %d\n",
               dev_prop.maxBlocksPerMultiProcessor);
    }

    return 0;
}