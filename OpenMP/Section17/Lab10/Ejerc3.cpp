// Profesor en vez de realizar la multiplicacion de matrices, quise realizar este
// ejercicio que es el numero 3.
#include <iostream>
#include <omp.h>
#include <mpi.h>
#include <stdio.h>

using namespace std;

long N = 1000000000;
double h,x,pi;

double sumTotal; 

int main(int argc, char *argv[])
{
	h = 1.0/(double)N;
	long i;
	double ini,fin;

	int numproc,myid;

	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);

	long particion = N/numproc;
	
	MPI_Bcast(&particion,1,MPI_LONG,0,MPI_COMM_WORLD);

	int Nthreads = 16;
	double sum;
	if(myid==0)
		ini = MPI_Wtime();
	omp_set_num_threads(Nthreads);

	#pragma omp parallel shared(h,sum,myid,particion) private(i)
	{
		#pragma omp master
			sum=0.0;
		#pragma omp barrier
		#pragma omp for reduction(+:sum) nowait
			for(i=(myid)*particion;i<(myid+1)*particion;i++)
			{
				double x=(i+0.5)*h;
				sum += (4.0/(1.0+x*x));
			}
	}

	MPI_Reduce(&sum,&sumTotal,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(myid==0)
	{
		pi = h*sumTotal;
		fin = MPI_Wtime();
		cout<<"El calculo de pi es: "<<pi<<endl;
		cout<<"Numero de Procesadores: "<<numproc<<endl;
		cout<<"Numero de Hilos: "<<Nthreads<<endl;
		cout<<"Tiempo: "<<(fin-ini)<<endl;
	}

	MPI_Finalize();	
	return 0;
}

// EN PARALELO

// Se utilizo este numero N ya que es en el que puede apreciar mejor la eficiencia.

// N = 10^9 
// Siempre se obtiene el valor de 3.14159 para PI
// Procesadores		Hilos	Tiempo
// 2				2		3.14677
// 2				4 		3.17542
// 2				8		3.08965
// 2				16		3.08087
// 4				2 		3.22155		
// 4				4 		3.15439
// 4				8		3.09184
// 4				16 		3.14155
// 8				2 		3.22590
// 8				4 		3.33991
// 8				8		3.24394
// 8				16      3.36392
// 16				2 		3.28393
// 16				4 		3.41992
// 16				8		3.20389
// 16				16 		3.34787

// Estos valores se calculando el promedio.
// El más eficiente fue para 2 procesadores y 16 hilos.

// EN SECUENCIAL

// N = 10^9
// Siempre se obtiene el valor de 3.14159 para PI
// El tiempo es: 19.6281 segundos