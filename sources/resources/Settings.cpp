// File: Settings.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-10-25
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <algorithm>
#include <fstream>
#include <string>

// Private
#include "nnb/resources/Settings.hpp"
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/constants.hpp"

std::string const nnb::Settings::SETTINGS_EMPTY = "__SETTINGS_EMPTY__";

nnb::Settings::Settings() :
imported{false},
db{SETTINGS_EMPTY} {
}

nnb::Settings::Settings(std::string db_) :
Settings() {
	import(db_);
}

nnb::Settings::~Settings() {
}

std::string nnb::Settings::get(std::string key) {
	auto result = dict.find(key);
	if (result != dict.end()) {
		return result->second;
	} else {
		NNB_ERROR << "Key \"" << key << "\" not found in settings";
		return "";
	}
}

int nnb::Settings::getInt(std::string key) {
	auto result = get(key);

	return nnb::stoi(result);
}

float nnb::Settings::getFloat(std::string key) {
	auto result = get(key);

	return nnb::stof(result);
}

bool nnb::Settings::import(std::string db_) {
	if (imported) {
		NNB_INFO << "Discarding imported settings from \"" << db << "\"";
		dict.clear();
		imported = false;
		db = SETTINGS_EMPTY;
	}

	std::ifstream file("media/settings/" + db_);
	std::string line;
	
	if (!file) {
		NNB_ERROR << "Error opening settings file " << db_;
		return nnb::FAILURE;
	}
	
	int linenum = 0;
	while(std::getline(file, line)) {
		if (!nnb::beginsWith(line, "//")) {
			if (nnb::contains(line, "=")) {
				std::vector<std::string> pair = nnb::chopLeft(line, "=");
				pair[0] = nnb::trim(pair[0]);
				pair[1] = nnb::trim(pair[1]);

				if (dict.find(pair[0]) == dict.end()) {
					dict[pair[0]] = pair[1];
				} else {
					NNB_ERROR << "Detected key \"" << pair[0] << "\" double on line " << linenum << " in settings file \"" << db_ << "\"";
				}
			}
		}

		++linenum;
	}

	imported = true;
	db = db_;

	NNB_INFO << "Imported settings \"" << db << "\"";

	return nnb::SUCCESS;
}

bool nnb::Settings::hasImported() {
	return imported;
}

std::string nnb::Settings::getDB() {
	return db;
}
