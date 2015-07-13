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

	/**
	 * When asked, nnb::SoundManager indexes the base sound directory (media/sound by default). You can then
	 * get pointers to sound and music files. load* loads a file and returns a pointer to it. Use this to "preload"
	 * files. When you're done with the files, unload them using the name or the pointer. To play it, use the play*
	 * functions with either the name or the pointer.
	 */
	class SoundManager {
	public:
		SoundManager(int channels = 32, std::string base_ = "media/sound/");

		void doIndexing();

		void loadMusic(std::string name);
		void loadSound(std::string name);
		
		Mix_Chunk* loadSound(std::string name);
		Mix_Music* loadMusic(std::string name);

		void unload(std::string name);
		void unload(Mix_Chunk* chunk);
		void unload(Mix_Music* music);

		void playSound(Mix_Chunk* chunk, double volume = 100);
		void playSound(std::string name, double volume = 100);

		void playMusic(Mix_Music* music, double volume = 100);
		void playMusic(std::string name, double volume = 100);

	private:
		std::string base;

	} ;
}

#endif // NNB_SOUNDMANAGER_HPP
