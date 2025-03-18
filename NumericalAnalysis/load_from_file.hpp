#pragma once
#include <vector>
#include <string>

struct function_data {
	std::vector<float> x;
	std::vector<float> y;
};

function_data load_from_file(std::string file_name);