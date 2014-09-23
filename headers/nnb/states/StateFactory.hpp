// File: StateFactory.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_STATEFACTORY_HPP
#define NNB_STATEFACTORY_HPP

// Public

// Private
#include "nnb/log/log.hpp"

namespace nnb {

	class AbstractStateFactory {
	public:
		AbstractStateFactory(){}
		virtual ~AbstractStateFactory(){}

		virtual State* get() = 0;
		virtual std::string getID() = 0;

	private:

	} ;

	template <
		class T
	>class SimpleStateFactory : public AbstractStateFactory {
	public:
		SimpleStateFactory(std::string id_) :
		id{id_} {
		}

		~SimpleStateFactory() {
		}

		virtual State* get() {
			State* newState = new T();
			newState->setID(id);
			return newState;
		}

		std::string getID() {
			return id;
		}

	private:
		std::string id;

	} ;

}

#endif
