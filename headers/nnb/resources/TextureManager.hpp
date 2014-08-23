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
		TextureManager(SDL_Renderer *tgt_, bool loadDefault = true, std::string rootPath_ = "media/images", std::vector<std::string> suffices_ = {".jpg", ".png", ".bmp"}) :
		tgt{tgt_},
		rootPath{rootPath_},
		suffices{suffices_},
		textures() {
			if (loadDefault) {
				loadGroup("default");
			}
		}

		~TextureManager() {
			std::vector<std::string> groups;
			for (auto &pair : textures) {
				groups.push_back(pair.first);
			}
			// Can't iterate over a group while deleting from it brr

			for (auto &groupName : groups) {
				unloadGroup(groupName);
			}
		}

		bool loadGroup(std::string group) {
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

		void unloadGroup(std::string group) {
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

		bool loadTexture(std::string group, std::string path) {
			// TODO: Finish this
			return false;
		}

		void unloadTexture(std::string group, std::string key) {
			// TODO: Finish this
		}

		/**
		 * Don't use this if you can use getTexture()!
		 */
		SDL_Texture* getRaw(std::string group, std::string key) const {
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

		nnb::PersistentTexture getTexture(std::string group, std::string key) const {
			SDL_Texture* theTexture = getRaw(group, key);
			return nnb::PersistentTexture(tgt, theTexture);
		}

	private:
		SDL_Renderer *tgt;
		std::string rootPath;
		std::vector<std::string> suffices;
		std::unordered_map<std::string, std::unordered_map<std::string, SDL_Texture*>> textures;

	} ;
}

#endif
