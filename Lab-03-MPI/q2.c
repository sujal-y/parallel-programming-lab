//Write a MPI program to read an integer value M and NXM elements into an ID array in the 
// root process, where N is the number of processes. Root process sends M elements to each 
// process. Each process finds average of M elements it received and sends these average values 
// to root. Root collects all the values and finds the total average. Use collective communication 
// routines

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

        double sum =0;
        for(int i =0;i<m;i++){
            sum +=array[i];
        }
        double avg = sum/m;

        //make a avg array for root
        double avgArray[n];
        MPI_Gather(&avg,1,MPI_DOUBLE,avgArray,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

        if(rank ==0){//root
            double totalAvg =0;
            for(int i =0;i<n;i++){
                totalAvg +=avgArray[i];
            }    
            totalAvg /= n;
            printf("Rank %d: total average is %f\n",rank,totalAvg);
        }


    

    MPI_Finalize();
    return 0;
}