//pragma once
#include <cmath>
#include <vector>
#include <functional>

struct Approximator {
    int degree;
    double a, b;
    int n_intervals, n_nodes;

    Approximator(int degree_, double a_, double b_, int intervals, int nodes);
    
    std::vector<double> approximate(std::function<double(double)> f);
    double evaluate(const std::vector<double>& coeffs, double x);
    void test_accuracy(std::function<double(double)> f, const std::vector<double>& coeffs);
};