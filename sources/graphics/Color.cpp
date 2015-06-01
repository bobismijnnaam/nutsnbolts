// File: Color.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-05-29
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/graphics/Color.hpp"

namespace nnb {
	Color toColor(Tint t) {
		Color c;

		c.r = (unsigned char) t.r * 255;
		c.g = (unsigned char) t.g * 255;
		c.b = (unsigned char) t.b * 255;
		c.a = (unsigned char) t.a * 255;

		c.clamp();
		
		return c;
	}

	Tint toTint(Color c) {
		Tint t;

		t.r = c.r / 255.0;
		t.g = c.g / 255.0;
		t.b = c.b / 255.0;
		t.a = c.a / 255.0;

		return t;
	}
}
