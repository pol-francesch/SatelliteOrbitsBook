#include <iostream>
#include <cmath>

#include "SAT_Const.h"
#include "SAT_Force.h"
#include "SAT_VecMat.h"

using namespace std;

double solarDrag(double h);

int main() {
    //Define constants
    const double J2 = 4.841e-4;
    const double J22 = 2.812e-06;
    const double r_Moon = 384400.0e+03;
    
    //Define variables
    double r, a, h;
    
    //Balance acceleration between solar radiation and drag
    h = 150.0e3;
    a = 1.0;
    while (a > 1.0e-6) {
        a = solarDrag(h);
        h += 10000.0*a;
        cout<<h<<endl;
    }
    
    cout << "Balance btwn solr rad and drag: \t" << h/1000 << endl;
    
    //Balance accelerations between J20 and Moon
    r = 3.0/2.0*GM_Earth/GM_Moon*pow(Grav.R_ref, 2)*pow(r_Moon, 3)*J2;
    r = pow(r,0.2) - Grav.R_ref;
    
    cout << "Balance btwn J20 and Moon: \t\t" << r/1000 << endl;
    
    //Balance accelerations between J22 and Moon
    r = 3.0/2.0*GM_Earth/GM_Moon*pow(Grav.R_ref, 2)*pow(r_Moon, 3)*J22;
    r = pow(r,0.2) - Grav.R_ref;
    
    cout << "Balance btwn J22 and Moon: \t\t" << r/1000 << endl;
    
    //Balance accelerations between J20 and Sun
    r = 3.0/2.0*GM_Earth/GM_Sun*pow(Grav.R_ref, 2)*pow(AU, 3)*J2;
    r = pow(r,0.2) - Grav.R_ref;
    
    cout << "Balance btwn J20 and Sun: \t\t" << r/1000 << endl;
    
    //Balance accelerations between J22 and Sun
    r = 3.0/2.0*GM_Earth/GM_Sun*pow(Grav.R_ref, 2)*pow(AU, 3)*J22;
    r = pow(r,0.2) - Grav.R_ref;
    
    cout << "Balance btwn J22 and Sun: \t\t" << r/1000 << endl;
    
    return 0;
}

double solarDrag(double h) {
    //Define constants
    const double cd = 2.3;
    const double cr = 1.3;
    const double mjd = 51269.0;
    
    //Define variables
    Vector r(3);
    double rho;
    
    //Find density
    r = Vector(1.0,0.0,0.0) * (Grav.R_ref+h);
    rho = Density_HP(mjd, r);
    
    //Get difference in accel
    return 0.5*cd*rho*GM_Earth/(Grav.R_ref+h)-P_Sol*cr;
}