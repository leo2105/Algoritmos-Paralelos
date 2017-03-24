#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;


int suma(vector<int> A,int N,int i)
{	
	int S=0;
	for(i=0;i<N;i++)
		S+=A[i];
	return S;
}

vector<int> ini(int N,int i)
{
	vector<int> B;
	for(i=0;i<N;i++)
		B.push_back(i+1); 
	return B;
}

int main()
{

omp_set_num_threads(3);

int N=10,i,sum=1; // Si imprime 1 esta mal
bool flag=true;
double t2,t1;

vector<int> A;

	#pragma omp parallel shared(A,t1,t2,N,sum,cout,flag)
	{
		#pragma omp master
			t1 = omp_get_wtime();
   		#pragma omp sections
   		{
      		#pragma omp section
   				if(flag==true)
   				{
        			A=ini(N,i);
        			flag = false;
     			}
      		#pragma omp section
       		{
       			cout<<"hilo es: "<<omp_get_thread_num()<<endl;
        		if(flag==false)
        			sum=suma(A,N,i);
   			}
   		} 
    	
    	#pragma omp master
			t2 = omp_get_wtime();
		#pragma omp master
			cout<<"La suma es: "<<sum<<" y el tiempo es: "<<(t2-t1)<<" segundos."<<endl;
	}
	
	return 0;
}


// LA LINEA 49 LE DA UN PEQUEÑO LAPSO DE TIEMPO PARA QUE SE ACTUALICE EL VALOR DE 
// FLAG.