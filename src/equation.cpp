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