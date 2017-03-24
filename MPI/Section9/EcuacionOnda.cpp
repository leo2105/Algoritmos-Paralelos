#include <stdio.h>
#include <math.h>
#define MAXPOINTS 1000
#define MAXSTEPS 1000
#define MINPOINTS 20
#define PI 3.14159265

//using namespace::std;

int tpoints;
int nsteps;

double values[MAXPOINTS+2];	// valores en t
double oldval[MAXPOINTS+2];	// valores en t-dt
double newval[MAXPOINTS+2];	// valotes en t+dt

void init_line();
void update();
void printfinal1( int );
void printfinal2( int );
void printfinal3( int );


int main( int argc, char *argv[] )
{
	printf("Ingrese tpoints: ");
	scanf("%d",&tpoints);

	printf("Ingrese nsteps: ");
	scanf("%d",&nsteps);

	init_line();
	update();
	//printfinal();cout << "tu vieja" << endl;
}

void init_line()
{
	int i, j;	
	double x, fac, k, tmp;
	// Calcular valores iniciales basados en la curva seno
	fac = 3.0 * PI;
	k = 0.002;
	tmp = tpoints - 1;

	for( j = 1; j <= tpoints; j++ )
	{
		x = k/tmp;
		values[j] = sin(fac * x);
		k += 1.0;
	} 
	//Inicializar valores antiguos

	for( i = 1; i <= tpoints; i++ )
		oldval[i] = values[i];

}


void do_math(int i)
{
	double dtime,c,dx,tau,sqtau;	

	dtime = 0.3;
	c = 1.0;
	dx = 1.0;
	tau = ( c*dtime/dx );
	sqtau = tau * tau;

	newval[i] = ( 2.0 * values[i] ) - oldval[i] + ( sqtau * ( values[i-1] - ( 2.0 * values[i] ) + values[i+1] ));
	//newval[i] = values[i] + (dtime * 0.002 /dx * dx ) * (values[i-1] - 2.0 * values[i] + values[i+1]);
	//newval[i] = 2.0 * values[i] - oldval[i] - (values[i+1] - 2.0 * values[i] + values[i-1])*(c*c*dtime*dtime)/(dx*dx);
}

void update()
{
	int i, j;

	for( i = 1; i <= nsteps; i++ )
	{
		for( j = 1; j <= tpoints; j++ )
		{
			if( j == 1 || j == tpoints )
				newval[j] = 0.0;
			else 
				do_math(j);
		}

		for( j = 1;j <= tpoints; j++ )
		{
			oldval[j] = values[j];
			values[j] = newval[j];
		}
		
		if( i == 1 )
			printfinal1(i);
		if( i==200 )
			printfinal2(i);
		if( i==500 )
			printfinal3(i);
	}
}

void printfinal1( int x )
{
	int i; 
  	FILE *f;
  	f=fopen("ondaPoints1.txt","w");
  	for( i = 1; i <= tpoints; i++ ){
    	printf("%.5lf\n",values[i]);
    	fprintf(f,"%lf\n",values[i]);
  	}
  	fclose(f);
}

void printfinal2( int x )
{
	int i; 
  	FILE *f;
  	f=fopen("ondaPoints2.txt","w");
  	for( i = 1; i<= tpoints; i++ ){
    	printf("%.5lf\n",values[i]);
    	fprintf(f,"%lf\n",values[i]);
  	}
  	fclose(f);
}
void printfinal3(int x)
{
	int i; 
  	FILE *f;
  	f=fopen("ondaPoints3.txt","w");
  	for( i = 1; i <= tpoints; i++ ){
    	printf("%.5lf\n",values[i]);
    	fprintf(f,"%lf\n",values[i]);
  	}
  	fclose(f);
}
