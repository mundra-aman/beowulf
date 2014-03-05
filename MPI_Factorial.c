// Task 1. Sum(1/n!)
// Author: Anton Danshin
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  double result;
  int n = 0;
  if(argc>1)
    n = atoi(argv[1]);

  double startwtime = 0.0;
  double endwtime;

  // Initialize the MPI environment
  MPI_Init(&argc, &argv);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if(world_rank==0)
    startwtime = MPI_Wtime();

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  double a = 0.0;
  double f = 1.0;
  double s = 0.0;

  int i;
  int t = n/world_size;
  if(n%world_size) t++;
  for(i = (n/world_size)*world_rank; i<world_rank*(n/world_size)+t; i++) {
    if(i+1>n)
       break;
    f /= (double)(i+1);
    s += f;
  }

  // Receive A and F from previous node
  double a_p, f_p = 1.0;
  if(world_rank > 0) {
    MPI_Recv(&f_p, 1, MPI_DOUBLE, world_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    f *= f_p;
  }
  s *=f_p;

  // Send my A nad F to the next node
  if(world_rank < world_size-1) {
    MPI_Send(&f, 1, MPI_DOUBLE, world_rank+1, 0, MPI_COMM_WORLD);
  }

  MPI_Reduce(&s, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if(world_rank==0) {
    endwtime = MPI_Wtime();
    printf("Result: %.10f\n", result+1);
    printf("Time elapsed: %fms\n", (endwtime-startwtime)*1000);
  }

  MPI_Finalize();
}
