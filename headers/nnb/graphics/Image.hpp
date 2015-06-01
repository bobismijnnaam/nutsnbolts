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

namespace nnb {
	class Image {
	public:
		Image();
		Image(int w_, int h_, Color baseColor = {0, 0, 0, 255});
		Image(std::string file);
		Image(Image const &other);

		static std::unique_ptr<Image> fromFile(std::string file);
		static std::unique_ptr<Image> fromBytesRGB(unsigned char* src, int srcW, int srcH);
		static std::unique_ptr<Image> fromBytesGray(unsigned char* src, int srcW, int srcH);

		void loadPng(std::string file);
		void loadJpeg(std::string file);
		void savePng(std::string file);
		void saveJpeg(std::string file, int quality = 80);
		void loadBytesRGB(unsigned char* src, int srcW, int srcH);
		void loadBytesGray(unsigned char* src, int srcW, int srcH);

		void ensureBufferSize(int width, int height);
		
		void resize(int newW, int newH);
		std::unique_ptr<Image> getResized(int newW, int newH) const;
		void scale(float pw, float ph = 0);
		std::unique_ptr<Image> getScaled(float pw, float ph = 0) const;
		Color getColor(int x, int y) const;
		void setColor(int x, int y, Color c);
		void floodFill(Color c);
		//void floodFillAlpha(Color c);
		int getWidth() const;
		int getHeight() const;
		void copyImage(int x, int y, Image const * img, unsigned char alpha = 255);
		void pasteImage(int x, int y, Image const * img);
		void copyImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const * otherImg);
		void pasteImageRegion(int x, int y, int sx, int sy, int sw, int sh, Image const * otherImg);
		void setModulation(Color colorMod = {255, 255, 255, 255});
		std::unique_ptr<Image> clone() const;

		std::string printColors();
		unsigned char* getBuffer();

	private:
		int w, h;
		std::unique_ptr<unsigned char> img;
		Color colorMod = {255, 255, 255, 255};
		bool doColorModulation = false;

	} ;
}

#endif // MJ3_IMAGE_HPP
