// La cantidad de np es igual a N+1
// El nodo 0 administra la entrega de cada elemento en el array

#include <iostream>
#include <mpi.h>
#define N 8

using namespace std;

int A[N];

int main(int argc,char* argv[])
{
	int myid,numproc;
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);

	int val1,val2;
	MPI_Status status;
	if(myid==0)
	{
		for(int i=0;i<N;i++)
			cin>>A[i];
		for(int i=0;i<N;i++)
			MPI_Send(&A[i],1,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv(&val1,1,MPI_INT,0,myid,MPI_COMM_WORLD,&status);
	}

	for(int i=0;i<N;i++)
	{
		if(i%2==0)
		{
			MPI_Send
		}
		else
		{

		}
	}
	
	MPI_Finalize();
	return 0;
}