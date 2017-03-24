#include <iostream>
using namespace std;

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

int main()
{
   int n = 9;
   int i, a, b[n];
#ifdef _OPENMP
   omp_set_num_threads(4);
#endif
   for (i=0; i<n; i++)
       b[i] = -1;
  	double t1,t2;
#pragma omp parallel shared(t1,t2,a,b) private(i)
{
   #pragma omp master
		t1 = omp_get_wtime();
   #pragma omp single
   {
      a = 10;
      cout<<"constructor Single ejecutado por el hilo "<<omp_get_thread_num()<<endl;
   }
   #pragma omp for
   for (i=0; i<n; i++)
       b[i] = a;
   #pragma omp master
		t2 = omp_get_wtime();
	#pragma omp master
		cout<<"El tiempo de ejecucion es: "<<(t2-t1)<<" segundos."<<endl;
} 
cout<<"Fin de la region en paralelo: "<<endl;
   for (i=0; i<n; i++)
   cout<<"b["<<i<<"]"<<"= "<<b[i]<<endl;

}
