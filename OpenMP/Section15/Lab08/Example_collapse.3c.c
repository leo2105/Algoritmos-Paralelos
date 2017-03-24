/*
* @@name:	collapse.3c
* @@type:	C
* @@compilable:	yes
* @@linkable:	no
* @@expect:	success
*/
#include <omp.h>
#include <stdio.h>

void work(int a, int j, int k){};

void sub()
{
   int j, k, a;
   #pragma omp parallel num_threads(2)
   {
      //#pragma omp for collapse(2) ordered private(j,k) schedule(static,3)
      #pragma omp for collapse(2)  
      for (k=1; k<=15; k++)
         for (j=1; j<=10; j++)
         {
//            #pragma omp ordered
            printf("%d %d %d\n", omp_get_thread_num(), k, j);
            /* end ordered */
            work(a,j,k);
         }
   }
}

int main(){
	sub();

}
