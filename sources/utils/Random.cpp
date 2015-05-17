// File: Random.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-17
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/utils/Random.hpp"

namespace nnb {
	thread_local randutils::mt19937_rng rng;
}
