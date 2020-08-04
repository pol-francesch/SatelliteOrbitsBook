#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <vector>

#define MU 3.9860044188e14 //m^3/s^2

double norm(std::vector<double> array);
double inner_prod(std::vector<double> arr1, std::vector<double> arr2);
std::vector<double> orb_elements(std::vector<double> r, std::vector<double> rdot);

int main() {
    std::vector<double> r = {10000.0e3,40000.0e3,-5000.0e3}; //m
    std::vector<double> rdot = {-1.5e3,1.0e3,-0.1e3}; //m/s
    std::vector<double> elems = orb_elements(r,rdot);
    
    std::cout<< "Semi-major axis\t\t" << elems.at(0)/1000 << " km"<<std::endl;
    std::cout<< "Eccentricity\t\t" << elems.at(1)<<std::endl;
    std::cout<< "Inclination\t\t" << elems.at(2) << " deg"<<std::endl;
    std::cout<< "RA ascening node\t" << 180+elems.at(3) << " deg"<<std::endl;
    std::cout<< "Arg of perigee\t\t" << elems.at(4) << " deg"<<std::endl;
    std::cout<< "Mean anomaly\t\t" << elems.at(5) << "deg"<<std::endl;
    
    return 0;
}


double norm(std::vector<double> array) {
    double normx = 0;
    int size = array.size();    
    for (int i=0; i < size; i++) 
        normx += array.at(i)*array.at(i);
    
    normx = sqrt(normx);
    return normx;
}

double inner_prod(std::vector<double> arr1, std::vector<double> arr2) {
    double inner = 0;
    int size = arr1.size();
    if (size != arr2.size())
        return -1;
    for (int i=0; i<size; i++)
        inner += arr1.at(i)*arr2.at(i);
    
    return inner;
}

std::vector<double> orb_elements(std::vector<double> r, std::vector<double> rdot) {
    double normr = norm(r);
    double normv = norm(rdot);
    double inner = inner_prod(r,rdot);
    
    std::vector<double> h = {r.at(1)*rdot.at(2)-r.at(2)*rdot.at(1), r.at(2)*rdot.at(0)-r.at(0)*rdot.at(2), r.at(0)*rdot.at(1)-r.at(1)*rdot.at(0)};
    double normh = norm(h);
    std::vector<double> W = {h.at(0)/normh, h.at(1)/normh, h.at(2)/normh};
    
    double inc = atan(sqrt(W.at(0)*W.at(0)+W.at(1)*W.at(1))/W.at(2))*180/M_PI;
    double omega = atan(W.at(0)/(-W.at(1)))*180/M_PI;
    double p = normh*normh/MU;
    
    double am = 1/(2/normr-(normv*normv/MU)); //m
    double n = sqrt(MU/pow(am,3));
    double ecc = sqrt(1-p/am);
    
    double E = M_PI + atan((inner/(am*am*n))/(1-normr/am));
    double M = (E - ecc*sin(E))*180/M_PI;
    
    double u = atan(r.at(2)/(-r.at(0)*W.at(1)+r.at(1)*W.at(0)));
    double v = atan((sqrt(1-ecc*ecc)*sin(E))/(cos(E)-ecc));
    double w = (u-v)*180/M_PI;
    
    std::vector<double> elements = {am, ecc,inc,omega,w,M};
    
    return elements;
}