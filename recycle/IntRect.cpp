// File: IntRect.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 28-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cmath>
#include <SDL2/SDL.h>

// Private
#include "nnb/utils/IntRect.hpp"
#include "nnb/utils/FloatRect.hpp"

nnb::IntRect::IntRect(nnb::FloatRect const rect) {
	x = floor(rect.x);
	y = floor(rect.y);
	w = floor(rect.w);
	h = floor(rect.h);
}

SDL_Rect nnb::IntRect::toSDLRect() const {
	SDL_Rect result;
	result.x = x;
	result.y = y;
	result.w = w;
	result.h = h;

	return result;
}
