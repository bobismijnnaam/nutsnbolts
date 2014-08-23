// File: PersistentText.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_PERSISTENTTEXT_HPP
#define NNB_PERSISTENTTEXT_HPP

// Public
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// Private
#include "nnb/graphics/PersistentTexture.hpp"
#include "nnb/utils/SDL_Helpers.hpp"

namespace nnb {
	
	enum class Align {
		LEFT,
		CENTER,
		RIGHT
	} ;
	
	class PersistentText {
	public:
		PersistentText();
		PersistentText(SDL_Renderer* tgt_, bool autoCommit_ = true);
		~PersistentText();

		void setText(std::string text_);
		void setFont(TTF_Font *font_);
		void setPosition(int x_, int y_);
		void setX(int x_);
		void setY(int y_);
		void setAlign(Align align_);
		void setColor(SDL_Color clr_);
		void setColor(int r, int g, int b);
		void setColor(nnb::Color clr_);
		void setAlpha(Uint8 alpha_);
		void setAutoCommit(bool autoCommit_);
		void calculateBounds();
		void commit();

		void render() const;

		int getWidth() const;
		int getHeight() const;
		int getX() const;
		int getY() const;
		SDL_Rect getBounds() const;

	private:
		bool autoCommit;
		int x = 0, y = 0;
		TTF_Font *font = NULL;
		std::string text = "";
		Align align;
		nnb::PersistentTexture txt;
		SDL_Renderer *tgt;
		SDL_Rect dst;
		SDL_Color clr;
		bool dirty = true;

	} ;

}

#endif
