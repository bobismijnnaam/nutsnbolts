// File: Directions.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: za 26-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_DIRECTIONS_HPP
#define NNB_DIRECTIONS_HPP

namespace nnb {

	enum class Dir2 {
		LEFT,
		RIGHT
	} ;

	enum class Dir4 {
		LEFT,
		RIGHT,
		UP,
		DOWN
	} ;

	enum class Dir8 {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		TOPRIGHT,
		TOPLEFT,
		BOTTOMRIGHT,
		BOTTOMLEFT
	} ;

}

#endif
