// File: ImageTests.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-06-1
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <iostream>
#include <cstdlib>

// Private
#include "catch.hpp"
#include "nnb/graphics/Image.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"

TEST_CASE("Image class and image loading", "[img]") {
	SECTION("Image manipulation") {
		// TODO
	}

	SECTION("Memory management") {
		nnb::Image stackImg(100, 100, {50, 50, 50});

		auto heapImg = new nnb::Image(std::move(stackImg));

		CHECK(stackImg.getBuffer() == nullptr);
		CHECK(heapImg->getBuffer() != nullptr);

		nnb::Image otherStackImg(std::move(*heapImg));

		CHECK(heapImg->getBuffer() == nullptr);
		CHECK(otherStackImg.getBuffer() != nullptr);
	}

	SECTION("Image loading") {
		nnb::Image img;

		SECTION("Loading a PNG") {
			REQUIRE(img.loadPng("red3x3.png"));

			CHECK(img.getWidth() == 3);
			CHECK(img.getHeight() == 3);

			for (int y = 0; y < 3; ++y) {
				for (int x = 0; x < 3; ++x) {
					auto c = img.getColor(x, y);
					CHECK(c.r == 255);
					CHECK(c.g == 0);
					CHECK(c.b == 0);
					CHECK(c.a == 255);
				}
			}
		}

		SECTION("Loading a JPEG") {
			img.loadJpeg("red3x3.jpeg");

			CHECK(img.getWidth() == 3);
			CHECK(img.getHeight() == 3);

			for (int y = 0; y < 3; ++y) {
				for (int x = 0; x < 3; ++x) {
					auto c = img.getColor(x, y);
					CHECK((int) c.r == Approx(255).epsilon(5));
					CHECK((int) c.g == Approx(0).epsilon(5));
					CHECK((int) c.b == Approx(0).epsilon(5));
					CHECK((int) c.a == Approx(255).epsilon(5));
				}
			}
		}
	}

	SECTION("Image saving") {
		nnb::Image img(3, 3, {0, 0, 255});

		SECTION("Writing a PNG") {
			std::system("rm blue3x3.png");
			CHECK_FALSE(nnb::fileExists("blue3x3.png"));
			CHECK(img.savePng("blue3x3.png"));
			CHECK(nnb::fileExists("blue3x3.png"));

			nnb::Image finalImg;
			REQUIRE(finalImg.loadFile("blue3x3.png"));
			CHECK(finalImg.getWidth() == 3);
			CHECK(finalImg.getHeight() == 3);
			for (int y = 0; y < finalImg.getHeight(); ++y) {
				for (int x = 0; x < finalImg.getWidth(); ++x) {
					nnb::Color c = finalImg.getColor(x, y);
					CHECK(c.r == 0);
					CHECK(c.g == 0);
					CHECK(c.b == 255);
					CHECK(c.a == 255);
				}
			}
		}

		SECTION("Writing a JPEG") {
			std::system("rm blue3x3.jpeg");
			CHECK_FALSE(nnb::fileExists("blue3x3.jpeg"));
			CHECK(img.saveJpeg("blue3x3.jpeg", 100));
			CHECK(nnb::fileExists("blue3x3.jpeg"));

			nnb::Image finalImg;
			REQUIRE(finalImg.loadFile("blue3x3.jpeg"));
			CHECK(finalImg.getWidth() == 3);
			CHECK(finalImg.getHeight() == 3);
			for (int y = 0; y < finalImg.getHeight(); ++y) {
				for (int x = 0; x < finalImg.getWidth(); ++x) {
					nnb::Color c = finalImg.getColor(x, y);
					CHECK(c.r == Approx(0).epsilon(5));
					CHECK(c.g == Approx(0).epsilon(5));
					CHECK(c.b == Approx(255).epsilon(5));
					CHECK(c.a == Approx(255).epsilon(5));
				}
			}
		}
	}
}

