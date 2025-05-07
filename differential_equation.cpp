#include "differential_equation.hpp"
using namespace std;

double f_sphere_cooling(double T){
    return (-5 * pow(10,-12) * pow(T,4));
}

//f - y'=f, n-ilosc przedzialow, a-b przedzial calkowania, y0 - poczatkowy y
double solve_diff(std::function<double(double)> f_diff, int n, double a, double b, double y0){
    double step = (b-a)/n;
    double y=y0;
    for (double xi = a; xi <= b; xi += step){
        y = y + step * f_diff(y);
    }
    return y;
}