// File: Context.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-28
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_CONTEXT_HPP
#define NNB_CONTEXT_HPP

// Public
#include <SDL2/SDL.h>
#include <memory>

// Private

namespace nnb {
	
	struct Context {
		//////////////////////
		// SDL initializers //
		//////////////////////

		void initSDL(bool audio = false, bool video = true, bool timer = true);
		void initWindow(std::string windowTitle, int w, int h, bool fullscreen = false, bool desktopsize = false, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED);
		void initGL(int major = 3, int minor = 2);
		void initSDL_Image(bool jpg = true, bool png = true, bool tif = true);
		void initSDL_TTF();
		void initSDL_Mixer(bool mp3 = true, bool flac = true, bool mod = true, bool ogg = true);
		void initialize();
		void quit();

		//////////////////////
		// NnB initializers //
		//////////////////////
		
		// TODO Initialize gamestate, tm, fm, etc. Should be optional for most (e.g. specifying different texture folders, etc.)

		///////////////////
		// SDL variables //
		///////////////////

		SDL_Window *window = nullptr;
		SDL_Surface *windowSurface = nullptr;
		SDL_Renderer *renderer = nullptr;
		
		///////////////////
		// NnB variables //
		///////////////////

		std::unique_ptr<GameStateMachine> g_gm;
		std::unique_ptr<TextureManager> g_tm;
		std::unique_ptr<FontManager> g_fm;
		// TODO: std::unique_ptr<SoundManager> g_sm;
		
		////////////////////////
		// External Variables //
		////////////////////////

		int getInt(std::string name);
		std::string getString(std::string name);
		double getDouble(std::string name);

		/////////////////
		// Screen info //
		/////////////////

		int getScrW();
		int getScrH();
		// TODO: Use GLM vec2d?
		
	} ;
}

extern nnb::Context g_nnb;
