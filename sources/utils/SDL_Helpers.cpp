// File: SDL_Helpers.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 21-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cstring>

// Private
#include "nnb/utils/SDL_Helpers.hpp"
#include "nnb/resources/CustomDeleters.hpp"

bool nnb::pointInRect(SDL_Point p, SDL_Rect r) {
	if (p.x >= r.x && p.x <= r.x + r.w) {
		if (p.y >= r.y && p.y <= r.y + r.h) {
			return true;
		}
	}

	return false;
}

std::unique_ptr<SDL_Surface, nnb::SDLDeleter> nnb::imageToSDL_Surface(nnb::Image const & img) {
	auto surf = SDL_CreateRGBSurface(0, img.getWidth(), img.getHeight(), 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	SDL_LockSurface(surf);
	std::memcpy(surf->pixels, img.getBuffer(), img.getWidth() * img.getHeight() * 4);
	SDL_UnlockSurface(surf);

	return std::unique_ptr<SDL_Surface, nnb::SDLDeleter>(surf);
}
