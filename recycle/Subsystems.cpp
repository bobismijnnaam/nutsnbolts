// File: Subsystems.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: vr 24-10-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Private
#include "nnb/utils/GameFrame.hpp"
#include "nnb/utils/constants.hpp"

nnb::Subsystem::Subsystem(std::string name_) :
name{name_} {
}

std::string nnb::Subsystem::getError() {
	return error;
}

std::string nnb::Subsystem::getName() {
	return name;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

nnb::SDLSubsystem::SDLSubsystem(Uint32 flags_) :
flags{flags_},
Subsystem("SDL") {
}

bool nnb::SDLSubsystem::init() {
	if (SDL_Init(flags) != 0) {
		error = SDL_GetError();
		return nnb::FAILURE;
	} else {
		return nnb::SUCCESS;
	}
}

bool nnb::SDLSubsystem::quit() {
	SDL_Quit();

	return nnb::SUCCESS;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

nnb::SDL_ImageSubsystem::SDL_ImageSubsystem(int flags_) :
flags{flags_},
Subsystem("SDL_Image") {
}

bool nnb::SDL_ImageSubsystem::SDL_ImageSubsystem::init() {
	if (IMG_Init(flags) & flags != flags) {
		error = IMG_GetError();
		return nnb::FAILURE;
	} else {
		return nnb::SUCCESS;
	}
}

bool nnb::SDL_ImageSubsystem::quit() {
	IMG_Quit();

	return nnb::SUCCESS;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

nnb::SDL_TTFSubsystem::SDL_TTFSubsystem() :
Subsystem("SDL_TTF") {
}

bool nnb::SDL_TTFSubsystem::init() {
	if (TTF_Init() < 0) {
		error = TTF_GetError();
		return nnb::FAILURE;
	} else {
		return nnb::SUCCESS;
	}
}

bool nnb::SDL_TTFSubsystem::quit() {
	TTF_Quit();

	return nnb::SUCCESS;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

nnb::SDL_MixerSubsystem::SDL_MixerSubsystem(int flags_) :
flags{flags_},
Subsystem("SDL_Mixer") {
}

bool nnb::SDL_MixerSubsystem::init() {
	if (Mix_Init(flags) & flags != flags) {
		error = Mix_GetError();
		return nnb::FAILURE;
	} else {
		return nnb::SUCCESS;
	}
}

bool nnb::SDL_MixerSubsystem::quit() {
	Mix_Quit();

	return nnb::SUCCESS;
}
