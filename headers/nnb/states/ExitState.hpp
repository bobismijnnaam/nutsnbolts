// File: ExitState.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_EXITSTATE_HPP
#define NNB_EXITSTATE_HPP

// Public

// Private
#include "StateMachine.hpp"
#include "State.hpp"
#include "nnb/log/log.hpp"

namespace nnb {

	class ExitState : public State {
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

		std::string getID() {
			return nnb::StateMachine::STATE_EXIT;
		}

	private:

	} ;

}

#endif
