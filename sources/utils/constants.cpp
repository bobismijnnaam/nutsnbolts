// File: constants.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 20150714
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/utils/constants.hpp"

namespace nnb {
    #ifdef NNB_WIN
        std::string DIRSEP = "\\";
    #elif NNB_UNIX
        std::string DIRSEP = "/";
    #endif
}

