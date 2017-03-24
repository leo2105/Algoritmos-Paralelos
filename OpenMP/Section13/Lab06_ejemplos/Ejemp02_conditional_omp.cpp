
#include <iostream>

using namespace::std;

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main( int argc, char *argv[] )
{
   int TID = omp_get_thread_num();
   cout<< "Hilo maestro es " << TID << endl;

	#ifdef _OPENMP
   		omp_set_num_threads(4);
	#endif

	//cout<<"Hilos paralelos: "<<endl;
	#pragma omp parallel
	{
   		int TID = omp_get_thread_num();
		#pragma omp critical
   			cout<<"Hilo paralelo "<<TID<<endl;
	}

	cout<<endl;

	#ifdef _OPENMP
		cout << _OPENMP << endl;
	#endif

	return 0;
}

