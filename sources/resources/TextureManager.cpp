// File: TextureManager.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: sa 13-09-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/resources/TextureManager.hpp"

nnb::TextureManager::TextureManager(SDL_Renderer *tgt_, bool loadDefault, std::string rootPath_, std::vector<std::string> suffices_)  :
tgt{tgt_},
rootPath{rootPath_},
suffices{suffices_},
textures() {
	if (loadDefault) {
		loadGroup("default");
	}
}

nnb::TextureManager::~TextureManager() {
	std::vector<std::string> groups;
	for (auto &pair : textures) {
		groups.push_back(pair.first);
	}

	// Can't iterate over a group while deleting from it brr

	for (auto &groupName : groups) {
		unloadGroup(groupName);
	}
}

bool nnb::TextureManager::loadGroup(std::string group) {
	std::string groupPath = rootPath + "/" + group;
	bool retVal = true;

	for (std::string suffix : suffices) {
		std::vector<std::string> files = getFiles(groupPath, suffix);

		for (std::string file : files) {
				std::string tgtFile = groupPath + "/" + file;
				SDL_Texture* loadedFile = IMG_LoadTexture(tgt, tgtFile.c_str());
				
				if (loadedFile == NULL) {
					NNB_LOG << "Error! Unable to load file: \"" << tgtFile << "\"";
					retVal = false;
				} else {
					textures[group][file] = loadedFile;
				}
		}
	}

	NNB_LOG << "Loaded texture group \"" << group << "\"";

	return retVal;
}

void nnb::TextureManager::unloadGroup(std::string group) {
	auto groupIt = textures.find(group);
	if (groupIt == end(textures)) {
		NNB_LOG << "Error! Unable to find group \"" << group << "\"";
	} else {
		auto groupMap = groupIt->second;
		for (auto pair : groupMap) {
			SDL_DestroyTexture(pair.second);
			groupMap.erase(pair.first);
		}

		textures.erase(groupIt);
	}
}

bool nnb::TextureManager::loadTexture(std::string group, std::string path) {
	// TODO: Finish this
	return false;
}

void nnb::TextureManager::unloadTexture(std::string group, std::string key) {
	// TODO: Finish this
}

SDL_Texture* nnb::TextureManager::getRaw(std::string group, std::string key) const {
	auto groupIt = textures.find(group);
	if (groupIt == end(textures)) {
		NNB_LOG << "Error! Unknown group: \"" << group << "\"";
		return nullptr;
	} else {
		auto resourceIt = groupIt->second.find(key);
		if (resourceIt == end(groupIt->second)) {
			NNB_LOG << "Error! Texture not found: \"" << key << "\" (" << group << ")";
			return nullptr;
		} else {
			return resourceIt->second;
		}
	}
}

nnb::TextureContainer nnb::TextureManager::getTexture(std::string group, std::string key) const {
	SDL_Texture* theTexture = getRaw(group, key);
	return nnb::TextureContainer(tgt, theTexture);
}

