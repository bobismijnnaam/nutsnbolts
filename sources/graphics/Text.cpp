// File: Text.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <memory>

// Private
#include "nnb/utils/unique_ptr.hpp"
#include "nnb/graphics/Text.hpp"

nnb::Text::Text() : Text(NULL, true) {}

nnb::Text::Text(SDL_Renderer* tgt_, bool autoCommit_) :
autoCommit{autoCommit_},
halign{nnb::HAlign::LEFT},
valign{nnb::VAlign::TOP},
txt(tgt_, NULL),
tgt{tgt_},
dst{0, 0, 0, 0},
clr{0, 0, 0, 255} {
}

nnb::Text::Text(const nnb::Text& other) :
autoCommit{other.autoCommit},
x{other.x},
y{other.y},
font{other.font},
text{other.text},
halign{other.halign},
valign{other.valign},
txt{other.txt},
tgt{other.tgt},
dst{other.dst.x, other.dst.y, other.dst.w, other.dst.h}, 
clr{other.clr.r, other.clr.g, other.clr.b, other.clr.a},
dirty{other.dirty} {
	txt.setTexture(tgt, nullptr);
	dirty = true;
	commit();
}

nnb::Text& nnb::Text::operator=(const nnb::Text& rhs) {
	if (this != &rhs) {
		autoCommit = rhs.autoCommit;
		x = rhs.x;
		y = rhs.y;
		font = rhs.font;
		text = rhs.text;
		halign = rhs.halign;
		valign = rhs.valign;
		txt = rhs.txt;
		tgt = rhs.tgt;
		dst = rhs.dst;
		clr = rhs.clr;
		dirty = rhs.dirty;

		txtTexture.reset(nullptr);
		txt.setTexture(tgt, nullptr);
		dirty = true;
		commit();
	}

	return *this;
}

void nnb::Text::setText(std::string text_) {
	text = text_;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::Text::setFont(TTF_Font *font_) {
	font = font_;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::Text::setPosition(int x_, int y_) {
	x = x_;
	y = y_;
	calculateBounds();
}

void nnb::Text::setX(int x_) {
	setPosition(x_, getY());
}

void nnb::Text::setY(int y_) {
	setPosition(getX(), y_);
}

void nnb::Text::setHAlign(HAlign align_) {
	halign = align_;
	calculateBounds();
}

void nnb::Text::setVAlign(VAlign align_) {
	valign = align_;
	calculateBounds();
}

void nnb::Text::setColor(SDL_Color clr_) {
	clr = clr_;
	clr.a = 255;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::Text::setColor(int r, int g, int b) {
	clr.r = r;
	clr.g = g;
	clr.b = b;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::Text::setColor(nnb::Color clr_) {
	clr.r = clr_.r;
	clr.g = clr_.g;
	clr.b = clr_.b;
	clr.a = clr_.a;
	dirty = true;
	if (autoCommit) commit();
}

void nnb::Text::setAlpha(Uint8 alpha_) {
	txt.setAlpha(alpha_);
}

// TODO: Make sure autocommit works everywhere
void nnb::Text::setAutoCommit(bool autoCommit_) {
	autoCommit = autoCommit_;
}

void nnb::Text::calculateBounds() {
	txt.resetSize();

	switch (halign) {
	case nnb::HAlign::LEFT:
		txt.setX(x);
		break;
	case nnb::HAlign::RIGHT:
		txt.setX(x - txt.getRenderWidth());
		break;
	case nnb::HAlign::CENTER:
		txt.setX(x - txt.getRenderWidth() / 2);
		break;
	default:
		txt.setX(x);
		NNB_ERROR << "This case should not be triggered";
		break;
	}

	switch (valign) {
	case nnb::VAlign::TOP:
		txt.setY(y);
		break;
	case nnb::VAlign::CENTER:
		txt.setY(y - txt.getRenderHeight() / 2);
		break;
	case nnb::VAlign::BOTTOM:
		txt.setY(y - txt.getRenderHeight());
		break;
	default:
		txt.setY(y);
		NNB_ERROR << "This case should not be triggered";
		break;
	}
}

void nnb::Text::commit() {
	if (!dirty) return;
	
	if (text == "") {
		if (txt.getTexture() != NULL) {
			txtTexture.reset(nullptr);
			txt.setTexture(tgt, NULL);
		}
	} else {
		SDL_Surface *tempText = TTF_RenderText_Blended(font, text.c_str(), clr);
		if (tempText == NULL) {
			NNB_LOG << "ERROR! Text generation of \"" << text << "\" failed. The error message: " << TTF_GetError();
		}
		txt.setTexture(tgt, SDL_CreateTextureFromSurface(tgt, tempText));
		SDL_FreeSurface(tempText);
		txtTexture.reset(txt.getTexture());
		calculateBounds();
	}

	dirty = false;
}

void nnb::Text::render() const {
	if (dirty) {
		NNB_WARNING << "Warning! Dirty render should not happen, commit() beforehand";
	}
	txt.render();
}

int nnb::Text::getWidth() const {
	return txt.getRenderWidth();
}

int nnb::Text::getHeight() const {
	return txt.getRenderHeight();
}

int nnb::Text::getX() const {
	return x;
}

int nnb::Text::getY() const {
	return y;
}

SDL_Rect nnb::Text::getBounds() const {
	return txt.getBounds();
}
