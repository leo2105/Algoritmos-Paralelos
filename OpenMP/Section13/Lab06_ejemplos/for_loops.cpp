#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int i,n=9;
	int a[n],b[n];

	int nthreads = 4;
	omp_set_num_threads(nthreads);

	#pragma omp parallel default(none) shared(n,a,b,cout) private(i)
	{
		//cout<<"primer bucle, numero de hilos: "<<omp_get_num_threads()<<endl;
	#pragma omp for //private(i)
	for(i=0;i<n;i++)
	{
		a[i]=i;
		cout<<"i: "<<i<<", a_i:"<<a[i]<<endl;
	}

	#pragma omp for //private(i)
	for(i=0;i<n;i++)
	{
		b[i] = 2*a[i];
		cout<<"i: "<<i<<", b_i: "<<b[i]<<endl;
	}
	}
}