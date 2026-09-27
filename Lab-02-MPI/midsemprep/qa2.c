//Write a MPI program to read value of N in the root process. Using N processes, including 
// root, find out 1! + ( 1+2 ) +3! +( 1+2+3+4 ) +5! +(1+2+3+4+5+6) and print the result in 
// the root process

#include <stdio.h>
#include "mpi.h"

long long compute_term(int k) {
    if (k % 2 != 0) {// odd process so factorial
        long long fact = 1;
        for (int i = 1; i <= k; i++) {
            fact *= i;
        }
        return fact;
    } else {//even process so sum
        return (long long)k * (k + 1) / 2;
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int k = rank + 1; 
    long long my_term = compute_term(k);

    if (rank == 0) {//master
        long long total_sum = my_term;
        printf("Rank 0: Term %d = %lld\n", k, my_term);

        for (int i = 1; i < size; i++) {
            long long term;
            MPI_Recv(&term, 1, MPI_LONG_LONG, i, 0, MPI_COMM_WORLD, &status);
            printf("Rank 0: Received Term %d = %lld from Rank %d\n", i + 1, term, i);
            total_sum += term;
        }

        printf("Final Series Sum = %lld\n", total_sum);
    } 
    else {//slaves send
        MPI_Send(&my_term, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}