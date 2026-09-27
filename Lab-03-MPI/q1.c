// Write a MPI program to read N values in the root process. Root process sends one value to 
// each process. Every process receives it and finds the factorial of that number and returns it to 
// the root process. Root process gathers the factorial and finds sum of it. Use N number of 
// processes.  

#include "mpi.h"
#include <stdio.h>
int factorial(int x){
    int fact = 1;
    for(int i = 1; i <= x;i++){
        fact *= i;
    }
    return fact;
}

int main(int argc,char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int arr[size];
    int gathered_facts[size];
    int val;
    if(rank ==0){//root
        printf("Rank %d:Enter %d values \n",rank,size);
        for(int i=0;i<size;i++){
            scanf("%d",&arr[i]);
        }
    }
    //needs to be accessible to every rank
    MPI_Scatter(arr,1,MPI_INT,&val,1,MPI_INT,0,MPI_COMM_WORLD);

    int fact = factorial(val);
    printf("Rank %d: Factorial of %d = %d\n", rank, val, fact);

    //gathered_facts should be accessible to all
    MPI_Gather(&fact, 1, MPI_INT, gathered_facts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank ==0){//root to sum
        int sum=0;
        for(int i=0;i<size;i++){
            sum += gathered_facts[i];
        }
        printf("Rank %d:Sum: %d  \n",rank,sum);
    }

    MPI_Finalize();
    return 0;
}