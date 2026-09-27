// Write a MPI program using collective communication functions, to replace all even 
// elements of array A to 1 and replace all odd elements to 0 of size N. Display the resultant 
// array A, count of all even and odd numbers in root process. Assume N is evenly divisible 
// by number of processes.  

#include "mpi.h"
#include <stdio.h>

int isOdd(int x){
    if(x%2 ==0){
        return 0;
    }
    else{
        return 1;
    }
}

int main(int argc , char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int totalElements;
    if(rank ==0){//root
        printf("how many elements \n");
        scanf("%d",&totalElements);

    }
    MPI_Bcast(&totalElements,1,MPI_INT,0,MPI_COMM_WORLD);

    int mainArray[totalElements];
    if(rank ==0){
        printf("enter elements \n");
        for(int i =0;i<totalElements;i++){
            scanf("%d",&mainArray[i]);
        }
    }
    int count = totalElements/size;

    int eachArray[count];
    MPI_Scatter(mainArray,count,MPI_INT,eachArray,count,MPI_INT,0,MPI_COMM_WORLD);

    for(int i=0;i<count;i++){
        if(isOdd(eachArray[i])){
            eachArray[i] =0;
        }
        else{
            eachArray[i] =1;
        }
    }

    MPI_Gather(eachArray,count,MPI_INT,mainArray,count,MPI_INT,0,MPI_COMM_WORLD);

    if(rank ==0){
        printf("printing the result \n");
        int oddCount;
        for(int i = 0; i<totalElements;i++){
            if(mainArray[i] ==0)oddCount++;
            printf("%d ",mainArray[i]);
        }
        printf("\n");
        printf("total odd: %d , total even :%d",oddCount,(totalElements-oddCount));
    }
    MPI_Finalize();
    return 0;
}