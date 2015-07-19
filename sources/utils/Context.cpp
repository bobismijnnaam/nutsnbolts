// File: Context.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 20150719
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include "nnb/utils/Context.hpp"

// Private
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/utils/constants.hpp"

namespace nnb {
   		void Context::initSDL(bool audio = false, bool video = true, bool timer = true) {
			sdl = true;

			sdlAudio = audio;
			sdlVideo = video;
			sdlTimer = timer;
		}

		void Context::initWindow(std::string windowTitle_, int w, int h, bool fullscreen = false, bool desktopsize = false, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED) {
			initWindow = true;

			windowTitle = windowTitle_;
			windowW = w;
			windowH = h;
			windowX = x;
			windowY = y;
			windowFullscreen = fullscreen;
			windowDesktopsize = desktopsize
		}

		void Context::initGL(int major = 3, int minor = 2) {

		}

		void Context::initSDL_Mixer(bool mp3 = true, bool flac = true, bool mod = true, bool ogg = true) {

		}

		void Context::initialize() {

		}

		void Context::quit() {

		}

		void Context::enable(bool gm = true, bool tm = true, bool fm = true, bool sm = true) {

		}

		int Context::getInt(std::string name) {
			NNB_ERROR << "getInt() not yet implemented";
		}

		std::string Context::getString(std::string name) {
			NNB_ERROR << "getString() not yet implemented";
		}

		double Context::getDouble(std::string name) {
			NNB_ERROR << "getDouble() not yet implemented";
		}

		int Context::getScrW() {
			NNB_ERROR << "getScrW() not yet implemented";
		}

		int Context::getScrH() {
			NNB_ERROR << "getScrH() not yet implemented";
		}
}
