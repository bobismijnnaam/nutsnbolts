// File: FontManager.hpp2
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_FONTMANAGER_HPP
#define NNB_FONTMANAGER_HPP

// Public
#include <unordered_map>
#include <SDL2/SDL_ttf.h>
#include <string>

// Private
#include "nnb/graphics/PersistentText.hpp"

namespace nnb {
	
	class FontManager {
	public:
		FontManager(SDL_Renderer *tgt_, std::string rootPath_ = "media/fonts");
		~FontManager();

		TTF_Font* getRaw(std::string fontName, int size);
		nnb::PersistentText getText(std::string fontName, int size);

	private:
		std::unordered_map<std::string, std::unordered_map<int, TTF_Font*>> fonts;
		std::string rootPath;
		SDL_Renderer *tgt;
	} ;

}

#endif
