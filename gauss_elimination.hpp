#ifndef GAUSS_H
#define GAUSS_H

#include <vector>
#include <string>
#include <fstream>

class gauss_data {
public:
    int n; // liczba równań
    std::vector<std::vector<int> > A; // główna macierz
    std::vector<int> b; // wyrazy wolne

    gauss_data(int size=5);
    void partial_pivot();
    void print_matrix();
    std::vector<double> back_substitute();
    void verify_solution(const std::vector<double>& x);
};

// void load_from_file_gauss(const std::string filename, gauss_data& data);
gauss_data load_from_file_gauss(const std::string& filename);

#endif