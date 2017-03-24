#include <iostream>
#define oo 1<<30
#define N 10

using namespace std;

void Imprimir(int A[])
{
	for(int i=0;i<N;i++)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
}

void Merge(int A[],int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
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
void MergeSort(int A[],int p, int r)
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
    int p=0;
    int r=N-1;
    int A[N] = {26,57,60,82,7,24,12,67,64,156};

    MergeSort(A,p,r);

	Imprimir(A);

    return 0;
}
