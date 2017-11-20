#ifndef CURVE_2D_HERMITE_H
#define CURVE_2D_HERMITE_H

#include "curve2D.h"
#include "PolyN.h"

class Curve2DHermite : public Curve2D {
 public:
 Curve2DHermite(const QString &name) : Curve2D(name) {}
 Curve2DHermite(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);

    p.moveTo(pt[0],pt[1]);
    for(unsigned int i=1;i<nbPts();++i) {
      pt = evalAnimPt(get(i),frame);
      p.lineTo(pt[0],pt[1]);
    }
    return p;
  }

 private:
 PolyN* HermitePolynome;
};


class Curve2DHermiteConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DHermiteConstructor()                     {}
  virtual const QString type() const                      { return "HermiteCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DHermite(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DHermite(c,name); }
};


#endif // CURVE_2D_HERMITE_H
