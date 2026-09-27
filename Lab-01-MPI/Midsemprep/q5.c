//Write a program in MPI where even ranked process prints factorial of the rank and odd 
// ranked process prints ranks Fibonacci number.

#include<stdio.h>
#include "mpi.h"

int main(int argc,char* argv[]){

    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank%2 == 0){
        int fact = 1;
        for(int i=1;i<=rank;i++){
            fact *= i;
        }
        printf("Rank: %d Fact:%d\n",rank,fact);
    }
    else{
        int fib;
        if (rank <= 0) {
            fib = 0;
        } else if (rank == 1) {
            fib = 1;
        } else {
            int a = 0, b = 1, c;
            for (int i = 2; i <= rank; i++) {
                c = a + b;
                a = b;
                b = c;
            }
            fib = c;
        }
        

         printf("Rank: %d Fib: %d \n",rank,fib);
    }

    MPI_Finalize();
}