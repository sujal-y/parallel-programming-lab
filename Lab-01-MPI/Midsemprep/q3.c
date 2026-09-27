//Write a program in MPI to simulate simple calculator. Perform each operation using 
// different process in parallel.

#include<stdio.h>
#include "mpi.h"

int main(int argc,char* argv[]){

    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int x =5 , y=5;
    int result;
    if(rank == 0){
        result = x+y;
        printf("Rank: %d ,Result: %d \n",rank,result);
    }
    else if(rank == 1){
        result = x-y;
        printf("Rank: %d ,Result: %d \n",rank,result);
    }
    else if(rank == 2){
        result = x*y;
        printf("Rank: %d ,Result: %d \n",rank,result);
    }
    else if(rank == 3){
        if(y != 0){
            result = x/y;
        }
        else{
            result =-1;       
         }
        
        printf("Rank: %d ,Result: %d \n",rank,result);
    }

    MPI_Finalize();
}