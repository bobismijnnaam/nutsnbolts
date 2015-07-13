// File: Directory.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-08-17
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include <dirent.h>
#include <vector>

// Private
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/utils/StringHelpers.hpp"

// TODO: (Possibly optional?) runtime checking of the format of the arguments of all the file paths and such

namespace nnb {

	/**
	 * For future reference, the types of d_type in struct dirent:
	 *
     * DT_BLK      This is a block device.
     * DT_CHR      This is a character device.
     * DT_DIR      This is a directory.
     * DT_FIFO     This is a named pipe (FIFO).
     * DT_LNK      This is a symbolic link.
     * DT_REG      This is a regular file.
     * DT_SOCK     This is a UNIX domain socket.
     * DT_UNKNOWN  The file type is unknown.
	 *
	 */

	std::vector<std::string> getFiles(std::string tgtDir, std::string suffix) {
		struct dirent *ent = nullptr;
		std::vector<std::string> dirs;
		DIR *dir = opendir(tgtDir.c_str());

		if (dir != NULL) {
			ent = readdir(dir);

			while (ent != NULL) {
				if (ent->d_type == DT_REG) {
					std::string dirStr{ent->d_name};
					if ((suffix.empty() || nnb::endsWith(dirStr, suffix))) {
						dirs.push_back(dirStr);
					}
				}

				ent = readdir(dir);
			}

			closedir(dir);

			return dirs;
		} else {
			NNB_ERROR << "Error opening directory: \"" << tgtDir << "\"\n";
			return {};
		}
	}

	std::vector<std::string> getFilesRecursively(std::string tgtDir, std::string suffix) {

		return {};
	}

	bool fileExists(std::string path) {
		std::string folder;
		if (nnb::contains(path, "\\") || nnb::contains(path, "/")) {
			folder = folderFromPathToFile(path);
		} else {
			folder = "./"
		}

		auto file = fileFromPathToFile(path);

		auto files = getFiles(folder);

		for (auto f : files) {
			if (f == file) {
				return true;
			}
		}

		return false;
	}

	std::string folderFromPathToFile(std::string path) {
		std::tuple<std::string, std::string> result;
			
		if (nnb::contains(path, "\\")) {
			result = nnb::chopRight(path, "\\");
		} else if (nnb::contains(path, "/")) {
			result = nnb::chopRight(path, "/");
		} else {
			NNB_ERROR << "\"" << path "\" is not a valid path to a file";
			return "";
		}

		return std::get<0>(result);
	}

	std::string fileFromPathToFile(std::string path) {
		std::tuple<std::string, std::string> result;

		if (nnb::contains(path, "\\")) {
			result = nnb::chopRight(path, "\\");
		} else if (nnb::contains(path, "/")) {
			result = nnb::chopRight(path, "/");
		} else {
			NNB_ERROR << "\"" << path "\" is not a valid path to a file";
			return "";
		}

		return std::get<0>(result);
	}

}
