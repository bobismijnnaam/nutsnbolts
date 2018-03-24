// File: GameState.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-15
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_GAMESTATE_HPP
#define NNB_GAMESTATE_HPP

// Public
#include <SDL2/SDL.h>
#include <vector>
#include <string>

// Private

namespace nnb {
	struct GameState {
		virtual ~GameState();

		virtual void update();
		virtual void enter();
		virtual void leave();
		virtual std::vector<std::string> resources();
	} ;

	struct CoolGameState : public GameState {
		CoolGameState(int fps_ = 60);

		void update();
		virtual void event(SDL_Event e);
		virtual void logic(double dt);
		virtual void render() const;

		int fps;
		double lag = 0;
	} ;
}

#endif // NNB_GAMESTATE_HPP
