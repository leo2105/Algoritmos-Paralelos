/*
* @@name:	nowait.1c
* @@type:	C
* @@compilable:	yes
* @@linkable:	no
* @@expect:	success
*/
#include <math.h>
#include <stdio.h>
#include <omp.h>

void nowait_example(int n, int m, float *a, float *b, float *y, float *z)
{
  int i;
  #pragma omp parallel
  {
    #pragma omp for nowait
      for (i=1; i<n; i++){
        b[i] = (a[i] + a[i-1]) / 2.0;
printf("thread: %d i: %d a_i: %f b_i: %f\n",omp_get_thread_num(),i,a[i],b[i]);
      }
#pragma omp for nowait
      for (i=0; i<m; i++){
        y[i] = sqrt(z[i]);
printf("thread: %d i: %d z_i: %f y_i: %f\n",omp_get_thread_num(),i,z[i],y[i]);
  	}
  }
}

int main(){
int n=10,m=10,i;
float a[n],b[n],y[m],z[m];

      for (i=0; i<n; i++) a[i]=1;
      for (i=0; i<m; i++) z[i]=10;

nowait_example(n,m,a,b,y,z);

}
