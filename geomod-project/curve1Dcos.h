#ifndef CURVE_1D_COS_H
#define CURVE_1D_COS_H

#include <cmath>
#include "curve1D.h"

class Curve1Dcos : public Curve1D {
 public:
 Curve1Dcos(const QString &name) : Curve1D(name) {}
 Curve1Dcos(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;

    // empty test 
    if(empty()) 
      return p;
      
    // global variable
 	unsigned int M=500;
    
	// left part 
	if(xmin<_points[0][0]) {
		p.moveTo(xmin,_points[0][1]);
		for(unsigned int j=0;j<M;j++){
			float x = xmin + j*((_points[0][0]-xmin)/M);
			float y = _points[0][1] + 200*cos (x);
			p.lineTo(x,y);
		}
	} else {
		p.moveTo(_points[0][0],_points[0][1]);
	}

    // draw function 
    for(unsigned int i=0;i<nbPts()-1;i++){	
		for(unsigned int j=0;j<M;j++){
		float x = _points[i][0] + j*((_points[i+1][0]-_points[i][0])/M);
		float y = _points[i][1]+(_points[i+1][1]-_points[i][1])*((x-_points[i][0])/(_points[i+1][0]-_points[i][0])) + 200*cos(x-_points[i][0]);
		p.lineTo(x,y);
		}
    }

    // right part 
	if(xmax>_points[nbPts()-1][0]) {
		for(unsigned int j=0;j<M;j++){
			float x = _points[nbPts()-1][0]+j*((xmax-_points[nbPts()-1][0])/M);
			float y = _points[nbPts()-1][1] + 200*cos (x);
			p.lineTo(x,y);
		}
	}

    return p;
  }

  /* To maintain the curve already drawn */
  float evalAt(float x){
  	// special cases 
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) {
      float a = 0.0f;
      return _points[0][1] + cos(x);
    }
    if(x>=_points[nbPts()-1][0]) {
      return _points[nbPts()-1][1] + 200*cos(x);
    }
    
    // interpolation
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
	return _points[i][1]+(_points[i+1][1]-_points[i][1])*((x-_points[i][0])/(_points[i+1][0]-_points[i][0])) + 200*cos(x-_points[i][0]);
      }
    }
    return _points[0][1];
  }
};


class Curve1DcosConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DcosConstructor()                     {}
  virtual const QString type() const                      { return "CosinusCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1Dcos(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1Dcos(c,name); }
};


#endif // CURVE_1D_COS_H
