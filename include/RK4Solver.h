#pragma once

#include <vector>
#include <functional>
#include <mutex>

// xi : initial x value
// yi : initial y value
// xf : final x value

class RK4Solver{
    public:
        RK4Solver(double dh); // dh : step size
        std:: vector<double> solve(std::function<double(double, double)> f, double xi, double yi, double xf, int num_threads = 4);
    private:
        double dh;
        double rk4_step(std::function<double(double, double)> f, double xi, double yi);
        std::mutex y_vector_mtx; // mutex for solve_vector to ensure read write operations
};