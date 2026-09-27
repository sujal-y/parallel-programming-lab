// Write a MPI program using synchronous send. The sender process sends a word to the 
// receiver. The second process receives the word, toggles each letter of the word and sends 
// it back to the first process. Both processes use synchronous send operations.


#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char* argv[]){
    int rank,size;
    char word[100];
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    

    if(rank == 0){

        char input[100];
        printf("Enter a word : ");
        scanf("%s",input);
        strcpy(word,input);

        int len = strlen(word) + 1;

        printf("Rank : %d :sending the word\n",rank);
        MPI_Ssend(word,len,MPI_CHAR,1,0,MPI_COMM_WORLD);

        MPI_Recv(word,len,MPI_CHAR,1,0,MPI_COMM_WORLD,&status);
        printf("Rank : %d :Recived the toggled word \n",rank);

        printf("Rank : %d :word is : %s \n",rank,word);
    }
    else if(rank == 1){

        MPI_Recv(word,100,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
        printf("Rank : %d :received the word\n",rank);

        int len = strlen(word) +1;
        //toggle
        for(int i =0; word[i] != '\0';i++){
            if(isupper(word[i])){
                word[i] = tolower(word[i]);
            }
            else if(islower(word[i])){
                word[i] = toupper(word[i]);
            }
        }
        printf("Rank : %d :toggled the word , sending\n",rank);

        MPI_Ssend(word,len,MPI_CHAR,0,0,MPI_COMM_WORLD);
        printf("Rank : %d :Sent toggled word\n",rank);

    }

    MPI_Finalize();
    return 0;
}