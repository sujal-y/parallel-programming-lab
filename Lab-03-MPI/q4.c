//Write a MPI Program to read two strings Sl and S2 of same length in the root process. Using 
// N processes including the root (string length is evenly divisible by N), produce the resultant 
// string as shown below. Display the resultant string in the root process. Use Collective 
// communication routines. Example:
// String Sl: string   String S2: length  Resultant String : slternigntgh

#include "mpi.h"
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int len;
    int chunkSize ;
    char str1[100];
    char str2[100];

    if(rank ==0){//root to read string
        printf("Rank %d: Write a string 1 of multiple of %d \n",rank,size);
        scanf("%s",str1);
        printf("Rank %d: Write a string 2 of same length\n",rank);
        scanf("%s",str2);

        len = strlen(str1);
        chunkSize = len/size;
    }
    
    char Result[200];

    MPI_Bcast(&chunkSize,1,MPI_INT,0,MPI_COMM_WORLD);

    char str1Each[chunkSize];
    char str2Each[chunkSize];
    MPI_Scatter(str1,chunkSize,MPI_CHAR,str1Each,chunkSize,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Scatter(str2,chunkSize,MPI_CHAR,str2Each,chunkSize,MPI_CHAR,0,MPI_COMM_WORLD);

    //do individual calc
    char strResultEach[chunkSize*2];
    int j=0,k=0;
    for(int i =0;i<chunkSize*2;i++){
        if(i%2 == 0){
            strResultEach[i] = str1Each[j++];
        }
        else{
            strResultEach[i] = str2Each[k++];
        }
    }


    MPI_Gather(strResultEach,chunkSize*2,MPI_CHAR,Result,chunkSize*2,MPI_CHAR,0,MPI_COMM_WORLD);

    if(rank ==0){//root display result
        printf("Rank %d:result = %s \n",rank,Result);
    }

    MPI_Finalize();
    return 0;
}