#include <iostream>
#include <string>
#include <vector>
using namespace std;

// wspolczynniki wielomianu, a do b: zakres calkowania, n: ilosc przedzialow
float prostokaty(const vector<float>& wspolczynniki, float a, float b, int n);
float trapezy(const vector<float>& wspolczynniki, float a, float b, int n);
float simpson(const vector<float>& wspolczynniki, float a, float b, int n);
