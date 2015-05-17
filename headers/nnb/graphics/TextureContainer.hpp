// File: TextureContainer.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_TEXTURECONTAINER_HPP
#define NNB_TEXTURECONTAINER_HPP

// Public
#include "SDL2/SDL.h"

// Private 
#include "nnb/utils/SDL_Helpers.hpp"

namespace nnb {
	
	class TextureContainer {
	public:
		TextureContainer();
		TextureContainer(SDL_Renderer* tgt_, SDL_Texture* txt_);

		/* All constructors should be defined by default!
		 *TextureContainer(TextureContainer const &) = default;
		 *TextureContainer& operator=(TextureContainer const &) = default;
		 *TextureContainer& operator=(TextureContainer&&) = default;
		 *TextureContainer(TextureContainer&&) = default;
		 */

		void setSrcRect(SDL_Rect newRect);
		void setRotation(double newAngle);
		void setRotationCenter(SDL_Point newCenter);
		void setRotationCenter(int x, int y);
		void setOrigin(int x, int y);
		void setFlip(SDL_RendererFlip newFlip);
		
		void setAlpha(Uint8 newAlpha);
		void setBlendMode(SDL_BlendMode newBlendMode);
		void setColor(Uint8 r, Uint8 g, Uint8 b);
		void setColor(nnb::Color clr_);
		void setColor(SDL_Color clr_);

		SDL_Texture* getTexture() const;

		Uint8 getAlpha() const;
		SDL_BlendMode getBlendMode() const;
		SDL_Color getColor() const;

		void setTexture(SDL_Renderer* newTgt, SDL_Texture* newTxt);
		void move(int x, int y);
		void setPosition(int x, int y);
		void setX(int x);
		void setY(int y);
		void setSize(int w_, int h_);
		void setWidth(int w_);
		void setHeight(int h_);
		void resetSize();

		int getRenderWidth() const;
		int getRenderHeight() const;
		int getTextureWidth() const;
		int getTextureHeight() const;
		Uint32 getFormat() const;
		double getRotation() const;
		int getX() const;
		int getY() const;
		SDL_Rect getBounds() const;
		void render() const;

		TextureContainer clone() const;

	private:
		SDL_Renderer* tgt;
		SDL_Texture* txt;

		SDL_Rect src, dst;
		double angle;
		SDL_Point center;
		SDL_Point origin;
		SDL_RendererFlip flip;
		Uint8 alpha;
		SDL_BlendMode blendMode;
		SDL_Color clr;

		int w, h;
		Uint32 format;
	} ;

}

#endif

