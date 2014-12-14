// File: GameState.cpp
// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: ma 21-07-2014 
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>

 // Private
#include "nnb/states/GameState.hpp" 
#include "nnb/states/StateMachine.hpp"
#include "nnb/log/log.hpp"

nnb::GameState::GameState() {

}

nnb::GameState::~GameState() {

}

void nnb::GameState::update() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			NNB_INFO << "SDL_MOUSEBUTTONDOWN " << e.type;
		} else if (e.type == SDL_MOUSEBUTTONUP) {
			NNB_INFO << "SDL_MOUSEBUTTONUP " << e.type;
		} else if (e.type == SDL_MOUSEMOTION) {
			NNB_INFO << "SDL_MOUSEMOTION " << e.type;
		}
		event(e);
	}

	Uint32 currFrame = SDL_GetTicks();
	float delta = (currFrame - lastFrame) / 1000.0;
	lastFrame = currFrame;

	logic(delta);

	render();
}

void nnb::GameState::activate() {

}

void nnb::GameState::deactivate() {

}

void nnb::GameState::event(SDL_Event &e) {

}

void nnb::GameState::logic(float delta) {

}

void nnb::GameState::render() const {

}
