// File: Image.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-29
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cstring>
#include <stdio.h>

// Private
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/graphics/Image.hpp"
#include "nnb/utils/ImageLoaders.hpp"
#include "nnb/graphics/Color.hpp"
#include "nnb/utils/macros.hpp"
#include "nnb/utils/Rect.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/Directory.hpp"
#include "nnb/resources/CustomDeleters.hpp"
#include "nnb/utils/unique_ptr.hpp"

namespace nnb {
	// Default constructor. Constructs an empty transparent image of 0 pixels
	Image::Image() :
	w{0},
	h{0},
   	img{new unsigned char[0]()} {}

	// Constructs a black opaque image
	Image::Image(int w_, int h_, Color baseColor) :
   	w{w_},
	h{h_},
	img{new unsigned char[w * h * 4]()}	{
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				setColor(x, y, baseColor);
			}
		}
	}

	// Constructs an image from a file
	bool Image::loadFile(std::string file) {
		if (endsWith(file, ".png")) {
			return loadPng(file);
		} else if (endsWith(file, ".jpg") || endsWith(file, ".jpeg")) {
			return loadJpeg(file);
		} else {
			NNB_ERROR << "Unknown file format: " << file;
			return false;
		}
	}

	Image::Image(Image const &other) :
	w{0},
	h{0},
	colorMod{other.colorMod},
	doColorModulation{other.doColorModulation},
	wrap{other.wrap},
	border{other.border} {
		ensureBufferSize(w, h);
		std::memcpy(img.get(), other.img.get(), w * h * 4);
	}

	Image& Image::operator=(Image const &other) {
		colorMod = other.colorMod;
		doColorModulation = other.doColorModulation;
		wrap = other.wrap;
		border = other.border;

		ensureBufferSize(other.w, other.h);

		std::memcpy(img.get(), other.img.get(), w * h * 4);

		return *this;
	}

	// Helper function to construct an image from a file
	Image Image::fromFile(std::string file) {
		Image result;
		result.loadFile(file);

		return std::move(result);
	}

	Image Image::fromBytesRGB(unsigned char* src, int srcW, int srcH) {
		Image img(srcW, srcH);
		img.loadBytesRGB(src, srcW, srcH);

		return std::move(img);
	}

	Image Image::fromBytesRGBA(unsigned char* src, int srcW, int srcH) {
		Image img(srcW, srcH);
		img.loadBytesRGBA(src, srcW, srcH);

		return std::move(img);
	}

	Image Image::fromBytesGray(unsigned char* src, int srcW, int srcH) {
		Image img(srcW, srcH);
		img.loadBytesGray(src, srcW, srcH);

		return std::move(img);
	}

	// Constructs an image from a png
	bool Image::loadPng(std::string file) {
		int imW = -1, imH = -1;
		auto imgBuf = readPng(file, &imW, &imH);
		if (imgBuf.get() != nullptr) {
			// Success
			loadBytesRGBA(imgBuf.get(), imW, imH);
			return true;
		} else {
			// Failure
			NNB_ERROR << "Failed to load png: " << file;
			return false;
		}
	}

	// Constructs an image instance from a jpeg
	bool Image::loadJpeg(std::string file) {
		int imW = -1, imH = -1;
		auto imgBuf = readJpeg(file, &imW, &imH);
		if (imgBuf.get() != nullptr) {
			// Success
			loadBytesRGBA(imgBuf.get(), imW, imH);
			return true;
		} else {
			// Failure
			NNB_ERROR << "Failed to load jpeg: " << file;
			return false;
		}
	}

	// Saves the image as a png
	bool Image::savePng(std::string file) {
		if (!writePng(img.get(), w, h, file)) {
			NNB_ERROR << "Failed to write png to file: " << file;
			return false;
		}

		return true;
	}

	// Saves the image as a jpeg
	bool Image::saveJpeg(std::string file, int quality) {
		if (!writeJpeg(img.get(), w, h, file, quality)) {
			NNB_ERROR << "Failed to write jpeg to file: " << file;
			return false;
		}

		return true;
	}

	// Copies RGBA values to image
	void Image::loadBytesRGBA(unsigned char* src, int srcW, int srcH) {
		ensureBufferSize(srcW, srcH);

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; ++x) {
				setColor(x, y, {src[y * w * 4 + x*4], src[y * w * 4 + x * 4 + 1], src[y * w * 4 + x * 4 + 2], src[y * w * 4 + x * 4 + 3]});
			}
		}
	}
	
	// Copies RGB values at full opacity to image
	void Image::loadBytesRGB(unsigned char* src, int srcW, int srcH) {
		ensureBufferSize(srcW, srcH);

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; ++x) {
				setColor(x, y, {src[y * w * 3 + x*3], src[y * w *3 + x * 3 + 1], src[y * w * 3 + x * 3 + 2], 255});
			}
		}
	}

	// Copies a series of grayscale values to all channels
	void Image::loadBytesGray(unsigned char* src, int srcW, int srcH) {
		ensureBufferSize(srcW, srcH);

		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				setColor(x, y, {src[y * w + x], src[y * w + x], src[y * w + x], 255});
			}
		}
	}

	void Image::ensureBufferSize(int width, int height) {
		if (!(width == w && height == h)) {
			w = width;
			h = height;
			img.reset(new unsigned char[w * h * 4]);
		}
	}

	// Resizes the image to the given resolution
	void Image::resize(int newW, int newH) {
		// Acquire buffer of new size
		auto newImg = std::unique_ptr<unsigned char[]>(new unsigned char[newW * newH * 4]);

		// Copy resized image to new image instance
		double dx = getWidth() / (double) newW;
		double dy = getHeight() / (double) newH;
		int px, py;
		for (int y = 0; y < newH; ++y) {
			for (int x = 0; x < newW; ++x) {
				px = std::floor(x * dx);
				py = std::floor(y * dy);

				Color c = getColor(px, py);
				newImg.get()[y * newW * 4 + x * 4] = c.r;
				newImg.get()[y * newW * 4 + x * 4 + 1] = c.g;
				newImg.get()[y * newW * 4 + x * 4 + 2] = c.b;
				newImg.get()[y * newW * 4 + x * 4 + 3] = c.a;
			}
		}

		// Replace buffer by new one and apply changes
		img = std::move(newImg);
		w = newW;
		h = newH;
	}

	// Returns a new resized instance of the current image
	Image Image::getResized(int newW, int newH) const {
		// Acquire new image instance
		auto newImg = clone();

		// Apply resize
		newImg.resize(newW, newH);

		// Return resized instance
		return std::move(newImg);
	}

	// Scales the current image
	void Image::scale(float pw, float ph) {
		int newW, newH;

		if (pw == 0) {
			newW = ph * w;
		} else {
			newW = pw * w;
		}

		if (ph == 0) {
			newH = pw * h;
		} else {
			newH = ph * h;
		}

		resize(newW, newH);
	}

	// Returns a scaled instance of the current image
	Image Image::getScaled(float pw, float ph) const {
		auto newImg = clone();
		newImg.scale(pw, ph);

		return std::move(newImg);
	}

	Color Image::getColor(int x, int y) const {
		Color c;

		if (x < 0 || x >= w || y < 0 || y >= h) {
			switch (wrap) {
				case PixelWrap::Border:
					c = border;
					break;
				default:
					NNB_ERROR << "An unimplemented pixel wrap mode was selected";
			}
		} else {
			c.r = img.get()[y * w * 4 + x * 4];
			c.g = img.get()[y * w * 4 + x * 4 + 1];
			c.b = img.get()[y * w * 4 + x * 4 + 2];
			c.a = img.get()[y * w * 4 + x * 4 + 3];
		}

		if (doColorModulation) {
				c.r = (unsigned char) (c.r / 255.0 * colorMod.r);
				c.g = (unsigned char) (c.g / 255.0 * colorMod.g);
				c.b = (unsigned char) (c.b / 255.0 * colorMod.b);
				c.a = (unsigned char) (c.a / 255.0 * colorMod.a);
		}

		return c;
	}

	void Image::setColor(int x, int y, Color c) {
		if (x < 0 || x >= w || y < 0 || y >= h) {
			return; // Fail silently
		} 

		img.get()[y * w * 4 + x * 4] = c.r;
		img.get()[y * w * 4 + x * 4 + 1] = c.g;
		img.get()[y * w * 4 + x * 4 + 2] = c.b;
		img.get()[y * w * 4 + x * 4 + 3] = c.a;
	}

	void Image::floodFill(Color c) {
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				setColor(x, y, c);
			}
		}
	}

	int Image::getWidth() const {
		return w;
	}

	int Image::getHeight() const {
		return h;
	}

	// Pastes an images disregaring alpha channel, taking into account a given alpha channel
	void Image::copyImage(int x, int y, Image const & otherImg, unsigned char alpha) {
		if (alpha == 255) {
			for (int sy = 0; sy < otherImg.getHeight(); ++sy) {
				for (int sx = 0; sx < otherImg.getWidth(); ++sx) {
					setColor(x + sx, y + sy, otherImg.getColor(sx, sy));	
				}
			}
		} else {
			for (int sy = 0; sy < otherImg.getHeight(); ++sy) {
				for (int sx = 0; sx < otherImg.getHeight(); ++sx) {
					Color oc = otherImg.getColor(sx, sy);
					Color c = getColor(x + sx, y + sy);

					c.r = (c.r * (255 - alpha) + oc.r * alpha) / 255;
					c.g = (c.g * (255 - alpha) + oc.g * alpha) / 255;
					c.b = (c.b * (255 - alpha) + oc.b * alpha) / 255;

					setColor(x + sx, y + sy, c);
				}
			}
		}
	}

	// Pastes an image assuming pre-multiplied alpha is the case
	void Image::pasteImage(int x, int y, Image const & otherImg) {
		for (int sy = 0; sy < otherImg.getHeight(); sy++) {
			for (int sx = 0; sx < otherImg.getWidth(); sx++) {
				// First we convert the colors to tints
				// Which are colors in the range [0,1] instead of [0, 255]
				Tint ot = toTint(otherImg.getColor(sx, sy));
				Tint t = toTint(getColor(x + sx, y + sy));

				// Some awkward alpha blending formulas I found on the interwebs
				Tint rt;
				rt.a = ot.a + t.a * (1.0 - ot.a);
				if (rt.a != 0) {
					// Used to be this:
					// rt.r = (ot.r * ot.a + t.r * (1.0 - ot.a)) / rt.a;
					// rt.g = (ot.g * ot.a + t.g * (1.0 - ot.a)) / rt.a;
					// rt.b = (ot.b * ot.a + t.b * (1.0 - ot.a)) / rt.a;
					// These are the formulas by wikipedia 
					// Above are the same formulas with the alpha components removed
					// With them it gave some sort of dark edges
					// Something with premultiplied alpha - leaving this here for future reference
					
					rt.r = (ot.r * ot.a + t.r * t.a * (1.0 - ot.a)) / rt.a;
					rt.g = (ot.g * ot.a + t.g * t.a * (1.0 - ot.a)) / rt.a;
					rt.b = (ot.b * ot.a + t.b * t.a * (1.0 - ot.a)) / rt.a;
				} else {
					rt.r = 0;
					rt.g = 0;
					rt.b = 0;
				}

				setColor(x + sx, y + sy, toColor(rt));
			}
		}
	}

	// Creates an entirely separate instance of Image identical to this. It has absolutely NO shared resources! :D
	Image Image::clone() const {
		// Create new Image instance
		Image newImg(w, h);

		// Copy raw bytes over
		std::memcpy(newImg.img.get(), img.get(), w * h * 4);

		// Copy the rest of the settings
		newImg.colorMod = colorMod;
		newImg.doColorModulation = doColorModulation;

		return std::move(newImg);
	}

	// TODO: Optimize the inbetween image away
	void Image::copyImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const & otherImg) {
		Image timg(sw, sh, {0, 0, 0, 0});

		for (int ty = 0; ty < sh; ++ty) {
			for (int tx = 0; tx < sw; ++tx) {
				timg.setColor(tx, ty, otherImg.getColor(tx + sx, ty + sy));
			}
		}

		copyImage(x, y, timg);
	}

	// TODO: Optimize the inbetween image away
	void Image::pasteImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const & otherImg) {
		Image timg(sw, sh, {0, 0, 0, 0});

		for (int ty = 0; ty < sh; ++ty) {
			for (int tx = 0; tx < sw; ++tx) {
				timg.setColor(tx, ty, otherImg.getColor(tx + sx, ty + sy));
			}
		}

		pasteImage(x, y, timg);
	}

	// Sets the color modulation
	void Image::setModulation(Color colorMod_) {
		colorMod = colorMod_;

		doColorModulation = !(colorMod == Color(255, 255, 255, 255));
	}

	void Image::setWrapMode(PixelWrap wrap_, Color border_) {
		wrap = wrap_;
		border = border_;

		// TODO: Implement remaining modes
		if (wrap != PixelWrap::Border) {
			switch (wrap) {
				case PixelWrap::Edge:
					NNB_ERROR << "WrapMode Edge is not yet implemented";
					break;
				case PixelWrap::MirroredRepeat:
					NNB_ERROR << "WrapMode MirroredRepeat is not yet implemented";
					break;
				case PixelWrap::Repeat:
					NNB_ERROR << "WrapMode Repeat is not yet implemented";
					break;
				default:
					NNB_ERROR << "This switch statement should not be activated";
			}
		}
	}

	unsigned char* Image::getBuffer() const {
		return img.get();
	}

	std::string Image::toString() const {
		std::string result = "";
		result.reserve(w * h * 4 * 3);

		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				Color c = getColor(x, y);
				result += nnb::tos(c.r) + " " ;
				result += nnb::tos(c.g) + " " ;
				result += nnb::tos(c.b) + " " ;
				result += nnb::tos(c.a) + " " ;
			}
		}

		return result;
	}

	std::ostream& operator<< (std::ostream& os, const Image &i) {
		os << i.toString(); 
		return os;
	}
	
}

