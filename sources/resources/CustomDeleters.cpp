// File: CustomDeleters.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/resources/CustomDeleters.hpp"

void nnb::SDLDeleter::operator()(SDL_Window *p) const {
	SDL_DestroyWindow(p); 
}

void nnb::SDLDeleter::operator()(SDL_Renderer *p) const {
	SDL_DestroyRenderer(p); 
}

void nnb::SDLDeleter::operator()(SDL_Texture *p) const {
	SDL_DestroyTexture(p); 
}

void nnb::SDLDeleter::operator()(SDL_Cursor *p) const {
	SDL_FreeCursor(p);
}

void nnb::SDLDeleter::operator()(SDL_Surface *p) const {
	SDL_FreeSurface(p);
}
