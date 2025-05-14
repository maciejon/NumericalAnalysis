#include <cmath>

#include <differential_equation.hpp>

using namespace std;

double f_sphere_cooling(double t, double T){
    return (-27 * pow(10,-12) * pow(T,4));
}

//f - y'=f, n-ilosc przedzialow, a-b przedzial calkowania, y0 - poczatkowy y
double euler_diff(std::function<double(double, double)> f_diff, int n, double a, double b, double y0){
    double step = (b-a)/n;
    double y=y0;
    for (double xi = a; xi <= b; xi += step){
        y = y + step * f_diff(xi,y);
    }
    return y;
}

double heun_diff(std::function<double(double, double)> f_diff, int n, double a, double b, double y0){
    double y = y0;
    double step = (b-a)/n;

    for (double xi = a; xi <= b; xi += step){
        double y_euler = y + step * f_diff(xi,y);
        y = y + step/2 * (f_diff(xi, y) + f_diff(xi+step, y_euler));
    }
    return y;
}