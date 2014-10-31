// File: NullStream.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: fr 24-10-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_NULLSTREAM_HPP
#define NNB_NULLSTREAM_HPP

// Public
#include <ostream>

// Private

// Source: http://stackoverflow.com/questions/11826554/standard-no-op-output-stream


namespace nnb {

	class NullBuffer : public std::streambuf {
	public:
		int overflow(int c);
	};

	class NullStream : public std::ostream {
	public:
		NullStream();
	private: 
		NullBuffer m_sb;
	};
	
	extern NullStream nullstream;
}

#endif
