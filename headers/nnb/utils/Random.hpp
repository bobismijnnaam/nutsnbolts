// File: Random.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-17
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_RANDOM_HPP
#define NNB_RANDOM_HPP

// Public

// Private
#include "nnb/utils/randutils.hpp"

namespace nnb {
	extern thread_local randutils::mt19937_rng rng;
}

#endif // NNB_RANDOM_HPP
