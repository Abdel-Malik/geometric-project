//test
#ifndef LAGRANGE_H
#define LAGRANGE_H
#include "curve2D.h"
#include <iostream>


class Lagrange : public Curve2D {
 private:
 std::vector<float> A;
 public:
 Lagrange(const QString &name) : Curve2D(name) {}
 Lagrange(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}



void coef_newton(float frame){
  std::vector<std::vector<float> > Atemp;
  Atemp.resize(nbPts());
  A.resize(nbPts());
  Vector2f pt, x1, x2;
  for (unsigned int i=0; i<nbPts(); ++i) {
	Atemp[i].resize(nbPts());
  	pt = evalAnimPt(get(i),frame);
  	Atemp[i][0]=pt[1];
  }
  for (unsigned int i=1; i<nbPts(); ++i) {
  	for (unsigned int j=i;j<nbPts();++j) {
		x1=evalAnimPt(get(j-i),frame);
		x2=evalAnimPt(get(j),frame);
		Atemp[j][i]=(Atemp[j][i-1]-Atemp[j-1][i-1])/(x2[0]-x1[0]);

   		}
	}
   for (unsigned int i=0; i<nbPts(); ++i) {A[i]=Atemp[i][i];}
}



QPainterPath path(float frame) {
	QPainterPath p;
	if(nbPts()==0)
		return p;

	Vector2f x;
    Vector2f y = evalAnimPt(get(0),frame);
    p.moveTo(y[0],y[1]);

    float min = 10000;
	float max = 0;
	unsigned int M = 500;
	float t;
	coef_newton(frame);
	if (nbPts()!=1)  {
		for(unsigned int i=0;i<nbPts();i++){
			if(min > evalAnimPt(get(i),frame)[0]){
				min = evalAnimPt(get(i),frame)[0];
			}
			if(max < evalAnimPt(get(i),frame)[0]){
				max = evalAnimPt(get(i),frame)[0];
			}
		}
		y[0] = min;
		for(unsigned int i=1;i<M+1;i++) {
			x=evalAnimPt(get(nbPts()-2),frame);
			y[1] = A[nbPts()-1]*(y[0]-x[0]);
			for(unsigned int j=nbPts()-2;j>0;--j) {
				x=evalAnimPt(get(j-1),frame);
				y[1] = (y[1]+A[j])*(y[0]-x[0]);
			}
			y[1] = A[0]+y[1];
			p.lineTo(y[0],y[1]);
			y[0] = min+i*((max-min)/M);
		}
	}
	return p;
  }



};



class LagrangeConstructor : public Curve2DConstructor {
 public:
  virtual ~LagrangeConstructor()                     {}
  virtual const QString type() const                      { return "LagrangeCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Lagrange(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Lagrange(c,name); }
};


#endif // LAGRANGE_H



