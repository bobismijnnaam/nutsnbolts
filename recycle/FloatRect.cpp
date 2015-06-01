// File: FloatRect.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 28-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cmath>
#include <SDL2/SDL.h>

// Private
#include "nnb/utils/IntRect.hpp"
#include "nnb/utils/FloatRect.hpp"

nnb::FloatRect::FloatRect(nnb::IntRect const rect) {
	x = rect.x;
	y = rect.y;
	w = rect.w;
	h = rect.h;
}

SDL_Rect nnb::FloatRect::toSDLRect() const {
	SDL_Rect result;
	result.x = floor(x);
	result.y = floor(y);
	result.w = floor(w);
	result.h = floor(h);

	return result;
}
