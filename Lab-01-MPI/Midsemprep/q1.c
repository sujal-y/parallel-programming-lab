//Write a simple MPI program to find out pow (x, rank) for all the processes where 'x' is the 
// integer constant and 'rank' is the rank of the process.

#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc,char* argv[]){
    int rank,size;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int result = pow(2,rank);
    printf("My rank is %d , result is %d \n",rank,result);

    MPI_Finalize();
}