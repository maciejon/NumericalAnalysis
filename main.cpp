#include "load_from_file.hpp"
#include "lagrange_interpolation.hpp"
#include "mean_squared_error.hpp"
#include "newton_interpolation.hpp"
#include "gauss_elimination.hpp"
#include <iostream>
#include <chrono>
using namespace std;

void lagrange_interpolation_main(int step);
void newton_main(int step);

int main() {
    gauss_data gauss = load_from_file_gauss("gauss_elimination_gr4_A.txt");

    gauss.partial_pivot();

    for (int i=0;i<5;i++){
            for (int j; j<5;j++){
                cout << gauss.A[i][j] << " ";
            }
            cout << endl;
        }
}


















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

void newton_main(int step) {
    
    function_data function_data_from_file = load_from_file("interpolacja_H_gr_4.txt");

    for (unsigned int n = 3; n < function_data_from_file.x.size(); n++) {

        auto start_time = chrono::high_resolution_clock::now();
        for (int i = 0; i < function_data_from_file.y.size(); i++) {
            // cout << "X: " << function_data_from_file.y[i] << " Wartosc wielomianu: " << polynomialValue(function_data_from_file.x, function_data_from_file.y[i], n) << endl;
        }
        auto end_time = chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        // cout << "Czas obliczen metoda naturalna: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << "us dla n= " << n << endl;
    }

    cout << endl;
    for (unsigned int n = 3; n < function_data_from_file.x.size(); n++) {

        auto start_time = chrono::high_resolution_clock::now();
        for (int i = 0; i < function_data_from_file.y.size(); i++) {
            // cout << "X: " << function_data_from_file.y[i] << " Wartosc wielomianu hornerem: " << hornerValue(function_data_from_file.x, function_data_from_file.y[i], n) << endl;
        }
        auto end_time = chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        // cout << "Czas obliczen metoda hornera: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << "us dla n= " << n << endl;
    }
    function_data function_data_from_file_N = load_from_file("interpolacja_N_gr_4.txt");
    function_data function_data_for_newton;

    for (int i = 0; i < function_data_from_file_N.x.size(); i++)
    {
       if ((i % step) == 0)
       {
           function_data_for_newton.x.push_back(function_data_from_file_N.x[i]);
           function_data_for_newton.y.push_back(function_data_from_file_N.y[i]);
       }
    }


    vector<float> newtonCo = newtonCoefficients(function_data_for_newton.x, function_data_for_newton.y);
    
    // for (int i=0; i<newtonCo.size(); i++){
    //     cout << newtonCo[i] << endl;
    // }

    vector<float> newton_interpolated_function;

    for (int i=0; i < function_data_from_file_N.x.size(); i++){
       newton_interpolated_function.push_back(newtonInterpolation(function_data_for_newton.x,newtonCo,function_data_from_file_N.x[i]));
    }

    cout << "Sredni blad: " << mean_squared_error(newton_interpolated_function, function_data_from_file_N.y, step) << "  (wezly co " << step << " elementow)";

}

