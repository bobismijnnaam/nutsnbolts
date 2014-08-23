// File: PersistentText.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "nnb/graphics/PersistentText.hpp"

nnb::PersistentText::PersistentText() : PersistentText(NULL, true) {}

nnb::PersistentText::PersistentText(SDL_Renderer* tgt_, bool autoCommit_) :
autoCommit{autoCommit},
align{nnb::Align::LEFT},
txt(tgt_, NULL),
tgt{tgt_},
dst{0, 0, 0, 0},
clr{0, 0, 0, 255} {
}

nnb::PersistentText::~PersistentText() {
	if (txt.getTexture() != NULL) {
		SDL_DestroyTexture(txt.getTexture());
		txt.setTexture(NULL, NULL);
	}
}

void nnb::PersistentText::setText(std::string text_) {
	text = text_;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::PersistentText::setFont(TTF_Font *font_) {
	font = font_;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::PersistentText::setPosition(int x_, int y_) {
	x = x_;
	y = y_;
	calculateBounds();
}

void nnb::PersistentText::setX(int x_) {
	setPosition(x_, getY());
}

void nnb::PersistentText::setY(int y_) {
	setPosition(getX(), y_);
}

void nnb::PersistentText::setAlign(Align align_) {
	align = align_;
	calculateBounds();
}

void nnb::PersistentText::setColor(SDL_Color clr_) {
	clr = clr_;
	clr.a = 255;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::PersistentText::setColor(int r, int g, int b) {
	clr.r = r;
	clr.g = g;
	clr.b = b;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::PersistentText::setColor(nnb::Color clr_) {
	clr = nnb::getSDL_Color(clr_);
	dirty = true;
	if (autoCommit) commit();
}

void nnb::PersistentText::setAlpha(Uint8 alpha_) {
	txt.setAlpha(alpha_);
}

// TODO: Make sure autocommit works everywhere
void nnb::PersistentText::setAutoCommit(bool autoCommit_) {
	autoCommit = autoCommit_;
}

void nnb::PersistentText::calculateBounds() {
	txt.resetSize();

	switch (align) {
	case nnb::Align::LEFT:
		txt.setX(x);
		break;
	case nnb::Align::RIGHT:
		txt.setX(x - txt.getRenderWidth());
		break;
	case nnb::Align::CENTER:
		txt.setX(x - txt.getRenderWidth() / 2);
		break;
	default:
		NNB_LOG << "ERROR! This case should not be triggered";
		break;
	}

	txt.setY(y);
}

void nnb::PersistentText::commit() {
	if (!dirty) return;
	
	if (text == "") {
		if (txt.getTexture() != NULL) {
			SDL_DestroyTexture(txt.getTexture());
			txt.setTexture(tgt, NULL);
		}
	} else {
		SDL_Surface *tempText = TTF_RenderText_Blended(font, text.c_str(), clr);
		if (tempText == NULL) {
			NNB_LOG << "ERROR! Text generation of \"" << text << "\" failed. The error message: " << TTF_GetError();
		}
		SDL_DestroyTexture(txt.getTexture());
		txt.setTexture(tgt, SDL_CreateTextureFromSurface(tgt, tempText));
		SDL_FreeSurface(tempText);

		calculateBounds();
	}

	dirty = false;
}

void nnb::PersistentText::render() const {
	if (dirty) NNB_LOG << "Warning! Dirty render should not happen, commit() beforehand";
	txt.render();
}

int nnb::PersistentText::getWidth() const {
	return txt.getRenderWidth();
}

int nnb::PersistentText::getHeight() const {
	return txt.getRenderHeight();
}

int nnb::PersistentText::getX() const {
	return x;
}

int nnb::PersistentText::getY() const {
	return y;
}

SDL_Rect nnb::PersistentText::getBounds() const {
	return txt.getBounds();
}
