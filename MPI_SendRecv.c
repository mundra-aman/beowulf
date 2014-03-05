/*********************************************************************

 Description : Send/Recv point to point communication example

 Author	   : Amandeep Singh
 Website	   : http://kodevelop.com/
 Email	   : aman.adsm@gmail.com
 github	   : https://github.com/aman-devy

 **********************************************************************/


#include <stddef.h>
#include <stdlib.h>
#include "mpi.h"

main (int argc, char **argv )
{
  char message[20];
  int i, rank, size, type=99;
  MPI_Status status;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  if (rank == 0)
    {
      strcpy (message, "Hello!");
      for (i = 1; i < size; i++)
        MPI_Send (message, 7, MPI_CHAR, i, type, MPI_COMM_WORLD);
    }
  else
    {
      MPI_Recv(message, 20, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status);
    }
  printf ("%s from process %d\n", message, rank);
  MPI_Finalize();
}