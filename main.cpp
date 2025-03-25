#include "load_from_file.hpp"
#include "lagrange_interpolation.hpp"
#include "mean_squared_error.hpp"
#include "newton_interpolation.hpp"
#include <iostream>
#include <chrono>
using namespace std;

void lagrange_interpolation_main(int step) {
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
       interpolated_function.push_back(lagrange_interpolation(function_data_for_interpolation.x, function_data_for_interpolation.y, function_data_for_interpolation.x.size(), function_data_from_file.x[i]));
   }

   /*for (int i = 0; i < function_data_from_file.x.size(); i++)
   {
       cout << "X: " << function_data_from_file.x[i] << " Zinterpolowane F :" << interpolated_function[i] << " Prawdziwe F: " << function_data_from_file.y[i] << endl;
   }*/

   float error = mean_squared_error(function_data_from_file.y, interpolated_function, step);

   cout << "Odleglosc miedzy wezlami: " << step << ", Sredni blad kwadratowy: " << error << endl;
}



int main() {

    function_data function_data_from_file = load_from_file("interpolacja_H_gr_4.txt");

    for (unsigned int n = 3; n < function_data_from_file.x.size(); n++) {

        auto start_time = chrono::high_resolution_clock::now();
        for (int i = 0; i < function_data_from_file.y.size(); i++) {
            polynomialValue(function_data_from_file.x, function_data_from_file.y[i], n);
        }
        auto end_time = chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        cout << "Czas obliczen metoda naturalna: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << "us dla n= " << n << endl;
    }

    cout << endl;
    for (unsigned int n = 3; n < function_data_from_file.x.size(); n++) {

        auto start_time = chrono::high_resolution_clock::now();
        for (int i = 0; i < function_data_from_file.y.size(); i++) {
            hornerValue(function_data_from_file.x, function_data_from_file.y[i], n);
        }
        auto end_time = chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        cout << "Czas obliczen metoda hornera: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << "us dla n= " << n << endl;
    }

    function_data function_data_from_file_N = load_from_file("interpolacja_N_gr_4.txt");
    function_data function_data_for_newton;

    int step = 5;

    for (int i = 0; i < function_data_from_file.x.size(); i++)
   {
       if ((i % step) == 0)
       {
           function_data_for_newton.x.push_back(function_data_from_file.x[i]);
           function_data_for_newton.y.push_back(function_data_from_file.y[i]);
       }
   }

    // vector<float> newtonCoefficients = newtonCoefficients()
}