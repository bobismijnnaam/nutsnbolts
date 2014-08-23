// File: StringHelpers.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <vector>
#include <string>

// Private
#include "nnb/utils/StringHelpers.hpp"

namespace nnb {

	std::vector<std::string> split(std::string input, std::string delimiter) {
		std::vector<std::string> result;
		if (input.find(delimiter) == std::string::npos) return {};
		result.push_back("");

		for (char c : input) {
			std::string s(1, c);
			if (s == delimiter) {
				result.push_back("");
			} else {
				result[result.size() - 1] = result.back() + s;
			}
		}

		return result;
	}

	bool endsWith(std::string input, std::string suffix) {
		if (suffix.size() > input.size()) {
			return false;
		}

		if (suffix.empty() && input.empty()) {
			return true;
		}
		
		int j = input.size() - 1;
		for (int i = suffix.size() - 1; i >= 0; i--) {
			if (suffix[i] != input[j])
				return false;

			j--;
		}

		return true;
	}

	bool contains(std::string input, std::string query) {
		return input.find(query, 0) != std::string::npos;
	}

}
