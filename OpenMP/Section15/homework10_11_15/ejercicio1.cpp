#include <iostream>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

#define Nthreads 3

using namespace std;

int fib(int n){
	int i , j;
	
    if(n<2)
	   return n;
    
	else{
	   #pragma omp task shared(i)
       {
       i = fib(n-1);
       cout << "Thread " << omp_get_thread_num() << endl;
       }
       #pragma omp task shared(j)
       {
	   j = fib(n-2);
       cout << "Thread " << omp_get_thread_num() << endl;
       }
       #pragma omp taskwait       
       return i+j;
	}
}
int main(){
    int n = 4;
    #ifdef _OPENMP
     omp_set_num_threads(Nthreads);
    #endif

    #pragma omp parallel shared(n)
        #pragma omp single// nowait
            cout << n << "th number " << fib(n) << " ";

    cout << endl;
}


