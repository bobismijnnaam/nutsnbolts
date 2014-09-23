// File: PersistentTexture.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include "SDL2/SDL.h"

// Private
#include "nnb/graphics/PersistentTexture.hpp"
#include "nnb/log/log.hpp"

nnb::PersistentTexture::PersistentTexture() : PersistentTexture(NULL, NULL) {}

nnb::PersistentTexture::PersistentTexture(SDL_Renderer* tgt_, SDL_Texture* txt_) :
tgt{tgt_},
txt{txt_},
src{0, 0, 0, 0},
dst{0, 0, 0, 0},
angle{0.0},
center{0, 0},
flip{SDL_FLIP_NONE},
alpha{255},
blendMode{SDL_BLENDMODE_BLEND},
clr{255, 255, 255, 255},
w{0},
h{0},
format{0} {
	int err = SDL_QueryTexture(txt, &format, NULL, &w, &h);
	if (err != 0 && txt != NULL) {
		NNB_LOG << "Unable to query texture properties. Error code " << err << ", error message: " << SDL_GetError();
	}

	src.w = w;
	src.h = h;
	dst.w = w;
	dst.h = h;

	setAlpha(alpha);
	setBlendMode(blendMode);
	setColor(clr);

}

nnb::PersistentTexture::~PersistentTexture() {
	// RAII should take care of this. Also we're not the owner of the texture/renderer
}

void nnb::PersistentTexture::setSrcRect(SDL_Rect newRect) {
	src = newRect;
}

void nnb::PersistentTexture::setRotation(double newAngle) {
	angle = newAngle;
}

void nnb::PersistentTexture::setCenter(SDL_Point newCenter) {
	center = newCenter;
}

void nnb::PersistentTexture::setCenter(int x, int y) {
	center.x = x;
	center.y = y;
}

void nnb::PersistentTexture::setFlip(SDL_RendererFlip newFlip) {
	flip = newFlip;
}

void nnb::PersistentTexture::setAlpha(Uint8 newAlpha) {
	alpha = newAlpha;
	SDL_SetTextureAlphaMod(txt, alpha);
}

void nnb::PersistentTexture::setBlendMode(SDL_BlendMode newBlendMode) {
	blendMode = newBlendMode;
	SDL_SetTextureBlendMode(txt, blendMode);
}

void nnb::PersistentTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
	clr.r = r;
	clr.g = g;
	clr.b = b;
	SDL_SetTextureColorMod(txt, clr.r, clr.g, clr.b);
}

void nnb::PersistentTexture::setColor(nnb::Color clr_) {
	SDL_Color tempClr = getSDL_Color(clr_);
	setColor(tempClr.r, tempClr.g, tempClr.b);
}

void nnb::PersistentTexture::setColor(SDL_Color clr_) {
	setColor(clr_.r, clr_.g, clr_.b);
}

SDL_Texture* nnb::PersistentTexture::getTexture() const {
	return txt;
}

Uint8 nnb::PersistentTexture::getAlpha() const {
	return alpha;
}

SDL_BlendMode nnb::PersistentTexture::getBlendMode() const {
	return blendMode;
}

SDL_Color nnb::PersistentTexture::getColor() const {
	return clr;
}

// TODO: Do we really need this? Why not create a new instance instead of reusing, that way you don't have to think about retaining properties. Because at the moment we reset position/sizes, but retain rotation and color.
void nnb::PersistentTexture::setTexture(SDL_Renderer* newTgt, SDL_Texture* newTxt) {
	txt = newTxt;
	tgt = newTgt;

	int err = SDL_QueryTexture(txt, &format, NULL, &w, &h);
	if (err != 0 && (newTgt != NULL && newTxt != NULL)) {
		NNB_LOG << "Unable to query texture properties. Error code " << err << ", error message: " << SDL_GetError();
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

void nnb::PersistentTexture::move(int x, int y) {
	dst.x += x;
	dst.y += y;
}

void nnb::PersistentTexture::setPosition(int x, int y) {
	setX(x);
	setY(y);
}

void nnb::PersistentTexture::setX(int x) {
	dst.x = x;
}

void nnb::PersistentTexture::setY(int y) {
	dst.y = y;
}

void nnb::PersistentTexture::setSize(int w_, int h_) {
	dst.w = w_;
	dst.h = h_;
}

void nnb::PersistentTexture::setWidth(int w_) {
	dst.w = w_;
}

void nnb::PersistentTexture::setHeight(int h_) {
	dst.h = h_;
}

void nnb::PersistentTexture::resetSize() {
	setSize(getTextureWidth(), getTextureHeight());
}

int nnb::PersistentTexture::getRenderWidth() const {
	return dst.w;
}

int nnb::PersistentTexture::getRenderHeight() const {
	return dst.h;
}

int nnb::PersistentTexture::getTextureWidth() const {
	return w;
}

int nnb::PersistentTexture::getTextureHeight() const {
	return h;
}

Uint32 nnb::PersistentTexture::getFormat() const {
	return format;
}

SDL_Rect nnb::PersistentTexture::getBounds() const {
	return dst;
}

void nnb::PersistentTexture::render() const {
	if (txt == NULL) return;
	int err = SDL_RenderCopyEx(tgt, txt, &src, &dst, angle, &center, flip);
	if (err != 0) {
		NNB_LOG << "Unable to render texture. Error code " << err << ", error message: " << SDL_GetError();
	}
}

