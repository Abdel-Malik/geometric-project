#ifndef CURVE_2D_Caligraphy
#define CURVE_2D_Caligraphy

#include "curve2D.h"

class Caligraphy : public Curve2D {
 public:
 Caligraphy(const QString &name) : Curve2D(name) {}
 Caligraphy(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);

    addPoints(frame);
    p.moveTo(pt[0],pt[1]);
    for(unsigned int i=1;i<nbPts();++i) {
      pt = evalAnimPt(get(i),frame);
      p.lineTo(pt[0],pt[1]);
    }
    return p;
  }

 void addPoints(float frame){
     if(nbPts()<500){
 	 Vector2f ptS = evalAnimPt(get(0),frame);
	 add(ptS[0],ptS[1]);
     }else{
	//DivideByFour();
     }
 }
/*
 void diviveByFour(){
     Vec
 }*/
};


class CaligraphyConstructor : public Curve2DConstructor {
 public:
  virtual ~CaligraphyConstructor()                     {}
  virtual const QString type() const                      { return "CaligraphyCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Caligraphy(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Caligraphy(c,name); }
};


#endif // CURVE_2D_Caligraphy
