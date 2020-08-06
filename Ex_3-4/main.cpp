#include <iostream>
#include <iomanip>

//#include "SAT_Time.h"
//#include "SAT_Const.h"
//#include "SAT_VecMat.h"
//#include "SAT_Force.h"
//#include "SAT_DE.h"

using namespace std;

struct AuxParam {
    double Mjd0;
    double area, mass, cr, cd;
    int n,m;
    bool sun, moon, srad, drag;
};

Vector Accel(double Mjd0, const Vector& r, const Vector& v,
             double area, double mass, double cr, double cd,
             int n, int m,
             bool sun, bool moon, bool srad, bool drag) {
    
    //Setting variables
    double Mjd_UT1;
    Vector a(3), rSun(3), rMoon(3);
    Matrix T(3,3), E(3,3);
    
    //Acceleration - Harmonic grav field
    Mjd_UT1 = Mjd0 + (IERS::UT1_UTC(Mjd0)-IERS::TT_(Mjd0))/86400.0;
    
    T = NutMatrix(Mjd0)*PrecMatrix(MJD_J2000, Mjd0);
    E = GHAMatrix(Mjd_UT1) * T;
    
    a = AccelHarmonic(r, e, Grav.GM, Grav.R_ref, Grav.CS, n, m);
    
    //Adding perturbations if requested
    //Moon and Sun
    rSun = Sun(Mjd0);
    rMoon = Moon(Mjd0);
    
    if(sun) a += AccelPointMass(r, rSun, GM_Sun);
    if(moon) a += AccelPointMass(r, rMoon, GM_Moon);
    
    //Solar radiation pressure
    if(srad) a += AccelSolrad(r, rSun, area, mass, cr, P_Scol, AU);
    
    //Atmoshperic drag
    if(drag) a += AccelDrag(Mjd0, r, v, T, area, mass, cd);
    
    return a;
}

void Deriv (double t, const Vector& y, Vector& yp, void* pAux) {
    //Pointer to auxiliary info
    AuxParam* p = static_cast<AuxParam*>(pAux);
    
    //Time
    
    double Mjd0 = (*p).Mjd0 + t/86400.0;
    
    //State vector
    Vector r = y.slice(0,2);
    Vector v = y.slice(3,5);
    
    //Acceleration
    Vector a(3)
    
    a = Accel(Mjd0, r, v, (*p).area, (*p).mass, (*p).cr, (*p).cd,
              (*p).n, (*p).m, (*p).sun, (*p).moon, (*p).srad, (*p).drag);
    
    yp = Stack(v,a);
    
}

void Ephemeris (const Vector& y0, int nStep, double step, AuxParam p, Vector Eph[]) {
    //Defining variables
    int i;
    double t, tEnd;
    double relerr, abserr;      //Accuracy requirements
    DE Orb(Deriv,6,&p);         //Integrate Eoms
    Vector y(6);
    
    relerr = 1.0e-3;
    abserr = 1.0e-6;
    t = 0.0;
    y = y0;
    Orb.Init(t,relerr,abserr);
    
    for (i = 0; i < nStep+1; i++) {
        t_end = step*i;
        Orb.Integ(t_end, y);
        Eph[i] = y;
    }
}

template<class T> const T& Max (const T& a, const T& b) {
    return (a<b) ? b:a;
}

