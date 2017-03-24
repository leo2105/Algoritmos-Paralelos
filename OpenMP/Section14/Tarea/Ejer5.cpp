#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	int a,i;
	double t1,t2;
	omp_set_num_threads(20);
	#pragma omp parallel shared(a,t1,t2,cout) private(i)
	{
		#pragma omp master
			t1 = omp_get_wtime();
		#pragma omp master
			a=10;
		#pragma omp barrier
		#pragma omp for reduction(+:a)
			for(i=0;i<10;i++)
			{
				a+=i;
			}
		#pragma omp master
			t2 = omp_get_wtime();
		#pragma omp single	
			cout<<"La suma es: "<<a<<endl;
		#pragma omp master
			cout<<"El tiempo es: "<<(t2-t1)<<" segundos."<<endl;
	}
	
	return 0;
}

// ES NECESARIO EL BARRIER EN LA LINEA 14, SINO SALDRÍA UN VALOR ERRÓNEO