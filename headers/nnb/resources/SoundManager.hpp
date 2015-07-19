// File: SoundManager.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-06-13
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_SOUNDMANAGER_HPP
#define NNB_SOUNDMANAGER_HPP

// Public
#include <string>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <memory>

// Private
#include "nnb/resources/CustomDeleters.hpp"

namespace nnb {

	/**
	 * When asked, nnb::SoundManager indexes the base sound directory (media/sound by default). You can then
	 * get pointers to sound and music files. load* loads a file and returns a pointer to it. Use this to "preload"
	 * files. When you're done with the files, unload them using the name or the pointer. To play it, use the play*
	 * functions with either the name or the pointer.
	 */
	class SoundManager {
	public:
		SoundManager(int channels_ = MIX_DEFAULT_CHANNELS, std::string base_ = "media/sound/");
		~SoundManager();

		void doIndexing();
		void load(std::string name);
		void unload(std::string name);
		void play(std::string name, int loops = 0, double volume = 100);

	private:
		std::string base;
		int channels;
		std::map<std::string, std::string> nameLocationMap;

		std::map<std::string, std::unique_ptr<Mix_Chunk, SDLDeleter>> chunks;
		std::map<std::string, std::unique_ptr<Mix_Music, SDLDeleter>> musics;
	} ;
}

#endif // NNB_SOUNDMANAGER_HPP
