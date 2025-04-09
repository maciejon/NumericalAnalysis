#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "newton_interpolation.hpp"
#include "integrate.hpp"
using namespace std;

// wspolczynniki, a do b: zakres calkowania, n: ilosc przedzialow
float prostokaty(const vector<float>& wspolczynniki, float a, float b, int n) {
    int stopien = wspolczynniki.size()-1;
    float h = (b - a) / n;
    float suma = 0.0;
    for (int i = 0; i < n; ++i) {
        float xi = a + i * h;
        suma += hornerValue(wspolczynniki, xi, stopien+1);
    }
    return suma * h;
}

float trapezy(const vector<float>& wspolczynniki, float a, float b, int n) {
    int stopien = wspolczynniki.size()-1;
    float h = (b - a) / n;
    float suma = (hornerValue(wspolczynniki, a, stopien + 1) + hornerValue(wspolczynniki, b, stopien + 1)) / 2.0;
    for (int i = 1; i < n; ++i) {
        float xi = a + i * h;
        suma += hornerValue(wspolczynniki, xi, stopien + 1);
    }
    return suma * h;
}

float simpson(const vector<float>& wspolczynniki, float a, float b, int n) {
    int stopien = wspolczynniki.size()-1;
    if (n % 2 != 0){
         n++;
    }

    float h = (b - a) / n;
    float suma = hornerValue(wspolczynniki, a, stopien + 1) + hornerValue(wspolczynniki, b, stopien + 1);

    for (int i = 1; i < n; ++i) {
        float xi = a + i * h;

        if (i % 2 == 0) {
            suma += hornerValue(wspolczynniki, xi, stopien + 1) * 2;
        }
        else {
            suma += hornerValue(wspolczynniki, xi, stopien + 1) * 4;
        }    
    }

    return suma * h / 3.0;
}