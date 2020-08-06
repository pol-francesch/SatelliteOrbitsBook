#include <iostream>
#include <cmath>
#include <ctime>
#include <cmath>

#include "SAT_Const.h"
#include "SAT_RefSys.h"
#include "SAT_VecMat.h"
#include "SAT_Force.h"

using namespace std;

Vector Harmonic(const Vector& r, const Matrix& E, const Matrix& CS,
                double GM, double rRef, int nMax, int mMax);

int main() {
    //Define constants
    const int n_step = 10000;
    const int nMax = 20;
    
    const Vector r(6525.919e3, 1710.416e3, 2508.886e3);
    
    //Define variables
    int i,n;        //Loop variables
    clock_t start,end;      //Clock vairables for the processor
    double duration;
    Vector a(3);
    
    //Create Header for output
    cout<< "Order \t\t CPU Time [s]" <<endl;
    
    for (n = 2; n<nMax+1; n+=2) {
        start = clock();
        
        for(i=0; i < n_step; i++)
        {
            //a = AccelHarmonic (r,Id(3),Grav.GM,Grav.R_ref,Grav.CS,n,n);
            a = Harmonic(r, Id(3),Grav.CS,Grav.GM, Grav.R_ref,n,n);
        }
        
        end = clock();
        
        duration = (double)(end-start)/(double)(CLOCKS_PER_SEC);
        
        cout << n << " \t\t " << duration << endl;
    }
    
}

Vector Harmonic(const Vector& r, const Matrix& E, const Matrix& CS,
                double GM, double rRef, int nMax, int mMax) {
    //Defining Variables
    int n,m;                        //Loop variables
    double rSqr, fac;
    double x0, y0, z0;              // Coordinates normalized
    double ax, ay, az;              //Acceleration
    double c,s;                     //Grav coefficients
    Vector r_bf(3);                 //Body-fixed position
    Vector a_bf(3);                  //Body-fixed acceleration
    Matrix v(nMax+2, nMax+2);
    Matrix w(nMax+2, nMax+2);
    
    //Body-fixed position
    r_bf = E*r;
    rSqr = Dot(r_bf,r_bf);
    
    x0 = rRef * r_bf(0) / rSqr; //Normalize coordinates 
    y0 = rRef * r_bf(1) / rSqr; //based on ref length
    z0 = rRef * r_bf(2) / rSqr;
    
    //Calculate initial V and W
    v(0,0) = rRef/sqrt(rSqr);
    w(0,0) = 0.0;
    
    v(1,0) = z0 * v(0,0);
    w(1,0) = 0.0;
    
    //Calculate Zonal terms of v and w
    for (n = 2; n < nMax+2; n++) {
        v(n,0) = (2*n-1)*z0*v(n-1,0)/n - (n-1)*pow(rRef/sqrt(rSqr),2)*v(n-2,0)/n;
        w(n,0) = 0.0;
    }
    
    //Calcuate the rest of v and w (tesseral and sectorial terms
    for (m = 1; m < nMax + 2; m++) {
        v(m,n) = (2*m-1)*(x0*v(m-1,m-1)-y0*w(m-1,m-1));
        w(m,m) = (2*m-1)*(x0*w(m-1,m-1)-y0*v(m-1,m-1));
        
        if (m <= nMax) {
            v(m+1,m) = (2*m+1)*z0*v(m,m);
            w(m+1,m) = (2*m+1)*z0*w(m,m);
        }
        
        for (n = m+2; n < nMax+2; n++) {
            v(n,m) = (2*n-1)*z0*v(n-1,0)/(n-m) - (n+m-1)*pow(rRef/sqrt(rSqr),2)*v(n-2,0)/(n-m);
            w(n,m) = (2*n-1)*z0*w(n-1,0)/(n-m) - (n+m-1)*pow(rRef/sqrt(rSqr),2)*w(n-2,0)/(n-m);
        }
    }
    
    //Calculate accelerations
    ax=ay=az=0.0;
    for (m = 0; m < mMax+1; m++) {
        for (n = 0; n < nMax+1; n++) {
            if (m==0) {
                c = CS(n,0);            //C_n,0
                ax -= c*v(n+1,1);
                ay -= c*w(n+1,1);
                az -= (n+1)*c*v(n+1,0);
            }
            else {
                c = CS(n,m);            //C_n,m
                s = CS(m-1,n);          //S_n,m
                fac = 0.5*(n-m+1)*(n-m+2);
                
                ax += 0.5*(-c*v(n+1,m+1)-s*w(n+1,n+1) +
                      fac*(c*v(n+1,m-1)+s*w(n+1,m-1)));
                ay += 0.5*(-c*w(n+1,m+1)+s*v(n+1,n+1) +
                      fac*(-c*w(n+1,m-1)+s*v(n+1,m-1)));
                az += (n-m+1)*(-c*v(n+1,0)-s*w(n+1,m));
            }
        }
    }
    
    //Normalize the vector by multiplying by scale length
    a_bf = GM/pow(rRef,2)*Vector(ax,ay,az);
    
    return Transp(E)*a_bf;
} 