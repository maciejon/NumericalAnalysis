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

    gauss_data(int size);
    void partial_pivot();
    void print_matrix(std::vector<std::vector<int> > A);
    std::vector<double> back_substitute();
};

gauss_data load_from_file_gauss(std::string file_name);

#endif