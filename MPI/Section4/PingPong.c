
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[] )
{
	int world_rank, world_size, i = 0;
	double time1, time2;

	MPI_Init( NULL, NULL );
	MPI_Comm_size( MPI_COMM_WORLD, &world_size );
	MPI_Comm_rank( MPI_COMM_WORLD, &world_rank );

	time1 = MPI_Wtime();	

	int number = 1;
	float *A = NULL;
	A = (float*) malloc(sizeof(float)*number);

	if ( world_rank == 0 ) 
    		MPI_Send( &number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD );
  	 
  	else if ( world_rank == 1 ) 
	{
   		MPI_Recv( A, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		printf("Proceso 1 recibió número %d del proceso 0\n", number);
		number *= 2;
		MPI_Send(&number, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);  			
	}	

	i++;

	for( ; i <= 9; i++ )
	{
		if ( world_rank == 0) 
		{
       		MPI_Recv(&number, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Proceso 0 recibió número %d del proceso 1\n", number);
			number *= 2;
			MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		} 
  		else if ( world_rank == 1 )
		{    			 				
		    	MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		    	printf("Proceso 1 recibió número %d del proceso 0\n", number);
			number*=2;
			MPI_Send(&number, 1, MPI_INT, 0, 1, MPI_COMM_WORLD); 			
		}
			
	}
	
	time2 = MPI_Wtime();
	
	if( world_rank == 0 )
		printf("\nEl tiempo es: %.10f\n", time2-time1);
	
	MPI_Finalize();
	
	return 0;
}


