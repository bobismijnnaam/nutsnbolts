// File: Directory.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include <dirent.h>
#include <vector>

// Private
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/utils/StringHelpers.hpp"

namespace nnb {

	std::vector<std::string> getFiles(std::string tgtDir, std::string suffix) {
		DIR *dir;
		struct dirent *ent;
		std::vector<std::string> dirs;

		if ((dir = opendir(tgtDir.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				std::string dirStr{ent->d_name};
				if ((suffix.empty() || nnb::endsWith(dirStr, suffix)) && dirStr != "." && dirStr != "..")   {
					dirs.push_back(dirStr);
				}
			}
			closedir(dir);
			return dirs;
		} else {
			NNB_LOG << "Error opening directory: \"" << tgtDir << "\"\n";
			return {};
		}
	}

	bool exists(std::string path) {
		auto folder = folderFromPath(path);
		auto file = fileFromPath(path);
		auto files = getFiles(folder);
		
		for (auto f : files) {
			if (f == file) {
				return true;
			}
		}

		return false;
	}

	std::string folderFromPath(std::string path) {
		std::tuple<std::string, std::string> result;
			
		if (nnb::contains(path, "\\")) {
			result = nnb::chopRight(path, "\\");
		} else if (nnb::contains(path, "/")) {
			result = nnb::chopRight(path, "/");
		} else {
			return "";
		}

		return std::get<0>(result);
	}

	std::string fileFromPath(std::string path) {
		std::vector<std::string> result;

		if (nnb::contains(path, "\\")) {
			result = nnb::split(path, "\\");
		} else if (nnb::contains(path, "/")) {
			result = nnb::split(path, "/");
		} else {
			return "";
		}

		if (result.size() > 0) {
			return result[result.size() - 1];
		} else {
			return "";
		}
	}

}