int main() {
    //Defining constants
    const int nStep = 720;
    
    //Defining variables
    int i, nStep1, nStep2;
    double step, Mjd0;
    Vector y0(6), Kep(6);
    AuxParam Aux_ref, Aux;
    double maxJ20, maxJ22, maxJ44, maxJ1010;
    double maxSun, maxMoon, maxSrad, maxDrag;
    Vector    Eph_Ref  [N_Step+1];
    Vector    Eph_J20  [N_Step+1];
    Vector    Eph_J22  [N_Step+1];
    Vector    Eph_J44  [N_Step+1];
    Vector    Eph_J1010[N_Step+1];
    Vector    Eph_Sun  [N_Step+1];
    Vector    Eph_Moon [N_Step+1];
    Vector    Eph_SRad [N_Step+1];
    Vector    Eph_Drag [N_Step+1];
    
    //Init UT1-UTC and UTC-TAI time difference
    IERS::Set(-0.05, -30.00, 0.0, 0.0);
    
    /*
     * REMOTE SENSING START
     * */
    //Epoch State
    Mjd0 = Mjd(1999, 03, 01);
    Kep = Vector ( 7178.0e3, 0.0010, 98.57*Rad, 0.0, 0.0, 0.0 ); 
    y0 = State (GM_Earth, Kep, 0.0);
    
    //Parameters
    Aux_ref.Mjd0 = Mjd0 + IERS::TT_UTC(Mjd0)/86400.0;
    Aux_ref.area = 5.0;
    Aux_ref.mass = 1000.0;
    Aux_ref.cr = 1.3;
    Aux_ref.cd = 2.3;
    Aux_ref.n = 20;
    Aux_ref.m = 20;
    Aux_ref.sun = true;
    Aux_ref.moon = true;
    Aux_ref.srad = true;
    Aux_ref.drag = true;
    
    //Orbit
    step = 120.0;
    nStep1 = 50; //100 mins
    nStep2 = 720; //1 day
    
    Aux = Aux_ref;
    Ephemeris(y0, nStep2, step, Aux, Eph_Ref);
    
    //J2,0 perturbations
    Aux.n = 2;
    Aux.m = 0;
    Ephemeris(y0, nStep2, step, Aux, Eph_J20);
    
    //J2,2 perturbations
    Aux.n = 2;
    Aux.m = 2;
    Ephemeris(y0, nStep2, step, Aux, Eph_J22);
    
    //J4,4 perturbations
    Aux.n = 4;
    Aux.m = 4;
    Ephemeris(y0, nStep2, step, Aux, Eph_J44);
    
    //J10,10 perturbations
    Aux.n = 10;
    Aux.m = 10;
    Ephemeris(y0, nStep2, step, Aux, Eph_J1010);
    
    //Solar perturbations
    Aux.sun = false;
    Ephemeris(y0, nStep2, step, Aux, Eph_Sun);
    Aux.sun = true;
    
    //Lunar perturbations
    Aux.moon = false;
    Ephemeris(y0, nStep2, step, Aux, Eph_Moon);
    Aux.sun = false;
    
    //Solar rad pressure perturbations
    Aux.srad = false;
    Ephemeris(y0, nStep2, step, Aux, Eph_SRad);
    Aux.srad = true;
    
    //Solar perturbations
    Aux.drag = false;
    Ephemeris(y0, nStep2, step, Aux, Eph_Drag);
    Aux.drag = true;
    
    Max_J20=Max_J22=Max_J44=Max_J1010=Max_Sun=Max_Moon=Max_SRad=Max_Drag = 0.0;
    for (i=0;i<=N_Step1;i++) {
        Max_J20   = Max(Norm (Eph_J20  [i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_J20);
        Max_J22   = Max(Norm (Eph_J22  [i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_J22);
        Max_J44   = Max(Norm (Eph_J44  [i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_J44);
        Max_J1010 = Max(Norm (Eph_J1010[i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_J1010);
        Max_Sun   = Max(Norm (Eph_Sun  [i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_Sun);
        Max_Moon  = Max(Norm (Eph_Moon [i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_Moon);
        Max_SRad  = Max(Norm (Eph_SRad [i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_SRad);
        Max_Drag  = Max(Norm (Eph_Drag [i].slice(0,2)-Eph_Ref[i].slice(0,2)), Max_Drag);
    }
    
    cout << "Remote Sensing" <<endl
         << "    J2,0    J2,2    J4,4  J10,10     Sun    Moon  SolRad    Drag" << endl;
    cout << setw(8) << Max_J20   << setw(8) << Max_J22  << setw(8) << Max_J44
         << setw(8) << Max_J1010 << setw(8) << Max_Sun  << setw(8) << Max_Moon
         << setw(8) << Max_SRad  << setw(8) << Max_Drag << endl << endl;

    return 0;
}