// File: Image.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-29
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_IMAGE_HPP
#define NNB_IMAGE_HPP

// Public
#include <string>
#include <memory>

// Private
#include "Color.hpp"

// TODO: Add out of bounds policies: a few options, for example transparent,
// which gives back a transparent black pixel when you do getPixel out of bounds.
// Or wrap, which wraps to the other side if you do getpixel. Should also
// work for setpixel? Makes all the intersection stuff a lot easier and keeps working
// when an edge case occurs, but still shows you that something went wrong.

namespace nnb {
	enum class PixelWrap {
		Repeat,
		MirroredRepeat,
		Edge,
		Border
	} ;

	class Image {
	public:
		Image();
		Image(Image const &other);
		Image& operator=(Image const &other); 
		Image(Image&& other) = default; 	
		Image& operator=(Image&& other) = default;

		Image(int w_, int h_, Color baseColor = {0, 0, 0, 255});
		Image(std::string file);

		static Image fromFile(std::string file);
		static Image fromBytesRGB(unsigned char* src, int srcW, int srcH);
		static Image fromBytesRGBA(unsigned char* src, int srcW, int srcH);
		static Image fromBytesGray(unsigned char* src, int srcW, int srcH);

		void loadPng(std::string file);
		void loadJpeg(std::string file);
		bool savePng(std::string file);
		bool saveJpeg(std::string file, int quality = 80);
		void loadBytesRGB(unsigned char* src, int srcW, int srcH);
		void loadBytesRGBA(unsigned char* src, int srcW, int srcH);
		void loadBytesGray(unsigned char* src, int srcW, int srcH);

		void ensureBufferSize(int width, int height);
		
		void resize(int newW, int newH);
		Image getResized(int newW, int newH) const;
		void scale(float pw, float ph = 0);
		Image getScaled(float pw, float ph = 0) const;
		Color getColor(int x, int y) const;
		void setColor(int x, int y, Color c);
		void floodFill(Color c);
		int getWidth() const;
		int getHeight() const;
		void copyImage(int x, int y, Image const * img, unsigned char alpha = 255);
		void pasteImage(int x, int y, Image const * img);
		void copyImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const * otherImg);
		void pasteImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const * otherImg);
		void setModulation(Color colorMod = {255, 255, 255, 255});
		Image clone() const;
		void setWrapMode(PixelWrap wrap_, Color border_ = {0, 0, 0, 0});

		unsigned char* getBuffer();

		std::string toString() const;
		friend std::ostream& operator<<(std::ostream& os, const Image &i);

	private:
		int w, h;
		std::unique_ptr<unsigned char[]> img;
		Color colorMod = {255, 255, 255, 255};
		bool doColorModulation = false;
		PixelWrap wrap = PixelWrap::Border;
		Color border = {0, 0, 0, 0};

	} ;
}

#endif // MJ3_IMAGE_HPP
