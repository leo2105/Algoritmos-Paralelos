#include <iostream>
#include <mpi.h>
#define MAX 3
using namespace std;

int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

void init()
{
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			A[i][j]=i+j+1;
			B[i][j]=i+j;
			C[i][j]=0;
		}
	}
}

int main(int argc,char* argv[])
{
	int numproc,myid;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Status status;

	for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++)
			C[i][j]=0;

	init();
		
	MPI_Barrier(MPI_COMM_WORLD);
	if(myid==0)
	{
		for(int dest=1;dest<numproc;dest++)
		{	
			MPI_Send(&A[dest-1][0],MAX,MPI_INT,dest,dest,MPI_COMM_WORLD);
		}

		for(int i=1;i<numproc;i++)
		{
			MPI_Recv(&C[i-1][0],MAX,MPI_INT,i,i,MPI_COMM_WORLD,&status);
		}
	}
	else
	{
		MPI_Recv(&A[0][0],MAX,MPI_INT,0,myid,MPI_COMM_WORLD,&status);
		// Calcular submatrix
		for(int i=0;i<MAX;i++)
		{
			for(int j=0;j<MAX;j++)
			{
				C[0][i]+=A[0][j]*B[j][i];
			}
		}
		
		MPI_Send(&C[0][0],MAX,MPI_INT,0,myid,MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	

	if(myid==0)
	{
		for(int i=0;i<MAX;i++)
		{
			cout<<endl;
			for(int j=0;j<MAX;j++)
			{
				cout<<A[i][j]<<" ";
			}
		}
		cout<<endl;
		for(int i=0;i<MAX;i++)
		{
			cout<<endl;
			for(int j=0;j<MAX;j++)
			{
				cout<<B[i][j]<<" ";
			}
		}
		cout<<endl;
		for(int i=0;i<MAX;i++)
		{
			cout<<endl;
			for(int j=0;j<MAX;j++)
			{
				cout<<C[i][j]<<" ";
			}
		}
		cout<<endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	
	MPI_Finalize();
	return 0;
}