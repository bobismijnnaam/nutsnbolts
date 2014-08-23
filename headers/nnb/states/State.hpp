// File: State.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 20-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_STATE_HPP
#define NNB_STATE_HPP

// Public
#include <string>
#include <SDL2/SDL.h>

// Private

namespace nnb {

	class State {
	public:
		State();
		virtual ~State();

		/**
		 * Does the logic of that state
		 */
		virtual void update();

		/**
		 * Is called to notify the instance it will be used again
		 */
		virtual void activate();

		/**
		 * Is called to notify the instance that from that moment on it will be paused
		 */
		virtual void deactivate();

		/**
		 * Returns the ID of the state
		 */
		virtual std::string getID() = 0;

	private:

	};

}

#endif
