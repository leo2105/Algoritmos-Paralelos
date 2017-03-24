#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
	int i,n=9;
	int a[n],b[n];
	double t1,t2;
	int nthreads = 2;
	omp_set_num_threads(nthreads);

	int id;

	#pragma omp parallel default(none) \
		shared(a,b,n,nthreads,cout,t1,t2) private(i,id)
	{
		#pragma omp master
			t1 = omp_get_wtime();
				
		id = omp_get_thread_num();

		#pragma omp single
			cout<<"La cantidad de hilos es: "<<nthreads<<endl;

		#pragma omp for schedule(runtime)
				for(i=0;i<n;i++)
				{	
					a[i]=i;
					//#pragma omp critical
					cout<<"i: "<<i<<", a_i: "<<a[i]<<" id: "<<omp_get_thread_num()<<endl;
				}

		//#pragma omp barrier
 		
 		#pragma omp single
				cout<<endl;

		#pragma omp for schedule(runtime)
				for(i=0;i<n;i++)
				{
					b[i]=2*a[i];
					//#pragma omp critical
					cout<<"i: "<<i<<", b_i: "<<b[i]<<" id: "<<omp_get_thread_num()<<endl;
				}
		#pragma omp master
			t2 = omp_get_wtime();
		#pragma omp master
			cout<<"El tiempo es: "<<(t2-t1)<<" segundos."<<endl;
	}
	return 0;
}
