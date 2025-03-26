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

