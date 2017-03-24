#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;

int N = 1000000000;
double h,x,pi;
double sum=0.0;

int main(int argc, char const *argv[])
{
	h = 1.0/(double)N;
	int i;
	clock_t t1,t2;
	double inicio,fin;
	t1= clock();
	for(i=0;i<N;i++)
	{
		double x=(i+0.5)*h;
		sum += (4.0/(1.0+x*x));
	}
	pi = h*sum;
	t2 = clock();
	cout<<"El calculo de pi es: "<<pi<<endl;
	cout<<"N: "<<N<<endl;
	float diff ((float)t2-(float)t1);
    cout<<(diff/CLOCKS_PER_SEC)<<endl;

	return 0;
}