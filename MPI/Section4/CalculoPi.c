#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include "mpi.h"

int main(int argc,char *argv[])
{
	int numproc, myid, i, j, n = 10000;
	double aux, sum, local;
	double pi = 3.14159265358979323846;
	double h = 1.0/n;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &numproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	MPI_Bcast( &n, 1, MPI_INT, 0, MPI_COMM_WORLD );
	
	local = 0;
	for( i = myid + 1; i <=n; i += numproc )
	{
		aux = h * ((double)i - 0.5);
		local += ( 4.0/(1.0 + aux*aux ) );
	}
	
	MPI_Reduce( &local, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
	
	if( myid == 0 )
	{
		sum = sum*h;
		printf("La suma es: %.10f\n", sum);
		printf("Un error de: %.10f\n", fabs(sum-pi));
	}
	MPI_Finalize();

	return 0;
}

