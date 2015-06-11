// File: RectTests.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-06-01
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include <iostream>
#include <sstream>

// Private
#include "catch.hpp"
#include "nnb/utils/Rect.hpp"

TEST_CASE("Rect class and functionality", "[rect]") {
	nnb::Rect left{0, 0, 100, 100};
	nnb::Rect right;
	nnb::Rect overlap;
	nnb::Rect result;

	SECTION("Normal use") {
		right = {50, 50, 150, 150};
		overlap = {50, 50, 50, 50};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);

		right = {25, 25, 50, 50};
		overlap = {25, 25, 50, 50};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);

		right = {-25, -25, 150, 150};
		overlap = {0, 0, 100, 100};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);
	}

	SECTION("Nasty edge cases") {
		right = {-1, -1, 101, 101};
		overlap = {0, 0, 100, 100};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);

		right = {1, 1, 98, 98};
		overlap = {1, 1, 98, 98};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);

		right = {-1, 0, 100, 100};
		overlap = {0, 0, 99, 100};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);

		right = {1, 0, 100, 100};
		overlap = {1, 0, 99, 100};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);

		right = {0, 1, 100, 100};
		overlap = {0, 1, 100, 99};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);

		right = {0, -1, 100, 100};
		overlap = {0, 0, 100, 99};
		REQUIRE(left.intersect(right) == overlap);
		REQUIRE(right.intersect(left) == overlap);
	}

	SECTION("And ofcourse no intersections") {
		right = {50, 50, 50, 50};
		left = {0, 0, 50, 50};
		CHECK(left.intersect(right).isEmpty());
		CHECK(right.intersect(left).isEmpty());

		right = {0, -50, 50, 50};
		CHECK(left.intersect(right).isEmpty());
		CHECK(right.intersect(left).isEmpty());
		
		right = {-50, -50, 50, 50};
		CHECK(left.intersect(right).isEmpty());
		CHECK(right.intersect(left).isEmpty());

		right = {-50, -10, 150, 5};
		CHECK(left.intersect(right).isEmpty());
		CHECK(right.intersect(left).isEmpty());
	}
}

//TEST_CASE("String functions", "[string]") {
	//std::string example = "Pack my box with five dozen liquor jugs.";

	//std::tuple<std::string, std::string> left, right;
	//left = std::make_tuple("Pack", "my box with five dozen liquor jugs.");
	//right = std::make_tuple("Pack my box with five dozen liquor", "jugs.");

	//REQUIRE(left == nnb::chopLeft(example, " "));
	//REQUIRE(right == nnb::chopRight(example, " "));

	//REQUIRE(nnb::endsWith(example, " liquor jugs."));
	//REQUIRE_FALSE(nnb::endsWith(example, "obviously not the ending"));
	//REQUIRE(nnb::beginsWith(example, "Pack my box wi"));
	//REQUIRE_FALSE(nnb::beginsWith(example, "Totally something else "));

	//std::vector<std::string> splitted = {"Pack","my","box","with","five","dozen","liquor","jugs."};
	//REQUIRE(nnb::split(example, " ") == splitted);

	//REQUIRE(nnb::contains(example, "ith five do"));
//}


