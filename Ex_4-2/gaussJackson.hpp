#ifndef _GAUSS_JACKSON_HPP_
#define _GAUSS_JACKSON_HPP_

#include "SAT_VecMat.h"

//Function prototype for 2nd order dfq
typedef void (*GJ4Pfunct)(
    double t,                //Independent vector
    const Vector& r,        //Position vector
    const Vector& v,        //Velocity vector; r' = v
    Vector& a,              //Acceleration vector; r'' = a = f(t,r,v)
    void* pAux              //Pinter to auxiliary data used within f
);

//4th order Gauss-Jackson Method
class GJ4P {
    private:
        //4th order Runge-Kutta step
        void RK4(
            double& t,              //Independent variable; updated by t+h
            Vector& r,              //Value of r(t); updated by r(t+h)
            Vector& v,              //Value of v(t) = dr/dt(t); updated by v(t+h)
            double h                //Step size
        );

        //Elements
        int n_eqn;                  //Dimension
        GJ4Pfunct f;                //Differential equation
        double h;                   //Step size
        void* pAux;                 //Pointer to auxiliary data required by f
        Vector S2, S1;              //First and second sums of acceleration
        Vector D[4];                //Backward differences of acceleration at t
        Vector d[4];                //Backward differences of acceleration at t + h
        Vector r_p, v_p;            //Position and velocity predictors

    public:
        //Constructor
        GJ4P (
            GJ4Pfunct f_,           //Differential equation
            int n_eqn_,             //Dimension
            void* pAux_             //Pointer to auxiliary data
            )
        : n_eqn(n_eqn_), f(f_), pAux(pAux_) {};

        //Initialization
        void init (
            double t_0,             //Initial value of independent variable
            const Vector& r_0,      //Initial value r_0 = r(t_0)
            const Vector& v_0,      //Initial value v_0 = dr/dt(t0)
            double h_               //Step size
        );

        //Integration step
        void step (
            double& t,              //Independent vairable; updated by t + h
            Vector& r,              //Value of r(t); updated by r(t+h)
            Vector& v               //Value of v(t) = dr/dt(t); updated by v(t+h)
        );
};

/**
 * 4th order Runge-Kutta step for 2nd order dfq
*/
void GJ4P::RK4 (double &t, Vector& r, Vector& v, double h) {
    //Defining variables
    Vector v_1, v_2, v_3, v_4;
    Vector a_1, a_2, a_3, a_4;

    //Runge-Kutta step
    v_1 = v;
    f(t, r, v_1, a_1, pAux);
    v_2 = v + (h/2.0) * a_1;
    f(t + h/2.0, r + (h/2.0)*v_1, v_2, a_2, pAux);
    v_3 = v + (h/2.0) * a_2;
    f(t + h/2.0, r + (h/2.0)*v_2, v_3, a_3, pAux);
    v_4 = v + h*a_3;
    f(t + h, r + h*v_3, v_4, a_4, pAux);

    //Updates
    t = t + h;
    r = r + (h/6.0) * (v_1 + 2.0*v_2 + 2.0*v_3 + v_4);
    v = v + (h/6.0) * (a_1 + 2.0*a_2 + 2.0*a_3 + a_4);

}

/**
 * Initialization of backwards differences from initial conditions
*/
void GJ4P::init(double t_0, const Vector& r_0, const Vector& v_0, double h_) {
    //Order of the method
    const int m = 4;

    //Coefficients gamma/delts of 1st/2nd order Moulton/Cowell corrector method

    const double gc[m+1] = {+1.0, -1/2.0, -1/12.0, -1/24.0, -19/720.0 };
    const double dc[m+2] = {+1.0,   -1.0, +1/12.0,     0.0,  -1/240.0, -1/240.0 };

    int i,j;
    double t {t_0};
    Vector r {r_0};
    Vector v {v_0};

    //Save step size
    h = h_;

    //Create table of accelerations at t-3h, t-2h, and t-h using RK4
    f(t, r, v, D[0], pAux);     //D[i] = a(t - ih)
    for(i = 1; i <= m - 1; i++) {
        RK4(t, r, v, -h);
        f(t, r, v, D[i], pAux);
    }

    //Compute backwards differences
    for(i = 1; i <= m - 1; i++) {
        for(j = m - 1; j >= i; j--)
            D[j] = D[j-1] - D[j];
    }

    //Initialize backwards sum using 4th order GJ correctior
    S1 = v_0/h;
    for(i = 1; i <= m; i++)
        S1 -= gc[i]*D[i-1];
    
    S2 = r_0/(h*h) - dc[1]*S1;
    for(i = 2; i <= m + 1; i++)
        S2 -= dc[i]*D[i-2];
}

/**
 * Step from t to t+h
*/
void GJ4P::step(double& t, Vector& r, Vector& v) {
    //Order of method
    const int m = 4;

    // Coefficients gamma/delta of 1st/2nd order Bashforth/Stoermr predictor
    const double gp[m+1] = {+1.0, +1/2.0, +5/12.0,  +3/8.0, +251/720.0 };
    const double dp[m+2] = {+1.0,    0.0, +1/12.0, +1/12.0,  +19/240.0,  +3/40.0 };

    int i;

    //4th order predictor
    r_p = dp[0]*S2;
    for(i = 2; i <= m + 1; i++)
        r_p += dp[i]*D[i-2];
    r_p = (h*h)*r_p;

    v_p = gp[0]*S1;
    for(i = 1; i <= m; i++)
        v_p += gp[i]*D[i-1];
    v_p = h*v_p;

    //Update backwarsd difference table
    f(t + h, r_p, v_p, d[0], pAux);                     //Acceleration at t+h
    for(i = 1; i <= m - 1; i++)
        d[i] = d[i-1] - D[i-1];                         //New differences at t+h
    for(i = 0; i <= m - 1; i++)
        D[i] = d[i];                                    //Update differences
    S1 += d[0];                                         //Update sums
    S2 += S1;

    //Update independent variable and solution
    t = t + h;
    r = r_p;
    v = v_p;
}

#endif