/*
* @@name:	nowait.2c
* @@type:	C
* @@compilable:	yes
* @@linkable:	no
* @@expect:	success
*/

#include <math.h>
#include <stdio.h>
#include <omp.h>

void nowait_example2(int n,float *a, float *b, float *c, float *y, float
*z)
{
   int i;
#pragma omp parallel
   {
#pragma omp for schedule(static) nowait
   for (i=0; i<n; i++)
   {      c[i] = (a[i] + b[i]) / 2.0f;
//printf("thread: %d i: %d a_i: %f b_i: %f c_i %f\n",omp_get_thread_num(),i,a[i],b[i],c[i]);
   }
#pragma omp for schedule(static) nowait
   for (i=0; i<n; i++)
   {  z[i] = sqrtf(c[i]);
//printf("thread: %d i: %d c_i: %f z_i %f\n",omp_get_thread_num(),i,c[i],z[i]);
   }
#pragma omp for schedule(static) nowait
   for (i=1; i<=n; i++)
   {    y[i] = z[i-1] + a[i];
//printf("thread: %d i: %d a_i: %f z_i %f y_i %f\n",omp_get_thread_num(),i,a[i],z[i],y[i]);
   }
   }
}


int main(){
	int n=10,m=10,i;
	float a[n],b[n],c[n],y[m],z[m];

	for (i=0; i<n; i++) {
		a[i]=2;
		b[i]=3.5;
	}

	nowait_example2(n,a,b,c,y,z);
for (i=0; i<n; i++)  printf("salida i %d c_i: %f\n",i,c[i]);
for (i=0; i<n; i++)  printf("salida i %d z_i: %f\n",i,z[i]);
for (i=0; i<n; i++)  printf("salida i %d y_i: %f\n",i,y[i]);
}
