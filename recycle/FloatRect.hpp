// File: FloatRect.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 24-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_FLOATRECT_HPP
#define NNB_FLOATRECT_HPP

// Public
#include <SDL2/SDL.h>

// Private

namespace nnb {

	struct IntRect;

	struct FloatRect {
		FloatRect() {}

		FloatRect(nnb::IntRect const rect);

		float x = 0, y = 0, w = 0, h = 0;

		SDL_Rect toSDLRect() const;
	} ;

}

#endif
