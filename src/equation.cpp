#include "equation.h"
#include <cmath>

double Equation::differentialEquation1(double x, double y){
    return y+x+3;
}

double Equation::differentialEquation2(double x, double y){
    return 2*y-x*x+1;
}

double Equation::differentialEquation3(double x, double y){
    return y-x*x+1;
}


double Equation::harmonicOscillator(double x, double y) {
    return -y;  
}

double Equation::exponentialGrowth(double x, double y) {
    return y;  
}

double Equation::logisticGrowth(double x, double y) {
    return y * (1 - y);  
}

double Equation::pendulum(double x, double y) {
    return std::sin(y);  
}