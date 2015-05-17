// File: TextureContainer.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include "SDL2/SDL.h"

// Private
#include "nnb/graphics/TextureContainer.hpp"
#include "nnb/log/log.hpp"

nnb::TextureContainer::TextureContainer() : TextureContainer(NULL, NULL) {}

nnb::TextureContainer::TextureContainer(SDL_Renderer* tgt_, SDL_Texture* txt_) :
tgt{tgt_},
txt{txt_},
src{0, 0, 0, 0},
dst{0, 0, 0, 0},
angle{0.0},
center{0, 0}, 
origin{0, 0},
flip{SDL_FLIP_NONE},
alpha{255},
blendMode{SDL_BLENDMODE_BLEND},
clr{255, 255, 255, 255},
w{0},
h{0},
format{0} {
	int err = SDL_QueryTexture(txt, &format, NULL, &w, &h);
	if (err != 0 && txt != NULL) {
		NNB_ERROR << "Unable to query texture properties. Error code " << err << ", error message: " << SDL_GetError();
	}

	src.w = w;
	src.h = h;
	dst.w = w;
	dst.h = h;

	setAlpha(alpha);
	setBlendMode(blendMode);
	setColor(clr);

}

void nnb::TextureContainer::setSrcRect(SDL_Rect newRect) {
	src = newRect;
}

void nnb::TextureContainer::setRotation(double newAngle) {
	angle = newAngle;
}

void nnb::TextureContainer::setRotationCenter(SDL_Point newCenter) {
	center = newCenter;
}

void nnb::TextureContainer::setRotationCenter(int x, int y) {
	center.x = x;
	center.y = y;
}

void nnb::TextureContainer::setOrigin(int x, int y) {
	origin.x = x;
	origin.y = y;
}

void nnb::TextureContainer::setFlip(SDL_RendererFlip newFlip) {
	flip = newFlip;
}

void nnb::TextureContainer::setAlpha(Uint8 newAlpha) {
	alpha = newAlpha;
}

void nnb::TextureContainer::setBlendMode(SDL_BlendMode newBlendMode) {
	blendMode = newBlendMode;
	SDL_SetTextureBlendMode(txt, blendMode);
}

void nnb::TextureContainer::setColor(Uint8 r, Uint8 g, Uint8 b) {
	clr.r = r;
	clr.g = g;
	clr.b = b;
}

void nnb::TextureContainer::setColor(nnb::Color clr_) {
	SDL_Color tempClr = getSDL_Color(clr_);
	setColor(tempClr.r, tempClr.g, tempClr.b);
}

void nnb::TextureContainer::setColor(SDL_Color clr_) {
	setColor(clr_.r, clr_.g, clr_.b);
}

SDL_Texture* nnb::TextureContainer::getTexture() const {
	return txt;
}

Uint8 nnb::TextureContainer::getAlpha() const {
	return alpha;
}

SDL_BlendMode nnb::TextureContainer::getBlendMode() const {
	return blendMode;
}

SDL_Color nnb::TextureContainer::getColor() const {
	return clr;
}

// TODO: Do we really need this? Why not create a new instance instead of reusing, that way you don't have to think about retaining properties. Because at the moment we reset position/sizes, but retain rotation and color.
void nnb::TextureContainer::setTexture(SDL_Renderer* newTgt, SDL_Texture* newTxt) {
	txt = newTxt;
	tgt = newTgt;

	int err = SDL_QueryTexture(txt, &format, NULL, &w, &h);
	if (err != 0 && (newTgt != NULL && newTxt != NULL)) {
		NNB_ERROR << "Unable to query texture properties. Error code " << err << ", error message: " << SDL_GetError();
	}

	src.w = w;
	src.h = h;
	dst.w = w;
	dst.h = h;

	src.x = 0;
	src.y = 0;
	dst.x = 0;
	dst.y = 0;

	setAlpha(alpha);
	setBlendMode(blendMode);
	setColor(clr);
}

void nnb::TextureContainer::move(int x, int y) {
	dst.x += x;
	dst.y += y;
}

void nnb::TextureContainer::setPosition(int x, int y) {
	setX(x);
	setY(y);
}

void nnb::TextureContainer::setX(int x) {
	dst.x = x;
}

void nnb::TextureContainer::setY(int y) {
	dst.y = y;
}

void nnb::TextureContainer::setSize(int w_, int h_) {
	dst.w = w_;
	dst.h = h_;
}

void nnb::TextureContainer::setWidth(int w_) {
	dst.w = w_;
}

void nnb::TextureContainer::setHeight(int h_) {
	dst.h = h_;
}

void nnb::TextureContainer::resetSize() {
	setSize(getTextureWidth(), getTextureHeight());
}

int nnb::TextureContainer::getRenderWidth() const {
	return dst.w;
}

int nnb::TextureContainer::getRenderHeight() const {
	return dst.h;
}

int nnb::TextureContainer::getTextureWidth() const {
	return w;
}

int nnb::TextureContainer::getTextureHeight() const {
	return h;
}

Uint32 nnb::TextureContainer::getFormat() const {
	return format;
}

double nnb::TextureContainer::getRotation() const {
	return angle;
}

int nnb::TextureContainer::getX() const {
	return dst.x;
}

int nnb::TextureContainer::getY() const {
	return dst.y;
}

SDL_Rect nnb::TextureContainer::getBounds() const {
	return dst;
}

void nnb::TextureContainer::render() const {
	if (txt == NULL) return;
	
	SDL_Rect tdst = dst;
	tdst.x -= origin.x;
	tdst.y -= origin.y;

	SDL_SetTextureAlphaMod(txt, alpha);
	SDL_SetTextureColorMod(txt, clr.r, clr.g, clr.b);

	int err = SDL_RenderCopyEx(tgt, txt, &src, &tdst, angle, &center, flip);
	if (err != 0) {
		NNB_ERROR << "Unable to render texture. Error code " << err << ", error message: " << SDL_GetError();
	}
}

nnb::TextureContainer nnb::TextureContainer::clone() const {
	nnb::TextureContainer tc;
	tc = *this;
	return tc;
}

