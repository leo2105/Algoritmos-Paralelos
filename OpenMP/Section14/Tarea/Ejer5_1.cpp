#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int N=10;
	int A[N],i;
	int a,b;
	double t1,t2;
	omp_set_num_threads(20);
	#pragma omp parallel shared(A,t1,t2,a,N,cout) private(i)
	{
		srand(time(NULL));
		#pragma omp master
			t1 = omp_get_wtime();
		#pragma omp for
			for(i=0;i<N;i++)
				A[i]=rand()%50;
		

		#pragma omp for reduction(max:a)
			for(i=0;i<N;i++)
			{
				if(A[i]>a)
					a=A[i];
			}
		#pragma omp for reduction(min:b)
			for(i=0;i<N;i++)
			{
				if(A[i]<b)
					b=A[i];
			}
		#pragma omp master
			t2 = omp_get_wtime();

		#pragma omp master
			for(i=0;i<N;i++)
				cout<<A[i]<<" ";
		#pragma omp single
			cout<<endl;

		#pragma omp single	
			cout<<endl<<"El mayor es: "<<a<<endl;
		#pragma omp single
			cout<<"El menor es: "<<b<<endl;
		#pragma omp master
			cout<<"El tiempo es: "<<(t2-t1)<<" segundos."<<endl;
	}
	
	return 0;
}
