#include <nonlinear_equations.hpp>
#include <math.h>
using namespace std;

double fn1(double x){
    return log(x+1) - 1/(x+3);
}

double fn2(double x){
    return x*x*x + 30*cos(x) - 1/x;
}

double fn3(double x){
    return sin(3*M_PI*x)/(x+2) + 1/(x+4);
}

double dfn1(double x){
    return 1/((x+3)*(x+3))+1/(x+1);
}

double dfn2(double x){
    return -30*sin(x)+3*x*x+1/(x*x);
}

double dfn3(double x){
    return (3*M_PI*(x+2)*cos(3*M_PI*x)-sin(3*M_PI*x))/((x+2)*(x+2))-1/((x+4)*(x+4));
}

double df_num(std::function<double(double)> f, double x, double h=1e-6){
    return (f(x+h)-f(x-h)) / (h*2);
}

double bisection(std::function<double(double)> f, double a, double b, double tol) {
    if (f(a) * f(b) >= 0) {
        return NAN; // Root not bracketed
    }

    double c;
    while ((b - a) / 2.0 > tol) {
        c = (a + b) / 2.0;
        double fc = f(c);

        if (std::fabs(fc) < tol) {
            return c;
        }

        if (f(a) * fc < 0)
            b = c;
        else
            a = c;
    }

    return (a + b) / 2.0;
}

// Newton-Raphson Method
double newtons_nonlinear(std::function<double(double)> f, std::function<double(double)> df, double x0, double tol, int max_iter) {
    double x = x0;

    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (std::fabs(dfx) < tol) {
            return NAN; // Division by near-zero
        }

        double x_new = x - fx / dfx;

        if (std::fabs(x_new - x) < tol) {
            return x_new;
        }

        x = x_new;
    }

    return NAN; // No convergence
}

// Secant Method
double secants(std::function<double(double)> f, double x0, double x1, double tol, int max_iter) {
    double f0 = f(x0);
    double f1 = f(x1);

    for (int i = 0; i < max_iter; ++i) {
        if (std::fabs(f1 - f0) < tol) {
            return NAN; // Division by near-zero
        }

        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);

        if (std::fabs(x2 - x1) < tol) {
            return x2;
        }

        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f(x1);
    }

    return NAN; // No convergence
}
