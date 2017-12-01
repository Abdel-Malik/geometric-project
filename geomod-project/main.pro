# define your application name here 
TARGET = yourAppName

# add your source cpp files here 
SOURCES += \
    main.cpp \
    mainWidget.cpp \
    toolsWidget.cpp \
    drawingWidgetItems.cpp \
    drawingWidget.cpp \
    animationWidgetItems.cpp \
    animationWidget.cpp \
    scene.cpp \
    PolyN.cpp \
    animatedPoint.cpp 

# add your header files here
HEADERS += \
    mainWidget.h \
    toolsWidget.h \
    drawingWidgetItems.h \
    drawingWidget.h \
    animationWidgetItems.h \
    animationWidget.h \
    scene.h \
    curve1D.h \
    curve2D.h \    
    curve1DLinear.h \
    curve2DLinear.h \
    curve2DLinearClosed.h \
    curve2DHermite.h \
    curve1DHermite.h \
    curve2DMoindreCarre.h \
    curve1DLagrange.h \
    caligraphy.h \
    lagrange.h \
    bezier.h \
    1DBspline.h \
    bspline.h \
    curve2DCircle.h \
    PolyN.h \
    animatedPoint.h 

TEMPLATE = app

INCLUDEPATH += eigen

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-misleading-indentation -Wno-deprecated-declarations

QT += core gui widgets
