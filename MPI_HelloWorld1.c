/*********************************************************************

 Description : A simple hello world program using MPICH
 			implementation in C
 Author	   : Amandeep Singh
 Website	   : http://kodevelop.com/
 Email	   : aman.adsm@gmail.com
 github	   : https://github.com/aman-devy

 **********************************************************************/

#include <stdio.h>
#include "mpi.h"

void main(int argc, char **argv)
	{
        int taskID;
        int total_processes;
        int namelen;
        char processor_name[MPI_MAX_PROCESSOR_NAME];

        MPI_Init(&argc, &argv);

        MPI_Comm_size(MPI_COMM_WORLD, &total_processes);
        MPI_Comm_rank(MPI_COMM_WORLD, &taskID);
        MPI_Get_processor_name(processor_name, &namelen);

        printf("Hello World!  I'm process %d of %d on %s\n",
        taskID, total_processes, processor_name);

        MPI_Finalize();

	}