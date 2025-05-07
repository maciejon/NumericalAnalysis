#include <iostream>
#include <functional>

double f_sphere_cooling(double T);
double solve_diff(std::function<double(double)> f_diff, int n, double a, double b,double y0);