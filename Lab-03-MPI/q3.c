// Write a MPI program to read a string. Using N processes (string length is evenly divisible by 
// N), find the number of non-vowels in the string. In the root process print number of nonvowels 
// found by each process and print the total number of non-vowels.  

#include "mpi.h"
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

int isVowel(char x){
    x = tolower(x);
    int vowel =0;
    if(isalpha(x)){
        if(x == 'a' ||x == 'e'||x == 'i'||x == 'o'||x == 'u'){
            vowel =1;
        }
    }
    return vowel;
}


int main(int argc,char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int len ;
    int chunkSize ;
    char str[100];

    if(rank ==0){//root to read string
        printf("Rank %d: Write a string \n",rank);
        scanf("%s",str);
        len = strlen(str);
        chunkSize = len/size;
    }
    

    MPI_Bcast(&chunkSize,1,MPI_INT,0,MPI_COMM_WORLD);

    char rankStr[chunkSize];
    MPI_Scatter(str,chunkSize,MPI_CHAR,rankStr,chunkSize,MPI_CHAR,0,MPI_COMM_WORLD);

    //do individual calc
    int nonVowelCount =0;
    for(int i=0;i<chunkSize;i++){
        if(isVowel(rankStr[i])){
            //do nothing
        }
        else{
            nonVowelCount++;
        }
    }

    int nonvowelsEachRank[size];

    MPI_Gather(&nonVowelCount,1,MPI_INT,nonvowelsEachRank,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank ==0){//root display
        printf("Rank %d: non vowels in each process \n",rank);
        int sum =0;
        for(int i =0;i<size;i++){
            printf("process %d gave %d \n",i,nonvowelsEachRank[i]);
            sum += nonvowelsEachRank[i];
        }
        printf("Rank %d:Total sum is %d \n",rank,sum);

    }

    MPI_Finalize();
    return 0;
}