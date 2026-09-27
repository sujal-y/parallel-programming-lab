// Write a program in MPI to toggle the character of a given string indexed by the rank of the 
// process. Hint: Suppose the string is HELLO and there are 5 processes, then process 0 toggle 
// 'H' to 'h', process 1 toggle 'E' to 'e' and so on.  

#include<stdio.h>
#include "mpi.h"

int main(int argc,char* argv[]){

    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    char str[] = "HELLO";
    int str_len = 5;

    for(int i =0;i<str_len;i++){
        if(rank ==i){
            str[i] +=32;
            printf("final string : %s\n",str);
            }
    }

    MPI_Finalize();
}