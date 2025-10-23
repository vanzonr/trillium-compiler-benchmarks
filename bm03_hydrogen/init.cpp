// init.cpp
#include "init.h"
#include <cassert>
#include <cmath>

double hammat(int I, int J, double L, int r)
{
    const int n = 2*r+1;
    const int nnn = n*n*n;    
    assert(I < nnn);
    assert(J < nnn);
    const int i1 = I%n;
    const int j1 = (I/n)%n;
    const int k1 = (I/n)/n;
    const int i2 = J%n;
    const int j2 = (J/n)%n;
    const int k2 = (J/n)/n;
    const double dx = L/n;
    const double xc1 = (i1-r)*dx;
    const double yc1 = (j1-r)*dx;
    const double zc1 = (k1-r)*dx;
    auto V = [](double x, double y, double z) { return -1.0/sqrt(x*x+y*y+z*z); };
    if (i1==i2 && j1==j2 && k1==k2) {
        const double Vijk = (V(xc1-dx/2,yc1,zc1)+V(xc1+dx/2,yc1,zc1)
                             +V(xc1,yc1-dx/2,zc1)+V(xc1,yc1+dx/2,zc1)
                             +V(xc1,yc1,zc1-dx/2)+V(xc1,yc1,zc1+dx/2))/6;
        const double t = -1/(2*dx*dx);
        return Vijk - 6*t;
    } else if ( (i1==i2 && j1==j2 && abs(k1-k2)==1)
                || (i1==i2 && abs(j1-j2)==1 && k1==k2)
                || (abs(i1-i2)==1 && j1==j2 && k1==k2) ) {
        const double t = -1/(2*dx*dx);
        return t;
    } else {
        return 0;
    }
}

int icbrt(int n)
{
    int lo = cbrt(n);
    int hi = lo+1;
    if (hi*hi*hi == n)
	return hi;
    else
	return lo;
}

double hamiltonian(int I, int J, int n, double L)
{
    int r = (icbrt(n)-1)/2;
    while ((2*r+1)*(2*r+1)*(2*r+1) > n) r--;
    return hammat(I,J,L,r);
}

double H(int i,int j,int n) {
    const double L=50.0;
    return hamiltonian(i,j,n,L);
}


rmatrix<double> initMatrix(int n)
{
    rmatrix<double> m(n,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = H(i,j,n);
        }
    }
    return m;
}
