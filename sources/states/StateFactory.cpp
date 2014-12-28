// File: StateFactory.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 26-12-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include <memory>

// Private
#include "nnb/states/StateFactory.hpp"
#include "nnb/states/State.hpp"
#include "nnb/log/log.hpp"

std::unordered_map<std::string, std::function<nnb::State*(void)>> nnb::GameStatePark::park;

nnb::State* nnb::GameStatePark::get(std::string stateID) {
	auto e = nnb::GameStatePark::park.find(stateID);
	if (e != end(nnb::GameStatePark::park)) {
		return e->second();
	} else { 
		NNB_ERROR << "State not found: \"" << stateID << "\"";
		return nullptr;
	}
}
