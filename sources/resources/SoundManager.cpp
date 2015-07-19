// File: SoundManager.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-06-13
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <algorithm>
#include <memory>

// Private
#include "nnb/resources/SoundManager.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/utils/StringHelpers.hpp"

namespace nnb {

    /**
     * SoundManager is a simple class. load() loads files, unload() unloads them. If you
     * want to play them, call play(). Each music file located in the directory tree
     * located at base is identified by its filename without file extension. Thus,
     * any two files cannot have the same name - even if the extension differs!
     * WAV's are considered samples (loaded as Mix_Chunk), anything else (MP3, MOD, OGG)
     * is considered music (loaded as Mix_Music).
     */

    SoundManager::SoundManager(int channels_, std::string base_) :
    base{base_},
    channels{channels_} {
        // load support for the OGG/MOD/WAV/MP3 sample/music formats
        int flags = MIX_INIT_OGG|MIX_INIT_MOD|MIX_INIT_MP3;
        int initted=Mix_Init(flags);

        if(initted & flags != flags) {
            NNB_ERROR << "Failed to init mp3, ogg, and mod support\n";
            NNB_ERROR << "Error: " << Mix_GetError();
            return;
        }

        // 1024 is just a lucky guess. It's just a ballpark figure, and tends to work fine.
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, channels, 1024) == -1) {
            NNB_ERROR << "Channels: " << channels;
            NNB_ERROR << "An error occurred while opening audio. Error: " << Mix_GetError();
        }
    }

    SoundManager::~SoundManager() {
        Mix_CloseAudio();
        Mix_Quit();
    }

    void SoundManager::doIndexing() {
        auto allFiles = getFilesRecursively(base);
        nameLocationMap.clear();

        std::for_each(allFiles.begin(), allFiles.end(), [this](std::string file){
            if (nnb::endsWith(file, ".wav")
                    | nnb::endsWith(file, ".mp3")
                    | nnb::endsWith(file, ".ogg")
                    | nnb::endsWith(file, ".mod")) {
                std::string name = std::get<0>(nnb::chopRight(nnb::fileFromPathToFile(file), "."));
                if (nameLocationMap.find(name) == nameLocationMap.end()) {
                    nameLocationMap[name] = file;
                } else {
                    NNB_ERROR << "Duplicate sound entry found: \"" << name << "\" with paths "
                        << file << " and " << nameLocationMap[name];
                    return;
                }
            }
        });
    }

    void SoundManager::load(std::string name) {
        if (nameLocationMap.find(name) == nameLocationMap.end()) {
            NNB_ERROR << "No entry found for name \"" << name << "\"";
            return;
        }

        auto location = nameLocationMap[name];
        auto type = std::get<1>(nnb::chopRight(nnb::fileFromPathToFile(location), "."));

        if (type == "wav") {
            if (chunks.find(name) != chunks.end()) {
                return;
            }

            chunks[name] = std::unique_ptr<Mix_Chunk, SDLDeleter>(Mix_LoadWAV(location.c_str()));

            if (chunks[name] == nullptr) {
                NNB_ERROR << "An error occurred while loading a WAV file: "
                    << Mix_GetError();
            }
        } else {
            if (musics.find(name) != musics.end()) {
                return;
            }

            musics[name] = std::unique_ptr<Mix_Music, SDLDeleter>(Mix_LoadMUS(location.c_str()));

            if (musics[name] == nullptr) {
                NNB_ERROR << "An error occurred while loading a music file: "
                    << Mix_GetError();
            }
        }
    }

    void SoundManager::unload(std::string name) {
        if (chunks.find(name) != chunks.end()) {
            chunks.erase(name);
        } else if (musics.find(name) != musics.end()) {
            musics.erase(name);
        } else {
            NNB_ERROR << "No music or chunk entry found for name \"" << name << "\"";
        }
    }

    void SoundManager::play(std::string name, int loops, double volume) {
        if (nameLocationMap.find(name) == nameLocationMap.end()) {
            NNB_ERROR << "No entry found for name \"" << name << "\"";
            return;
        }

        auto location = nameLocationMap[name];
        auto type = std::get<1>(nnb::chopRight(nnb::fileFromPathToFile(location), "."));

        if (type == "wav") { // Sound
            if (chunks.find(name) == chunks.end()) {
                NNB_ERROR << "Chunk for \"" << name << "\" not loaded";
                return;
            }

            auto chunk = chunks[name].get();
            if (Mix_PlayChannel(-1, chunk, loops) == -1) {
                NNB_ERROR << "An error occurred while playing " << name << ". Error: "
                    << Mix_GetError();
            }
        } else { // Music
            if (musics.find(name) == musics.end()) {
                NNB_ERROR << "Music for \"" << name << "\" not loaded";
                return;
            }

            auto music = musics[name].get();

            if (loops == -1) {
                loops = -2;
            }

            if (Mix_PlayMusic(music, loops + 1) == -1) {
                NNB_ERROR << "An error occurred while playing " << name << ". Error: "
                    << Mix_GetError();
            };
        }
    }
}

