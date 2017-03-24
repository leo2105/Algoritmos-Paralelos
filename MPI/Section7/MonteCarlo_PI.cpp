#include <iostream>
#include <ctime>
#include <cstdlib>
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
	double r = 1.0; // radio del circulo. Lado del cuadrado es 2*r
	time_t  t;
	seed(0.0,1.0);
	//srand(time(&t));
	long num_trials=100000000;
	
	for(i=0;i<num_trials;i++)
	{
		//x = (double)rand() / RAND_MAX;
		//y = (double)rand / RAND_MAX;
		//cout<<x<<endl;
		//cout<<y<<endl;
		x = drandom();
		y = drandom();
		if(x*x + y*y <= r*r)
			Ncirc++;
	}	

	pi = 4.0 * ((double)Ncirc/(double)num_trials);

	Ncirc = 0;

	for(i=0;i<num_trials;i++)
	{
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		//cout<<x<<endl;
		//cout<<y<<endl;
		//x = drandom();
		//y = drandom();
		if(x*x + y*y <= r*r)
			Ncirc++;
	}	

	pi1 = 4.0 * ((double)Ncirc/(double)num_trials);

	cout<<endl<<num_trials<<" trials, pi is "<<pi<<endl;
	cout<<endl<<num_trials<<" trials, pi1 is "<<pi1<<endl;
	return 0;
}