// File: GameFrame.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 16-10-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stack>

// Private
#include "nnb/utils/GameFrame.hpp"
#include "nnb/utils/unique_ptr.hpp"
#include "nnb/utils/constants.hpp"
#include "nnb/log/log.hpp"

nnb::GameFrame::GameFrame() :
errorMsg{""},
success{false} {
}

void nnb::GameFrame::giveSDL(bool timer, bool audio, bool video) {
	Uint32 flags = 0;
	flags = timer ? flags | SDL_INIT_TIMER : flags;
	flags = audio ? flags | SDL_INIT_AUDIO : flags;
	flags = video ? flags | SDL_INIT_VIDEO : flags;

	giveSDL(flags);
}

void nnb::GameFrame::giveSDL(Uint32 flags) {
	queue.push_back(make_unique<nnb::SDLSubsystem>(flags));
}

void nnb::GameFrame::giveSDL_Image(bool jpg, bool png, bool tif) {
	Uint32 flags = 0;
	flags = jpg ? flags | IMG_INIT_JPG : flags;
	flags = png ? flags | IMG_INIT_PNG : flags;
	flags = tif ? flags | IMG_INIT_TIF : flags;

	giveSDL_Image(flags);
}

void nnb::GameFrame::giveSDL_Image(int flags) {
	queue.push_back(make_unique<nnb::SDL_ImageSubsystem>(flags));
}

void nnb::GameFrame::giveSDL_TTF() {
	queue.push_back(make_unique<nnb::SDL_TTFSubsystem>());
}

void nnb::GameFrame::giveSDL_Mixer(bool flac, bool mod, bool mp3, bool ogg) {
	int flags = 0;
	flags = flac ? flags | MIX_INIT_FLAC : flags;
	flags = mod ? flags | MIX_INIT_MOD : flags;
	flags = mp3 ? flags | MIX_INIT_MP3 : flags;
	flags = ogg ? flags | MIX_INIT_OGG : flags;

	giveSDL_Mixer(flags);
}

void nnb::GameFrame::giveSDL_Mixer(int flags) {
	queue.push_back(make_unique<nnb::SDL_ImageSubsystem>(flags));
}

void nnb::GameFrame::give(std::unique_ptr<Subsystem> ss) {
	queue.push_back(std::move(ss));
}

bool nnb::GameFrame::launch() {
	bool error = false;
	
	while (queue.size() > 0) {
		std::unique_ptr<Subsystem> ss = std::move(queue.front());
		queue.pop_front();
		if (ss->init() == nnb::SUCCESS) {
			NNB_INFO << "Initialized " << ss->getName();
			active.push(std::move(ss));
		} else {
			error = true;
			errorMsg = ss->getError();
			NNB_ERROR << "Failed to initialize " << ss->getName();
			break;
		}
	}

	if (error) {
		while (active.size() > 0) {
			std::unique_ptr<Subsystem> ss = std::move(active.top());
			active.pop();
			ss->quit();
		}

		success = nnb::FAILURE;
	} else {
		success = nnb::SUCCESS;
	}

	return success;
}

bool nnb::GameFrame::land() {
	while (active.size() > 0) {
		std::unique_ptr<Subsystem> ss = std::move(active.top());
		active.pop();
		ss->quit();
		NNB_INFO << "Successfully quit " << ss->getName();
	}

	return nnb::SUCCESS;
}

std::string nnb::GameFrame::getError() {
	return errorMsg;
}

bool nnb::GameFrame::getSuccess() {
	return success;
}
