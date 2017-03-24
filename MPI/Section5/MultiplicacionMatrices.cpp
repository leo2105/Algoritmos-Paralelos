#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
	int a,b,c;
	cout<<"Ingresar a (filas de A), c (columnas de A y filas de B) y b (columnas de B): ";

	cin>>a>>c>>b;

	vector<vector<int> > A;
	vector<vector<int> > B;	
	vector<vector<int> > C;

	C.resize(a);
	for(int i=0;i<a;i++)
		C[i].resize(b);

	
	A.resize(a);
	for(int i=0;i<a;i++)
		A[i].resize(c);

	B.resize(c);
	for(int i=0;i<c;i++)
		B[i].resize(b);
	
	cout<<endl<<"Ingresar matriz A: "<<endl;
	for(int i=0;i<a;i++)
		for(int j=0;j<c;j++)
			cin>>A[i][j];

	cout<<endl<<"Ingresar matriz B: "<<endl;
	for(int i=0;i<c;i++)
		for(int j=0;j<b;j++)
			cin>>B[i][j];

//...................................

	for(int i=0;i<a;i++)
		for(int j=0;j<b;j++)
			C[i][j]=0;

	for(int i=0;i<a;i++)
		for(int j=0;j<b;j++)
			for(int k=0;k<c;k++)
				C[i][j] += A[i][k]*B[k][j];

	cout<<endl<<"A x B :"<<endl;
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++)
			cout<<C[i][j]<<" ";
		cout<<endl;
	}

	return 0;
}