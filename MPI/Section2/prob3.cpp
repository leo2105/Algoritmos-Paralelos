#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int N=32;
int main(){
    int A[N]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    vector<int> S;
    S.resize(N);
    
    S[0]=A[0];

    for(int i=1;i<N;i++)
    {
        S[i] = S[i-1] + A[i];
    }

    cout<<S[N-1];
}
//---------
/*
    int N=8;
    int p=N; // cantidad de procesos
    int A[N]={1,2,3,4,5,6,7,8};
    vector<int> B;
    B.resize(N);
    int S;
    int i;

    for i=0 to log(N) do
    {    
        
        int j;
        if(i%2==0)
        {
            for j=0 to pow(2,i)-1 par do
            {
                B[j] := A[j];
            }
            
            j = pow(2,i);
            k = 0;

            for j<N par do
            {
                B[j] := A[k] + A[j];
                j++;
                k++;
            }
            
        }
        else
        {
            for j=0 to pow(2,i)-1 par do
            {
                A[j] := B[j];
            }
            
            j = pow(2,i);
            k = 0;

            for j<N par do
            {
                A[j] := B[k] + B[j];
                j++;
                k++;
            }
        }
    }

    if(i%2!=0)
    {
        S=B[N-1];
    }
    else
    {    
        S=A[N-1];
    }

    //  A : 1   2   3   4   5   6   7   8
    //  B : 1   3   5   7   9   11  13  15
    //  A : 1   3   6   10  14  18  22  26
    //  B : 1   3   6   10  15  21  28  36

    // Las lineas 36 - 48 paraleliza el programa con todos los procesadores posibles.  A->B
    // Las lineas 54 - 66 paraleliza el programa con todos los procesadores posibles.  B->A

    // si p = 1   : T(n) = O(n)      y S(n) = O(1) => W(n) = O(n)
    // si p = n   : T(n) = O(log(n)) y S(n) = O(n) => W(n) = O(n*log(n))

    // Conclusion: El algoritmo en paralelo es más veloz en n/log(n) 
    //             pero el secuencial es mas eficiente.

*/



