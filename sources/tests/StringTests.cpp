// File: StringTests.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-29
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>

// Private
#include "catch.hpp"
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/log/log.hpp"

TEST_CASE("String functions", "[string]") {
	std::string example = "Pack my box with five dozen liquor jugs.";

	std::tuple<std::string, std::string> left, right;
	left = std::make_tuple("Pack", "my box with five dozen liquor jugs.");
	right = std::make_tuple("Pack my box with five dozen liquor", "jugs.");

	auto otherR = nnb::chopRight(example, " ");
	NNB_INFO << std::get<0>(otherR) << "|" << std::get<1>(otherR);

	REQUIRE(left == nnb::chopLeft(example, " "));
	REQUIRE(right == nnb::chopRight(example, " "));

	REQUIRE(nnb::endsWith(example, " liquor jugs."));
	REQUIRE_FALSE(nnb::endsWith(example, "obviously not the ending"));
	REQUIRE(nnb::beginsWith(example, "Pack my box wi"));
	REQUIRE_FALSE(nnb::beginsWith(example, "Totally something else "));

	std::vector<std::string> splitted = {"Pack","my","box","with","five","dozen","liquor","jugs."};
	REQUIRE(nnb::split(example, " ") == splitted);

	REQUIRE(nnb::contains(example, "ith five do"));
}

