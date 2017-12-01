#ifndef CURVE_1D_LAGRANGE_H
#define CURVE_1D_LAGRANGE_H

#include "curve1D.h"
#include "PolyN.h"

class Curve1DLagrange : public Curve1D {
 public:
 Curve1DLagrange(const QString &name) : Curve1D(name) {}
 Curve1DLagrange(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;
    //empty test
    if(empty())
	return p;

    computeMeanSquare();
    unsigned int nbDiscretePts = 1;
    double valX = xmin;
    double dx = (1.0)/nbDiscretePts;
    p.moveTo(valX,meanSquarePoly.val(valX));
    for(unsigned int k=valX;k<xmax;k+=dx){
        p.lineTo(k,evalAt(k));
    }
    return p;
  }

  float evalAt(float x){
    return meanSquarePoly.val(x);
  }

  private:
  PolyN meanSquarePoly = PolyN(0);

  void computeMeanSquare(){
    int ordrep1=nbPts();
    //row - column
    MatrixXd A(nbPts(),ordrep1);
    VectorXd b(nbPts());
    double xTemp = 1 ;
    for(unsigned int ligne=0; ligne<nbPts();ligne++){
      b(ligne) = _points[ligne][1];
      for(int colonne=ordrep1-1; colonne>=0;colonne--){
        A(ligne,colonne) = xTemp;
       	xTemp = xTemp*_points[ligne][0];
      }
      xTemp = 1;
    }
    MatrixXd tA = A.transpose();
    MatrixXd invtAA = tA*A;
    invtAA = invtAA.inverse();
    MatrixXd finalA = (invtAA)*tA;
    VectorXd meanSquare = finalA*b;
    remplirPolyN(meanSquare,ordrep1);
  }

  void remplirPolyN(VectorXd coeffs,unsigned int t){
    for(unsigned int i=0;i<t;i++){
      meanSquarePoly.editCoef(i,coeffs((t-1)-i));
    }
  }

};


class Curve1DLagrangeConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DLagrangeConstructor()                   {}
  virtual const QString type() const                      { return "LagrangeCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DLagrange(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DLagrange(c,name); }
};


#endif // CURVE_1D_LINEAR_H
