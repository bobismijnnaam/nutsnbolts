// File: SDL_Helpers.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-08-10
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_SDL_HELPERS_HPP
#define NNB_SDL_HELPERS_HPP

// Public
#include <SDL2/SDL.h>
#include <memory>

// Private
#include "nnb/log/log.hpp"
#include "nnb/resources/CustomDeleters.hpp"
#include "nnb/graphics/Image.hpp"

namespace nnb {
	bool pointInRect(SDL_Point p, SDL_Rect r);

	std::unique_ptr<SDL_Surface, nnb::SDLDeleter> imageToSDL_Surface(nnb::Image const & img);
}

#endif // NNB_SDL_HELPERS_HPP

