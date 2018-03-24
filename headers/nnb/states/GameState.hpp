// File: GameState.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 20-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_GAMESTATE_HPP
#define NNB_GAMESTATE_HPP

// Public
#include <string>
#include <SDL2/SDL.h>

// Private
#include "nnb/states/StateFactory.hpp"
#include "nnb/states/State.hpp"


namespace nnb {

	template <typename T, T /*unnamed*/>
	struct InitProxy { };

	template <
		class T
	>
	class GameState : public State {
	public:
		GameState() : State(T::id) {}
		virtual ~GameState() {}; 

		/**
		 * Does the logic of that state
		 */
		virtual void update() = 0; 

		/**
		 * Is called to notify the instance it will be used again
		 */
		virtual void activate() = 0;

		/**
		 * Is called to notify the instance that from that moment on it will be paused
		 */
		virtual void deactivate() = 0;

	protected:
		struct Proxy {
			Proxy() {
				nnb::GameStatePark::record<T>();
			}
		};
		static Proxy proxy;
		// For more info see: http://stackoverflow.com/questions/27672559/using-static-initialization-to-register-classes/27677642#27677642
		typedef InitProxy<Proxy&, proxy> __nnb_typedef_dummy__; // The spelling of the second part is not relevant as it's never used - just to force instantiation

	} ;

	template<
		class T
	>
	typename GameState<T>::Proxy GameState<T>::proxy;

}

#endif
