// Implement at least 2 programs to identify deadlock conditions in synchronous send and 
// standard send with multiple point to point communications between two processes  
#include <stdio.h>
#include "mpi.h"

//here both processes try to send each other a msg but a recv is not sent as its waiting to send and get a matching receive
int main(int argc, char *argv[]) {
    int rank, size;
    int send_val = 10, recv_val;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Process 0: Attempting Ssend to Process 1...\n");
        // DEADLOCK: Waits until Process 1 receives, but Process 1 is also waiting to send
        MPI_Ssend(&send_val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
    } else if (rank == 1) {
        printf("Process 1: Attempting Ssend to Process 0...\n");
        // DEADLOCK: Waits until Process 0 receives, but Process 0 is blocked above
        MPI_Ssend(&send_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    printf("Process %d completed successfully (Deadlock resolved).\n", rank);
    MPI_Finalize();
    return 0;
}