/*#include <omp.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int nthreads,tid;
	//Fork a team of threads with each thread having a private tid variable
	#pragma omp parallel private(tid)
	{
		//Obtain and print thread id
		tid = omp_get_thread_num();
		printf("Hello World from thread = %d\n",tid);

		//Only master thread does this
		if(tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n",nthreads );
		}
		
	}All threads join master thread and terminate
	return 0;
}*/
// how to compile :
// g++ filename.cpp -fopenmp
// export OMP_NUM_THREADS=N;
// ./a.out

#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc,char* argv[])
{
	int nthreads = 5;
	omp_set_num_threads(nthreads);

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		#pragma omp critical
			cout<<"Hello World from thread= "<<id<<endl;
		//cout<<" with "<<omp_get_num_threads()<<" threads"<<endl;
	}
	cout<<"all done, with hopefully "<<nthreads<<" threads"<<endl;
	return 0;
} 