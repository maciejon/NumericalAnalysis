#pragma once
#include <vector>
#include <string>

struct function_data {
	std::vector<float> x;
	std::vector<float> y;
};

class gauss_data {
public:
    int n; // liczba równań
    std::vector<std::vector<int> > A; // główna macierz
    std::vector<int> b; // wyrazy wolne

    gauss_data(int size) : n(size), A(size, std::vector<int>(size)), b(size) {}
};

gauss_data load_from_file_gauss(std::string file_name);
function_data load_from_file(std::string file_name);