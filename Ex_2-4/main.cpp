#include <iostream>
#include <iomanip>

#include "SAT_Const.h"
#include "SAT_Kepler.h"
#include "SAT_RefSys.h"
#include "SAT_Time.h"
#include "SAT_VecMat.h"

using namespace std;

int main() {
    //Defining the ground station
    const double longi_station = 11.*Rad;     //deg
    const double lat_station = 48.*Rad;       //deg
    
    const Geodetic Sta(longi_station, lat_station, 0.0e3);
    
    //Defining the satellite
    const double a = 960.e3+R_Earth;      //m
    const double ecc = 0.;
    const double inc = 97.*Rad;     //rad
    const double Omega = 130.7*Rad;  //rad
    const double omega = 0.*Rad;     //rad
    const double M0 = 0*Rad;         //rad
    
    const double Mjd_Epoch = Mjd(1997,01,01);
    const Vector Kep(a,ecc,inc,Omega,omega,M0);
    
    //Defining Variables
    double Mjd_Utc, dt;
    double Azimuth, Elevation, Distance;
    Vector R_Sta(3), s(3);
    Vector r(3);
    Matrix E(3,3), U(3,3);
    
    //Station Coordinates
    R_Sta = Sta.Position(R_Earth, f_Earth);
    E = Sta.LTC_Matrix();
    
    cout<<"Date \t\t UTC \t\t Az \t El \t Dist"<<endl;
    cout<<"yyyy/mm/dd \t hh:mm:ss.sss \t [deg] \t [deg] \t [km]"<<endl<<endl;
    
    for (int minu = 0; minu <=30; minu++) {
        Mjd_Utc = Mjd_Epoch + minu/1440.0;
        dt = (Mjd_Utc-Mjd_Epoch)*86400.0;
        
        r = State(GM_Earth, Kep, dt).slice(0,2);
        
        U = R_z(GMST(Mjd_Utc));
        s = E*(U*r-R_Sta);
        
        Distance = Norm(s);
        AzEl(s, Azimuth, Elevation);
        
        cout<<Date(Mjd_Utc)<<fixed<<setprecision(1)
            <<setw(10)<<Azimuth*Deg<<setw(10)<<Elevation*Deg
            <<setw(10)<<Distance/1000. << endl;
        
    }
    return 0;
}