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

	/**
	 * How to use these functions:
	 * getFiles 			- 	Expects a path to a directory, and an optional suffix to filter on file types
	 * fileExists			-	Expects a path to a file.
	 * folderFromPathToFile -	Returns the folder part of a path, given that the path leads to a file
	 * fileFromPathToFile	-	Return the file part of a path, given that the path leads to a file
	 *
	 * If a path leads to a file in the current working directory, use the unix notation of "./file_path.ext"
	 */

	std::vector<std::string> getFiles(std::string tgtDir, std::string suffix = "");
	std::vector<std::string> getFilesRecursively(std::string tgtDir);
	bool fileExists(std::string path);
	std::string folderFromPathToFile(std::string path);
	std::string fileFromPathToFile(std::string path);
}

#endif
