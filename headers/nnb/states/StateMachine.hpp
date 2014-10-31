// File: StateMachine.hpp
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
#include "StateFactory.hpp"

namespace nnb {

	enum class StateAction {
		SET,
		PUSH,
		POP,
		NONE
	} ;

	std::string stateActionToString(StateAction a);

	class StateMachine {
	public:
		StateMachine();
		~StateMachine();

		void update();
		void changeState(StateAction inputAction, std::string inputTarget);
		void changeState(StateAction inputAction);
		void exit();
		std::string getCurrentStateID();

		void addState(nnb::AbstractStateFactory* fact);
		
		template<class T>
		void addState(std::string id) {
			addState(new SimpleStateFactory<T>(id));
		}

		static const std::string STATE_NONE;
		static const std::string STATE_NULL;
		static const std::string STATE_EXIT;

	private:
		void emptyStateStack();

		std::unordered_map<std::string, nnb::AbstractStateFactory*> states;
		std::stack<State*> stateStack;

		StateAction action = StateAction::NONE;
		std::string target = STATE_NONE;

		bool quit = false;
	} ;

}

#endif
