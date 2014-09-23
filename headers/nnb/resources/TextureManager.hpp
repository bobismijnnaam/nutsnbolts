// File: TextureManager.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_TEXTUREMANAGER_HPP
#define NNB_TEXTUREMANAGER_HPP

// Public
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>

// Private
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/graphics/PersistentTexture.hpp"

namespace nnb {

	class TextureManager {
	public:
		TextureManager(SDL_Renderer *tgt_, bool loadDefault = true, std::string rootPath_ = "media/images", std::vector<std::string> suffices_ = {".jpg", ".png", ".bmp"});
		~TextureManager();

		bool loadGroup(std::string group); 
		void unloadGroup(std::string group); 
		bool loadTexture(std::string group, std::string path);
		void unloadTexture(std::string group, std::string key);

		/**
		 * Don't use this if you can use getTexture()!
		 */
		SDL_Texture* getRaw(std::string group, std::string key) const; 
		nnb::PersistentTexture getTexture(std::string group, std::string key) const; 

	private:
		SDL_Renderer *tgt;
		std::string rootPath;
		std::vector<std::string> suffices;
		std::unordered_map<std::string, std::unordered_map<std::string, SDL_Texture*>> textures;

	} ;
}

#endif
