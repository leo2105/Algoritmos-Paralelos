#include <stdlib.h>
#include <iostream>
#include <omp.h>
using namespace std;
#define NMAX 1000
#define MMAX 1000

int main(int argc, char *argv[])
{
	double a[NMAX],b[NMAX*MMAX],c[NMAX];
	int m, n;
	double timeA,timeB;

	cout << "Ingresar m: " << endl;
	cin >> n;
	cout << "Ingresar n: " << endl;
	cin >> m;
	cout << endl;

	cout<<"Initializing matrix B and vector c"<<endl;

	for ( int j = 0; j < n; j++ )
  		c[j] = 2.0;
 
	for ( int i = 0; i < m; i++ )
  		for ( int j = 0; j < n; j++ )
  	  		b[i*n+j] = i;
   
	for ( int j = 0; j < n; j++ )
  		cout << c[j] << endl; 
	
	cout << endl;
	
	for ( int i = 0; i < m; i++ )
  	{	
		for ( int j = 0; j < n; j++ )	  	
			cout << b[i*n+j];
		cout << endl;	
	}

	#pragma omp parallel default(none) \
     shared (m,n,a,b,c,cout,timeA,timeB) private(i,j)
   	{
     	#pragma omp master
        	timeA = omp_get_wtime();
     	#pragma omp parallel for
      
		for (i=0; i<m; i++)
      	{
         		a[i] = 0.0;
         		for (j=0; j<n; j++)
          		a[i] += b[i*n+j]*c[j];
         //cout<<"i: "<<i<<"thread: "<<omp_get_thread_num()<<endl;
      	}
      
		#pragma omp master
          timeB = omp_get_wtime();
	}

	cout<<"calculo finalizado"<<endl;

	for(i=0;i<m;i++)
     	cout<<"i:"<<i<<", "<<"a_i: "<<a[i]<<endl;
	
	cout<<"Tiempo de ejecución: "<<(timeB-timeA)<<endl;
}


