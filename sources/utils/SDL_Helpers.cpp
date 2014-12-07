// File: SDL_Helpers.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 21-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/utils/SDL_Helpers.hpp"

SDL_Color nnb::getSDL_Color(Color clr) {
	switch(clr) {
		case Color::RED:
			return {255, 0, 0, 255};
		case Color::GREEN:
			return {0, 255, 0, 255};
		case Color::BLUE:
			return {0, 0, 255, 255};
		case Color::YELLOW:
			return {255, 255, 0, 255};
		case Color::CYAN:
			return {0, 255, 255, 255};
		case Color::PURPLE:
			return {255, 0, 255, 255};
		case Color::WHITE:
			return {255, 255, 255, 255};
		case Color::BLACK:
			return {0, 0, 0, 255};
		default:
			NNB_LOG << "ERROR! Either a color is not yet defined or some crazy bug is crawling around";
			return {0, 0, 0, 0};
	}
}

bool nnb::pointInRect(SDL_Point p, SDL_Rect r) {
	if (p.x >= r.x && p.x <= r.x + r.w) {
		if (p.y >= r.y && p.y <= r.y + r.h) {
			return true;
		}
	}

	return false;
}
