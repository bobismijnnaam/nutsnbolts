// File: GameStateMachine.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-16
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/states/GameStateMachine.hpp"

namespace nnb {
	GameStateMachine::GameStateMachine(std::shared_ptr<GameState> state_) :
	state(state_) {}

	void GameStateMachine::update() {
		state->update();
	}

	void GameStateMachine::setState(std::shared_ptr<GameState> state_) {
		nextState = state_;
	}

	void GameStateMachine::switchStates() {
		state = nextState;
		nextState = nullptr;
	}
}
