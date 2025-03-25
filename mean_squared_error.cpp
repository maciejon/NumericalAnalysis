#include "mean_squared_error.hpp"
#include <iostream>

float mean_squared_error(std::vector<float> f, std::vector<float> g, int step)
{
    float error = 0;
    float sum = 0;
    int j = 0;

    for (int i = 0; i < f.size(); i++)
    {
        if ((i % step) != 0)
        {

            error = (f[i] - g[i]) * (f[i] - g[i]);
            // std::cout << "F: " << f[i] << ", Blad kwadratowy: " << error << std::endl;
            sum += (f[i] - g[i]) * (f[i] - g[i]);
            j++;
        }
    }
    error = sum / j;
    return error;
}