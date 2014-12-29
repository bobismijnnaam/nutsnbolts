// File: TextureGroup.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-28
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/resources/TextureGroup.hpp"

nnb::TextureGroup::TextureGroup(TextureManager& tm_, std::string group_) :
tm(tm_),
group{group_} {
	tm.loadGroup(group);
}

nnb::TextureGroup::~TextureGroup() {
	tm.unloadGroup(group);
}
