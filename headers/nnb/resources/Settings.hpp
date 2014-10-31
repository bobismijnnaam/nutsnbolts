// File: Settings.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-10-25
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_SETTINGS_HPP
#define NNB_SETTINGS_HPP

// Public
#include <unordered_map>

// Private

namespace nnb {
	
	class Settings {
	public:
		Settings();
		Settings(std::string db_);
		~Settings();

		std::string get(std::string key);
		int getInt(std::string key);
		float getFloat(std::string key);

		bool import(std::string db_);
		bool hasImported();
		std::string getDB();

		static std::string const SETTINGS_EMPTY ;

	private:
		std::unordered_map<std::string, std::string> dict;
		bool imported;
		std::string db;
	} ;

}


#endif
