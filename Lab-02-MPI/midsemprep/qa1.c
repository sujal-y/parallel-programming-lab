//Write a MPI program to read N elements of an array in the master process. Let N processes 
// including master process check the array values are prime or not.  

#include "mpi.h"
#include <stdio.h>
#include <math.h>
int isPrime(int x){
    int prime = 1;//true
    if(x == 1)return 0;
    if(x == 2) return 1;
    for(int i= 2;i<x;i++){
        if(x%i ==0){
            prime = 0;
            return prime;
        }
    }
    return prime;
}

int main(int argc,char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0){//master
        int arr[size];
        printf("rank:%d Enter %d elements into array \n",rank,size);
        for(int i=0; i<size;i++){
            scanf("%d",&arr[i]);
        }
        int primematrix[size];
        for(int i=1; i<size;i++){
            MPI_Send(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
        }

        //checking for index 0
        if(isPrime(arr[0])){
            primematrix[0] = 1;
        }
        else{
            primematrix[0] = 0;
        }
        //receiving

        for(int i=1; i<size;i++){
            MPI_Recv(&primematrix[i],1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
        }

         printf("rank:%d here is prime or not \n",rank);
         for(int i=0; i<size;i++){
            printf("Number %d : prime: %d\n",arr[i],primematrix[i]);
        }

        

    }
    else{//slaves
        int num;
        MPI_Recv(&num,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        
        if(isPrime(num)){
            int prime =1;
            MPI_Send(&prime,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }
        else{
            int prime =0;
            MPI_Send(&prime,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }
    }
    


    MPI_Finalize();
}