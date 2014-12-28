// File: GameStateMachine.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 20-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_STATEMACHINE_HPP
#define NNB_STATEMACHINE_HPP

// Public
#include <unordered_map>
#include <stack>
#include <string>

// Private
#include "State.hpp"

namespace nnb {

	enum class StateAction {
		SET,
		PUSH,
		POP,
		NONE
	} ;

	std::string stateActionToString(StateAction a);

	class State;

	class GameStateMachine {
	public:
		GameStateMachine();
		~GameStateMachine();

		void update();
		void setState(std::string stateID);
		void pushState(std::string stateID);
		void popState();
		void exit();
		std::string getCurrentStateID();

		static constexpr auto STATE_NONE = "__NO_CLASS_SELECTED__";
		static constexpr auto STATE_NULL = "__NULL__";
		static constexpr auto STATE_EXIT = "__EXIT__";

	private:
		void emptyStateStack();
		void changeState(StateAction inputAction, std::string inputTarget);

		std::stack<State*> stateStack;

		StateAction action = StateAction::NONE;
		std::string target = STATE_NONE;

		bool quit = false;
	} ;

}

#endif
