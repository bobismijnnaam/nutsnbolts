// File: macros.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_MACROS_HPP
#define NNB_MACROS_HPP

#define NNB_STRINGIFY(x) #x
#define NNB_STRINGIFY_(x) NNB_STRINGIFY(x)
#define NNB__LINE__S NNB_STRINGIFY_(__LINE__)

#endif
