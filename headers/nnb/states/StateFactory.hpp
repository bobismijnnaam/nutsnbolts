// File: StateFactory.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-01-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_STATEFACTORY_HPP
#define NNB_STATEFACTORY_HPP

// Public
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

// Private
#include "nnb/states/State.hpp"
#include "nnb/log/log.hpp"

namespace nnb {

	template < 
		class T
	>
	State* makeState() {
		return new T();
	}

	class GameStatePark {
	public: 

		template <
			class T
		>
		static void record() {
			auto e = nnb::GameStatePark::park.find(T::id);
			if (e == end(nnb::GameStatePark::park)) {
				nnb::GameStatePark::park[T::id] = makeState<T>;
				NNB_INFO << "Sucessfully added state \"" << T::id << "\"";
			} else {
				NNB_ERROR << "Duplicate ID found: \"" << T::id << "\", did not add it to collection";
			}
		}
			
		static nnb::State* get(std::string stateID);

	private:
		// static std::unordered_map<std::string, std::unique_ptr<AbstractStateFactory>> park;
		static std::unordered_map<std::string, std::function<State*(void)>> park;

	} ;

} 

#endif
