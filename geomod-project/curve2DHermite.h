#ifndef CURVE_2D_HERMITE_H
#define CURVE_2D_HERMITE_H

#include "curve2D.h"
#include "PolyN.h"

using namespace std;

class Curve2DHermite : public Curve2D {
 public:
 Curve2DHermite(const QString &name) : Curve2D(name) {
    initialiseHermitePolynomes();
 }
 Curve2DHermite(Curve2D *curve,const QString &name) : Curve2D(curve,name) {
    initialiseHermitePolynomes();
 }
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    vector<Vector2f> pts1;

    for(unsigned int i=0;i<nbPts();++i) {
      pts1.push_back(evalAnimPt(get(i),frame));
    }
    vector<Vector2f> pts2=Hermite(pts1);
    p.moveTo(pts2[0][0],pts2[0][1]);
    for(unsigned int j=0;j<pts2.size();j++){
      p.lineTo(pts2[j][0],pts2[j][1]);
    }
    return p;
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

  vector<float> derive(vector<Vector2f> pts){
	int s=pts.size();
  	vector<float> d(s);
	d[0]=(pts[1][1]-pts[0][1])/(pts[1][0]-pts[0][0]);
	d[s-1]=(pts[s-1][1]-pts[s-2][1])/(pts[s-1][0]-pts[s-2][0]);
	for(int i=1;i<s-1;i++) {
		d[i]=(pts[i+1][1]-pts[i-1][1])/(pts[i+1][0]-pts[i-1][0]);
  	}
  return d;
  }

  vector<Vector2f> Hermite(vector<Vector2f> pts){
    vector<Vector2f> connard;
    int s=pts.size();
    cout << s << endl;
    float pas= 1.0/50;
    for(int j=0;j<s;j++) {
      for(int i=0;i<50;i++) {
	float T=HermitePolynomes[0].val(i*pas)*pts[j][1]+HermitePolynomes[1].val(i*pas)*derive(pts)[j]+HermitePolynomes[2].val(i*pas)*pts[j+1][1]+HermitePolynomes[3].val(i*pas)*derive(pts)[j+1];
	float reso=T*(pts[j+1][1]-pts[j][1])+pts[j][1];
	float resa=i*pas*(pts[j+1][0]-pts[j][0])+pts[j][0];
	Vector2f salope(resa,reso);
	connard.push_back(salope);
	cout << resa << " "<< reso << endl;
      }
    }
    return connard;
  }
};


class Curve2DHermiteConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DHermiteConstructor()                     {}
  virtual const QString type() const                      { return "HermiteCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DHermite(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DHermite(c,name); }
};


#endif // CURVE_2D_HERMITE_H
