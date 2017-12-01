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
 	unsigned int M=100;
 	//A is amplitude
 	unsigned int A=20;
 	//W is frequency
 	unsigned int W=0.5;
 	
 	
	// left part 
	if(xmin<_points[0][0]) {
		p.moveTo(xmin,_points[0][1]);
		for(unsigned int j=0;j<M;j++){
			float t = (j+0.0)/M;
			float y = _points[0][1] + A*cos (W*t);
			p.lineTo(_points[0][0],y);
		}
	} else {
		p.moveTo(_points[0][0],_points[0][1]);
	}
	

    // draw function 
    
    for(unsigned int i=0;i<nbPts()-1;i++){	
		for(unsigned int j=0;j<M;j++){
			float t = (j+0.0)/M;
			float y = _points[i][1] + A*cos (W*t);
			//float y = _points[i][1]+(_points[i+1][1]-_points[i][1])*((x-_points[i][0])/(_points[i+1][0]-_points[i][0])) + A*cos(x-_points[i][0]);
			//float y = _points[i][1]+(_points[i+1][1]-_points[i][1])*(j/M) + A*cos(W*(x-_points[i][0]))*sin(W*(x-_points[i][0]));
			p.lineTo(_points[i][0],y);
		}
    }
    

    // right part 
	if(xmax>_points[nbPts()-1][0]) {
		for(unsigned int j=0;j<M;j++){
			float t = (j+0.0)/M;
			float y = _points[0][1] + A*cos (W*t);
			p.lineTo(_points[0][0],y);
		}
	}

    return p;
  }
  

  /* To maintain the curve already drawn */
  
  float evalAt(float x){
	 unsigned int A=20;
 	unsigned int W=0.5;
  	// special cases 
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) {
      float a = 0.0f;
      return _points[0][1] + A*cos(W*x);
    }
    if(x>=_points[nbPts()-1][0]) {
      return _points[nbPts()-1][1] + A*cos(W*x);
    }
    
    // interpolation
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
	return _points[i][1]+(_points[i+1][1]-_points[i][1])*((x-_points[i][0])/(_points[i+1][0]-_points[i][0])) + A*cos(W*(x-_points[i][0]));
      }
    }
    return _points[0][1];
  }
};


  /* To maintain the curve already drawn */
  float evalAt(float x){
  	// special cases 
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) {
      float a = 0.0f; /*eqivalent to xmin*/
      float b = _points[0][0];
      float c = _points[0][1];
      return c + S*sin(W*(x-a))*sin(W*(b-x));
    }
    if(x>=_points[nbPts()-1][0]) {
      float a = _points[nbPts()-1][0];
      float c = _points[nbPts()-1][1];
      return c + S*sin(W*(x-a))/* *sin(W*(b-x))*/;
    }
    
    // linear interp
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
	float a = _points[i][0];
      	float b = _points[i+1][0];
      	float c = _points[i][1];
      	float d = _points[i+1][1];
      	// we are in interval [a;b] 
	return c+(d-c)*((x-a)/(b-a)) + S*sin(W*(x-a))*sin(W*(b-x));
      }
    }
    return _points[0][1];
  }



class Curve1DcosConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DcosConstructor()                     {}
  virtual const QString type() const                      { return "CosinusCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1Dcos(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1Dcos(c,name); }
};


#endif // CURVE_1D_COS_H


