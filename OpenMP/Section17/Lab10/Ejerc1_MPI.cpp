#include <iostream>
#include <ctime>
#include <cstdlib>
#include <mpi.h>

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

	random_next = (MULTIPLIER * random_last + ADDEND) % PMOD;
	random_last = random_next;

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
int main(int argc,char *argv[])
{
	long i; long Ncirc;
	int myid,numproc;

	long suma=0;
	double pi,x,y,test,pi1;
	double ini,fin;
	long num_trials=100000000;
	double r = 1.0;
	time_t  t;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	ini = MPI_Wtime();
	MPI_Bcast(&num_trials,1,MPI_LONG,0,MPI_COMM_WORLD);
	seed(0.0,1.0);	
	
	Ncirc=0;
	for(i=myid;i<num_trials;i+=(numproc))
	{
		x = drandom();
		y = drandom();
		if(x*x + y*y <= r*r)
			Ncirc++;
	}	

	MPI_Reduce(&Ncirc,&suma,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(myid==0)
	{
		fin = MPI_Wtime();
		pi = 4.0 * ((double)suma/(double)num_trials);
		cout<<endl<<num_trials<<" trials, pi is "<<pi<<endl;
		cout<<(fin-ini)<<endl<<endl;
	}

	MPI_Finalize();
	return 0;
}

// MPI

//N			  Pi		  Tiempo (seg)

//100000	  3.14352	  0.00095
//1000000	  3.14109	  0.01707
//10000000	  3.14158	  0.15949
//100000000	  3.14159	  1.04441


// Tenemos que para un valor grande N, el calculo de Pi es muy preciso y 
// además el tiempo de ejecución es menor.
