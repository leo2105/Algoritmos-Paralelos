#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;
const int G=1;
const int N=4;
class CuerpoCeleste{
	double pos[3];
	double vel[3];
	double F[3];
	double a[3];
	double m;
public:
	CuerpoCeleste(){
		for(int i=0;i<3;i++){
			pos[i]=((double)rand()/(RAND_MAX));// pos entre 0 y 1
			vel[i]=((double)rand()/(RAND_MAX));// vel entre 0 y 1
			F[i]=a[i]=0.0;
		}
		m=((double)rand()/(RAND_MAX));// m entre 0 y 1
		
	}
	CuerpoCeleste setF(double f){
		F[0]=F[1]=F[2]=f;
		return *this;
	}
	CuerpoCeleste seta(double f){
		a[0]=a[1]=a[2]=f;
		return *this;
	}	
	CuerpoCeleste setPosyVel(double t){
		for(int i=0;i<3;i++){
			vel[i]+=(a[i]*t);
			pos[i]+=(vel[i]*t);
		}
		return *this;
	}
	void getPos(){
		cout<<"("<<a[0]<<", "<<a[1]<<", "<<a[2]<<")"<<endl;
	}
	void imprimir(){
		cout << setprecision(5);
		cout<<"\tpos= ("<<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<")"<<endl;
		cout<<"\tvel= ("<<vel[0]<<", "<<vel[1]<<", "<<vel[2]<<")"<<endl;
		cout<<"\tF= ("<<F[0]<<", "<<F[1]<<", "<<F[2]<<")"<<endl;
		//cout<<"\ta= ("<<a[0]<<", "<<a[1]<<", "<<a[2]<<")"<<endl;
		cout<<"\tmasa= "<<m<<endl;
	}
	void imprimir(int i){
		cout<<"Cuerpo "<<(i+1)<<endl;
		imprimir();
	}
	CuerpoCeleste calculoFuerza(CuerpoCeleste b){
		double f[3];
		double r[3];
		double r2=0;
		for(int i=0;i<3;i++){
			r[i]=b.pos[i]-pos[i];
			//r2+=(r[i]*r[i]);
		}
		//r2=r2*sqrt(r2);
		for(int i=0;i<3;i++){
			a[i] += (G*b.m) / (r[i]*r[i]);
			F[i] += (G*m*b.m) / (r[i]*r[i]);
		}
		return *this;
	}
};

int main(){
	
	int size,rank;
	

	CuerpoCeleste Universo[N];
	

	for(double t=0.0;t<0.005;t+=0.001){
		for(int i=0;i<N;i++){
			Universo[i].setF(0);
			for(int j=0;j<N;j++){
				if(i!=j){
					Universo[i].calculoFuerza(Universo[j]);
				}
			}
			Universo[i].setPosyVel(t);
			cout<<"t="<<t<<endl;
			cout<<"a["<<i+1<<"]= ";
			Universo[i].getPos();
			//Universo[i].imprimir(i);
			Universo[i].seta(0);
		}
	}

	return 0;
}
