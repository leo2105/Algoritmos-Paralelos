#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

using namespace std;
const int G=1;
const int N=1024;

float pos[3][N];
float vel[3][N];
float m[N];
float a[3][N];
float F[3][N];

float dt = 0.001;
float tf = 1.0;

int size,rank;

/*
struct CuerpoCeleste{
	double pos[3];
	double vel[3];
	double F[3];
	double a[3];
	double m;
};*/
void force(float t);
void init();

int main(int argc,char *argv[])
{
	srand(time(NULL));
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	double ta,tb;
	init();
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	ta = MPI_Wtime();
	for(float t=0.0;t<tf;t+=dt)
	{
		force(t);
	}
	tb = MPI_Wtime();
	if(rank==0)
		cout<<endl<<"El tiempo de ejecucion es: "<<(tb-ta)<<endl;
}

void force(float t)
{
	
	for(int i=0;i<N;i++)
	{
		float my_r_x = pos[0][i];
		float my_r_y = pos[1][i];
		float my_r_z = pos[2][i];

		for(int j=0;j<3;j++)
		{
			F[j][i] = 0;
		}

		float aux_a[3];
		float d[3];

		

		for(int j=rank;j<N;j+=size)
		{
			if(j!=i)
			{
				d[0] = pos[0][j] - my_r_x;				
				aux_a[0]+= (G * m[j]) / (d[0]*d[0]);
				d[1] = pos[1][j] - my_r_y;				
				aux_a[1] += (G * m[j]) / (d[1]*d[1]);
				d[2]= pos[2][j] - my_r_z;				
				aux_a[2] += (G * m[j]) / (d[2]*d[2]);
				// Fi = mi * a
				//F[0][j] += (m[i] * a[0][j]);
				//F[1][j] += (m[i] * a[1][j]);
				//F[2][j] += (m[i] * a[0][j]);

			}
			
		}

		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(&aux_a[0],&a[0][i],3,MPI_FLOAT,MPI_SUM,MPI_COMM_WORLD);
		

	    vel[0][i]+=(a[0][i]*t);
		pos[0][i]+=(vel[0][i]*t);

		vel[1][i]+=(a[1][i]*t);
		pos[1][i]+=(vel[1][i]*t);

		vel[2][i]+=(a[2][i]*t);
		pos[2][i]+=(vel[2][i]*t);
		

		for(int j=0;j<3;j++)
		{
			a[j][i] = 0;
		}

	}
	
}

void init()
{

	for(int i=0;i<N;i++)
	{

		for(int j=0;j<3;j++)
		{
			pos[j][i] = ((float)rand()/(RAND_MAX));
			vel[j][i] = ((float)rand()/(RAND_MAX));
			a[j][i] = 0.0;
			F[j][i] = 0.0;
		}	
		m[i] = ((float)rand()/(RAND_MAX));
	}

}