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
   		void Context::initSDL(bool audio, bool video, bool timer) {
			sdl = true;

			sdlAudio = audio;
			sdlVideo = video;
			sdlTimer = timer;
		}

		void Context::initWindow(std::string windowTitle_, int w, int h, bool fullscreen, bool desktopsize, int x, int y) {
			windowIsInitialised = true;

			windowTitle = windowTitle_;
			windowW = w;
			windowH = h;
			windowX = x;
			windowY = y;
			windowFullscreen = fullscreen;
			windowDesktopsize = desktopsize;
		}

		void Context::initGL(int major, int minor) {

		}

		void Context::initSDL_Mixer(bool mp3, bool flac, bool mod, bool ogg) {

		}

		void Context::initialize() {

		}

		void Context::quit() {

		}

		void Context::enable(bool gm, bool tm, bool fm, bool sm) {

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
