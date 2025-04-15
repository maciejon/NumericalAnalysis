#include "newton_interpolation.hpp"
#include <math.h>
using namespace std;

float polynomialValue(const vector<float>& a, double x, int n) {
    float result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = a[i];
        for (int j = 0; j < i; j++) {
            term *= x;
        }
        result += term;
    }
    return result;
}

float hornerValue(const vector<float>& a, double x, int n) {
    // return x * std::pow(std::cos(x), 3);
    float result = 0.0;
    for (int i = n - 1; i >= 0; i--) {
        result = result * x + a[i];
    }
    return result;
}

vector<float> newtonCoefficients(const vector<float>& x, const vector<float>& y) {
    int n = x.size();
    vector<vector<float> > dividedDifferences(n, vector<float>(n, 0.0));
    vector<float> coefficients(n, 0.0);

    for (int i = 0; i < n; i++) {
        dividedDifferences[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            dividedDifferences[i][j] = (dividedDifferences[i + 1][j - 1] - dividedDifferences[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        coefficients[i] = dividedDifferences[0][i];
    }

    return coefficients;
}

double newtonInterpolation(const vector<float> x, const vector<float> coefficients, float inputValue) {
    float result = coefficients[0];
    float term = 1.0;

    for (int i = 1; i < x.size(); i++) {
        term *= (inputValue - x[i - 1]);
        result += coefficients[i] * term;
    }
    return result;
}