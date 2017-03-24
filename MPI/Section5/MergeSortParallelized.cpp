
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#include <time.h>

#define inf (1<<30)
#define N 16

using namespace::std;

int rank,size;

//Merge Secuencial

void Merge( int* B, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1+1];
    int R[n2+1];

    for( int m = 0; m < n1; m++ )
        L[m] = B[p+m];

    for(int m = 0; m < n2; m++ )
        R[m] = B[q+m+1];
        
    L[n1]= inf;
    R[n2]= inf;
    int i,j;
    i = 0;
    j = 0;

    for( int k = p; k <= r; k++ )
    {
        if( L[i] <= R[j] )
        {
            B[k] = L[i];
            i++;
        }
        else
        {
            B[k] = R[j];
            j++;
        }
    }
}

//Merge Paralelizado

int* MergeParal( int* B, int* D, int p, int q, int r, int x, int nproc)
{
     int n=r+1;
  
     int* C = (int*) malloc ( sizeof(int) * (N/size)* 2 * x );

     MPI_Barrier(MPI_COMM_WORLD );
     MPI_Gather(B, n, MPI_INT, D, n, MPI_INT, 0, MPI_COMM_WORLD);
     MPI_Scatter(D, n*2, MPI_INT, C, n*2, MPI_INT, 0, MPI_COMM_WORLD);
     MPI_Barrier(MPI_COMM_WORLD);
     MPI_Barrier(MPI_COMM_WORLD);
    
     if( rank < (size/(2*x)) )
     {
         int n1 = r+1;
         int n2 = r+1;

         int L[n1+1];
         int R[n2+1];
        
         for( int m = 0; m < n1; m++ )
             L[m] = C[m];

         for( int m = 0; m < n2; m++ )
             R[m] = C[n1+m];
        
         L[n1] = inf;
         R[n2] = inf;
 
         int i, j;
         i = 0;
         j = 0;

         for( int k = p; k <= 2*(r+1); k++ )
         {
             if( L[i] <= R[j] )
             {
                 C[k] = L[i];
                 i++;
             }
             else
             {
                 C[k] = R[j];
                 j++;
             }
         }
     }
    	else
        free(C);

    free(B);
 
    return C;
}
void MergeSort( int* B, int p, int r )
{
    int q;
   
    if( p < r )
    {
        q = (p+r)/2;
        MergeSort(B, p, q);
        MergeSort(B, q+1, r);
        Merge(B, p, q, r);
    }
}

int main( int argc, char* argv[] )
{
    	int *A;
    	A = (int*) malloc(sizeof(int)*N);
    	double ta, tb;
	MPI_Init(&argc,&argv);
    	ta = MPI_Wtime();
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	MPI_Status status;

   	if(rank==0)
	{
     	for(int i=0;i<N;i++)
          	A[i]=rand()%20+1;
    	}
    
  	int *B;
  	B = (int*)malloc(sizeof(int)*(N/size)*2);

	MPI_Scatter(A, (int)(N/size), MPI_INT, B, (int)(N/size), MPI_INT, 0, MPI_COMM_WORLD );
    
	MPI_Barrier(MPI_COMM_WORLD);

    	if( B[0] > B[1] )
    	{
     	int aux;
 		aux = B[0];
    		B[0] = B[1];
     	B[1] = aux;
    	}

  	MPI_Barrier(MPI_COMM_WORLD);
  
   	int y;
  	int r = 1;
    	int x = 1;
 
   	while( x < size )
    	{
        r = 2*x - 1;
        int* D = (int*) malloc (sizeof(int)*N);
        B = MergeParal( B, D, 0, (int)(r/2), r, x, size );
        x *= 2;
        MPI_Barrier( MPI_COMM_WORLD );
    	}
    	if( rank == 0 )
	{
        cout << endl;
        for( int i = 0; i < N; i++ )
            cout << B[i] << " ";
        cout << endl;
     }
     tb = MPI_Wtime();
	MPI_Finalize();

     cout << "El tiempo es: "<< (tb - ta);
  
    return 0;
}
