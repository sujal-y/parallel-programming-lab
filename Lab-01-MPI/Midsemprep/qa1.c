// Write a program in MPI to reverse the digits of the following integer array of size 9 with 9 
// processes. Initialize the array to the following values.  
// Input array: 18, 523, 301, 1234, 2, 14, 108, 150, 1928 
// output array:81, 325, 103, 4321, 2, 41, 801, 51, 8291 

#include "mpi.h"
#include <stdio.h>

int reverse (int x){
    int rev =0;
    while(x > 0){
        int temp = x %10;
        rev = rev*10 +temp;
        x = x/10;
    }

    return rev;

}

int main(int argc , char* argv[]){
    int rank , size;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int array[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};

    for(int i =0; i<9;i++){
        if(rank == i){
            int old = array[rank];
            array[rank] = reverse(array[rank]);
            printf("rank %d flipped %d to %d \n", rank,old,array[rank]);
        }
    }

    MPI_Finalize();

}