// File: SoundManager.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-06-13
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_SOUNDMANAGER_HPP
#define NNB_SOUNDMANAGER_HPP

// Public
#include <string>
#include <SDL2/SDL_mixer.h>

// Private

namespace nnb {
	class SoundManager {
	public:
		SoundManager(int channels = 32, std::string base_ = "media/sound/");

		void loadMusic(std::string file);
		void loadSound(std::string file);
		
		Mix_Chunk* getSound(std::string name);
		Mix_Music* getMusic(std::string name);

		void playSound(Mix_Chunk* chunk, double volume = 100);
		void playMusic(Mix_Music* music, double volume = 100);

	private:

	} ;
}

#endif // NNB_SOUNDMANAGER_HPP
