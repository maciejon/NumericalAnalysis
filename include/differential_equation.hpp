#include <iostream>
#include <functional>

double f_sphere_cooling(double t, double T);
double euler_diff(std::function<double(double, double)> f_diff, int n, double a, double b, double y0);
double heun_diff(std::function<double(double, double)> f_diff, int n, double a, double b, double y0);