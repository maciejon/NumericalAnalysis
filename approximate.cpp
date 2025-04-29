#include "approximate.hpp"
#include "gauss_elimination.hpp"
#include "gauss_legendre.hpp"
#include <iostream>
#include <cmath>

Approximator::Approximator(int degree_, double a_, double b_, int intervals, int nodes) : degree(degree_), a(a_), b(b_), n_intervals(intervals), n_nodes(nodes) {}

std::vector<double> Approximator::approximate(std::function<double(double)> f) {
    gauss_data data(degree + 1);
    data.A.resize(degree + 1, std::vector<double>(degree + 1));
    data.b.resize(degree + 1);


    for (int i = 0; i <= degree; ++i) {
        data.b[i] = section_integrate([=](double x) {
            return f(x) * pow(x, i);
        }, a, b, n_intervals, n_nodes);

        for (int j = 0; j <= degree; ++j) {
            double val = section_integrate([=](double x) {
                return pow(x, i + j);
            }, a, b, n_intervals, n_nodes);
            data.A[i][j] = val;
        }
    }
    data.partial_pivot();
    std::vector<double> x = data.back_substitute();
    return x;
}

double Approximator::evaluate(const std::vector<double>& coeffs, double x) {
    double result = 0.0;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result += coeffs[i] * pow(x, i);
    }
    return result;
}

void Approximator::test_accuracy(std::function<double(double)> f, const std::vector<double>& coeffs) {
    std::cout << "\nPorownanie wartosci dokladnych i aproksymowanych:\n";
    for (double x = a; x <= b; x += 0.2) {
        double fx = f(x);
        double px = evaluate(coeffs, x);
        std::cout << "x = " << x << ", f(x) = " << fx << ", p(x) = " << px << ", blad = " << fabs(fx - px) << std::endl;
    }
}