#include <nonlinear_equations.hpp>
#include <math.h>
#include <fstream>
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

double fn21(double x){
    return log10(x+1) - x*x*x;
}

double fn22(double x){
    return cosh(x) - sqrt(x*x) - 0.55;
}

double fn23(double x){
    return (cos(3*M_PI*x))/(x+1);
}

double df_num(std::function<double(double)> f, double x, double h=1e-6){
    return (f(x+h)-f(x-h)) / (h*2);
}

double bisection(std::function<double(double)> f, double a, double b, double tol) {
    // cout << "------------ BISEKCJA ------------" << endl;
    if (f(a) * f(b) >= 0) {
        return NAN;
    }

    double c;
    while ((b - a) / 2.0 > tol) {
        int i=0;
        c = (a + b) / 2.0;
        double fc = f(c);

        if (std::fabs(fc) < tol) {
            return c;
        }

        if (f(a) * fc < 0)
            b = c;
        else
            a = c;
        // cout << "Przyblizenie: " << c << endl;
        i++;
    }

    return (a + b) / 2.0;
}

double newtons_nonlinear(std::function<double(double)> f, std::function<double(double)> df, double x0, double tol, int max_iter) {
    // cout << "------------ NEWTON ANALITYCZNIE -" << endl;
    double x = x0;

    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (std::fabs(dfx) < tol) {
            return NAN;
        }

        double x_new = x - fx / dfx;

        if (std::fabs(x_new - x) < tol) {
            return x_new;
        }

        x = x_new;
        // cout << "Przyblizenie: " << x_new << endl;
    }

    return NAN;
}

double newtons_nonlinear_numeric(std::function<double(double)> f, double x0, double tol, int max_iter) {
    // cout << "------------ NEWTON NUMERYCZNIE --" << endl;
    double x = x0;

    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = df_num(f,x);

        if (std::fabs(dfx) < tol) {
            return NAN;
        }

        double x_new = x - fx / dfx;

        if (std::fabs(x_new - x) < tol) {
            return x_new;
        }

        x = x_new;
        // cout << "Przyblizenie: " << x_new << endl;
    }

    return NAN;
}

double secants(std::function<double(double)> f, double x0, double x1, double tol, int max_iter) {
    // cout << "------------ SIECZNE -------------" << endl;
    double f0 = f(x0);
    double f1 = f(x1);

    for (int i = 0; i < max_iter; ++i) {
        if (std::isnan(f0) || std::isinf(f0) || std::isnan(f1) || std::isinf(f1)) {
            return NAN;
        }

        double denominator = f1 - f0;
        if (std::fabs(denominator) < tol || std::isnan(denominator) || std::isinf(denominator)) {
            return NAN;
        }

        double x2 = x1 - f1 * (x1 - x0) / denominator;
        if (std::isnan(x2) || std::isinf(x2)) {
            return NAN;
        }

        double f2 = f(x2);
        if (std::isnan(f2) || std::isinf(f2)) {
            return NAN;
        }

        if (std::fabs(x2 - x1) < tol && std::fabs(f2) < tol) {
            return x2;
        }

        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f2;

        // cout << "Przyblizenie: " << x2 << endl;
    }
    return NAN;
}

double falsi(std::function<double(double)> f, double a, double b,int nr_miejsca_zerowego, double tol, int max_iter){
    // cout << "------------ FALSI ---------------" << endl;
    // ofstream file("root" + to_string(nr_miejsca_zerowego) + ".csv");
    if (f(a) * f(b) >= 0) {
        return NAN;
    }
    double c = a;

    for (int i = 0; i < max_iter; ++i) {
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        double fc = f(c);

        if (std::abs(fc) < tol) {
            // file << c << "," << f(c) << endl;
            return c;
        }

        if (f(a) * fc < 0) {
            b = c;
        } else {
            a = c;
        }
        if (isfinite(c)){
            // cout << "Przyblizenie: " << c << " Blad: " << f(c) << endl;
            // file << c << "," << f(c) << endl;
            // cout << c << endl;
        }
    }

    return c;
}