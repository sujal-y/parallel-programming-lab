// In MPI_Alltoall, every process sends a unique, personalized piece of data to 
// every other process (including itself).   Think of it as a parallel matrix transpose across processes:  
//  Process $i$ sends its $j$-th chunk of data to Process $j$.   
// Process $j$ places the chunk received from Process $i$ at position $i$ of its receive buffer.   

// Before MPI_Alltoall (each process has a buffer with elements for P0, P1, P2):
// Process 0: [ A0, A1, A2 ]   (A0 for P0, A1 for P1, A2 for P2)
// Process 1: [ B0, B1, B2 ]   (B0 for P0, B1 for P1, B2 for P2)
// Process 2: [ C0, C1, C2 ]   (C0 for P0, C1 for P1, C2 for P2)

// After MPI_Alltoall:
// Process 0: [ A0, B0, C0 ]   (Received item 0 from P0, P1, P2)
// Process 1: [ A1, B1, C1 ]   (Received item 1 from P0, P1, P2)
// Process 2: [ A2, B2, C2 ]   (Received item 2 from P0, P1, P2)


// int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
//                  void *recvbuf, int recvcount, MPI_Datatype recvtype,
//                  MPI_Comm comm);

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *send_data = (int *)malloc(size * sizeof(int));
    int *recv_data = (int *)malloc(size * sizeof(int));

    // Prepare personalized message for each target process
    // Format: XY where X is sender rank and Y is destination rank
    for (int i = 0; i < size; i++) {
        send_data[i] = (rank * 10) + i;
    }

    // Perform total exchange
    // Each sends 1 int to every process, and receives 1 int from every process
    MPI_Alltoall(send_data, 1, MPI_INT, recv_data, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Process %d received: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%02d ", recv_data[i]);
    }
    printf("\n");

    free(send_data);
    free(recv_data);
    MPI_Finalize();
    return 0;
}