// File: log.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 23-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_LOG_HPP
#define NNB_LOG_HPP

// Public
#include <iostream>

// Private
#include "nnb/utils/macros.hpp"
#include "nnb/utils/NewlineOnDestruct.hpp"
#include "nnb/utils/NullStream.hpp"

#define NNB_LOG (nnb::NewlineOnDestruct(), std::cout << "[" << __BASE_FILE__ << ":" << NNB__LINE__S << "] ")

#ifdef NNB_LOGLVL_VERBOSE
	#undef NNB_LOGLVL_VERBOSE
	#define NNB_LOGLVL_VERBOSE 1
	#undef NNB_LOGLVL_DEBUG
	#define NNB_LOGLVL_DEBUG 1
	#undef NNB_LOGLVL_RELEASE
	#define NNB_LOGLVL_RELEASE 1
#else
	#define NNB_LOGLVL_VERBOSE 0
#endif

#ifdef NNB_LOGLVL_DEBUG
	#undef NNB_LOGLVL_DEBUG
	#define NNB_LOGLVL_DEBUG 1
	#undef NNB_LOGLVL_RELEASE
	#define NNB_LOGLVL_RELEASE 1
#else
	#define NNB_LOGLVL_DEBUG 0
#endif

#ifndef NNB_LOGLVL_QUIET
	#undef NNB_LOGLVL_RELEASE
	#define NNB_LOGLVL_RELEASE 1
#else
	#undef NNB_LOGLVL_VERBOSE
	#define NNB_LOGLVL_VERBOSE 0
	#undef NNB_LOGLVL_DEBUG
	#define NNB_LOGLVL_DEBUG 0
	#undef NNB_LOGLVL_RELEASE
	#define NNB_LOGLVL_RELEASE 0
#endif

#define NNB_TRACE \
	if (!NNB_LOGLVL_VERBOSE) {} \
	else NNB_LOG

#define NNB_WARNING \
	if (!NNB_LOGLVL_DEBUG) {} \
	else NNB_LOG

#define NNB_DEBUG \
	if (!NNB_LOGLVL_DEBUG) {} \
	else NNB_LOG

#define NNB_ERROR \
	if (!NNB_LOGLVL_RELEASE) {} \
	else NNB_LOG 

#define NNB_INFO \
	if (!NNB_LOGLVL_RELEASE) {} \
	else NNB_LOG

#endif
