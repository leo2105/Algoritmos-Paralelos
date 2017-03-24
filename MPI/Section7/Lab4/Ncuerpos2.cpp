#include    <iostream>
#include    <cstdlib>
#include    <ctime>
#include    <sys/timeb.h>
#include <stdio.h>
using namespace std;
const int G=1;
const int N=1024;

float pos[3][N];
float vel[3][N];
float m[N];
float a[3][N];
float F[3][N];

float dt = 0.001;
float tf = 1.000;
/*
struct CuerpoCeleste{
	double pos[3];
	double vel[3];
	double F[3];
	double a[3];
	double m;
};*/

void force(float t);
void Init();

int main(int argc,char *argv[])
{
	clock_t startC, finishC;
    struct timeb startT, finishT;
    unsigned int elements=100000;
    unsigned int operations=10000;
    unsigned int seconds, milliseconds;
 
    startC = clock();
    ftime(&startT);

	Init();

	
	for(float t=0.0;t<tf;t+=dt)
	{
		force(t);
	}
	
	finishC = clock();
    ftime(&finishT);
    seconds = finishT.time - startT.time - 1;
    milliseconds = (1000 - startT.millitm) + finishT.millitm;
 	cout << "Para 1000 cuerpos: "<<endl;
    //cout << "Time (clock): "    << (finishC - startC)/CLOCKS_PER_SEC << endl;
    //cout << "Time (difftime): " << difftime(finishC, startC) << " segundos" <<endl;
    cout << "Time (ftime): " << (milliseconds + seconds * 1000) << " milisegundos"<<endl;

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

		for(int j=0;j<N;j++)
		{
			if(j!=i)
			{
				float d0 = pos[0][j] - my_r_x;
				float d1 = pos[1][j] - my_r_y;
				float d2 = pos[2][j] - my_r_z;
				
				
				a[0][i] += (G * m[j]) / (d0*d0);
				a[1][i] += (G * m[j]) / (d1*d1);
				a[2][i] += (G * m[j]) / (d2*d2);

				// Fi = mi * a
				F[0][i] += (m[i] * a[0][i]);
				F[1][i] += (m[i] * a[1][i]);
				F[2][i] += (m[i] * a[2][i]);

			}
		}

		for(int j=0;j<3;j++)
		{
			vel[j][i]+=(a[j][i]*t);
			pos[j][i]+=(vel[j][i]*t);
		}

		//cout<<"t="<<t<<endl;
		//	cout<<"m["<<i+1<<"] = " <<m[i]<<" y a["<<i+1<<"]= ";

			/*for(int j=0;j<3;j++)
			{
				cout<<a[j][i]<<" ";

			}
			cout<<endl;
			*/
		

		for(int j=0;j<3;j++)
		{
			a[j][i] = 0;
		}


		
		
	}
}

void Init()
{

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<3;j++)
		{
			pos[j][i] = ((float)rand()/(RAND_MAX));
			vel[j][i] = ((float)rand()/(RAND_MAX));
			
		}	
		
		m[i] = ((float)rand()/(RAND_MAX));
	}

}