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
    double step = (b-a)/n; //step == h

    for (double xi = a; xi <= b; xi += step){
        double y_euler = y + step * f_diff(xi,y);
        y = y + step/2 * (f_diff(xi, y) + f_diff(xi+step, y_euler));
    }
    return y;
}

double midpoint_diff(std::function<double(double, double)> f_diff, int n, double a, double b, double y0){
    double y = y0;
    double step = (b-a)/n; //step == h

    for (double xi = a; xi <= b; xi += step){
        y = y + step * f_diff(xi+step/2,y+(step/2)*f_diff(xi,y));
    }
    return y;
}

double runge_kutta_diff(std::function<double(double, double)> f_diff, int n, double a, double b, double y0){
    double y = y0;
    double step = (b-a)/n; //step == h
    double k1,k2,k3,k4;
    for (double xi = a; xi <= b; xi += step){
        k1 = step * f_diff(xi,y);
        k2 = step * f_diff(xi+step/2,y + k1/2);
        k3 = step * f_diff(xi+step/2,y + k2/2);
        k4 = step * f_diff(xi+step,y+k3);

        y = y + (k1 + 2*k2 + 2*k3 + k4)/6;
    }
    return y;
}