// File: Text.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-07-21
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_TEXT_HPP
#define NNB_TEXT_HPP

// Public
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>

// Private
#include "nnb/graphics/TextureContainer.hpp"
#include "nnb/utils/SDL_Helpers.hpp"
#include "nnb/resources/CustomDeleters.hpp"

namespace nnb {
	
	enum class HAlign {
		LEFT,
		CENTER,
		RIGHT
	} ;

	enum class VAlign {
		TOP,
		CENTER,
		BOTTOM
	} ;
	
	class Text {
	public:
		Text();
		Text(SDL_Renderer* tgt_, bool autoCommit_ = true);
		Text(const Text& other);
        Text& operator=(const Text& rhs);

		void setText(std::string text_);
		void setFont(TTF_Font *font_);
		void setPosition(int x_, int y_);
		void setX(int x_);
		void setY(int y_);
		void setHAlign(HAlign align_);
		void setVAlign(VAlign align_);
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
		HAlign halign;
		VAlign valign;
		nnb::TextureContainer txt;
		SDL_Renderer *tgt;
		SDL_Rect dst;
		SDL_Color clr;
		bool dirty = false;

		std::unique_ptr<SDL_Texture, nnb::SDLDeleter> txtTexture;

	} ;

}

#endif
