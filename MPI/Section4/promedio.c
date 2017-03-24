#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main()
{
	srand(time(NULL));
	int N=100000000;
int i;
	clock_t tA,tB;
	int *A = (int*)malloc(sizeof(int) * N);
		//for(i=0;i<N;i++)
		//	A[i] = rand()%200+1;

	long S=0;
	printf("qwe");
	tA = clock();	
	for(i=0;i<N;i++)
		S+=A[i];
	tB =clock();
	printf("qwe");
	printf("Tiempo transcurrido: %f", (float)((tB-tA) / CLOCKS_PER_SEC)); 


	
		
}

