// File: CursorManager.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-06-12
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_CURSORMANAGER_HPP
#define NNB_CURSORMANAGER_HPP

// Public
#include <string>
#include <SDL2/SDL.h>

// Private
#include "nnb/graphics/Image.hpp"
#include "nnb/resources/CustomDeleters.hpp"

namespace nnb {
	enum class Cursor {
		Arrow,
		Ibeam,
		Wait,
		Crosshair,
		WaitArrow,
		Sizenwse,
		Sizenesw,
		Sizewe,
		Sizens,
		SizeAll,
		No,
		Hand
	} ;

	enum class Channel {
		Red,
		Green,
		Blue,
		Alpha
	} ;

	class CursorManager {
	public:
		void setSystemCursor(Cursor sc_);
		bool loadMonoCursor(std::string file, int hotX = 0, int hotY = 0, Channel chan = Channel::Red);
		void loadMonoCursor(Image const & img, int hotX = 0, int hotY = 0, Channel chan = Channel::Red);
		bool loadColorCursor(std::string file, int hotX = 0, int hotY = 0);
		void loadColorCursor(Image img, int hotX = 0, int hotY = 0);

	private:
		void setCursor(SDL_Cursor *newCur, SDL_Surface *newSurface = nullptr);

		std::unique_ptr<SDL_Cursor, SDLDeleter> currCursor;
		std::unique_ptr<SDL_Surface, SDLDeleter> currSurface;
	} ;
}

#endif // NNB_CURSORMANAGER_HPP

