// File: NullState.hpp2
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_NULLSTATE_HPP
#define NNB_NULLSTATE_HPP

// Public

// Private
#include "StateMachine.hpp"

namespace nnb {

	class NullState : public nnb::State {
	public:
		NullState() {}
		~NullState() {}

		void update() {

		}

		void activate() {

		}

		void deactivate() {

		}

	private:

	} ;

}

#endif
