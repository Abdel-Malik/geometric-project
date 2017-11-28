#ifndef BSPLINE_H
#define BSPLINE_H
#include "curve2D.h"
#include <iostream>


class Bspline : public Curve2D {
 private:
 std::vector<float> A;
 public:
 Bspline(const QString &name) : Curve2D(name) {}
 Bspline(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
 
 std::vector<float>  boor(std::vector<std::vector<float> > polygon, float tcur, std::vector<float>  t, int ORDER) {
    unsigned int n;
    n=polygon[0].size();
    std::vector<std::vector<float> > MCoefx, MCoefy, Coef;
    std::vector<float> result;
    result.resize(2);
    MCoefx.resize(n);
    MCoefy.resize(n);
    Coef.clear();
    Coef.resize(4);
    for (unsigned int i=0; i<n; i++) {
		MCoefx[i].resize(n);
		MCoefy[i].resize(n);
		MCoefx[i][0]=polygon[0][i];
		MCoefy[i][0]=polygon[1][i];
		for (unsigned int j=1; j<n; j++) {
			MCoefx[i][j] = 0;
			MCoefy[i][j] = 0;
		}
	}
	for (int i=0; i<4; i++) {
		Coef[i].resize(n);
		for (unsigned int j=0; j<n; j++) Coef[i][j] = 0;
	}
	for (unsigned int k=1; k<n; k++) {
		for (unsigned int j=k; j<n; j++) {
			MCoefx[j][k]=((tcur-t[j])*MCoefx[j][k-1]+(t[j+ORDER-k]-tcur)*MCoefx[j-1][k-1])/(t[j+ORDER-k]-t[j]);
            MCoefy[j][k]=((tcur-t[j])*MCoefy[j][k-1]+(t[j+ORDER-k]-tcur)*MCoefy[j-1][k-1])/(t[j+ORDER-k]-t[j]);
		}
	}
    Coef[1]=MCoefx[n-1];
    Coef[3]=MCoefy[n-1];
    for (unsigned int i=0; i<n; i++) {Coef[0][i]=MCoefx[i][i];  Coef[2][i]=MCoefy[i][i];} 
    result[0]=Coef[0][n-1];
    result[1]=Coef[2][n-1];
    return result;
}



QPainterPath path(float frame) {
	QPainterPath p;
	if(nbPts()==0) 
		return p;
		
	unsigned int ORDER=4;	
	unsigned int M=200;	
	float tcur;
	std::vector<std::vector<float> > input,inputshort;
	std::vector<float>  t, tshort, result;
	Vector2f y = evalAnimPt(get(0),frame);
    p.moveTo(y[0],y[1]);
    if (nbPts()==2) {
		y = evalAnimPt(get(1),frame);
		p.lineTo(y[0],y[1]);
		}
	if (nbPts()==3) {
		y = evalAnimPt(get(2),frame);
		p.lineTo(y[0],y[1]);
		}
		
	if (nbPts()>3)  {
		input.resize(2);
		unsigned int n=nbPts()-1;
		input[0].resize(nbPts());
		input[1].resize(nbPts());
		t.resize(n+ORDER+1);
		for (unsigned int i=0;i<ORDER;i++) t[i]=0;
		for (unsigned int i=ORDER;i<n+1;i++) t[i]=(i-ORDER+1.0)/(n-ORDER+2);
		for (unsigned int i=n+1;i<n+ORDER+1;i++) t[i]=1;
		for(unsigned int i=0;i<nbPts();i++){
			input[0][i]=evalAnimPt(get(i),frame)[0];
			input[1][i]=evalAnimPt(get(i),frame)[1];
			}
		inputshort.resize(2);
		inputshort[0].resize(ORDER);
		inputshort[1].resize(ORDER);
		for(unsigned int i=1;i<M;i++) {
			tcur=(i+0.0)/M;
			unsigned int r=ORDER-1;
			for (unsigned int s=ORDER;s<n+1;s++) {if (tcur>t[s]) r=s; else break;}
			tshort.resize(n+2*ORDER-r);
			for (unsigned int s=0;s<ORDER;s++) {
				inputshort[0][s]=input[0][r-ORDER+1+s];
				inputshort[1][s]=input[1][r-ORDER+1+s];
			}	
			for (unsigned int s=0;s<n+2*ORDER-r;s++) tshort[s]=t[r-ORDER+1+s];
			result=boor(inputshort,tcur,tshort,ORDER);		
			p.lineTo(result[0],result[1]);
			}
	}
	
	
	return p;	
  }
  
  
};
	


class BsplineConstructor : public Curve2DConstructor {
 public:
  virtual ~BsplineConstructor()                     {}
  virtual const QString type() const                      { return "BsplineCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Bspline(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Bspline(c,name); }
};


#endif // BSPLINE_H



