import matplotlib.pyplot as plt
from pylab import *
import numpy as np
import math as math
#----------------------
# Binomial coefficient
def nchoosek(n,p):
    cnp=math.factorial(n)/(math.factorial(p)*math.factorial(n-p))
    return cnp

#---------------------
# Bernstein Polynomials
# N is the degree
# t = np.linspace(0,1,500)
def Bernstein(N,t):
    BNt = np.zeros(N+1)
    for k in range(0,N+1,1): 
        BNt[k]=nchoosek(N,k)*(t**k)*((1-t)**(N-k))
    return BNt

def PlotBezierCurve(Polygon):
    # DETERMINE Bezier
    N=len(Polygon[0,:])
    t = np.linspace(0,1,500)
    Bern = np.zeros((500,N))
    for k in range(0,500,1): 
        Bern[k,:]=Bernstein(N-1,t[k])
    Bezier=Polygon.dot(Bern.T)     
    plt.draw()
    plt.plot(Bezier[0,:],Bezier[1,:],'g',label='Real Bezier curve')
    plt.legend(loc="lower right")
    return   

def DeCasteljau(Polygon,t):#returns the two diagonals
    n=len(Polygon[0,:]) 
    MCoefx=np.zeros((n,n))
    MCoefy=np.zeros((n,n))
    MCoefx[:,0]=Polygon[0,:]
    MCoefy[:,0]=Polygon[1,:]
    Coef=np.zeros((4,n))
    for k in range(1,len(Polygon[0,:]),1):
        for j in range(k,len(Polygon[0,:]),1):
            MCoefx[j,k]=t*MCoefx[j,k-1]+(1-t)*MCoefx[j-1,k-1]
            MCoefy[j,k]=t*MCoefy[j,k-1]+(1-t)*MCoefy[j-1,k-1]
    Coef[0,:]=np.diag(MCoefx)
    Coef[1,:]=MCoefx[n-1,:]
    Coef[2,:]=np.diag(MCoefy)
    Coef[3,:]=MCoefy[n-1,:]
    return Coef
    
def reccursive_sub(Polygon,t,N,i):
    AB=DeCasteljau(Polygon,t)
    m=len(AB[0,:])
    PolygonLx=AB[0,:]
    PolygonLy=AB[2,:]
    PolygonRx=np.flipud(AB[1,:])
    PolygonRy=np.flipud(AB[3,:])
    if (i<N):
        CD=reccursive_sub(np.array([PolygonLx,PolygonLy]),t,N,i+1)
        EF=reccursive_sub(np.array([PolygonRx,PolygonRy]),t,N,i+1)
        Polygon1 = np.zeros((2,2*len(CD[0,:])-1))
        Polygon1[0,:] = np.concatenate([CD[0,0:len(CD[0,:])-1],EF[0,:]])
        Polygon1[1,:] = np.concatenate([CD[1,0:len(CD[0,:])-1],EF[1,:]])
    else:
        Polygon1 = np.zeros((2,2*m-1))
        Polygon1[0,:] = np.concatenate([PolygonLx[0:len(PolygonLx)-1],PolygonRx])
        Polygon1[1,:] = np.concatenate([PolygonLy[0:len(PolygonLy)-1],PolygonRy])

    return Polygon1 
    
    
def PlotBezierCurveApproximation(Polygon,t):       
    plt.draw()
    Bezier1=reccursive_sub(Polygon,t,1,1)
    Bezier2=reccursive_sub(Polygon,t,2,1)
    plt.plot(Bezier1[0,:],Bezier1[1,:],'r',label='Bezier curve for 1 iteration')
    plt.plot(Bezier2[0,:],Bezier2[1,:],'b',label='Bezier curve for 2 iterations')
    plt.legend(loc="upper right")
    return  

def AcquisitionPolygone(minmax,color1,color2) :
    x = []
    y = []
    coord = 0
    while coord != []:
        coord = plt.ginput(1, mouse_add=1, mouse_stop=3, mouse_pop=2)
        if coord != []:
            plt.draw()
            xx = coord[0][0]
            yy = coord[0][1]
            plt.plot(xx,yy,color1,ms=8);
            x.append(xx);
            y.append(yy);
            if len(x) > 1 :
                plt.plot([x[-2],x[-1]],[y[-2],y[-1]],color2)
    #Polygon creation
    Polygon = np.zeros((2,len(x)))
    Polygon[0,:] = x
    Polygon[1,:] = y
    return Polygon

# main part of the program to call AcquisitionPolygone.
fig2 = plt.figure()
ax = fig2.add_subplot(111)    
minmax = 10
ax.set_xlim((-minmax,minmax))
ax.set_ylim((-minmax,minmax))
plt.title("Polygon acquisition and Bezier curve")
Poly = AcquisitionPolygone(minmax,'or',':r')
PlotBezierCurveApproximation(Poly,0.5)
PlotBezierCurve(Poly)
plt.waitforbuttonpress()
