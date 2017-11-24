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
    int pas = 50;
    unsigned int nbDiscretePts = pas*nbPts();
    Vector2f point = evalAnimPt(get(0),frame);
    double valX = point[0];
    computeMeanSquare(frame);
    for(unsigned int i=0;i<=nbDiscretePts;i++) {
      p.lineTo(valX,meanSquarePoly->val(valX));
      valX += 1/nbDiscretePts;
    }
    return p;
  }

 private:
 MatrixXf A;
 VectorXf b;
 VectorXf meanSquare;
 PolyN* meanSquarePoly;
 unsigned int taille = 0;

  void computeMeanSquare(float frame){
    if(taille != nbPts() || (taille ==0 && nbPts()>0)) {
      delete meanSquarePoly;
      //row - column
      A = MatrixXf(nbPts(),3);
      b = VectorXf(nbPts());
      meanSquarePoly = new PolyN(nbPts());
    }
    double xTemp = 1;
    Vector2f pt;
    for(unsigned int ligne=0; ligne<nbPts();ligne++){
      pt = evalAnimPt(get(ligne),frame);
      b(ligne) = pt[1];
      for(int colonne=2; colonne>=0;colonne--){
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
cout << meanSquare;
    remplirPolyN();
  }

  void remplirPolyN(){
    for(unsigned int i=0;i<nbPts();i++){
      meanSquarePoly->editCoef(i,meanSquare(i));
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
