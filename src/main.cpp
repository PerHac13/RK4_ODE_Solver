#include "RK4Solver.h"
#include "equation.h"

#include <iostream>

int main() {
    double dh = 0.01;
    double xi = 0, yi = 0.5 , xf = 1000;

    RK4Solver solver(dh);
    Equation eq;

    auto y_vector = solver.solve(eq.differentialEquation3, xi, yi, xf);

    for(int i = 0; i < y_vector.size(); i++){
        std::cout << "x: " << xi + i*dh << " \t y: " << y_vector[i] << std::endl;
    }

    return 0;
}