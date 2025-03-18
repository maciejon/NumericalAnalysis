#include "load_from_file.hpp"
#include "lagrange_interpolation.hpp"
#include "mean_squared_error.hpp"
#include <iostream>
using namespace std;

void old_main(int step) {
    function_data function_data_from_file = load_from_file("interpolacja_gr_4_ITE 1.txt");
    function_data function_data_for_interpolation;

    for (int i = 0; i < function_data_from_file.x.size(); i++)
    {
        if ((i % step) == 0)
        {
            function_data_for_interpolation.x.push_back(function_data_from_file.x[i]);
            function_data_for_interpolation.y.push_back(function_data_from_file.y[i]);
        }
    }

    vector<float> interpolated_function;

    for (int i = 0; i < function_data_from_file.x.size(); i++)
    {
        interpolated_function.push_back(interpolacja(function_data_for_interpolation.x, function_data_for_interpolation.y, function_data_for_interpolation.x.size(), function_data_from_file.x[i]));
    }

    /*for (int i = 0; i < function_data_from_file.x.size(); i++)
    {
        cout << "X: " << function_data_from_file.x[i] << " Zinterpolowane F :" << interpolated_function[i] << " Prawdziwe F: " << function_data_from_file.y[i] << endl;
    }*/

    float error = mean_squared_error(function_data_from_file.y, interpolated_function, step);

    cout << "Step: " << step << ", Sredni blad kwadratowy: " << error << endl;
}

int main() {
    for (int i = 2; i < 50; i++)
    {
        old_main(i);
    }
}