// File: GameStateMachine.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-15
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_GAMESTATEMACHINE_HPP
#define NNB_GAMESTATEMACHINE_HPP

// Public
#include <memory>

// Private
#include "nnb/states/GameState.hpp"

/*
 * Example usage:
 *
 * Setting a new state:
 * g_gm->setState(new MainMenu());
 * g_gm->setState(new SmoothTransition(g_gm->getState(), new Game()));
 * g_gm->setState(new LoadAndTransition(g_gm->getState(), new Settings()));
 *
 * Propagating new states and running the current state
 * g_gm->switchStates();
 * g_gm->update();
 *
 * Indicating that the machine should exit
 * g_gm->exit = true;
 * Note, this doesn't actually do anything. The idea is that the outside loop checks this value each loop, and once it's true it should exit. Nice and simple
 */

namespace nnb {
	struct GameStateMachine {
		GameStateMachine(std::shared_ptr<GameState> state_);

		void update();
		void setState(std::shared_ptr<GameState> state_);
		void switchStates();

		bool exit = true;
		std::shared_ptr<GameState> state, nextState;
	} ;
}

#endif // NNB_GAMESTATEMACHINE_HPP
