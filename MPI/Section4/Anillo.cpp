
#include <iostream>
#include <mpi.h>

using namespace::std;

int rank, size;

int main( int argc, char *argv[] )
{
	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	
	MPI_Status status;
	
	int valrec, valdar = rank;

	MPI_Barrier( MPI_COMM_WORLD );

	for( int i = 0; i < size; i++ )
	{
		if( i == rank )
		{
			if( i == 0 )
				MPI_Send( &valdar, 1, MPI_INT, 1, rank, MPI_COMM_WORLD );
			else
			{
				MPI_Recv(&valrec, 1, MPI_INT, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send(&valdar, 1, MPI_INT, (rank+1)%size, rank, MPI_COMM_WORLD);
			}
		}		
		MPI_Barrier(MPI_COMM_WORLD);
	}

	if( rank == 0 )
		MPI_Recv(&valrec,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	MPI_Barrier(MPI_COMM_WORLD);

	if ( rank == 0 )
		cout << "Rank\t\tUser/Proceso" << endl;	
	
	MPI_Barrier(MPI_COMM_WORLD);

	cout << rank << "\t\t" << valrec << endl;	

	MPI_Finalize();

	return 0;
}
