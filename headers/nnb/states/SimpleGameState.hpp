// File: SimpleGameState.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_SIMPLEGAMESTATE_HPP
#define NNB_SIMPLEGAMESTATE_HPP

// Public
#include <string>
#include <SDL2/SDL.h>

// Private
#include "GameState.hpp"

// TODO: make a version with fixed timestep and repeatedly calling of render
namespace nnb {

	template <
		class T
	>
	class SimpleGameState : public GameState<T> {
	public:
		SimpleGameState(std::string id) : GameState<T>(id) {}
		virtual ~SimpleGameState() {}; 

		virtual void update() override {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					// Because of templating between SimpleGameState and GameState thisarrow is needed
					this->machine->exit();
				}

				event(e);
			}

			Uint32 currFrame = SDL_GetTicks();
			float delta = (currFrame - lastFrame) / 1000.0;
			lastFrame = currFrame;

			logic(delta);

			render();
		}

		virtual void activate() override {}; 

		virtual void deactivate() override {};

		/**
		 * This function should handle events.
		 * @param e - The event received from SDL2
		 */
		virtual void event(SDL_Event& e) {};
		
		/**
		 * Game logic goes here.
		 */
		virtual void logic(float delta) {};

		/**
		 * Draws the current gamestate.
		 * @param target - Renderer to render on
		 */
		virtual void render() const {};

	private:
		Uint32 lastFrame = 0;

	};

}

#endif
