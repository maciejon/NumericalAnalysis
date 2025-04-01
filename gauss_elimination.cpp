#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "gauss_elimination.hpp"
using namespace std;

gauss_data::gauss_data(int size) : n(size), A(size, std::vector<int>(size)), b(size) {}

void gauss_data::print_matrix() {
        for (int i=0;i<5;i++){
            for (int j=0; j<5;j++){
                cout << A[i][j] << " ";
            }
            cout << "|" << b[i] << endl;
        }
}

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