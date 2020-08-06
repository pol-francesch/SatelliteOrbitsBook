#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>

#include "SAT_VecMat.h"
#include "integration.hpp"

using std::cout;
using std::endl;

//Simple math function(s)
double frac(double x) { return x - floor(x); }
double modulo(double x, double y) { return y * frac(x/y); }

//Function prototypes
double eccAnom(double M, double ecc);
Vector state(double GM, const Vector& Kep, double dt=0.0);
void f_Kep6d(double t, const Vector& y, Vector& yp, void* pAux);

//Main
int main() {
    //Define constants
    const double GM {1.0};                              //Gravitational coefficient
    const double ecc {0.1};                             //Eccentricity
    const double t_end {20.0};                          //End time
    const Vector kep(1.0, ecc, 0.0, 0.0, 0.0, 0.0);     //Vector containing Keplerian elements (a,e,i,Omega,omega,M)
    const Vector y_ref {state(GM, kep, t_end)};         //Reference solution

    const int steps[] = {50, 100, 250, 500, 750, 1000, 1500, 2000};

    //Define variables
    int nCalls;                                         //Function call count
    int iCase;
    double t,h;                                         //Time and step size
    Vector y(6);

    RK4 orbit(f_Kep6d, 6, &nCalls);

    //Header
    cout << " Problem D1 (ecc = 0.1)" << endl << endl;
    cout << "  N_fnc   Accuracy   Digits " << endl;

    //Loop over test cases
    for(iCase = 0; iCase < 8; iCase++) {
        //Step size calculation
        h = t_end/steps[iCase];

        //Initial values
        t = 0.0;
        y = Vector(1.0 - ecc, 0.0, 0.0,     0.0, sqrt((1 + ecc)/(1 - ecc)), 0.0);
        nCalls = 0;

        //Integrate from t=t to t=t_end
        for(int i {1}; i < steps[iCase]; i++)
            orbit.step(t, y, h);
        
        //Output
        cout << std::fixed << std::setw(6) << nCalls
             << std::scientific << std::setprecision(3) << std::setw(13) << Norm(y - y_ref)
             << std::fixed << std::setprecision(2) << std::setw(7) << -log10(Norm(y - y_ref)) << endl;
    }

    return 0;
}

/**
 * Computes eccentric anomally for elliptic orbits
 * 
 * M - mean anomally
 * ecc - eccentricity of the orbit
*/
double eccAnom(double M, double ecc) {
    //Define limit
    const double eps_mach = std::numeric_limits<double>::epsilon();

    //Define constants
    const int maxit = 15;
    const double eps = 100.0*eps_mach;

    //Define variables
    int i = 0;
    double E, f;

    //Starting value
    M = modulo(M, 2.0*M_PI);
    if(ecc < 0.8)
        E = M;
    else
        E = M_PI;
    
    //Iteration
    do {
        f = E - ecc*sin(E) - M;
        E = E - f / (1.0 - ecc*cos(E));
        ++i;
        if(i == maxit) {
            std::cerr << " convergence problems in eccAnom" << std::endl;
            break;
        }
    } while(fabs(f) > eps);

    return E;
}

/**
 * Computes state vector for satellite in elleiptic orbit given the Keplerian elements
*/
Vector state(double GM, const Vector& Kep, double dt) {
    //Define variables
    double a,ecc,inc,Omega,omega,M,M0,n;
    double E,cosE,sinE, fac, R,V;
    Vector r(3),v(3);
    Matrix PQW(3,3);

    //Keplerian elements at current epoch
    a = Kep(0);
    ecc = Kep(1);
    inc = Kep(2);
    Omega = Kep(3);
    omega = Kep(4);
    M0 = Kep(5);

    //Mean anomally
    if(dt == 0.0) {
        M = M0;
    }
    else {
        n = sqrt(GM/pow(a,3));
        M = M0 + n*dt;
    }

    //Eccentric anomally
    E = eccAnom(M, ecc);

    cosE = cos(E);
    sinE = sin(E);

    //Preifocal coordinates
    fac = sqrt((1.0 - ecc) * (1.0 + ecc));

    R = a * (1.0 - ecc*cosE);                     //Distance
    V = sqrt(GM * a) / R;                       //Velocity
    
    r = Vector(a * (cosE - ecc), a * fac * sinE, 0.0);
    v = Vector(-V * sinE, V * fac * cosE, 0.0);

    //Transform back to refernce system - Gaussian vectors
    PQW = R_z(-Omega) * R_x(-inc) * R_z(-omega);

    r = PQW*r;
    v = PQW*v;

    //State vector
    return Stack(r,v);
}

/**
 * Computes derivative of state vector for normalized Kepler's problem in 3D
*/
void f_Kep6d(double t, const Vector& y, Vector& yp, void* pAux) {
    //Pointer to pAux expected to be used as function call counter
    int* pCalls = static_cast<int*>(pAux);

    //State vector derivatives
    Vector r = y.slice(0,2);
    Vector v = y.slice(3,5);
    yp = Stack(v, -r/(pow(Norm(r),3)));

    //Increment function call count
    (*pCalls)++;
}