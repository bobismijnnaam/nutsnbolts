// File: FontManager.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL_ttf.h>
#include <unordered_map>

// Private
#include "nnb/resources/FontManager.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/StringHelpers.hpp"

nnb::FontManager::FontManager(SDL_Renderer* tgt_, std::string rootPath_) :
fonts(), 
rootPath{rootPath_},
tgt{tgt_} {
}

nnb::FontManager::~FontManager() {
	for (auto fontFamilyEntry : fonts) {
		auto fontFamily = fontFamilyEntry.second;

		for (auto fontSizeEntry : fontFamily) {
			TTF_CloseFont(fontSizeEntry.second);
		}
	}
}

TTF_Font* nnb::FontManager::getRaw(std::string fontName, int size) {
	// TODO: Maybe remove logging?
	if (!nnb::endsWith(fontName, ".ttf")) {
		NNB_LOG << "Error! Fontname does not end in \".ttf\" (" << fontName << ")";
		return NULL;
	}
	
	auto fontFamilyEntry = fonts.find(fontName);
	if (fontFamilyEntry == end(fonts)) {
		NNB_LOG << "First time loading font family " << fontName << ". Creating at size: " << size;

		fonts[fontName][size] = TTF_OpenFont((rootPath + "/" + fontName).c_str(), size);

		if (fonts[fontName][size] == NULL) 
			NNB_LOG << "Error loading font " << fontName << " of size " << size << ". Error: " << TTF_GetError();
		return fonts[fontName][size];
	} else {
		auto fontFamily = fontFamilyEntry->second;
		auto fontSizeEntry = fontFamily.find(size);

		if (fontSizeEntry == end(fontFamily)) {
			NNB_LOG << "First time loading font family " << fontName << " at size: " << size;

			fontFamily[size] = TTF_OpenFont((rootPath + "/" + fontName).c_str(), size);

			if (fontFamily[size] == NULL)
				NNB_LOG << "Error loading font " << fontName << " at size " << size << ". Error: " << TTF_GetError();
			return fontFamily[size];
		} else {
			NNB_LOG << "Found font " << fontName << " at size " << size;

			auto fontSize = fontSizeEntry->second;
			return fontSize;
		}
	}
}

nnb::PersistentText nnb::FontManager::getText(std::string fontName, int size) {
	nnb::PersistentText temp(tgt);
	temp.setFont(getRaw(fontName, size));
	return temp;
}
