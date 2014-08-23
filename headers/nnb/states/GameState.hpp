// File: GameState.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_GAMESTATE_HPP
#define NNB_GAMESTATE_HPP

// Public
#include <string>
#include <SDL2/SDL.h>

// Private
#include "State.hpp"

// TODO: make a version with fixed timestep and repeatedly calling of render
namespace nnb {

	class GameState : public State {
	public:
		GameState();
		virtual ~GameState();

		virtual void update();

		virtual void activate();

		virtual void deactivate();

		/**
		 * This function should handle events.
		 * @param e - The event received from SDL2
		 */
		virtual void event(SDL_Event& e); 
		
		/**
		 * Game logic goes here.
		 */
		virtual void logic(float delta);

		/**
		 * Draws the current gamestate.
		 * @param target - Renderer to render on
		 */
		virtual void render() const;

		/**
		 * Returns ID (name) of state
		 */
		virtual std::string getID() = 0;

	private:
		Uint32 lastFrame = 0;

	};

}

#endif
