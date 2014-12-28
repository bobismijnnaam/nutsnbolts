// File: State.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 26-12-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_STATE_HPP
#define NNB_STATE_HPP

// Public
#include <string>

// Private
#include "GameStateMachine.hpp"

namespace nnb {

	class GameStateMachine;

	class State {
	public:
		State(std::string id_) : stateID{id_} {}
		virtual ~State() {};

		virtual void update() = 0;
		virtual void activate() = 0;
		virtual void deactivate() = 0;

		std::string getID() {
			return stateID;
		}

		nnb::GameStateMachine *machine = nullptr;

	private:
		std::string stateID;
		

	} ;

}

#endif

