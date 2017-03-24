#include <iostream>
#include <ctime>
#include <cstdlib>
#ifdef _OPENMP 
  #include <omp.h>
#endif

#define NMAX 800
#define MMAX 800
using namespace std;

#ifdef _OPENMP
  #define NUM_THREADS 16
#endif

int flops;

void init(int a[][NMAX]){
	int i,j;
  for(j=0;j<NMAX;j++)
    for(i=0;i<MMAX;i++)
      a[j][i]=rand()%90+1;
}



void axb(int a[][NMAX],int b[][NMAX],int c[][NMAX]){
	int i,j,k;
	
	#pragma omp for private(i,j,k) 
		for(i=0;i<NMAX;i++){
			for(j=0;j<NMAX;j++){
				c[i][j] = 0;
				//flops+=2;
				for(k = 0;k<NMAX;k++)
		  			c[i][j] += a[i][k]*b[j][k];
		  			//flops+=3;
		  			
		        }
			//cout << endl;
			//flops++;
  		}
}


int main(int argc,char** argv){

  int n,m,i,j;

  int a[NMAX][MMAX],b[MMAX][NMAX],c[NMAX][MMAX];
  
  flops = 0;
  double start , end;
  
  srand(time(NULL));
    
  init(a); init(b); 
  
#ifdef _OPENMP
  omp_set_num_threads(NUM_THREADS);
#endif

start = omp_get_wtime();
#pragma omp parallel shared(a,b,c)
	axb(a,b,c); 
	
end = omp_get_wtime();

cout << "Elapsed time is : " << end - start << endl;
//cout << "Number of flops : " << flops << endl;
	return 0;

}


