// File: SDL_Helpers.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 10-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_SDL_HELPERS_HPP
#define NNB_SDL_HELPERS_HPP

// Public
#include <SDL2/SDL.h>

// Private
#include "nnb/log/log.hpp"

namespace nnb {

	enum class Color {
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		PURPLE,
		BLACK,
		WHITE
	} ;

	SDL_Color getSDL_Color(Color clr);
	

}

#endif
