// File: SoundManager.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-06-13
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/resources/SoundManager.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"

namespace nnb {
    SoundManager::SoundManager(int channels = 32, std::string base_ = "media/sound/") :
    base{base_}{
        // load support for the OGG and MOD sample/music formats
        int flags = MIX_INIT_OGG|MIX_INIT_MOD|MIX_INIT_MP3;
        int initted=Mix_Init(flags);

        if(initted & flags != flags) {
            NNB_ERROR << "Failed to init mp3, ogg, and mod support\n";
            NNB_ERROR << "Error: " << Mix_GetError();
        }
    }

    void SoundManager::doIndexing() {
        auto files = getFiles(base);
    }

    void SoundManager::loadSound(std::string name) {

    }

    Mix_Chunk* SoundManager::loadSound(std::string name) {

    }

    Mix_Music* SoundManager::loadMusic(std::string name) {

    }

    void SoundManager::unload(std::string name) {

    }

    void SoundManager::unload(Mix_Chunk* chunk) {

    }

    void SoundManager::unload(Mix_Music* music) {

    }


    void SoundManager::playSound(Mix_Chunk* chunk, double volume = 100) {

    }

    void SoundManager::playSound(std::string name, double volume = 100) {

    }

    void SoundManager::playMusic(Mix_Music* music, double volume = 100) {

    }

    void SoundManager::playMusic(std::string name, double volume = 100) {

    }
}

