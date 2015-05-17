// File: NullState.hpp2
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_NULLSTATE_HPP
#define NNB_NULLSTATE_HPP

// Public
#include <string>

// Private
#include "GameState.hpp"
#include "GameStateMachine.hpp"

namespace nnb {

	class NullState : public nnb::GameState<NullState> {
	public:
		NullState() {}
		~NullState() {}

		void update() {

		}

		void activate() {

		}

		void deactivate() {

		}

		constexpr static auto id = GameStateMachine::STATE_NULL;

	private:

	} ;

}

#endif
