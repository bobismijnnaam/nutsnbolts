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
	///////////////
	// GameState //
	///////////////

	GameState::~GameState() {}
	void update() {}
	void enter() {}
	void leave() {}
	std::vector<std::string> resources() {return {};}

	///////////////////
	// CoolGameState //
	///////////////////

	CoolGameState::CoolGameState(int fps_) :
	fps{fps_} {}

	void CoolGameState::update() {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
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

	void CoolGameState::event(SDL_Event e) {}
	void CoolGameState::logic(double dt) {}
	void CoolGameState::render() const {}
}
