#include "load_from_file.hpp"
#include "lagrange_interpolation.hpp"
#include "mean_squared_error.hpp"
#include "newton_interpolation.hpp"
#include "gauss_elimination.hpp"
#include "integrate.hpp"
#include "gauss_legendre.hpp"
#include "approximate.hpp"
#include "differential_equation.hpp"
#include <nonlinear_equations.hpp>
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;

void lagrange_interpolation_main(int step);
void newton_main(int step);
void gauss_main();
void integrate1_main();
void gauss_legendre_main();
void approximate_main(int degree);
double f4(double x);
void differential_equation_main();

int main() {

    double a = -3;
    double b_startowe = 3;
    int ilosc_miejsc_zerowych = 0;
    for (a;a<b_startowe;a+=0.01){
    double b = a + 0.01;
    // double b = b_startowe;
    #define FNC fn22
    #define DFNC dfn1
    double root_bisection = bisection(FNC,a,b);
    // double root_newton = newtons_nonlinear(FNC,DFNC,a);
    double root_newton_num = newtons_nonlinear_numeric(FNC,a);
    double root_secants = secants(FNC,a,b);
    double root_falsi = falsi(FNC,a,b,ilosc_miejsc_zerowych,1e-3);
    // if(isfinite(root_bisection) && isfinite(root_secants)){
    if(isfinite(root_falsi)){
        cout << "Zakres " << a << " -> " << b << ". " << endl;
        // cout << "Miejsca zerowe: " << endl;
        // cout << "Miejsce zerowe:: " << root_falsi << endl;
        // cout << root_falsi << endl;
        cout << "Bisekcja: " << root_bisection << " Blad: " << abs(FNC(root_bisection)) << endl;
        cout << "Newton:   " << root_newton_num << " Blad: " << abs(FNC(root_newton_num)) << endl;
        cout << "Sieczne:  " << root_secants << " Blad: " << abs(FNC(root_secants)) << endl;
        cout << "Falsi:    " << root_falsi << " Blad: " << abs(FNC(root_falsi)) << endl;
        // cout << "\n";
        ilosc_miejsc_zerowych++;
        }
    }
    cout << "Ilosc miejsc zerowych: " << ilosc_miejsc_zerowych << endl;
    return 0;
}












void differential_equation_main(){
    double a = 0;
    double b = 2027;
    double y0 = 2027;
    double exact_temperature = 182.57481; // alfa=-27,time=2027

    std::ofstream file("diff_cooling_results.csv");
    std::ofstream file2("diff_errors_results.csv");
    // for (b;b>=1;b-=1){
    // for (int steps =266;steps<=1000;steps++){
    for (int steps : {300,500,1000,10000}){
        cout << "Ilosc przedzialow " << steps << ": " << endl;

        double T = euler_diff(f_sphere_cooling,steps,a,b,y0);
        double squared_error = (T-exact_temperature)*(T-exact_temperature);

        cout << "Euler T ------- " << T << ", blad: " << squared_error << endl;

        T = heun_diff(f_sphere_cooling,steps,a,b,y0);
        squared_error = (T-exact_temperature)*(T-exact_temperature);

        cout << "Heun T -------- " << T << ", blad: " << squared_error << endl;

        T = midpoint_diff(f_sphere_cooling,steps,a,b,y0);
        squared_error = (T-exact_temperature)*(T-exact_temperature);

        cout << "Midpoint T ---- " << T << ", blad: " << squared_error << endl;

        T = runge_kutta_diff(f_sphere_cooling,steps,a,b,y0);
        squared_error = (T-exact_temperature)*(T-exact_temperature);

        cout << "Runge Kutta T - " << T << ", blad: " << squared_error << endl;

        cout << endl;
    }
    file << "t,Euler T,Heun T,Midpoint T,Runge Kutta T\n";
    for (b;b>=1;b-=1){
        file << b << "," << euler_diff(f_sphere_cooling,1000,a,b,y0) << ","<< heun_diff(f_sphere_cooling,1000,a,b,y0) << "," << midpoint_diff(f_sphere_cooling,1000,a,b,y0) << "," << runge_kutta_diff(f_sphere_cooling,1000,a,b,y0) << endl;
    }
    file << "0,2027,2027,2027,2027\n";

    b=2027;
    file2 << "steps,Error Euler,Error Heun,Error Midpoint,Error Runge Kutta\n";
    for (int steps = 300; steps<=1000;steps++){
        file2 << steps << "," << pow(euler_diff(f_sphere_cooling,steps,a,b,y0)-exact_temperature,2) << ","<< pow(heun_diff(f_sphere_cooling,steps,a,b,y0)-exact_temperature,2) << "," << pow(midpoint_diff(f_sphere_cooling,steps,a,b,y0)-exact_temperature,2) << "," << pow(runge_kutta_diff(f_sphere_cooling,steps,a,b,y0)-exact_temperature,2) << endl;
    }

}

void approximate_main(int degree)
{
    Approximator approx(degree, -1, 2, 10, 4);
    auto coeffs = approx.approximate(f4);
    approx.test_accuracy(f4, coeffs);
}

