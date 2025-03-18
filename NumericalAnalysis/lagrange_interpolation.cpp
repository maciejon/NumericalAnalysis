#include "lagrange_interpolation.hpp"

float interpolacja(std::vector<float> x, std::vector<float> f, int n, float xp) {
    float wynik = 0.0;

    for (int i = 0; i < n; i++) {
        float l = f[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                l *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        wynik += l;
    }
    return wynik;
}