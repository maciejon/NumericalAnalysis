#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "gauss_elimination.hpp"
using namespace std;

gauss_data::gauss_data(int size) : n(size), A(size, std::vector<int>(size)), b(size) {}

void print_matrix(std::vector<std::vector<float> > A){
    for (int i=0;i<5;i++){
            for (int j=0; j<5;j++){
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
}

std::vector<float> lu(gauss_data& data) {
    int n = data.n;
    std::vector<std::vector<float> > L(n, std::vector<float>(n, 0.0f));
    std::vector<std::vector<float> > U(n, std::vector<float>(n, 0.0f));

    //podzial na L i U
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            float sum = 0.0f;
            for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
            U[i][j] = data.A[i][j] - sum;
        }
        for (int j = i; j < n; j++) {
            if (i == j)
                L[i][i] = 1.0f;
            else {
                float sum = 0.0f;
                for (int k = 0; k < i; k++) sum += L[j][k] * U[k][i];
                L[j][i] = (data.A[j][i] - sum) / U[i][i];
            }
        }
        std::cout << "Iteracja " << i + 1 << " - Macierz L:" << std::endl;
        print_matrix(L);
        std::cout << "Iteracja " << i + 1 << " - Macierz U:" << std::endl;
        print_matrix(U);
    }

    std::cout << "Sprawdzanie poprawnosci rozkladu LU: L * U = A" << std::endl;
    std::vector<std::vector<float> > LU(n, std::vector<float>(n, 0.0f));
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                LU[i][j] += L[i][k] * U[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            if (abs(LU[i][j] - data.A[i][j]) > 0.00001f) {
                cout << "Blad w rozkladzie LU w polu ["<<i<<"] ["<<j<<"] ("<< LU[i][j] << " != " << data.A[i][j] << ")" << endl;
            }
            else {
                cout << "Brak bledow w polu ["<<i<<"] ["<<j<<"] ("<< LU[i][j] << " = " << data.A[i][j] << ")" << endl;
            }
        }
    }
    cout << "\nMacierz L * U: " << endl;
    print_matrix(LU);
    cout << "Oryginalna macierz A: " << endl;
    std::vector<std::vector<float> > A_float(data.n, std::vector<float>(data.n));
    for (int i = 0; i < data.n; i++)
        for (int j = 0; j < data.n; j++)
            A_float[i][j] = static_cast<float>(data.A[i][j]);
    print_matrix(A_float);

    std::vector<float> y(n, 0.0f);
    for (int i = 0; i < n; i++) {
        float sum = 0.0f;
        for (int k = 0; k < i; k++) sum += L[i][k] * y[k];
        y[i] = (data.b[i] - sum);
    }

    std::cout << "Rozwiazanie z (Ly = b): ";
    for (float val : y) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::vector<float> x(n, 0.0f);
    for (int i = n - 1; i >= 0; i--) {
        float sum = 0.0f;
        for (int k = i + 1; k < n; k++) sum += U[i][k] * x[k];
        x[i] = (y[i] - sum) / U[i][i];
    }

    std::cout << "Rozwiazanie x (Ux = z): ";
    for (float val : x) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Sprawdzanie poprawnosci: Ax = b" << std::endl;
    for (int i = 0; i < n; i++) {
        float sum = 0.0f;
        for (int j = 0; j < n; j++){
            sum += data.A[i][j] * x[j];
        }
        if (abs(sum - data.b[i]) > 0.00001f) {
            cout << "Blad w b[" << i << "], oczekiwane: " << data.b[i] << ", otrzymane: " << sum << endl;
        }
        else {
            std::cout << "Poprawne b[" << i << "] = " << data.b[i] << ", obliczone: " << sum << std::endl;
        }
    }
    return x;
}


void gauss_data::print_matrix() {
        for (int i=0;i<5;i++){
            for (int j=0; j<5;j++){
                cout << A[i][j] << " ";
            }
            cout << "|" << b[i] << endl;
        }
}











//GAUSS
void gauss_data::partial_pivot() {
        for (int i = 0; i < n; i++) {
            int pivot_row = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(A[j][i]) > abs(A[pivot_row][i])) {
                    pivot_row = j;
                }
            }
            
            if (pivot_row != i) {
                swap(A[i], A[pivot_row]);
                swap(b[i], b[pivot_row]);
            }
            
            for (int j = i + 1; j < n; j++) {
                if (A[i][i] == 0) continue;
                double factor = static_cast<double>(A[j][i]) / A[i][i];
                for (int k = i; k < n; k++) {
                    A[j][k] -= factor * A[i][k];
                }
                b[j] -= factor * b[i];
            }
            this->print_matrix();
            cout << endl;
        }
    }
    
    std::vector<double> gauss_data::back_substitute() {
        std::vector<double> x(n, 0);
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        return x;
    }


    gauss_data load_from_file_gauss(const std::string& filename) {
        gauss_data data(5);
        std::ifstream file(filename);
        
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return data;  // Return empty/invalid object
        }
    
        file >> data.n;
        data.b.resize(data.n);
        data.A.resize(data.n, std::vector<int>(data.n));
    
        for (int i = 0; i < data.n; ++i) {
            file >> data.b[i];
        }
    
        for (int i = 0; i < data.n; ++i) {
            for (int j = 0; j < data.n; ++j) {
                file >> data.A[i][j];
            }
        }
    
        return data;
    }
    
    void gauss_data::verify_solution(const vector<double>& x) {
        cout << "Sprawdzanie..." << endl;
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            if (abs(sum - b[i]) > 1e-6) {
                cout << "W wierszu " << i << " blad: " << sum << " != " << b[i] << endl;
            }
        }
        cout << "Sprawdzenie ukonczone." << endl;
    }