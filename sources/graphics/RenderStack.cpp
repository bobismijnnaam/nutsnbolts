// File: RenderStack.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-16
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/graphics/RenderStack.hpp"

namespace nnb {
	RenderStack *RenderStack::instance = nullptr;
	SDL_Renderer *RenderStack::renderer = nullptr;

	void RenderStack::setup(SDL_Renderer *renderer_) {
		static RenderStack *instance_ = new RenderStack();
		instance = instance_;

		renderer = renderer_;
	}

	RenderStack& RenderStack::i() {
		return *instance;
	}

	void RenderStack::push(SDL_Texture* tgt) {
		SDL_SetRenderTarget(renderer, tgt);
		targets.push(tgt);
	}

	void RenderStack::pop() {
		targets.pop();
		if (targets.size() > 0) {
			SDL_SetRenderTarget(renderer, targets.top());
		} else {
			SDL_SetRenderTarget(renderer, NULL);
		}
	}
}
