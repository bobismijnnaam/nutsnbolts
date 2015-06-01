// File: Image.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-29
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cstring>

// Private
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/graphics/Image.hpp"
#include "nnb/graphics/Color.hpp"
#include "nnb/utils/macros.hpp"

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
	Image::Image(std::string file) :
	w{0},
	h{0} {
		if (endsWith(file, ".png")) {
			loadPng(file);
		} else if (endsWith(file, ".jpg") || endsWith(file, ".jpeg")) {
			loadJpeg(file);
		}
	}

	Image::Image(Image const &other) :
	w{0},
	h{0},
	colorMod{other.colorMod},
	doColorModulation{other.doColorModulation} {
		ensureBufferSize(w, h);
		std::memcpy(img.get(), other.img.get(), w * h * 4);
	}

	// Helper function to construct an image from a file
	std::unique_ptr<Image> Image::fromFile(std::string file) {
		std::unique_ptr<Image> result = std::unique_ptr<Image>(new Image(file));

		return std::move(result);
	}

	std::unique_ptr<Image> Image::fromBytesRGB(unsigned char* src, int srcW, int srcH) {
		std::unique_ptr<Image> img(new Image(srcW, srcH));
		img->loadBytesRGB(src, srcW, srcH);

		return std::move(img);
	}

	std::unique_ptr<Image> Image::fromBytesGray(unsigned char* src, int srcW, int srcH) {
		std::unique_ptr<Image> img(new Image(srcW, srcH));
		img->loadBytesGray(src, srcW, srcH);

		return std::move(img);
	}

	// Constructs an image from a png
	void Image::loadPng(std::string file) {
		// TODO: Implement this shit

		//// Load the png
		//png::image<png::rgba_pixel> pngImg(file);
		
		//// Only reallocate memory if the current buffer has a different size
		//if (!(w == (int) pngImg.get_width() && h == (int) pngImg.get_height())) {
			//w = pngImg.get_width();
			//h = pngImg.get_height();
			//img.reset(new unsigned char[w * h * 4]);
		//}

		//// Copy colors
		//for (int y = 0; y < h; ++y) {
			//auto row = pngImg[y];
			//for (int x = 0; x < w; ++x) {
				//auto pixel = row[x];
				//setColor(x, y, {pixel.red, pixel.green, pixel.blue, pixel.alpha});
			//}
		//}

		// pngImg is deallocated here
	}

	// Constructs an image instance from a jpeg
	void Image::loadJpeg(std::string file) {
		// TODO: Implement this

   /*     // Initialize jpeg image*/
		//JPEGReader jpegImg;
		//jpegImg.header(file);
		//jpegImg.setColorSpace(JPEG::ColorSpace::COLOR_RGB);

		//// Prepare jpeg buffer
		//std::vector<std::unique_ptr<unsigned char>> gc;
		//auto rowsGC = std::unique_ptr<unsigned char*>(new unsigned char*[jpegImg.height()]);
		//auto rows = rowsGC.get();
		//for (size_t y = 0; y < jpegImg.height(); ++y) {
			//auto row = new unsigned char[jpegImg.width() * jpegImg.components()];
			//rows[y] = row;
			//gc.push_back(std::unique_ptr<unsigned char>(row));
		//}
		
		//// Load into buffer
		//jpegImg.load(rows);

		//// Check if image buffer should be resized
		//if (!(w == (int) jpegImg.width() && h == (int) jpegImg.height())) {
			//w = jpegImg.width();
			//h = jpegImg.height();
			//img.reset(new unsigned char[w * h * 4]);
		//}

		//// Copy over 
		//for (int y = 0; y < h; ++y) {
			//for (int x = 0; x < w; ++x) {
				//setColor(x, y, {rows[y][x * 3], rows[y][x * 3 + 1], rows[y][x * 3 + 2], 255});
			//}
		//}

		/*// rows/hRows should be automatically cleaned up now*/
	}

	// Saves the image as a png
	void Image::savePng(std::string file) {
		// TODO: Implement this

   /*     png::image<png::rgba_pixel> pngImg(w, h);*/

		//for (int y = 0; y < h; ++y) {
			//auto& row = pngImg[y];
			//for (int x = 0; x < w; ++x) {
				//Color c = getColor(x, y);
				//row[x].red = c.r;
				//row[x].green = c.g;
				//row[x].blue = c.b;
				//row[x].alpha = c.a;
			//}
		//}

		/*pngImg.write(file);*/
	}

	// Saves the image as a jpeg
	void Image::saveJpeg(std::string file, int quality) {
		// TODO: Implement this

   /*     // Initializa jpeg writer*/
		//JPEGWriter jpegImg;
		//jpegImg.header(w, h, 3, JPEG::COLOR_RGB);
		//jpegImg.setQuality(quality);

		//// Prepare jpeg buffer
		//std::vector<std::unique_ptr<unsigned char>> gc;
		//auto rowsGC = std::unique_ptr<unsigned char*>(new unsigned char*[h]);
		//auto rows = rowsGC.get();
		//for (int y = 0; y < h; ++y) {
			//gc.push_back(std::unique_ptr<unsigned char>(new unsigned char[w * 3]));
			//rows[y] = gc.back().get();
		//}

		//// Write to jpeg buffer
		//for (int y = 0; y < h; ++y) {
			//auto row = rows[y];
			//for (int x = 0; x < w; ++x) {
				//Color c = getColor(x, y);
				//row[x * 3] = c.r;
				//row[x * 3 + 1] = c.g;
				//row[x * 3 + 2] = c.b;
			//}
		//}

		//// Write to jpeg file
		//jpegImg.write(file, rows);

		/*// Buffers should be automatically deallocated here*/
	}

	// Copies RGB values at full opacity to images
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
		auto newImg = std::unique_ptr<unsigned char>(new unsigned char[newW * newH * 4]);

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
	std::unique_ptr<Image> Image::getResized(int newW, int newH) const {
		// Acquire new image instance
		auto newImg = clone();

		// Apply resize
		newImg->resize(newW, newH);

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
	std::unique_ptr<Image> Image::getScaled(float pw, float ph) const {
		auto newImg = clone();
		newImg->scale(pw, ph);

		return std::move(newImg);
	}

	Color Image::getColor(int x, int y) const {
		if (!doColorModulation) {
			return {
				img.get()[y * w * 4 + x * 4],
				img.get()[y * w * 4 + x * 4 + 1],
				img.get()[y * w * 4 + x * 4 + 2],
				img.get()[y * w * 4 + x * 4 + 3],
			};
		} else {
			return {
				(unsigned char) (img.get()[y * w * 4 + x * 4] / 255.0 * colorMod.r),
				(unsigned char) (img.get()[y * w * 4 + x * 4 + 1] / 255.0 * colorMod.g),
				(unsigned char) (img.get()[y * w * 4 + x * 4 + 2] / 255.0 * colorMod.b),
				(unsigned char) (img.get()[y * w * 4 + x * 4 + 3] / 255.0 * colorMod.a),
			};
		}
	}

	void Image::setColor(int x, int y, Color c) {
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
   /*     for (int i = 0; i < w * h; ++i) {*/
			//img.get()[i * 4] = c.r;
			//img.get()[i * 4 + 1] = c.g;
			//img.get()[i * 4 + 2] = c.b;
			//img.get()
		/*}*/
	}

	//void Image::floodFillAlpha(Color c) {
		//for (int y = 0; y < h; ++y) {
			//for (int x = 0; x < w; ++x) {
				//setColor(x, y, c);
			//}
		//}
	//}

	int Image::getWidth() const {
		return w;
	}

	int Image::getHeight() const {
		return h;
	}

	// Pastes an images disregaring alpha channel, taking into account a given alpha channel
	void Image::copyImage(int x, int y, Image const * otherImg, unsigned char alpha) {
		// Check if the image is at least 1 pixel in size
		if (otherImg->getWidth() <= 0 || otherImg->getHeight() <= 0) {
			return;
		}

		// Check if image is not outside of the image
		if (x >= w || y >= h) {
			return;
		}

		// Check if image is not on the... Other outside of the image
		if (x + otherImg->getWidth() <= 0 || y + otherImg->getHeight() <= 0) {
			return;
		}
		
		int sy = 0;
		int sh = otherImg->getHeight();
		int sx = 0;
		int sw = otherImg->getWidth();

		// Find out the specific region that needs to be copied, in case it's only a partial paste
		if (y < 0) {
			sy = y * -1;
		}

		if (x < 0) {
			sx = x * -1;
		}

		if (x + sw >= w) {
			sw = w - x;
		}

		if (y + sh >= h) {
			sh = h - y;
		}

		if (alpha == 255) { // If alpha is 255, just copy all the pixels
			for (int otherY = sy; otherY < sh; ++otherY) {
				for (int otherX = sx; otherX < sw; ++otherX) {
					setColor(x + otherX, y + otherY, otherImg->getColor(otherX, otherY));
				}
			}
		} else { // If not, blend the pixels with the alpha value
			for (int otherY = sy; otherY < sh; ++otherY) {
				for (int otherX = sx; otherX < sw; ++otherX) {
					Color oc = otherImg->getColor(otherX, otherY);
					Color c = getColor(x + otherX, y + otherY);

					c.r = (c.r * (255 - alpha) + oc.r * alpha) / 255;
					c.g = (c.g * (255 - alpha) + oc.g * alpha) / 255;
					c.b = (c.b * (255 - alpha) + oc.b * alpha) / 255;

					setColor(x + otherX, y + otherY, c);
				}
			}
		}
	}

	// Pastes an image assuming pre-multiplied alpha is the case
	void Image::pasteImage(int x, int y, Image const * otherImg) {
		// TODO: Continue here
		// See Image::pasteImage for comments on the first few statements
		if (otherImg->getWidth() <= 0 || otherImg->getHeight() <= 0) {
			return;
		}

		if (x >= w || y >= h) {
			return;
		}

		if (x + otherImg->getWidth() <= 0 || y + otherImg->getHeight() <= 0) {
			return;
		}

		int sy = 0;
		int sh = otherImg->getHeight();
		int sx = 0;
		int sw = otherImg->getWidth();

		if (y < 0) {
			sy = y * -1;
		}

		if (x < 0) {
			sx = x * -1;
		}

		if (x + sw>= getWidth()) {
			sw = getWidth() - x;
		}

		if (y + sh >= getHeight()) {
			sh = getHeight() - y;
		}

		for (int otherY = sy; otherY < sh; ++otherY) {
			for (int otherX = sx; otherX < sw; ++otherX) {
				// First we convert the colors to tints
				// Which are colors in the range [0,1] instead of [0, 255]
				Tint ot = toTint(otherImg->getColor(otherX, otherY));
				Tint t = toTint(getColor(x + otherX, y + otherY));

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

				setColor(x + otherX, y + otherY, toColor(rt));
			}
		}
	}

	// Creates an entirely separate instance of Image identical to this. It has absolutely NO shared resources! :D
	std::unique_ptr<Image> Image::clone() const {
		// Create new Image instance
		std::unique_ptr<Image> newImg(new Image(w, h));

		// Copy raw bytes over
		std::memcpy(newImg->img.get(), img.get(), w * h * 4);

		// Copy the rest of the settings
		newImg->colorMod = colorMod;
		newImg->doColorModulation = doColorModulation;

		return std::move(newImg);
	}

	void Image::copyImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const * otherImg) {
		if (sx + sw < 0 || sx >= otherImg->getWidth()) return;
		if (sy + sh < 0 || sy >= otherImg->getHeight()) return;

		int nsx = sx;
		int nsw = sw;
		if (sx < 0) {
			nsx = 0;
			nsw = sw - sx;
		}
		if (nsx + nsw >= otherImg->getWidth()) {
			nsw = otherImg->getWidth() - nsx;
		}
		
		int nsy = sy;
		int nsh = sh;
		if (sy < 0) {
			nsy = 0;
			nsh = sh - sy;
		}
		if (nsy + nsh >= otherImg->getHeight()) {
			nsh = otherImg->getHeight() - nsy;
		}
		
		Image timg(nsw, nsh);

		for (int ty = 0; y < nsh; ++y) {
			for (int tx = 0; x < nsw; ++x) {
				timg.setColor(tx, ty, otherImg->getColor(nsx + tx, nsy + ty));
			}
		}

		copyImage(x, y, &timg);
	}

	void Image::pasteImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const * otherImg) {
		if (sx + sw < 0 || sx >= otherImg->getWidth()) return;
		if (sy + sh < 0 || sy >= otherImg->getHeight()) return;

		int nsx = sx;
		int nsw = sw;
		if (sx < 0) {
			nsx = 0;
			nsw = sw - sx;
		}
		if (nsx + nsw >= otherImg->getWidth()) {
			nsw = otherImg->getWidth() - nsx;
		}
		
		int nsy = sy;
		int nsh = sh;
		if (sy < 0) {
			nsy = 0;
			nsh = sh - sy;
		}
		if (nsy + nsh >= otherImg->getHeight()) {
			nsh = otherImg->getHeight() - nsy;
		}
		
		Image timg(nsw, nsh, {0, 0, 0, 0});

		for (int ty = 0; ty < nsh; ++ty) {
			for (int tx = 0; tx < nsw; ++tx) {
				timg.setColor(tx, ty, otherImg->getColor(nsx + tx, nsy + ty));
			}
		}

		pasteImage(x, y, &timg);
	}

	// Sets the color modulation
	void Image::setModulation(Color colorMod_) {
		colorMod = colorMod_;

		doColorModulation = !(colorMod == Color(255, 255, 255, 255));
	}

	std::string Image::printColors() {
		std::string result = "";
		result += "[";
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				for (int c = 0; c < 4; ++c) {
					result += nnb::tos((int) img.get()[y * w * 4 + x * 4 + c]) + " ";
				}
				result += " | ";
			}
		}
		result += "]";

		return result;
	}

	unsigned char* Image::getBuffer() {
		return img.get();
	}
}

