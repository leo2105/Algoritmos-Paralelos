#include <iostream>
using namespace std;
int N=10;
int main(){
    int p; // cantidad de procesos
    int A[N]={0,1,2,3,4,5,6,7,8,9};
    int B[N]={0,1,2,3,4,5,6,7,8,9};
    int C[N];
    // T(n) = O(n) ya que p=1
    for(int i=0;i<N ;i++){
        C[i]=A[i]+B[i];
    }

    for(int i=0;i<N ;i++){
        cout<<C[i];
    }
}

/*        
        
    for i:=0 to p-1 pardo 
        for j:=i*(N/p) to (i+1)*(N/p)-1 do
            C[j]:=A[j]+B[j];
        endfor
    end

    // La linea 21 hace que cada procesador realice un for de la linea 22.
    // La linea 22 hace la suma de los 2 vectores y los almacena en C.

    // Si p =  N, entonces P(n) = O(n) y T(n) = O(1) => W(n) = O(n)
    // Si p =  1, entonces P(n) = O(1) y T(n) = O(n) => W(n) = O(n)

    // Conclusion: Los algoritmos son de igual eficiencia
    //             pero cuando p = N, este es más rapido.

*/
