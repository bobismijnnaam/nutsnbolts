// File: CustomDeleters.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_CUSTOMDELETERS_HPP
#define NNB_CUSTOMDELETERS_HPP

// Public
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

// Private

namespace nnb {
	struct SDLDeleter {
		void operator()(SDL_Window *p) const; 
		void operator()(SDL_Renderer *p) const; 
		void operator()(SDL_Texture *p) const; 
		void operator()(SDL_Cursor *p) const;
		void operator()(SDL_Surface *p) const;
		void operator()(Mix_Chunk *p) const;
		void operator()(Mix_Music *p) const;
	} ;
}

#endif
