// File: State.cpp
// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: ma 20-01-2014 
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>

 // Private
#include "nnb/states/State.hpp"
#include "nnb/states/StateMachine.hpp"
#include "nnb/log/log.hpp"

nnb::State::State() {

} 

nnb::State::~State() {

}

void nnb::State::update() {

}

void nnb::State::activate() {

}

void nnb::State::deactivate() {

}

std::string nnb::State::getID() {
	return id;
}

void nnb::State::setID(std::string id_) {
	id = id_;
}
