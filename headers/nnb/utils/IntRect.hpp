// File: IntRect.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 24-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_INTRECT_HPP
#define NNB_INTRECT_HPP

// Public
#include <SDL2/SDL.h>

// Private

namespace nnb {

	struct FloatRect;

	struct IntRect {
		IntRect() {}

		IntRect(nnb::FloatRect const rect);

		int x = 0, y = 0, w = 0, h = 0;

		SDL_Rect toSDLRect() const;
	} ;

}

#endif
