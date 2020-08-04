#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

void iteration(float m, float e);
void newtons(float m, float e);

int main() {
    float e = 0.72;
    int m = 4;
    float m_rad = m*M_PI/180;
    iteration(m_rad,e);
    //newtons(m_rad,e);
    return 0;
}

//Solving Euler's formula using fixed point iteration
void iteration(float m, float e) {
    double delE = 10.0;
    int count = 0;
    double E0 = m;
    double E = 0;
    
    std::cout <<"Fixed Point iteration" <<std::endl;
    std::cout <<"i \t E \t\t delE" <<std::endl;
    
    
    while(delE > 1/pow(10.0,11.0)) {
        E = m + e*sin(E0);
        delE = abs(E-E0);
        count++;
        E0 = E;
        std::cout<< count << " \t " << E << " \t " << delE <<std::endl;
    }
    
    return;
}

//Solving Euler's formula using Newton's method
void newtons(float m, float e) {
    double delE = 10.0;
    int count = 0;
    double E0 = m;
    double E = 0;
    
    std::cout <<"Newton's Method iteration" <<std::endl;
    std::cout <<"i \t E \t\t delE" <<std::endl;
    
    
    while(delE > 1/pow(10.0,11.0)) {
        E = E0 - (E0-e*sin(E0)-m)/(1-e*cos(E0));
        delE = abs(E-E0);
        count++;
        E0 = E;
        std::cout<< count << " \t " << E << " \t " << delE <<std::endl;
    }
}