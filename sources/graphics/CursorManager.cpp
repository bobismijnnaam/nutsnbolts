// File: CursorManager.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-06-12
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cstring>

// Private
#include "nnb/log/log.hpp"
#include "nnb/graphics/CursorManager.hpp"
#include "nnb/utils/SDL_Helpers.hpp"

namespace nnb {
	void CursorManager::setSystemCursor(Cursor sc) {
		SDL_SystemCursor desiredCursor = SDL_SYSTEM_CURSOR_ARROW;
		switch (sc) {
			case Cursor::Arrow:
				desiredCursor = SDL_SYSTEM_CURSOR_ARROW;
				break;
			case Cursor::Ibeam:
				desiredCursor = SDL_SYSTEM_CURSOR_IBEAM;
				break;
			case Cursor::Wait:
				desiredCursor = SDL_SYSTEM_CURSOR_WAIT;
				break;
			case Cursor::Crosshair:
				desiredCursor = SDL_SYSTEM_CURSOR_CROSSHAIR;
				break;
			case Cursor::WaitArrow:
				desiredCursor = SDL_SYSTEM_CURSOR_WAITARROW;
				break;
			case Cursor::Sizenwse:
				desiredCursor = SDL_SYSTEM_CURSOR_SIZENWSE;
				break;
			case Cursor::Sizenesw:
				desiredCursor = SDL_SYSTEM_CURSOR_SIZENESW;
				break;
			case Cursor::Sizewe:
				desiredCursor = SDL_SYSTEM_CURSOR_SIZEWE;
				break;
			case Cursor::Sizens:
				desiredCursor = SDL_SYSTEM_CURSOR_SIZENS;
				break;
			case Cursor::SizeAll:
				desiredCursor = SDL_SYSTEM_CURSOR_SIZEALL;
				break;
			case Cursor::No:
				desiredCursor = SDL_SYSTEM_CURSOR_NO;
				break;
			case Cursor::Hand:
				desiredCursor = SDL_SYSTEM_CURSOR_HAND;
				break;
		}
		
		setCursor(SDL_CreateSystemCursor(desiredCursor));
	}

	bool CursorManager::loadMonoCursor(std::string file, int hotX, int hotY, Channel chan) {
		Image cursorImg;
		if (!cursorImg.loadFile(file)) {
			NNB_ERROR << "File not found: " << file;
			return false;
		}

		loadMonoCursor(cursorImg, hotX, hotY, chan);
		return true;
	}

	void CursorManager::loadMonoCursor(Image const & img, int hotX, int hotY, Channel chan) {
		if (img.getWidth() % 8 != 0 || img.getHeight() % 8 != 0) {
			NNB_ERROR << "Image dimensions are not a multiple of 8";
		}

		int bufSize = img.getHeight() * (img.getHeight() / 8);
		std::unique_ptr<Uint8[]> data(new Uint8[bufSize]);
		std::unique_ptr<Uint8[]> mask(new Uint8[bufSize]);
		
		int i = -1;
		for (int y = 0; y < img.getHeight(); ++y) {
			for (int x = 0; x < img.getWidth(); ++x) {
				if (x % 8 == 0) {
					++i;
					data.get()[i] = 0;
					mask.get()[i] = 0;
				} else {
					data[i] <<= 1;
					mask[i] <<= 1;
				}

				int intensity = 0;
				int alpha = 0;

				// Acquire intensity and alpha
				Color c = img.getColor(x, y);
				alpha = c.a;
				switch(chan) {
					case Channel::Red:
						intensity = c.r;
						break;
					case Channel::Blue:
						intensity = c.b;
						break;
					case Channel::Green:
						intensity = c.g;
						break;
					default:
						NNB_ERROR << "This case should never happen";
						break;
				}

				if (intensity < 128) data.get()[i] |= 0x01;
				if (alpha >= 128) mask.get()[i] |= 0x01;
			}
		}

		setCursor(SDL_CreateCursor(data.get(), mask.get(), img.getWidth(), img.getHeight(), hotX, hotY));
	}

	bool CursorManager::loadColorCursor(std::string file, int hotX, int hotY) {
		Image cursorImg;
		if (!cursorImg.loadFile(file)) {
			NNB_ERROR << "File not found: " << file;
			return false;
		}

		loadColorCursor(cursorImg, hotX, hotY);
		return true;
	}

	void CursorManager::loadColorCursor(Image img, int hotX, int hotY) {
		auto surf = imageToSDL_Surface(img);
		auto surfPrime = surf.release();
		setCursor(SDL_CreateColorCursor(surfPrime, hotX, hotY), surfPrime);
	}

	void CursorManager::setCursor(SDL_Cursor *newCur, SDL_Surface *newSurface) {
		currCursor.reset(newCur);
		currSurface.reset(newSurface);

		SDL_SetCursor(currCursor.get());
	}
}
