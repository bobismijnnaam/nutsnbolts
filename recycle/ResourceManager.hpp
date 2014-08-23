// File: ResourceManager.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: sa 16-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_RESOURCEMANAGER_HPP
#define NNB_RESOURCEMANAGER_HPP

// Public
#include <algorithm>
#include <unordered_map>
#include <string>

// Private
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/utils/StringHelpers.hpp"

namespace nnb {

	template <
		class T,
		typename Alloc,
		typename Dealloc
	>
	class ResourceManager {
	public:
		ResourceManager(Alloc allocate_, Dealloc deallocate_, std::string preferredRootPath, std::vector<std::string> suffices_, bool loadDefault) :
		allocate{allocate_},
		deallocate{deallocate_},
		rootPath{preferredRootPath},
		suffices{suffices_} {

			if (loadDefault) {
				loadGroup("default");
			}
		}
		
		~ResourceManager() {
			for (auto groupIt = begin(resources); groupIt != end(resources); ++groupIt) {
				for (auto resourceIt = begin(groupIt->second); resourceIt != end(groupIt->second); ++resourceIt) {
					deallocate(resourceIt->second);
				}
			}
		}

		bool loadGroup(std::string groupName) {
			std::string groupPath = rootPath + "\\" + groupName;

			for (std::string suffix : suffices) {
				std::vector<std::string> files = getFiles(groupPath, suffix);

				for (std::string file : files) {
						T* loadedFile = allocate(file);
						
						if (loadedFile != NULL) {
							NNB_LOG << "Error! Unable to load file: \"" << file << "\"";
						} else {
							std::string key = nnb::fileFromPath(suffix);
							resources["default"][key] = loadedFile;
						}
				}
			}

			return false;
		}

		void unloadGroup(std::string groupName) {
			auto it = resources.find(groupName);
			if (it == end(resources)) {
				NNB_LOG << "Error! Tried to unload nonexistent or not loaded group!";
			} else {
				for (auto const &resource : *it) {
					deallocate(resource.second);
					resource = NULL;
				}

				resources.erase(it);
			}
		}

		bool loadResource(std::string group, std::string resourcePath) {
			// TODO: Make it possible to load arbitrary resources
			return false;
		}

		void unloadResource(std::string group, std::string key) {
			// TODO: Make it possible to unload arbitrary assets
		}

		T* get(std::string group, std::string key) {
			auto it = resources.find(group);
			if (it == end(resources)) {
				NNB_LOG << "Error! Tried to look into a nonexistent group";
			} else {
				auto resourceIt = it->second.find(key);
				if (resourceIt == end(*it)) {
					NNB_LOG << "Error! Tried to look up a nonexistent resource!";
				} else {
					return resourceIt->second;
				}
			}
			return nullptr;
		}

	private:
		Alloc allocate;
		Dealloc deallocate;
		std::string rootPath;
		std::vector<std::string> suffices;
		std::unordered_map<std::string, std::unordered_map<std::string, T*>> resources;
	} ;

}

#endif
