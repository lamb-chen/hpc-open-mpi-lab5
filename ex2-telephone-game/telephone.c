#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    printf("Telephone game with %d processes\n", size);
  }

  // Assume less than 61 ranks (printing A to tilde)
  if ( size > 61 ) {
    if (rank == 0) printf("Error: use less than 61 ranks\n");
    MPI_Finalize();
    return EXIT_FAILURE;
  }

  // Everyone allocate an array of size chars
  char *message = malloc(sizeof(char) * (size+1));
  
  // Null terminate the whole array
  for (int i = 0; i < size+1; ++i)
    message[i] = '\0';

  // Everyone set their character
  message[rank] = 'A'+rank;

  // First rank sends to right-hand neighbour (rank 1), then receives from final rank
  if (rank == 0) {
    MPI_Send(message, 1, MPI_CHAR, 1, 99, MPI_COMM_WORLD);
    MPI_Recv(message, size, MPI_CHAR, size-1, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  // Other ranks receive, then send to right-hand neighbour
  else {
    MPI_Recv(message, rank, MPI_CHAR, rank-1, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // The character was already set above
    MPI_Send(message, rank+1, MPI_CHAR, (rank+1)%size, 99, MPI_COMM_WORLD);
  }

 
  if (rank == 0) {
    printf("The message has %lu characters and says \"%s\"\n", strlen(message), message);
  }

  MPI_Finalize();
  return EXIT_SUCCESS;
}