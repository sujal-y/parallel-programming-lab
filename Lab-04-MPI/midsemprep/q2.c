// Write a MPI program to read a 3 X 3 matrix. Enter an element to be searched in the root 
// process. Find the number of occurrences of this element in the matrix using three processes

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void handle_mpi_error(int err){
    if(err != MPI_SUCCESS){
    char err_string[MPI_MAX_ERROR_STRING];
    int err_len,err_class;
    MPI_Error_class(err,&err_class);
    MPI_Error_string(err,err_string,&err_len);
    printf("Error class %d, meaning %s",err_class,err_string);
    }
}

int main(int argc,char* argv[]){
    int rank, size, err;
    long long fact = 1, scan_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

    err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    handle_mpi_error(err);

    err = MPI_Comm_size(MPI_COMM_WORLD, &size);
    handle_mpi_error(err);

    int array[3][3];
    int element;
    if(rank ==0){//root
        //reads the 3x3 matrix 
        printf("Rank %d: Enter the 3x3 matrix elements \n",rank);
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf("%d",&array[i][j]);
            }
        }

         printf("Rank %d: Enter element to find\n",rank);
         scanf("%d",&element);
    }

    err = MPI_Bcast(&element,1,MPI_INT,0,MPI_COMM_WORLD);
    handle_mpi_error(err);
    //send each process an row
    int eachRow[3];
    MPI_Scatter(array,3,MPI_INT,eachRow,3,MPI_INT,0,MPI_COMM_WORLD);

    int local_occurence = 0, total_occurence =0;

    for(int i=0;i<3;i++){
        if(eachRow[i] == element){
            local_occurence++;
        }
    }

    MPI_Reduce(&local_occurence,&total_occurence,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank == 0){
        printf("Rank %d: Total occurence : %d\n",rank,total_occurence);
    }




    MPI_Finalize();
    return 0;
}