//Write a MPI program to read N elements of the array in the root process (process 0) where 
// N is equal to the total number of processes. The root process sends one value to each of the 
// slaves. Let even ranked process finds square of the received element and odd ranked 
// process finds cube of received element. Use Buffered send.

#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank ==0){
        int arr[size];
        for (int i = 0; i < size; i++) {
            arr[i] = i ; // Sample values: 0,1, 2, 3, ...
        }

        int bufersize = sizeof(int) *MPI_BSEEND_OVERHEAD;
        void *buffer = malloc(bufersize);
        MPI_Buffer_attach(buffer,bufersize);

        for (int i = 1; i < size; i++) {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        int val = arr[0];
        printf("Rank 0: Element = %d, Square = %d\n", val, val * val);

        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    }
    else{
        int num;
        MPI_Recv(&num,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);

        if (rank % 2 == 0) {
            printf("Rank:%d got number %d square:%d\n",rank,num,(num*num));
        } else {
            printf("Rank:%d got number %d cube:%d\n",rank,num,(num*num*num));
        }
        

    }
    MPI_Finalize();
}