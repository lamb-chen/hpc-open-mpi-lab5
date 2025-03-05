#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>


int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int count = 5;
    char rbuf[count];
    for (int i = 0; i < 5; i ++) {
        rbuf[i] = '\0';
    }
    if (rank == 0) {
        MPI_Send(rbuf, count, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(rbuf, count, MPI_CHAR, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%s\n", rbuf);    
    }
    if (rank == 1) {
        MPI_Recv(rbuf, count, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
        rbuf[0] = 'h';
        MPI_Send(rbuf, count, MPI_CHAR, 2, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (rank == 2) {
        MPI_Recv(rbuf, count, MPI_CHAR, 1, 2, MPI_COMM_WORLD);
        rbuf[1] = 'i';
        MPI_Send(rbuf, count, MPI_CHAR, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Finalize();
}