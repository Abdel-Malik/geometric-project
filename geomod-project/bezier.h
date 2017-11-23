#ifndef BEZIER_H
#define BEZIER_H
#include "curve2D.h"
#include <iostream>


class Bezier : public Curve2D {
 private:
 std::vector<float> A;
 public:
 Bezier(const QString &name) : Curve2D(name) {}
 Bezier(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
 
 std::vector<std::vector<float> > casteljau(std::vector<std::vector<float> > polygon, float t) {
    unsigned int n;
    n=polygon[0].size();
    std::vector<std::vector<float> > MCoefx, MCoefy, Coef;
    MCoefx.resize(n);
    MCoefy.resize(n);
    Coef.clear();
    Coef.resize(4);
    for (unsigned int i=0; i<n; i++) {
		MCoefx[i].resize(n);
		MCoefy[i].resize(n);
		MCoefx[i][0]=polygon[0][i];
		MCoefy[i][0]=polygon[1][i];
		for (unsigned int j=1; j<n; j++) {
			MCoefx[i][j] = 0;
			MCoefy[i][j] = 0;
		}
	}
	for (int i=0; i<4; i++) {
		Coef[i].resize(n);
		for (unsigned int j=0; j<n; j++) Coef[i][j] = 0;
	}
	for (unsigned int k=1; k<n; k++) {
		for (unsigned int j=k; j<n; j++) {
			MCoefx[j][k]=t*MCoefx[j][k-1]+(1-t)*MCoefx[j-1][k-1];
            MCoefy[j][k]=t*MCoefy[j][k-1]+(1-t)*MCoefy[j-1][k-1];
		}
	}
    Coef[1]=MCoefx[n-1];
    Coef[3]=MCoefy[n-1];
    for (unsigned int i=0; i<n; i++) {Coef[0][i]=MCoefx[i][i];  Coef[2][i]=MCoefy[i][i];} 
    MCoefx.clear();
    MCoefy.clear();
    return Coef;
}


std::vector<std::vector<float> > reccursive_sub(std::vector<std::vector<float> > polygon, float t, int N, int i) {
	int m=0;
    std::vector<float> polygonLx, polygonLy, polygonRx, polygonRy, temp1, temp2;
    std::vector<std::vector<float> > AB, CD, EF, polygon1, temp3;
    AB=casteljau(polygon,t);
    m=AB[0].size();
    polygon1.resize(2);
    temp3.resize(2);
    polygonLx.resize(m);
    polygonLy.resize(m);
    polygonLx.resize(m);
    polygonRy.resize(m);
    polygonLx=AB[0];
    polygonLy=AB[2];
    polygonRx=AB[1];
    polygonRy=AB[3];
    std::reverse(polygonRx.begin(), polygonRx.end());
    std::reverse(polygonRy.begin(), polygonRy.end());
    if (i<N) {
		temp3[0].resize(m);
		temp3[1].resize(m);
		for (int j=0; j<m; j++) {temp3[0][j]=polygonLx[j]; temp3[1][j]=polygonLy[j];}
		CD=reccursive_sub(temp3,t,N,i+1);
		temp3[0].clear();
		temp3[1].clear();
        temp3[0].resize(m);
		temp3[1].resize(m);
		for (int j=0; j<m; j++) {temp3[0][j]=polygonRx[j]; temp3[1][j]=polygonRy[j];}
		EF=reccursive_sub(temp3,t,N,i+1);
		temp3[0].clear();
		temp3[1].clear();
		m=2*(CD[0].size())-1;
		for (int j=0; j<2; j++) {polygon1[j].resize(m);}
		copy(CD[0].begin(), CD[0].end()-1, back_inserter(temp1));
		copy(EF[0].begin(), EF[0].end(), back_inserter(temp1));
		for (int j=0; j<m; j++) {polygon1[0][j]=temp1[j];}
		temp1.clear();
		copy(CD[1].begin(), CD[1].end()-1, back_inserter(temp2));
		copy(EF[1].begin(), EF[1].end(), back_inserter(temp2));
		for (int j=0; j<m; j++) {polygon1[1][j]=temp2[j];}
		temp2.clear();
	}
    else {
		copy(polygonLx.begin(), polygonLx.end()-1, back_inserter(temp1));
		copy(polygonRx.begin(), polygonRx.end(), back_inserter(temp1));
		polygon1[0].resize(2*m-1); 
		for (int j=0; j<2*m-1; j++) {polygon1[0][j]=temp1[j];}
		temp1.clear();
		copy(polygonLy.begin(), polygonLy.end()-1, back_inserter(temp2));
		copy(polygonRy.begin(), polygonRy.end(), back_inserter(temp2));
		polygon1[1].resize(2*m-1);
		for (int j=0; j<2*m-1; j++) { polygon1[1][j]=temp2[j];}
		temp2.clear();

	}
	polygonLx.clear();
    polygonLy.clear();
    polygonRx.clear();
    polygonRy.clear();
	return polygon1;
}



QPainterPath path(float frame) {
	QPainterPath p;
	if(nbPts()==0) 
		return p;
		
	std::vector<std::vector<float> > input,polygon1;
	float t;
	t=0.5;	
	Vector2f y = evalAnimPt(get(0),frame);
    p.moveTo(y[0],y[1]);


    float min = 10000;
	float max = 0;
	unsigned int M = 500;
	if (nbPts()!=1)  {
		input.resize(2);
		input[0].resize(nbPts());
		input[1].resize(nbPts());
		for(unsigned int i=0;i<nbPts();i++){
			input[0][i]=evalAnimPt(get(i),frame)[0];
			input[1][i]=evalAnimPt(get(i),frame)[1];
			}
		polygon1=reccursive_sub(input,t,5,1);
		for(unsigned int i=1;i<polygon1[0].size();i++) {
			p.lineTo(polygon1[0][i],polygon1[1][i]);
			}
	}
	return p;	
  }
  
  
};
	


class BezierConstructor : public Curve2DConstructor {
 public:
  virtual ~BezierConstructor()                     {}
  virtual const QString type() const                      { return "BezierCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Bezier(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Bezier(c,name); }
};


#endif // BEZIER_H



