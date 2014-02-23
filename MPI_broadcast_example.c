#include <stdio.h>
#include "mpi.h"

#define ASIZE	100
#define PI	3.141592653589793238462643

void main(int argc, char **argv)
{
	int me, nprocs, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int i;
	double seed, init_val[ASIZE], val[ASIZE], sum, tsum;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	MPI_Get_processor_name(processor_name, &namelen);

	if (!me) {	/* Only the first process in the group */
		printf("Enter some kind of seed value:\n");
		scanf("%lf", &seed);
		for (i = 0; i < ASIZE; i++)
			init_val[i] = (double)i * seed * PI;
	}

	/* Broadcast computed initial values to all other processes */
	if (MPI_Bcast(init_val, ASIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD)
		!= MPI_SUCCESS)
		fprintf(stderr, "Oops! An error occurred in MPI_Bcast()\n");

	for (i = 0, sum = 0.0; i < ASIZE; i++) {
		val[i] = init_val[i] * me;
		sum += val[i];
	}
	printf("%d: My sum is %lf\n", me, sum);

	/* Send sum back to the first process */
	if (me)	{	/* All processes except the one of rank 0 */
		MPI_Send(&sum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	}
	else {
		tsum = sum;
		for (i = 1; i < nprocs; i++) {
			MPI_Recv(&sum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1,
				MPI_COMM_WORLD, &status);
			tsum += sum;
		}
		printf("%d: Total sum is %lf\n", me, tsum);
	}

	MPI_Finalize();
}