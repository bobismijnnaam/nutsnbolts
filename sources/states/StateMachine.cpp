// File: StateMachine.cpp
// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: ma 20-01-2014 
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <utility>
#include <iterator>
#include <SDL2/SDL.h>

// Private
#include "nnb/states/StateMachine.hpp" 
#include "nnb/states/State.hpp"
#include "nnb/log/log.hpp"
#include "nnb/states/NullState.hpp"
#include "nnb/states/ExitState.hpp"

const std::string nnb::StateMachine::STATE_NONE = "__NO_CLASS_SELECTED__";
const std::string nnb::StateMachine::STATE_NULL = "__NULL__";
const std::string nnb::StateMachine::STATE_EXIT = "__EXIT__";

nnb::StateMachine::StateMachine() :
	states(),
	stateStack() {

	addState<nnb::NullState>(nnb::StateMachine::STATE_NULL);
	addState<nnb::ExitState>(nnb::StateMachine::STATE_EXIT);

	changeState(nnb::StateAction::SET, nnb::StateMachine::STATE_NULL);
	update();
}

nnb::StateMachine::~StateMachine() {
	// Delete all current queued states
	emptyStateStack();

	// Delete state factory instances
	for (auto it = states.begin(); it != states.end(); it++) {
		delete it->second;
	}
}

void nnb::StateMachine::update() {
	switch (action) {
		case nnb::StateAction::NONE:
			break;
		case nnb::StateAction::SET:
			{
				emptyStateStack();
				State* newState = states[target]->get();
				stateStack.push(newState);

				NNB_LOG << "Set state " << target;
				break;
			}
		case nnb::StateAction::PUSH:
			{	
				State* newState = states[target]->get();
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
			break;
	}

	action = nnb::StateAction::NONE;
	target = "";

	if (stateStack.empty()) {
		// Pushes the exit state when the stack is empty
		stateStack.push(states[nnb::StateMachine::STATE_EXIT]->get());
	} else {
		State* currentState = stateStack.top();
		currentState->update();
	}
}

void nnb::StateMachine::addState(nnb::AbstractStateFactory* fact) {
	states[fact->getID()] = fact;

	NNB_LOG << "GameState registered: " << fact->getID();	
}

void nnb::StateMachine::changeState(StateAction inputAction) {
	changeState(inputAction, STATE_NONE);
}

void nnb::StateMachine::changeState(nnb::StateAction inputAction, std::string inputTarget) {
	action = inputAction;
	target = inputTarget;

	NNB_LOG << "Next state: " << inputTarget << ", action: " << nnb::stateActionToString(inputAction);
}

std::string nnb::StateMachine::getCurrentStateID() {
	if (stateStack.empty()) {
		return nnb::StateMachine::STATE_NONE;
	} else {
		return stateStack.top()->getID();
	}
}

void nnb::StateMachine::emptyStateStack() {
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
			return "";
	}
}
