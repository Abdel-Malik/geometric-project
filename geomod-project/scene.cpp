#include "scene.h"

//all types of 1D curves
#include "curve1DLinear.h"
#include "curve1DHermite.h"
#include "curve1DLagrange.h"
#include "curve1Dcos.h"

// add all your types of 2D curves here
#include "curve2DLinear.h"
#include "curve2DLinearClosed.h"
#include "curve2DHermite.h"
#include "curve2DMoindreCarre.h"
#include "caligraphy.h"
#include "lagrange.h"
#include "bezier.h"
#include "bspline.h"
#include "curve2Dcircle.h"




Scene *Scene::_instance = NULL;

using namespace std;

// add 2D curve builders here
void Scene::initCurveBuilders() {
  addCurveBuilder(new Curve2DLinearConstructor());
  addCurveBuilder(new Curve2DLinearClosedConstructor());
  addCurveBuilder(new Curve2DHermiteConstructor());
  addCurveBuilder(new Curve2DMoindreCarreConstructor());
  addCurveBuilder(new CaligraphyConstructor());
  addCurveBuilder(new LagrangeConstructor());
  addCurveBuilder(new BezierConstructor());
  addCurveBuilder(new BsplineConstructor());
  addCurveBuilder(new Curve2DCircleConstructor());
}

// add 1D curve builders (functions) here
void Scene::initFunctionBuilders() {
  addFunctionBuilder(new Curve1DLinearConstructor());
  addFunctionBuilder(new Curve1DLagrangeConstructor());
  addFunctionBuilder(new Curve1DHermiteConstructor());
  addFunctionBuilder(new Curve1DcosConstructor());
}


void Scene::cleanCurveBuilders() {
  map<QString,Curve2DConstructor *>::const_iterator mit(_curveBuilders.begin()),mend(_curveBuilders.end());

  for(;mit!=mend;++mit) {
    delete mit->second;
  }

  _curveBuilders.clear();
}

void Scene::cleanFunctionBuilders() {
  map<QString,Curve1DConstructor *>::const_iterator mit(_functionBuilders.begin()),mend(_functionBuilders.end());

  for(;mit!=mend;++mit) {
    delete mit->second;
  }

  _functionBuilders.clear();
}


Scene::Scene() {
  initFunctionBuilders();
  initCurveBuilders();
  setDefaultSettings();
}

Scene::~Scene() {
  clean();
  cleanFunctionBuilders();
  cleanCurveBuilders();
}

