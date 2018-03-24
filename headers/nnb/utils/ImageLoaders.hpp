// File: ImageLoaders.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-06-11
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_IMAGE_LOADERS_HPP
#define NNB_IMAGE_LOADERS_HPP

// Public
#include <memory>
#include <string>

// Private

namespace nnb {
	std::unique_ptr<unsigned char[]> readPng(std::string file, int *imgWidth, int *imgHeight);
	bool writePng(unsigned char * buffer, int width, int height, std::string file);
	std::unique_ptr<unsigned char[]> readJpeg(std::string file, int *imgWidth, int *imgHeight);
	bool writeJpeg(unsigned char * buffer, int width, int height, std::string file, int quality = 90);
}

#endif // NNB_IMAGE_LOADERS_HPP
