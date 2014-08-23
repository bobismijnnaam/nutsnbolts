// File: NewlineOnDestruct.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_NEWLINEONDESTRUCT_HPP
#define NNB_NEWLINEONDESTRUCT_HPP

// Src: stackoverflow.com/questions/12903814/make-a-c-macro-that-acts-like-a-stream

// Public
#include <iostream>

// Private

namespace nnb {
	
	struct NewlineOnDestruct {
	public:
		NewlineOnDestruct() {}
		~NewlineOnDestruct() { 
			std::cout << std::endl;
		}

	private:

	};

}

#endif
