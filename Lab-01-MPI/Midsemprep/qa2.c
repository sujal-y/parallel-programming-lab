// Write a MPI program to find the prime numbers between 1 and 100 using two processes.

#include<stdio.h>
#include "mpi.h"

int isPrime(int x){
    int prime = 1 ; //true
    if(x == 1) return 0;
    if(x == 2) return 1;
    for(int i = 2;i<x;i++){
        if(x%i ==0){
            prime =0;
        }
    }
    return prime;
}

int main(int argc,char* argv[]){

    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0){//prime 1 to 50
        for(int i = 1;i<=50;i++){
            if(isPrime(i) == 1){
                printf("Rank: %d prime: %d \n",rank,i);
            }
        }
        
    }
    if(rank == 1){//prime 51 to 100
         for(int i = 51;i<=100;i++){
            if(isPrime(i) == 1){
                printf("Rank: %d prime: %d \n",rank,i);
            }
        }
    }

    MPI_Finalize();
}