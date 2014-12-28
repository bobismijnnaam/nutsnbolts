// File: ExitState.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_EXITSTATE_HPP
#define NNB_EXITSTATE_HPP

// Public
#include <string>

// Private
#include "GameState.hpp"
#include "GameStateMachine.hpp"
#include "nnb/log/log.hpp"

namespace nnb {

	class ExitState : public GameState<ExitState> {
	public:
		ExitState() {}
		~ExitState() {
			NNB_LOG << "SHUTTING_DOWN.jpg";
		}

		void update() {

		}

		void activate() {

		}

		void deactivate() {

		}

		constexpr static auto id = nnb::GameStateMachine::STATE_EXIT;

	private:

	} ;

}

#endif
