/*
* @@name:	collapse.2c
* @@type:	C
* @@compilable:	yes
* @@linkable:	no
* @@expect:	success
*/
#include <stdio.h>
#include <omp.h>
void test()
{
   int j, k, jlast=0, klast=0;
   int nthreads = 10;
   int x=0;
   omp_set_num_threads(nthreads);
   #pragma omp parallel
   {
      printf("hola1");
      #pragma omp for collapse(2) lastprivate(jlast, klast)
      for (k=1; k<=2; k++)
         for (j=1; j<=3; j++)
         {
            x++;
            jlast=j;
            klast=k;
         }
      
      printf("hola2");
      printf("%d %d\n",jlast,klast);
      #pragma omp barrier
      #pragma omp single
         printf("%d %d %d\n", klast, jlast,x);
   }
}

int main(){
   test();
   return 0;
}
