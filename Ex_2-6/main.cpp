#include <iostream>
#include <iomanip>

#include "SAT_Const.h"
#include "SAT_Kepler.h"
#include "SAT_RefSys.h"
#include "SAT_Time.h"
#include "SAT_VecMat.h"

using namespace std;

int main() {
    //Station
    const double sta_x = 1344.143e3;    //m
    const double sta_y = 6068.601e3;    //m
    const double sta_z = 1429.311e3;    //m
    const Vector R_Sta(sta_x, sta_y, sta_z);
    
    const Geodetic Sta(R_Sta, R_Earth, f_Earth);    //Geodetic Coords
    
    //Observations from the Ground Station
    struct ObsType {
        double Mjd_Utc;
        double azim, elev, range;
    };
    
    const ObsType obs[2] = {{Mjd(1999,4,2,0,30,0.0),
                            132.67*Rad,32.44*Rad,16945.450e3},
                            {Mjd(1999,4,2,3,0,0.0),
                            123.08*Rad,50.06*Rad,37350.340e3}};

    //Defining variables
    Vector s(3), Kep(6);
    Matrix E(3,3), U(3,3);
    Vector r[2];
    
    E = Sta.LTC_Matrix();
    
    
    for (int i = 0; i<2; i++) {
        //Earth rotation
        U = R_z(GMST(obs[i].Mjd_Utc));
        //Topocentric position vector
        s = obs[i].range*VecPolar(pi/2.0-obs[i].azim,obs[i].elev);
        //Intertial position vector
        r[i] = Transp(U)*(Transp(E)*s+R_Sta);
    }

    //Orbital Elems
    Kep = Elements(GM_Earth, obs[0].Mjd_Utc, obs[1].Mjd_Utc, r[0], r[1]);
    
    //Print solution
    cout << "Date \t UTC \t\t\t x [km] \t y [km] \t z [km]" << endl;
    for (int i = 0; i < 2; i++) {
        cout << Date(obs[0].Mjd_Utc) << " \t " << r[i](0)/1000
             << " \t " << r[i](1)/1000 << " \t " << r[i](2)/1000 <<endl;
    }
    
    cout << endl << "a \t" << Kep(0)/1000. << endl 
         << "e \t" << Kep(1) << endl
         << "i \t" << Kep(2)*Deg << endl
         << "Omega \t" << Kep(3)*Deg << endl
         << "omega \t" << Kep(4)*Deg << endl
         << "M0 \t" << Kep(5)*Deg << endl;

}