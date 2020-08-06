#ifndef _INTEGRATION_HPP_
#define _INTEGRATION_HPP_

#include "SAT_VecMat.h"

//Special struct used for rk4
typedef void(*RK4funct) (
    double x,               //Independent variables
    const Vector& y,        //State vector
    Vector& yp,             //Derivative y' = f(x,y)
    void* pAux              //Pointer to auxiliary data used within f
);

/**
 * Runge-kutta 4 type integrator
*/
class RK4 {
    private:
        //Elements
        RK4funct f;
        int n_eqn;
        void* pAux;
        Vector k_1, k_2, k_3, k_4;
    public:
        //Constructor
        RK4 (
            RK4funct f_,            //Differential equation
            int n_eqn_,             //Dimension
            void* pAux_             //Pointer to auxiliary data
        )
        : f(f_), n_eqn(n_eqn_), pAux(pAux_) {  
            k_4 = k_3 = k_2 = k_1 = Vector(n_eqn);
        };

        //Integration step
        void step(
            double& t,              //Value of independent variable; updated by t+h
            Vector& y,              //Value of y(t); updated by y(t+h)
            double h               //Step size
        );
};


#endif