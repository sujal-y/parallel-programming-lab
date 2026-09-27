// Write a MPI program to read an integer value in the root process. Root process sends this 
// value to Processl, Processl sends this value to Process2 and so on. Last process sends the 
// value back to root process. When sending the value each process will first increment the 
// received value by one. Write the program using point to point communication routines.  

#include "mpi.h"
#include <stdio.h>

int main(int argc,char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int num =0;
    if(rank == 0)//root process
    {
        //take input and send it to process 2
        printf("Rank:%d Enter a number: ",rank);
        scanf("%d",&num);

        MPI_Send(&num,1,MPI_INT,1,0,MPI_COMM_WORLD);

        MPI_Recv(&num,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&status);

        printf("Rank:%d final number recived = %d \n",rank,num);

    } 
    else if(rank>0 && rank<size-1){
        //pass the num+1 to next
        MPI_Recv(&num,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);

        num += 1;
        printf("Rank:%d num:%d\n",rank,num);
        MPI_Send(&num,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);

    }
    else if(rank == size-1){
        //send back to root
        MPI_Recv(&num,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);

        num+=1;

        MPI_Send(&num,1,MPI_INT,0,0,MPI_COMM_WORLD);
        
    }

    

    MPI_Finalize();
}