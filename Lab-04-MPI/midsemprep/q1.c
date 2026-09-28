// Write a MPI program using N processes to find l ! + 2! +. ....+N!. Use scan. Also, handle 
// different errors using error handling routines

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void handle_mpi_error(int err_code){
    if(err_code != MPI_SUCCESS){
    char err_string[MPI_MAX_ERROR_STRING];
    int err_len,err_class;
    MPI_Error_class(err_code,&err_class);
    MPI_Error_string(err_code,err_string,&err_len);
     printf("[Error Handler] Code: %d, Class: %d, Message: %s\n", err_code, err_class, err_string);
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

    for(int i = 1;i<=rank+1;i++){
        fact = fact*i;
    }

    err = MPI_Scan(&fact,&scan_sum,1,MPI_LONG_LONG,MPI_SUM,MPI_COMM_WORLD);
    handle_mpi_error(err);

    printf("rank:%d prefix sum:%lld\n",rank,scan_sum);

    MPI_Finalize();
    return 0;
}

