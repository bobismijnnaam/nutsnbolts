// File: NullStream.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: fr 24-10-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include "nnb/utils/NullStream.hpp"

// Private

nnb::NullStream nnb::nullstream;

int nnb::NullBuffer::overflow(int c) {
	return c;
}

nnb::NullStream::NullStream() :
std::ostream(&m_sb) {
}
