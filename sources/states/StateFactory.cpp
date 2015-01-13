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

nnb::State* nnb::GameStatePark::get(std::string stateID) {
	auto park = nnb::GameStatePark::getPark();
	auto e = park.find(stateID);
	if (e != end(park)) {
		return e->second();
	} else { 
		NNB_ERROR << "State not found: \"" << stateID << "\"";
		return nullptr;
	}
}

std::unordered_map<std::string, std::function<nnb::State*(void)>>& nnb::GameStatePark::getPark() {
	static std::unordered_map<std::string, std::function<State*(void)>> thePark;

	return thePark; 
}

