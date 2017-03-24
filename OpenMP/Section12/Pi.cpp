#include <iostream>
#include <omp.h>
#include <stdio.h>

using namespace std;

int N = 1000000;
double h,x,pi;
double sum=0.0;

int main(int argc, char const *argv[])
{
	h = 1.0/(double)N;
	int i;
	int Nthreads = 256;
	double inicio,fin;
	omp_set_num_threads(Nthreads);
	
	#pragma omp parallel shared(h,sum,inicio,fin) private(i)
	{
		#pragma omp single
			inicio = omp_get_wtime();
		#pragma omp for reduction(+:sum) nowait
			for(i=0;i<N;i++)
			{
				double x=(i+0.5)*h;
				sum += (4.0/(1.0+x*x));
			}
		#pragma omp single		
			fin = omp_get_wtime();
	}
	pi = h*sum;
	cout<<"El calculo de pi es: "<<pi<<endl;
	cout<<"np: "<<Nthreads<<endl;
	cout<<"N: "<<N<<endl;
	cout<<"Tiempo: "<<(fin-inicio)<<endl;
	return 0;
}