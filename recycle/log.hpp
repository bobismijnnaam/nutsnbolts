// File: log.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 23-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)
// 
// This version uses a nullstream - but a faster version is possible using other macros!

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
	#ifndef NNB_LOGLVL_DEBUG
		#define NNB_LOGLVL_DEBUG
	#endif
	
#define NNB_TRACE NNB_LOG
#else
#define NNB_TRACE nnb::nullstream
#endif

#ifdef NNB_LOGLVL_DEBUG
	#define NNB_WARNING NNB_LOG
	#define NNB_DEBUG NNB_LOG
#else
	#define NNB_WARNING nnb::nullstream
	#define NNB_DEBUG nnb::nullstream
#endif

#define NNB_INFO NNB_LOG
#define NNB_ERROR NNB_LOG

#ifdef NNB_LOGLVL_QUIET
	#ifdef NNB_TRACE
		#undef NNB_TRACE
	#endif
	#define NNB_TRACE nnb::nullstream

	#ifdef NNB_DEBUG
		#undef NNB_DEBUG 
	#endif
	#define NNB_DEBUG nnb::nullstream

	#ifdef NNB_WARNING
		#undef NNB_WARNING 
	#endif
	#define NNB_WARNING nnb::nullstream

	#ifdef NNB_INFO
		#undef NNB_INFO  
	#endif
	#define NNB_INFO nnb::nullstream

	#ifdef NNB_ERROR
		#undef NNB_ERROR
	#endif
	#define NNB_ERROR nnb::nullstream
#endif

#endif
