#ifndef CURVE_2D_MOINDRECARRE_H
#define CURVE_2D_MOINDRECARRE_H

#include "curve2D.h"

class Curve2DMoindreCarre : public Curve2D {
 public:
 Curve2DMoindreCarre(const QString &name) : Curve2D(name) {}
 Curve2DMoindreCarre(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0)
      return p;
    unsigned int nbDiscretePts = 50;
    Vector2f pointPrec = evalAnimPt(get(0),frame);
    Vector2f point;
    double valX = pointPrec[0];
    computeMeanSquare(frame);
    double dx;
    p.moveTo(pointPrec[0],pointPrec[1]);
    for(unsigned int k=1;k<nbPts();k++){
      pointPrec = evalAnimPt(get(k-1),frame);
      point = evalAnimPt(get(k),frame);
      dx = (point[0]-pointPrec[0])/nbDiscretePts;
      for(unsigned int i=0;i<=nbDiscretePts;i++) {
        valX += dx;
        p.lineTo(valX,meanSquarePoly.val(valX));
      }
    }
    return p;
  }

 private:
 MatrixXf A;
 VectorXf b;
 VectorXf meanSquare;
 PolyN meanSquarePoly;

  void computeMeanSquare(float frame){
    //row - column
    unsigned int ordrep1 = 2;
    if(nbPts()<ordrep1)
      ordrep1=nbPts();
    A = MatrixXf(nbPts(),ordrep1);
    b = VectorXf(nbPts());
    meanSquarePoly = PolyN(ordrep1);
    double xTemp = 1;
    Vector2f pt;
    for(unsigned int ligne=0; ligne<nbPts();ligne++){
      pt = evalAnimPt(get(ligne),frame);
      b(ligne) = pt[1];
      for(int colonne=ordrep1-1; colonne>=0;colonne--){
        A(ligne,colonne) = xTemp;
       	xTemp = xTemp*pt[0];
      }
      xTemp = 1;
    }
    MatrixXf tA = A.transpose();
    MatrixXf invtAA = tA*A;
    invtAA = invtAA.inverse();
    MatrixXf finalA = (invtAA)*tA;
    meanSquare = finalA*b;
    remplirPolyN(ordrep1);
  }

  void remplirPolyN(unsigned int t){
    for(unsigned int i=0;i<t;i++){
      meanSquarePoly.editCoef(i,meanSquare((t-1)-i));
    }
  }
};


class Curve2DMoindreCarreConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DMoindreCarreConstructor()                     {}
  virtual const QString type() const                      { return "MoindreCarreCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DMoindreCarre(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DMoindreCarre(c,name); }
};


#endif // CURVE_2D_MOINDRECARRE_H
