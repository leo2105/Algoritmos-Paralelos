#include <stdlib.h>
#include <iostream>
#include <omp.h>
using namespace std;
#define NMAX 1000
#define MMAX 1000

int main(int argc, char *argv[])
{
	double a[NMAX],b[MMAX*NMAX],c[NMAX];
	int i, j, m, n;
	double timeA,timeB;

	cout << "Ingresar m: " << endl;
	cin >> m;
	cout << "Ingresar n: " << endl;
	cin >> n;
	cout<<endl;

	cout<<"Initializing matrix B and vector c"<<endl;
 
	for (j=0; j<n; j++)
  	   c[j] = 2.0;
   	
	for (i=0; i<m; i++)
    		for (j=0; j<n; j++)
     		b[i*n+j] = i;

	for (i=0; i<m; i++)
     {
  	   a[i] = 0.0;
        for (j=0; j<n; j++)
		   a[i] += b[i*n+j]*c[j];
      }
    
	cout<<"calculo finalizado"<<endl;
	
	for(i=0;i<m;i++)
 	    cout<<"i:"<<i<<", "<<"a_i: "<<a[i]<<endl;

}


