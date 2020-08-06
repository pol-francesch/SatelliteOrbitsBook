#include <iostream>
#include <cmath>
#include <iomanip>

#include "SAT_Const.h"
#include "SAT_Time.h"
#include "SAT_VecMat.h"

using namespace std;

double Frac(double x) {return x-floor(x); };

//Chebyshev approx of 3d vector
class Cheb3D{
    public:
        //Constructor
        Cheb3D(int n, double ta, double tb,
               const Vector& cx, const Vector& cy, const Vector& cz)
            : N(n), Ta(ta), Tb(tb)
        {
            Cx = cx; Cy = cy; Cz = cz;
        };
            
        //Eval
        Vector Value(double t) const;
     private:
        //Elems
        int N;          //Number of coefficeints
        double Ta;      //Begin interval
        double Tb;      //End interval
        Vector Cx;      //Coeffs of Chebyshev poly
        Vector Cy;
        Vector Cz;
};

Vector Cheb3D::Value (double t) const {
    //Defining variables
    int i;
    Vector f1(3), f2(3), old_f1(3);
    double tau;
    
    //Checking if within bounds
    if ( (t<Ta) || (Tb<t)) {
        cerr << "ERROR: Time out of range in Cheb3D::Value" << endl;
        exit(1);
    }
    
    //Algorithm
    tau = (2.0*t-Ta-Tb)/(Tb-Ta);
    
    f1 = f2 = 0.0;
    
    for (i = N-1; i > 0; i--) {
        old_f1 = f1;
        f1 = 2.0*tau*f1-f2+Vector(Cx(i), Cy(i), Cz(i));
        f2 = old_f1;
    }
    
    return tau*f1-f2+Vector(Cx(0),Cy(0),Cz(0));
}

int main() {
    //Defining constant
    double eta = 23.43929111*Rad;       //Obliquity of the ecliptic
    
    //Defining Variables
    double start, end, curr, step, T;    //Times
    double l0,l,lPrime, f,d;             //Used for computation
    double lm, bm, rm;                   //Longitude, latitude, distance
    Vector rMoon(3);
    
    //Times
    start = curr =  Mjd(2006,03,14);
    end = Mjd(2006,03,18);
    step = (end-start)/4;
    
    //Header for output
    cout << "Low order estimate for Moon ephemeris" << endl;
    cout << "Date \t\t TT \t\t x[km] \t\t y[km] \t\t z[km]" << endl;
    
    //Low order estimation
    while (curr <= end) {
        T = (curr-MJD_J2000)/36525.0;
        
        l0 = Frac(218.3167/360.0 + 481266.4837*T/360.0);
        l = pi2*Frac(134.96292/360.0 + 477198.86753*T/360.0);
        lPrime = pi2*Frac(357.52543/360.0 + 45999.04944*T/360.0);
        f = pi2*Frac(93.27283/360.0 + 483202.01873*T/360.0);
        d = pi2*Frac(297.85027/360.0 + 445267.11135*T/360.0);
        
        //Longitude
        lm = +22640.0*sin(l)+769.0*sin(2*l)-526.0*sin(f-2*d)+2370.0*sin(2*d)
             -668.0*sin(lPrime)-412.0*sin(2*f)-212.0*sin(2*l-2*d)-206.0*sin(l+lPrime-2*d)
             +192.0*sin(l+2*d)-165.0*sin(lPrime-2*d)+148.0*sin(l-lPrime)-125.0*sin(d)
             -110.0*sin(l+lPrime)-55.0*sin(2*f-2*d);
        lm = pi2*Frac(l0+lm/1296.0e3); //[rad]
        
        //Latitude
        bm = +18520.0*sin((f+lm-l0+412.0*sin(2*f)+541.0*sin(lPrime))/Arcs)
             -526.0*sin(f-2*d)+44.0*sin(l+f-2*d)-31.0*sin(-l+f-2*d)
             -25.0*sin(-2*l+f)-23.0*sin(lPrime+f-2*d)+21.0*sin(-l+f)
             +11.0*sin(-lPrime+f-2*d);
        bm = bm/Arcs; //[rad]
        
        //Distance
        rm = +385.0e6-20905.0e3*cos(l)-3699.0e3*cos(2*d-l)-2956.0e3*cos(2*d)-570.0e3*cos(2*l)
             +246.0e3*cos(2*l-2*d)-205.0e3*cos(lPrime-2*d)-171.0e3*cos(l+2*d)-152.0e3*(l+lPrime-2*d);
        
        //Coordinates
        rMoon = R_x(-eta)*Vector(rm*cos(lm)*cos(bm),rm*sin(lm)*cos(bm),rm*sin(bm));;
        
        cout << Date(curr)
             << fixed << setprecision(3) << setw(14) << rMoon/1000 << endl;
        
        curr += step;
    }
    
    //Working on the Chebyshev coefficeints
    const int    N_coeff = 13;          // Number of coefficients
    const double Cx_moon[N_coeff] = {   // Coefficients for x-coordinate
     -0.383089044877016277e+06, 0.218158411754834669e+05, 0.179067292901463843e+05,
     -0.836928063411765777e+02,-0.628266733052023696e+02,-0.459274434235101225e+00,
      0.491167202819885532e-01, 0.770804039287614762e-03,-0.125935992206166816e-03,
      0.500271026610991370e-05, 0.107044869185752331e-05, 0.172472464343636242e-08,
     -0.269667589576924680e-08};
    const double Cy_moon[N_coeff] = {   // Coefficients for y-coordinate
     -0.379891721705081436e+05,-0.143611643157166138e+06, 0.187126702787245881e+04, 
      0.112734362473135207e+04, 0.932891213817359177e+00,-0.191932684130578513e+01, 
     -0.266517663331897990e-01, 0.104558913448630337e-02,-0.359077689123857890e-04, 
     -0.123405162037249834e-04, 0.180479239596339495e-06, 0.525522632333670539e-07, 
      0.543313967008773005e-09}; 
    const double Cz_moon[N_coeff] = {   // Coefficients for z-coordinate
     -0.178496690739133737e+05,-0.788257550331743259e+05, 0.880684692614081882e+03, 
      0.618395886330471512e+03, 0.103331218594995988e+01,-0.104949867328178592e+01,
     -0.150337371962561087e-01, 0.569056416308259317e-03,-0.186297523286550968e-04,
     -0.680012420653791955e-05, 0.902057208454410917e-07, 0.287891446432139173e-07, 
    0.319822827699973363e-09};
    
    const Cheb3D MoonCheb(N_coeff, start, end,
                          Vector(&Cx_moon[0], N_coeff),
                          Vector(&Cy_moon[0], N_coeff),
                          Vector(&Cz_moon[0], N_coeff));
    
    curr = start;
    
    cout << endl << "Chebyshev estimate for Moon ephemeris" << endl;
    cout << "Date \t\t TT \t\t x[km] \t\t y[km] \t\t z[km]" << endl;
    
    while (curr <= end) {
        rMoon = MoonCheb.Value(curr);
        cout << Date(curr)
             << fixed << setprecision(3) << setw(14) << rMoon << endl;
        
        curr += step;
    }
    
    return 0;
}