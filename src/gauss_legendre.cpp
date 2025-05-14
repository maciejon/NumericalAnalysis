#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>
#include <vector>

#include <gauss_legendre.hpp>

// przeksztalcanie przedzialu a-b na -1-1
double transform(double x, double a, double b) {
    return ((b - a) / 2) * x + (a + b) / 2;
}

double f1(double x) {
    return x*x*pow(sin(x),3);
}

double f2(double x) {
    return exp(x*x)*(1-x);
}

double f3(double x){
    return -5 + 5*x - x*x + 7*x*x*x -5*x*x*x*x;
}

double section_integrate(std::function<double(double)> f, double a, double b, int n_intervals, int n_nodes) {
    GaussLegendre gl(n_nodes);
    double total = 0.0;
    double h = (b - a) / n_intervals;

    for (int i = 0; i < n_intervals; ++i) {
        double x0 = a + i * h;
        double x1 = x0 + h;
        total += gl.integrate(f, x0, x1);
    }

    return total;
}
