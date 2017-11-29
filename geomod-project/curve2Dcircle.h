#ifndef CURVE_2D_CIRCLE_H
#define CURVE_2D_CIRCLE_H
#include <math.h>
#include "curve2D.h"

class Curve2DCircle : public Curve2D {
 public:
 Curve2DCircle(const QString &name) : Curve2D(name) {}
 Curve2DCircle(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);
    
    p.moveTo(pt[0],pt[1]);
    
    unsigned int M=100;
    float R;
    float phi;
    Vector2f center=evalAnimPt(get(0),frame);
     
     
    for(unsigned int i=1;i<nbPts();++i) {
      pt = evalAnimPt(get(i),frame);
      R= sqrt((pt[0]-center[0])*(pt[0]-center[0]) + (pt[1]-center[1])*(pt[1]-center[1]));
      p.moveTo(center[0]+ R*cos(0),center[1]+ R*sin(0));
      for(unsigned int j=1;j<M+1;j++) {
		    phi=(M_PI*2*(j+0.0))/M;
			float x=center[0]+ R*cos(phi);
			float y=center[1]+ R*sin(phi); 
			p.lineTo(x,y);
			}
      center=pt;
      p.moveTo(pt[0],pt[1]);
     }
    return p;
  }
};


class Curve2DCircleConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DCircleConstructor()                     {}
  virtual const QString type() const                      { return "CircleCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DCircle(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DCircle(c,name); }
};


#endif // CURVE_2D_LINEAR_H
