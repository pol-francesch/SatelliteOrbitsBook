#include <iostream>
#include <cmath>
#include <iomanip>

#include "SAT_Const.h"

using namespace std;

// x mod y
double Modulo(double x, double y) {
  return y*((x/y)-floor(x/y));
};

int main() {
    //Defining constants
    const double J2 = 1.083e-3;
    const double alpha_Sun = 0.985647240*Rad;   
    const double K = 3.;                        //days
    const double N = 43.;                       //orbits
    
    //Defining Variables
    double TN, n0, w_dot, a, h, inc, h_old, del_n, lam_om;
    int iter = 0;
    int day = 1;
    
    //First iteration - guess
    TN = K/N;
    n0 = pi2/TN;
    w_dot = 0;
    del_n = 0;
    a = cbrt(GM_Earth/pow(n0/86400.0,2));
    h = a - R_Earth;
    inc = acos(-2.0*alpha_Sun/(3.0*n0*J2)*pow(a/R_Earth,2));
    
    /*cout << "Iteration " << iter << endl
             << "TN \t" << TN << endl
             << "2pi/TN \t" << pi2/TN*Deg << endl
             << "w_dot \t" << w_dot * Deg << endl
             << "n - n0 \t" << del_n*Deg << endl
             << "n0 \t" << n0*Deg << endl
             << "a \t" << a/1000 << endl
             << "h \t" << h/1000 << endl
             << "i \t" << inc*Deg << endl << endl;*/
         
    
    while (abs(h-h_old) > 1.0) {
        h_old = h;
        iter++;
        w_dot = -3./4.*n0*J2*pow(R_Earth,2.)/pow(a,2.)*(1.-5.*pow(cos(inc),2.));
        del_n = -3./4.*n0*J2*pow(R_Earth,2)/pow(a,2)*(1.-3.*pow(cos(inc),2.));
        n0 = pi2*N/K-del_n-w_dot;
        a = cbrt(GM_Earth/pow(n0/86400.0,2));
        h = a - R_Earth;
        inc = acos(-2*pow(a,2)*alpha_Sun/(3*n0*J2*pow(R_Earth,2)));
        
        /*cout << "Iteration " << iter << endl
             << "TN \t" << TN << endl
             << "2pi/TN \t" << pi2/TN*Deg << endl
             << "w_dot \t" << w_dot*Deg << endl
             << "n - n0 \t" << del_n*Deg << endl
             << "n0 \t" << n0*Deg << endl
             << "a \t" << a/1000 << endl
             << "h \t" << h/1000 << endl
             << "i \t" << inc*Deg << endl << endl;*/
    }
    lam_om = 0;
    cout << "Day " << day << endl << "i \t lam_omega" <<endl;
    cout << "0 \t" << lam_om << endl;
    
    for (int i = 1; i <= N+1; i++) {
        if ( i == 15 || i == 30){
            day++;
            cout << "Day " << day << endl << "i \t lam_omega" <<endl;
        }
        
        lam_om = Modulo(-1.0*i*K*360.0/N+180.0,360.0)-180.0;
        cout << i << " \t" << lam_om << endl;
    }
    
    
}