// File: Context.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 20150528
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_CONTEXT_HPP
#define NNB_CONTEXT_HPP

// Public
#include <SDL2/SDL.h>
#include <memory>

// Private
#include "nnb/states/GameStateMachine.hpp"
#include "nnb/resources/SoundManager.hpp"

namespace nnb {
	
	struct Context {
		void initSDL(bool audio = false, bool video = true, bool timer = true);
		void initWindow(std::string windowTitle_, int w, int h, bool fullscreen = false, bool desktopsize = false, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED);
		void initGL(int major = 3, int minor = 2);
		void initSDL_Mixer(bool mp3 = true, bool flac = true, bool mod = true, bool ogg = true);
		void initialize();
		void quit();

		void enable(bool gm = true, bool tm = true, bool fm = true, bool sm = true);

		int getInt(std::string name);
		std::string getString(std::string name);
		double getDouble(std::string name);

		int getScrW();
		int getScrH();

		SDL_Window *window = nullptr;
		SDL_Surface *windowSurface = nullptr;
		SDL_Renderer *renderer = nullptr;
		
		std::unique_ptr<GameStateMachine> g_gm;
		// std::unique_ptr<TextureManager> g_tm; // TODO: Implement TextureManager
		// std::unique_ptr<FontManager> g_fm; // TODO: Implement FontManager
		std::unique_ptr<SoundManager> g_sm;

		// SDL Parameters
		bool sdlAudio, sdlVideo, sdlTimer, sdl = false;

		// Window parameters
		std::string windowTitle;
		int windowW, windowH, windowX, windowY;
		bool windowFullscreen, windowDesktopsize;
		bool windowIsInitialised = false;

		// GL Parameters
		bool gl = false;

		// Mixer parameters
		bool mixer = false;

	} ;
}

extern nnb::Context g_nnb;

#endif // NNB_CONTEXT_HPP
