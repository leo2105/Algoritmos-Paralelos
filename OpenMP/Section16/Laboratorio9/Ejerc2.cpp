#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <omp.h>

using namespace std;

void quickSort(int*, int);

void quickSort(int *vector, int n) {
    int i,j;
    int t,p;
    if (n < 2)
        return;
    p = vector[n / 2];
    for (i=0,j=n-1;; i++, j--) {
        while (vector[i] < p)
            i++;
        while (p < vector[j])
            j--;
        if (i >= j)
            break;
        t = vector[i];
        vector[i] = vector[j];
        vector[j] = t;
    }
    #pragma omp task
      quickSort(vector, i);
    
    #pragma omp task
      quickSort(vector + i, n - i);
    
    #pragma omp taskwait
}

int main()
{
  int n=106;
  cout<<"N: "<<n<<endl;

  int vector[n];
  int i;
  int Nthreads=16;
  cout<<"np: "<<Nthreads<<endl;
  omp_set_num_threads(Nthreads);

  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
      vector[i]=rand()%99+1;
  
  printf("\n");
  printf("Vector antes de quickSort:\n");
  
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
      #pragma omp ordered
        printf("%d ",vector[i]);   
  
  printf("\n");
  
  double ini,fin;
  #pragma omp parallel
  {
    #pragma omp single
      ini = omp_get_wtime();
    #pragma omp single
      quickSort(vector,n);
    #pragma omp single
      fin = omp_get_wtime();
  }
  
  printf("\n");
  printf("Vector despues de quickSort:\n");
  
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
      #pragma omp ordered
        printf("%d ",vector[i]);   
  
  printf("\n\n");
  
  cout<<"Tiempo: "<<(fin-ini)<<endl;
  return 0;
}