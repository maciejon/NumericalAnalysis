#include <iostream>
#include <functional>
#include <cmath>

# define M_PI 3.14159265358979323846

double fn1(double x);
double fn2(double x);
double fn3(double x);
double dfn1(double x);
double dfn2(double x);
double dfn3(double x);

double fn21(double x);
double fn22(double x);
double fn23(double x);

double bisection(std::function<double(double)> f, double a, double b, double tol = 1e-6);
double secants(std::function<double(double)> f, double a, double b, double tol = 1e-7, int max_iter = 100);
double newtons_nonlinear(std::function<double(double)> f, std::function<double(double)> df, double x, double tol = 1e-7, int max_iter = 100);
double falsi(std::function<double(double)> f, double a, double b, double tol = 1e-7, int max_iter = 7);
