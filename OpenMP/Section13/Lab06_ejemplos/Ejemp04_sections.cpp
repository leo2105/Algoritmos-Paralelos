#include <iostream>
using namespace std;

#define N        10000
#define Nthreads 2

#define SEED       2531
#define RAND_MULT  1366
#define RAND_ADD   150889
#define RAND_MOD   714025
int numran = SEED;

/* inicializacion random del array */
void ini(int length, double *a)
{
   int i; 
   for (i=0;i<length;i++) {
     numran = (RAND_MULT * numran + RAND_ADD) % RAND_MOD;
     *(a+i) = ((double) numran)/((double) RAND_MOD);
   }   
}

/* suma de los elementos del array */
double suma(int length, double *a)
{
   int i;  double sum = 0.0;
   for (i=0;i<length;i++)  sum += *(a+i);  
   return sum; 
}
  
int main()
{
  double sum;
  double A[N];

  ini(N, A);
  sum = suma(N, A);
  cout<<"la suma es: "<<sum<<endl;
}
 