double f4(double x){
    return (exp(x) * cos(5*x) - x*x*x);
}

void gauss_legendre_main(){

    double exact1 = -10.1010101105917;

    for (int intervals : {1,2,3,5,10,20,50,100,1000}){
        for (int n : {2, 3, 4}) {
            double result = section_integrate(f1, 1, 4.764798248, intervals, n);
            cout << "ilosc przedzialow: " << intervals << endl;
            cout << "n = " << n << ", wynik = " << result << "\n";
            cout << "blad = " << abs(result-exact1) << endl;
        }
        cout << endl;
    }

    cout << "------------------------------------------------ DRUGA FUNKCJA ------------------------------------------------\n\n";

    double exact2 = -9876.54321007546; 
    for (int intervals : {1,2,3,5,10,20,50,100,1000}){
        for (int n : {2, 3, 4}) {
            double result = section_integrate(f2, -2, 3.20870913294, intervals, n);
            cout << "ilosc przedzialow: " << intervals << endl;
            cout << "n = " << n << ", wynik = " << result << "\n";
            cout << "blad = " << abs(result-exact2) << endl;
        }
        cout << endl;
    }
    
    cout << "------------------------------------------------ TRZECIA FUNKCJA ------------------------------------------------\n\n";

    double exact3 = -1656.08333;
    for (int intervals : {1,2,3,5,10,20,50,100,1000}){
        for (int n : {2, 3, 4}) {
            double result = section_integrate(f3, -4, 3, intervals, n);
            cout << "ilosc przedzialow: " << intervals << endl;
            cout << "n = " << n << ", wynik = " << result << "\n";
            cout << "blad = " << abs(result-exact3) << endl;
        }
        cout << endl;
    }

}

void integrate1_main(){
        ifstream file("kwadratury_gr_4.txt");
    if (!file) {
        cerr << "Nie mozna otworzyc pliku.\n";
    }

    int stopien;
    file >> stopien;

    std::vector<float> wspolczynniki(stopien + 1);
    for (int i = 0; i <= stopien; ++i) {
        file >> wspolczynniki[i];
    }

    double a, b;
    file >> a >> b;

    // a = 3.5;
    // b = 6.52968912439344;

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "\nWyniki metod i czasy ich wykonania:\n";
    std::cout << "n\tProstokaty\tt us]\tTrapezy\t\tt [us]\tSimpson\t\tt [us]\n";

    float dokladny_wynik = -1656.08333; //z mathDF
    // float dokladny_wynik = 4.202; // dla calki z cos
    int rozmiary_przedzialow[] = { 5, 10, 20, 40, 80, 160, 320, 640, 1000, 10000, 100000, 1000000 };

    for (int n : rozmiary_przedzialow) {
        auto t1_start = chrono::high_resolution_clock::now();
        double I1 = prostokaty(wspolczynniki, a, b, n);
        auto t1_end = chrono::high_resolution_clock::now();
        auto t1_time = chrono::duration_cast<chrono::microseconds>(t1_end - t1_start).count();

        auto t2_start = chrono::high_resolution_clock::now();
        double I2 = trapezy(wspolczynniki, a, b, n);
        auto t2_end = chrono::high_resolution_clock::now();
        auto t2_time = chrono::duration_cast<chrono::microseconds>(t2_end - t2_start).count();

        auto t3_start = chrono::high_resolution_clock::now();
        double I3 = simpson(wspolczynniki, a, b, n);
        auto t3_end = chrono::high_resolution_clock::now();
        auto t3_time = chrono::duration_cast<chrono::microseconds>(t3_end - t3_start).count();

        std::cout << n << "\t"
                  << I1 << "\t" << t1_time << "\t"
                  << I2 << "\t" << t2_time << "\t"
                  << I3 << "\t" << t3_time << "\n";
    }

    std::cout << "\nBledy:\n";
    std::cout << "n\tProstokaty\tTrapezy\t\tSimpson\n";
    for (int n : rozmiary_przedzialow) {
        double I1 = prostokaty(wspolczynniki, a, b, n) - dokladny_wynik;
        double I2 = trapezy(wspolczynniki, a, b, n) - dokladny_wynik;
        double I3 = simpson(wspolczynniki, a, b, n) - dokladny_wynik;
        std::cout << n << "\t" << I1 << "\t" << I2 << "\t" << I3 << "\n";
    }
}

void gauss_main(){
gauss_data gauss = load_from_file_gauss("gauss_elimination_gr4_A.txt");
    for (int i=0;i<5;i++){
        for (int j=0; j<5;j++){
            cout << gauss.A[i][j] << " ";
        }
        cout << "|" << gauss.b[i] << endl;
    }
    cout << endl;
    gauss.partial_pivot();
    vector<double> solution = gauss.back_substitute();
    gauss.verify_solution(solution);

    cout << "Wynik: " << endl;
    for (int i=0;i<5;i++){
        cout << "X" << i << " = " << solution[i] << " ";
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

