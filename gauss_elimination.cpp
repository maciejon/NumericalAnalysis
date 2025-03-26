#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "gauss_elimination.hpp"
using namespace std;

gauss_data::gauss_data(int size) : n(size), A(size, std::vector<int>(size)), b(size) {}

void gauss_data::print_matrix(std::vector<std::vector<int> > A) {
        for (int i=0;i<5;i++){
            for (int j; j<5;j++){
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
}

void gauss_data::partial_pivot() {
        for (int i = 0; i < n; i++) {
            int pivot_row = i;
            for (int j = i + 1; j < n; j++) {
                if (std::abs(A[j][i]) > std::abs(A[pivot_row][i])) {
                    pivot_row = j;
                }
            }
            
            if (pivot_row != i) {
                std::swap(A[i], A[pivot_row]);
                std::swap(b[i], b[pivot_row]);
            }
            
            for (int j = i + 1; j < n; j++) {
                if (A[i][i] == 0) continue;
                double factor = static_cast<double>(A[j][i]) / A[i][i];
                for (int k = i; k < n; k++) {
                    A[j][k] -= factor * A[i][k];
                }
                b[j] -= factor * b[i];
            }
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


gauss_data load_from_file_gauss(string file_name)
{
    ifstream file;
    file.open(file_name);
    string line;
    char del = '\t';

    if (file.is_open())
    {
        int line_number = 0;
        gauss_data gauss_data(5);

        while (getline(file, line))
        {
            if (line_number == 0) {
                gauss_data.n = stoi(line);
            }

            if (line_number == 1) {
                stringstream ss(line);
                string line1_content;

                while (getline(ss, line1_content, del)) {
                    gauss_data.b.push_back(stoi(line1_content));
                }
            }
            if (line_number == 2) {
                stringstream ss(line);
                string line2_content;
                // cout << "linia 2: " << endl;
                int i = 0;
                while (getline(ss, line2_content, del)) {
                    // cout << line2_content << endl;
                    for (int j = 0; j < gauss_data.n; j++)
                        for (int k = 0; k < gauss_data.n; k++){
                            gauss_data.A[j][k] = stoi(line2_content);
                        }
                    i++;
                }
            }
            line_number++;
        }
        file.close();
        return gauss_data;
    }
    else
    {
        cout << "Cannot open file.";
    }
}