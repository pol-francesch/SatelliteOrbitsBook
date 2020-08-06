#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

#include "integration.hpp"

void RK4::step(double& t, Vector& y, double h) {
    //Elementary RK4 step
    f(t, y, k_1, pAux);
    f(t + h/2.0, y + (h/2.0)*k_1, k_2, pAux);
    f(t + h/2.0, y + (h/2.0)*k_2, k_3, pAux);
    f(t + h, y + h*k_3, k_4, pAux);

    y = y + (h/6.0) * (k_1 + 2.0*k_2 + 2.0*k_3 + k_4);

    //Update independent variable
    t = t + h;
}