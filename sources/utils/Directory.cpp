// File: Directory.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 20140817
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include <dirent.h>
#include <vector>
#include <algorithm>

// Private
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/utils/constants.hpp"

// TODO: (Possibly optional?) runtime checking of the format of the arguments of all the file paths and such
// Or just plain conversion from anything to frontslashed paths
// All the libraries understand that format anyway

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
		std::vector<std::string> files;
		DIR *dir = opendir(tgtDir.c_str());

		if (dir != nullptr) {
			ent = readdir(dir);

			while (ent != nullptr) {
				if (ent->d_type == DT_REG) {
					std::string fileStr{ent->d_name};
					if ((suffix.empty() || nnb::endsWith(fileStr, suffix))) {
						files.push_back(fileStr);
					}
				}

				ent = readdir(dir);
			}

			closedir(dir);

			return files;
		} else {
			NNB_ERROR << "Error opening directory: \"" << tgtDir << "\"\n";
			return {};
		}
	}

	std::vector<std::string> getFilesRecursively(std::string tgtDir) {
		if (!nnb::endsWith(tgtDir, DIRSEP)) {
			tgtDir += DIRSEP;
		}

		// Initialize some variables
		struct dirent *ent = nullptr;
		std::vector<std::string> files;
		DIR *dir = opendir(tgtDir.c_str());

		if (dir != nullptr) {
			ent = readdir(dir);

			while (ent != nullptr) {
				std::string dirStr{ent->d_name};

				if (ent->d_type == DT_REG) {
					files.push_back(dirStr);
				} else if (ent->d_type == DT_DIR && dirStr != "." && dirStr != "..") {
					std::string deeperDir = tgtDir + dirStr;

					auto deeperFiles = getFilesRecursively(deeperDir);

					std::for_each(deeperFiles.begin(), deeperFiles.end(), [=](std::string &file) {
						file = dirStr + DIRSEP + file;
					});

					files.insert(files.end(), deeperFiles.begin(), deeperFiles.end());
				}

				ent = readdir(dir);
			}

			return files;
		} else {
			NNB_ERROR << "Error opening directory: \"" << tgtDir << "\"\n";
			return {};
		}
	}

	bool fileExists(std::string path) {
		std::string folder;
		if (nnb::contains(path, DIRSEP)) {
			folder = folderFromPathToFile(path);
		} else {
			folder = "./";
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
		if (nnb::contains(path, DIRSEP)) {
			auto result = nnb::chopRight(path, DIRSEP);
			return std::get<0>(result);
		} else {
			return path;
		}
	}

	std::string fileFromPathToFile(std::string path) {
		if (nnb::contains(path, DIRSEP)) {
			auto result = nnb::chopRight(path, DIRSEP);
			return std::get<1>(result);
		} else {
			return path;
		}
	}

}
