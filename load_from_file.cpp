#include "load_from_file.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;



function_data load_from_file(string file_name)
{
    ifstream file;
    file.open(file_name);
    string line;
    char del = '\t';

    if (file.is_open())
    {
        int line_number = 0;
        function_data function_data;

        while (getline(file, line))
        {
            if (line_number == 0) {
                stringstream ss(line);
                string line1_content;

                int i = 0;
                while (getline(ss, line1_content, del)) {
                        function_data.x.push_back(stof(line1_content));
                        i++;
                }
            }

            if (line_number == 1) {
                stringstream ss(line);
                string line2_content;

                int i = 0;
                while (getline(ss, line2_content, del)) {
                    function_data.y.push_back(stof(line2_content));
                    i++;
                }
            }
            line_number++;
        }
        file.close();
        return function_data;
    }
    else
    {
        cout << "Cannot open file.";
        function_data error;
        error.x.push_back(0);
        error.y.push_back(0);
        return error;
    }
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