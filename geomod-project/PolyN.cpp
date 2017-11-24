#include <assert.h>
#include <sstream>
#include <string>
#include "PolyN.h"

PolyN::PolyN(){
    this->n=0;
    this->coefs=NULL;
    PolyNDeriv = NULL;
}


PolyN::PolyN(float *coefs, int n){
    assert(n>0 && coefs[n-1] != 0);
    this->n=n;
    this->coefs=new float[n];
    for(int i=0;i<n;i++){
        this->coefs[i]=coefs[i];
    }
    PolyNDeriv = NULL;
}

PolyN::PolyN(int n){
    this->n=n;
    this->coefs=new float[n];
    for(int i=0;i<n;i++){
        this->coefs[i]=0;
    }
    PolyNDeriv = NULL;
}

PolyN::~PolyN(){
    delete(this->coefs);
}

PolyN* PolyN::derivative(){
    if(PolyNDeriv == NULL){
        int N;
        float* coefs2;
        if(n>1){
            N=n-1;
            coefs2 = new float[n-1];
            for(int i=0; i<n-1;i++){
                coefs2[i]= (i+1)*coefs[i+1];
            }
        }else{
            N=1;
            coefs2 = new float[1];
            coefs2[0]=0;
        }
        PolyN* pol=new PolyN(coefs2,N);
        delete(coefs2);
        PolyNDeriv = pol;
    }
    return PolyNDeriv;
}

float PolyN::val(float f){
    float f2=1;
    float resultat=0;
    for(int i=0;i<n;i++){
	resultat+=f2*coefs[i];
	f2=f2*f;
    }
    return resultat;
}

void PolyN::editCoef(int pos, float f){
    if(pos>=0 && pos < this->n)
  	   this->coefs[pos] = f;
}

std::ostream &operator<<(std::ostream &o, const PolyN &pol){
    for(int i=0;i<pol.n;i++){
            o << "+" << pol.coefs[i] << "x^"<< i;
    }
    return o;
}

