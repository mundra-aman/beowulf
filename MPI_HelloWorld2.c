/*********************************************************************

 Description : A simple program to print a message using MPICH
 			implementation in C. This is a SPMD code, so copies of
 			this program are running on multiple nodes.
 Author	   : Amandeep Singh
 Website	   : http://kodevelop.com/
 Email	   : aman.adsm@gmail.com
 github	   : https://github.com/aman-devy

 **********************************************************************/


#include <stdio.h>
#include "mpi.h"

#define BUFLEN 512

int main(argc,argv)
int argc; char *argv[];
{
      int MyRank;	 /* rank of processes */
      int Numprocs; 	/* number of processes */
      int Destination; 	/* rank of receiver */
      int source; 	/* rank of sender */
      int tag = 0; 	/* tag for messages */
      int Root = 0; 	/* Root processes with rank 0 */
      char Send_Buffer[BUFLEN],Recv_Buffer[BUFLEN]; 	/* Storage for message */
      MPI_Status status; 	/* returns status for receive */
      int iproc,Send_Buffer_Count,Recv_Buffer_Count;

     // MyRank is the rank of process and Numprocs is the number
     //   of processes in the communicator MPI_COMM_WORLD.


     /*....MPI initialization.... */

      MPI_Init(&argc,&argv);
      MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
      MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

     //   Now, each process with MyRank not equal to Root sends message to Root,
     //   i.e., process with rank 0. Process with rank Root receives message from
     //   all processes other than him and prints the message.

      if(MyRank != 0) {
          printf(Send_Buffer, "Hello World from process with rank %d !!!\n", MyRank);
          Destination = Root;

          Send_Buffer_Count=(strlen(Send_Buffer)+1);
		MPI_Send(Send_Buffer,Send_Buffer_Count,MPI_CHAR, Destination, tag, MPI_COMM_WORLD);
      }
      else{
          for(iproc = 1; iproc < Numprocs; iproc++) {
              source = iproc;
              Recv_Buffer_Count=BUFLEN;
MPI_Recv(Recv_Buffer,Recv_Buffer_Count, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
              printf("\n %s from Processor %d *** \n", Recv_Buffer, MyRank);
         }
      }

// After, this MPI_Finalize is called to terminate the program.
// Every process in MPI computation must make this call. It terminates
// the MPI "environment".

     /* ....Finalizing the MPI....*/

      MPI_Finalize();

}