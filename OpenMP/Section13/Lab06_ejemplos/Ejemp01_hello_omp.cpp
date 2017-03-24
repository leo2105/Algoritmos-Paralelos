#include <iostream>
#include <omp.h>
using namespace std;

int main ()  
{
   int nthreads = 8;
   omp_set_num_threads(nthreads);

   #pragma omp parallel 
   {
      int id = omp_get_thread_num();
      #pragma omp master //--solo ingresa el hilo maestro
      cout<<"Hello World from thread = "<<id<<endl;
      #pragma omp barrier
      #pragma omp critical //--ingresa un hilo a la vez
      	cout << id <<" with "<<omp_get_num_threads()<<" threads"<<endl;
   }  

   cout<<"all done, with hopefully "<< nthreads<<" threads"<<endl;;

}

 

