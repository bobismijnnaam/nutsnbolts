// File: GameState.cpp 
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-15
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>
#include <vector>
#include <string>

// Private
#include "nnb/states/GameState.hpp"
#include "nnb/states/GameStateMachine.hpp"

namespace nnb {
	//////////////////////////
	// GameState base class //
	//////////////////////////

	GameState::~GameState() {}

	////////////////////////
	// OrganizedGameState //
	////////////////////////

	OrganizedGameState::OrganizedGameState(int fps_) :
	fps{fps_} {}

	void OrganizedGameState::update() {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				GameStateMachine::exit = true;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					GameStateMachine::exit = true;
				}
			}

			event(e);
		}

		logic(1/(double) fps);
		lag += 1 / (double) fps;

		while (lag > 0) {
			int before = SDL_GetTicks();
			render();
			int after = SDL_GetTicks();

			lag -= (after - before) / 1000.0;
		}
	}

	void OrganizedGameState::event(SDL_Event e) {}
	void OrganizedGameState::logic(double dt) {}
	void OrganizedGameState::render() const {}

	//////////////////////
	// TransitGameState //
	//////////////////////

	TransitGameState::TransitGameState(int fps_) :
	OrganizedGameState(fps_) {}

	void TransitGameState::enter() {}
	void TransitGameState::leave() {}

	///////////////////////
	// ResourceGameState //
	///////////////////////

	ResourceGameState::ResourceGameState(int fps_) :
	TransitGameState(fps_) {}

	std::vector<std::string> resources() {
		return {};
	}
}
