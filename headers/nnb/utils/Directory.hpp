// File: Directory.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: sa 16-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_DIRECTORY_HPP
#define NNB_DIRECTORY_HPP

// Public
#include <string>
#include <vector>

// Private

namespace nnb {

	std::vector<std::string> getFiles(std::string tgtDir, std::string suffix); 
	std::string fileFromPath(std::string path);

}

#endif
