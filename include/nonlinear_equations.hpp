#include <iostream>
#include <functional>
#include <cmath>

double fn1(double x);
double fn2(double x);
double fn3(double x);
double dfn1(double x);
double dfn2(double x);
double dfn3(double x);

double bisection(std::function<double(double)> f, double a, double b, double tol = 1e-6);
double secants(std::function<double(double)> f, double a, double b, double tol = 1e-6, int max_iter = 100);
double newtons_nonlinear(std::function<double(double)> f, std::function<double(double)> df, double x, double tol = 1e-6, int max_iter = 100);