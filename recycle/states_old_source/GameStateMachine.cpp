// File: GameStateMachine.cpp
// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: ma 20-01-2014 
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <utility>
#include <iterator>
#include <SDL2/SDL.h>
#include <string>

// Private
#include "nnb/states/GameStateMachine.hpp" 
#include "nnb/states/State.hpp"
#include "nnb/log/log.hpp"
#include "nnb/states/NullState.hpp"
#include "nnb/states/ExitState.hpp"

nnb::GameStateMachine::GameStateMachine() :
stateStack() {
	changeState(nnb::StateAction::SET, nnb::GameStateMachine::STATE_NULL);
	update();
}

nnb::GameStateMachine::~GameStateMachine() {
	// Delete all current queued states
	emptyStateStack();
}

void nnb::GameStateMachine::update() {
	switch (action) {
		case nnb::StateAction::NONE:
			break;
		case nnb::StateAction::SET:
			{
				emptyStateStack();
				State* newState = GameStatePark::get(target);
				newState->machine = this;
				stateStack.push(newState);

				NNB_LOG << "Set state " << target;
				break;
			}
		case nnb::StateAction::PUSH:
			{	
				State* newState = GameStatePark::get(target);
				newState->machine = this;
				State* topState = stateStack.top();

				topState->deactivate();
				stateStack.push(newState);

				NNB_LOG << "Pushed state " << target;
				break;
			}
		case nnb::StateAction::POP:
			{
				State* oldTopState = stateStack.top();
				std::string oldTopStateName = oldTopState->getID();
				delete oldTopState;

				std::string newTopStateName = "no state";
				if (!stateStack.empty()) {
					stateStack.pop();
					State* newTopState = stateStack.top();
					newTopState->activate();
					newTopStateName = newTopState->getID();
				}

				NNB_LOG << "Popped state " << oldTopStateName << ", new state: " << newTopStateName;
				break;
			}
		default:
			NNB_ERROR << "The universe just exploded";
			break;
	}

	action = nnb::StateAction::NONE;
	target = "";

	if (stateStack.empty()) {
		// Pushes the exit state when the stack is empty
		stateStack.push(GameStatePark::get(GameStateMachine::STATE_EXIT));
	} else {
		State* currentState = stateStack.top();
		currentState->update();
	}
}

void nnb::GameStateMachine::setState(std::string stateID) {
	changeState(nnb::StateAction::SET, stateID);
}

void nnb::GameStateMachine::pushState(std::string stateID) {
	changeState(nnb::StateAction::PUSH, stateID);
}

void nnb::GameStateMachine::popState() {
	changeState(nnb::StateAction::POP, STATE_NONE);
}

void nnb::GameStateMachine::changeState(nnb::StateAction inputAction, std::string inputTarget) {
	action = inputAction;
	target = inputTarget;

	NNB_LOG << "Next state: " << inputTarget << ", action: " << nnb::stateActionToString(inputAction);
}

void nnb::GameStateMachine::exit() {
	changeState(nnb::StateAction::SET, nnb::GameStateMachine::STATE_EXIT);
}

std::string nnb::GameStateMachine::getCurrentStateID() {
	if (stateStack.empty()) {
		return nnb::GameStateMachine::STATE_NONE;
	} else {
		return stateStack.top()->getID();
	}
}

void nnb::GameStateMachine::emptyStateStack() {
	while(!stateStack.empty()) {
		State* topState = stateStack.top();
		stateStack.pop();

		delete topState;
	}
}

std::string nnb::stateActionToString(nnb::StateAction a) {
	switch (a) {
		case nnb::StateAction::SET:
			return "SET";
		case nnb::StateAction::PUSH:
			return "PUSH";
		case nnb::StateAction::POP:
			return "POP";
		case nnb::StateAction::NONE:
			return "NONE";
		default:
			return "NONE";
	}
}
