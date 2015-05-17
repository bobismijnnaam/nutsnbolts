// File: GameStateMachine.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-15
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_GAMESTATEMACHINE_HPP
#define NNB_GAMESTATEMACHINE_HPP

// Public

// Private
#include "nnb/states/GameState.hpp"

namespace nnb {
	class GameStateMachine {
	public:
		GameStateMachine(GameState *state_ = nullptr);

		void update();
		void setNextState(GameState *state_, bool deleteState_ = true);
		void switchStates();

		GameState *getCurrentState();

		static bool exit;

	private:
		GameState *state, *nextState = nullptr;
		bool deleteState = true;

	} ;
}

#endif // NNB_GAMESTATEMACHINE_HPP
