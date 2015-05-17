// File: RenderStack.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-16
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_RENDERSTACK_HPP
#define NNB_RENDERSTACK_HPP

// Public
#include <SDL2/SDL.h>
#include <stack>

// Private

namespace nnb {
	class RenderStack {
	public:
		static void setup(SDL_Renderer *renderer_);
		static RenderStack& i();

		void push(SDL_Texture* tgt);
		void pop();

	private:
		RenderStack();

		static RenderStack *instance;
		static SDL_Renderer *renderer;

		std::stack<SDL_Texture*> targets;
	} ;
}

#endif // NNB_RENDERSTACK_HPP
