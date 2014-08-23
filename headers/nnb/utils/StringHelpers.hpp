// File: StringHelpers.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: sa 16-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_STRINGHELPERS_HPP
#define NNB_STRINGHELPERS_HPP

// Public
#include <string>
#include <vector>

// Private

namespace nnb {

	std::vector<std::string> split(std::string input, std::string delimiter);
	bool endsWith(std::string input, std::string suffix);
	bool contains(std::string input, std::string query);

}

#endif
