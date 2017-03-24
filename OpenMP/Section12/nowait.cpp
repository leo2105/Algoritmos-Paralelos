#include <omp.h>
#include <iostream>
#include <stdio.h>
#define CHUNKSIZE 2 // cantidad de iteraciones por cada hilo
#define N 20

using namespace std;

int main(int argc, char const *argv[])
{
	int i,chunk,tid;
	float a[N],b[N],c[N];
	for(i=0;i<N;i++)
		a[i] = b[i] = i*1.0;
	chunk = CHUNKSIZE;

	#pragma omp parallel shared(a,b,c,chunk) private(i)
	{
		#pragma omp for schedule(dynamic,chunk) nowait
		for(i=0;i<N;i++)
			{c[i]=a[i]+b[i];tid = omp_get_thread_num();printf("%d Hello World from thread = %d\n",i,tid);}
	}

	for(int i=0;i<N;i++)
		cout<<c[i]<<endl;

	return 0;
}