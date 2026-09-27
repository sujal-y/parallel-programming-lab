// Write a MPI program to read a value M and NXM number of elements into ID array in the 
// root, where N is the total number of processes. Find the square of first M numbers, the cube 
// of next M numbers and so on. Print the results in the root.  

#include "mpi.h"
#include <stdio.h>

int main(int argc,char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int n =size;
    int m =0;
    
    if(rank == 0){//root
        printf("Rank %d: Enter the number m\n",rank);
        scanf("%d",&m);

    }
        //send the number m to all
        MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);

        //make a nXm matrix
        double BigArray[n][m];

        if(rank ==0){// adding to big array
            printf("Rank %d: Enter the %d elements for %d elements each\n",rank,m,size);
        for(int i =0;i<n;i++){
            for(int j=0;j<m;j++){
                scanf("%lf",&BigArray[i][j]);
            }
        }
        }
        double array[m];

        MPI_Scatter(BigArray,m,MPI_DOUBLE,array,m,MPI_DOUBLE,0,MPI_COMM_WORLD);

        
        for(int i =0;i<m;i++){
            double result = 1;

            for(int j = 0; j < rank + 2; j++){
                result *= array[i];
            }

            array[i] = result;
        }
       
        //make a square array for root
        double BigSqArray[n][m];
        
        MPI_Gather(array,m,MPI_DOUBLE,BigSqArray,m,MPI_DOUBLE,0,MPI_COMM_WORLD);

        if(rank ==0){//root
            for(int i =0;i<n;i++){
                for(int j= 0 ; j<m;j++){
                    printf("%f ",BigSqArray[i][j]);
                }
                printf("\n");
            }    
        }

    MPI_Finalize();
    return 0;
}