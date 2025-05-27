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

double bisection(std::function<double(double)> f, double a, double b, double tol)
{
    if (f(a) * f(b) >= 0)
    {
        cout << "no root here";
        return INFINITY;
    }

    double c = a;
    while ((b-a) >= tol)
    {
        c = (a+b)/2;

        if (f(c) == 0.0)
            break;

        else if (f(c)*f(a) < 0)
            b = c;
        else
            a = c;
    }
return c;
}

double secants(std::function<double(double)> f, double a, double b, double tol, int max_iter) {
    double fa = f(a);
    double fb = f(b);
    
    if (abs(fa) < tol) return a;
    if (abs(fb) < tol) return b;

    for (int i = 0; i < max_iter; ++i) {
        
        double c = b - fb * (b - a) / (fb - fa);

        a = b;
        fa = fb;
        b = c;
        fb = f(b);

        if (abs(b - a) < tol || abs(fb) < tol)
            return b;
    }
    return INFINITY;
    // cout << "Secant method did not converge within max_iter." << endl;
}

double newtons_nonlinear(std::function<double(double)> f, std::function<double(double)> df, double x, double tol, int max_iter) {

    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (std::abs(dfx) < 1e-14)
            return INFINITY;

        double x_new = x - fx / dfx;

        if (std::abs(x_new - x) < tol || std::abs(f(x_new)) < tol)
            return x_new;

        x = x_new;
    }
}
