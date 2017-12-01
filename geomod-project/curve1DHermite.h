#ifndef CURVE_1D_HERMITE_H
#define CURVE_1D_HERMITE_H

#include "curve1D.h"
#include "PolyN.h"

using namespace std;

class Curve1DHermite : public Curve1D {
 public:
 Curve1DHermite(const QString &name) : Curve1D(name) {initialiseHermitePolynomes();}
 Curve1DHermite(Curve1D *curve,const QString &name) : Curve1D(curve,name) {initialiseHermitePolynomes();}

  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;

    // empty test
    if(empty())
      return p;

	p.moveTo(xmin,evalAt(xmin));
   	for(unsigned int k=xmin;k<xmax;k++){
        p.lineTo(k,evalAt(k));
    	}

    return p;

    }

  float evalAt(float t) {
    float T=0.;
    if(empty()) return 0.0f;
    if(t<=_points[0][0]) return _points[0][1];
    if (t>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];
    unsigned int i = 0;
    for(i=0;_points[i][0]<t;i++);
    i--;
    float tNorm = (t-_points[i][0])/(_points[i+1][0]-_points[i][0]);
    T = Hermite(tNorm,i);
    return T;
    }

   private:
 PolyN* HermitePolynomes;

  void initialiseHermitePolynomes(){
    float coef0[4] = {1,0,-3,2};
    float coef1[4] = {0,1,-2,1};
    float coef2[4] = {0,0,3,-2};
    float coef3[4] = {0,0,-1,1};
    HermitePolynomes = new PolyN[4];
    HermitePolynomes[0] = PolyN(coef0,4);
    HermitePolynomes[1] = PolyN(coef1,4);
    HermitePolynomes[2] = PolyN(coef2,4);
    HermitePolynomes[3] = PolyN(coef3,4);
  }

  vector<float> derive(vector<Vector2f> _points){
	unsigned int s=nbPts() ; //_points.size()
  	vector<float> d(s);
	d[0]=(_points[1][1]-_points[0][1])/(_points[1][0]-_points[0][0]);
	d[s-1]=(_points[s-1][1]-_points[s-2][1])/(_points[s-1][0]-_points[s-2][0]);
	for(unsigned int i=1;i<s-1;i++){
		d[i]=(_points[i+1][1]-_points[i-1][1])/(_points[i+1][0]-_points[i-1][0]);
  	}
  return d;
  }



float Hermite(float t,unsigned int j){
	float T = HermitePolynomes[0].val(t)*_points[j][1]+HermitePolynomes[1].val(t)*derive(_points)[j]+HermitePolynomes[2].val(t)*_points[j+1][1]+HermitePolynomes[3].val(t)*derive(_points)[j+1];
return T;
}

};


class Curve1DHermiteConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DHermiteConstructor()                     {}
  virtual const QString type() const                      { return "HermiteCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DHermite(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DHermite(c,name); }
};

#endif // CURVE_1D_HERMITE_H
