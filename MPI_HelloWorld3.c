/*********************************************************************

 Description : A very basic C-program using MPICH
 Author	   : Amandeep Singh
 Website	   : http://kodevelop.com/
 Email	   : aman.adsm@gmail.com
 github	   : https://github.com/aman-devy

***********************************************************************/

#include "mpi.h"
#include <stdio.h>
int main( int argc, char *argv[] )
	{
MPI_Init( &argc, &argv );
printf( "Hello World\n" );
MPI_Finalize();
return 0;
}