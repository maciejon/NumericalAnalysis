#include <vector>

float polynomialValue(const std::vector<float>& a, double x, int n);
float hornerValue(const std::vector<float>& a, double x, int n);
std::vector<float> newtonCoefficients(const std::vector<float>& x, const std::vector<float>& y);
double newtonInterpolation(const std::vector<float> x, const std::vector<float> coefficients, float inputValue);