// File: TextureGroup.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-28
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_TEXTUREGROUP_HPP
#define NNB_TEXTUREGROUP_HPP

// Public
#include <string>

// Private
#include "TextureManager.hpp"

namespace nnb {

	class TextureGroup {
	public:
		TextureGroup(TextureManager& tm_, std::string group_);
		~TextureGroup();

	private:
		TextureManager& tm;
		std::string group;

	} ;
}

#endif // NNB_TEXTUREGROUP_HPP
