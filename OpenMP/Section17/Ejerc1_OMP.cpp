#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

static long MULTIPLIER = 1366;
static long ADDEND = 150889;
static long PMOD = 714025;

double random_low,random_hi;
long random_last;

double drandom()
{
	long random_next;
	double ret_val;

	// compute an integer number from zero to mod
	random_next = (MULTIPLIER * random_last + ADDEND) % PMOD;
	random_last = random_next;

	//shift into preset range
	ret_val = ((double)random_next/(double)PMOD) * (random_hi - random_low) + random_low;	
	return ret_val;
}

void seed(double low_in,double hi_in)
{
	if(low_in < hi_in)
	{
		random_low = low_in;
		random_hi = hi_in;
	}
	else
	{
		random_low = hi_in;
		random_hi = low_in;
	}

	random_last = PMOD/ADDEND;
}
int main()
{
	long i; long Ncirc = 0;
	double pi,x,y,test,pi1;
	double ini,fin;
	double r = 1.0;
	time_t  t;
	seed(0.0,1.0);
	omp_set_num_threads(4);

	long num_trials=100000000;

	ini = omp_get_wtime();
	#pragma omp parallel shared(Ncirc,r,num_trials) private(x,y,i)
	#pragma omp for reduction(+:Ncirc) nowait
	for(i=0;i<num_trials;i++)
	{
		x = drandom();
		y = drandom();
		
		if(x*x + y*y <= r*r)
			Ncirc=Ncirc+1;
	}	

	pi = 4.0 * ((double)Ncirc/(double)num_trials);

	fin = omp_get_wtime();
	
	cout<<endl<<num_trials<<" trials, pi is "<<pi<<endl;
	cout<<"Tiempo es: "<<(fin-ini)<<endl<<endl;
	
	return 0;
}

// OpenMP

//N			  Pi		  Tiempo (seg)

//100000	  3.11973	  0.01388
//1000000	  3.12354	  0.0615
//10000000	  3.12655	  0.56692
//100000000	  3.12883	  5.56635


// Tenemos que para un valor grande N, el calculo de Pi no es muy preciso y 
// además el tiempo de ejecución es mayor