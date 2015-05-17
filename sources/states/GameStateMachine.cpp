// File: GameStateMachine.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-16
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/states/GameStateMachine.hpp"

namespace nnb {
	bool GameStateMachine::exit = false;

	GameStateMachine::GameStateMachine(GameState *state_) :
	state{state_} {}

	void GameStateMachine::update() {
		state->update();
	}

	void GameStateMachine::setNextState(GameState *state_, bool deleteState_) {
		nextState = state_;
		deleteState = deleteState_;
	}

	void GameStateMachine::switchStates() {
		if (deleteState)
			delete state;

		state = nextState;
		nextState = nullptr;
	}

	GameState *GameStateMachine::getCurrentState() {
		return state;
	}
}
