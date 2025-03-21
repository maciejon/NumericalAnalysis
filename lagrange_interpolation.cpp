#include "lagrange_interpolation.hpp"

float lagrange_interpolation(std::vector<float> x, std::vector<float> f, int n, float xp) {
    float result = 0.0;

    for (int i = 0; i < n; i++) {
        float l = f[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                l *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        result += l;
    }
    return result;
}