//Write a MPI program where the master process (process 0) sends a number to each of the 
// slaves and the slave processes receive the number and prints it. Use standard send.  

#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc,char* argv[]){
    int rank,size;
    int number =0;
    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //master process
   if(rank == 0){
        //sending multiples of 5 : 5 , 10 , 15...
        int num =5;
        for(int i = 1; i <=size-1;i++){
            MPI_Send(&num,1,MPI_INT,i,0,MPI_COMM_WORLD);
            num += 5;
        }
   }
   else{
        MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        printf("Rank %d: number: %d\n",rank, number);
   }
    MPI_Finalize();
    return 0;
}