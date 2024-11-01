#include "RK4Solver.h"

#include <thread>
#include <algorithm>

RK4Solver::RK4Solver(double dh): dh(dh){}

double RK4Solver::rk4_step(std::function<double(double, double)> f, double xi, double yi){
    // Runge-Kutta 4th order method
    double k1 = dh * f(xi, yi);
    double k2 = dh * f(xi + dh/2, yi + k1/2);
    double k3 = dh * f(xi + dh/2, yi + k2/2);
    double k4 = dh * f(xi + dh, yi + k3);
    return yi + (k1 + 2*k2 + 2*k3 + k4)/6;
}


std::vector<double> RK4Solver::solve(std::function<double(double, double)> f, 
                                   double xi, double yi, double xf, 
                                   int num_threads) {
    int steps = (xf - xi) / dh;
    std::vector<double> y_vector(steps + 1);
    y_vector[0] = yi;

    // For small step counts, use single-threaded approach
    if (steps < 1000) {
        double x = xi;
        for(int i = 0; i < steps; i++) {
            y_vector[i + 1] = rk4_step(f, x, y_vector[i]);
            x += dh;
        }
        return y_vector;
    }

    // Function for each thread to process its chunk
    auto thread_task = [&](int start_idx, int end_idx) {
        double x = xi + start_idx * dh;
        for(int i = start_idx; i < end_idx; i++) {
            double next_y = rk4_step(f, x, y_vector[i]);
            {
                std::lock_guard<std::mutex> lock(y_vector_mtx);
                y_vector[i + 1] = next_y;
            }
            x += dh;
        }
    };

    // Create and launch threads
    std::vector<std::thread> threads;
    int chunk_size = steps / num_threads;
    
    for(int i = 0; i < num_threads - 1; i++) {
        int start = i * chunk_size;
        int end = (i + 1) * chunk_size;
        threads.push_back(std::thread(thread_task, start, end));
    }

    // Handle last chunk in main thread
    thread_task((num_threads - 1) * chunk_size, steps);

    for(auto& thread : threads) {
        thread.join();
    }

    return y_vector;
}