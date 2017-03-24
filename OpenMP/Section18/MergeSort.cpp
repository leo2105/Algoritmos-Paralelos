#include <iostream>
#include <omp.h>
#define N 8
using namespace std;

int A[N];
void Merge(int p,int q,int r)
{
    n1=q-p+1;
    n2=r-q;
    int L[n1+1];
    int R[n2+1];
    for(int m=0;m<n1;m++)
        L[m]=A[p+m];
    for(int m=0;m<n2;m++)
        R[m]=A[q+m+1];
    L[n1]=oo;
    R[n2]=oo;
    int i,j;
    i=0;
    j=0;
    for(int k=p;k<=r;k++)
    {
        if(L[i]<=R[j])
        {
            A[k]=L[i];
            i++;
        }
        else
        {
            A[k]=R[j];
            j++;
        }
    }
}

void MergeSort(int p, int r)
{
    int q;
    if(p<r)
    {
        q=(p+r)/2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}

int main()
{
	for(int i=0;i<N;i++)
		cin>>A[i];

	
	return 0;
}