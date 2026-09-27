// int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
//                   void *recvbuf, int recvcount, MPI_Datatype recvtype,
//                   MPI_Comm comm);

// Before MPI_Allgather:
// Process 0: [ 10 ]
// Process 1: [ 20 ]
// Process 2: [ 30 ]

// After MPI_Allgather:
// Process 0: [ 10, 20, 30 ]
// Process 1: [ 10, 20, 30 ]
// Process 2: [ 10, 20, 30 ]

// MPI_Allgather performs that exact same gather, but delivers the concatenated result 
// to every single process instead of just root. It is functionally identical to 
// doing an MPI_Gather followed immediately by an MPI_Bcast of the gathered array to all ranks.

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int my_val = (rank + 1) * 10; // e.g., P0: 10, P1: 20, P2: 30, P3: 40
    int all_vals[size];

    // Every process sends 1 integer and receives 1 integer from every process
    MPI_Allgather(&my_val, 1, MPI_INT, all_vals, 1, MPI_INT, MPI_COMM_WORLD);

    // Every process can now print the full array
    printf("Process %d received entire array: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", all_vals[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}