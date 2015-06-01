// File: Rect.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2015-05-30
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_RECT_HPP
#define NNB_RECT_HPP

// Public
#include <cassert>
#include <SDL2/SDL.h>

// Private
#include "nnb/utils/StringHelpers.hpp"

namespace nnb {
	template <
		class T
	>
	struct BasicRect {
		// Functions
		BasicRect(std::initializer_list<T> const r) {
			assert(r.size() == 4);

			auto it = r.begin();
			x = *it++;
			y = *it++;
			w = *it++;
			h = *it++;
		}

		BasicRect(std::initializer_list<BasicRect<T>> const r) {
			assert(r.size() <= 1);

			if (r.size() == 0) {
				x = 0;
				y = 0;
				w = 0;
				h = 0;
			} else {
				auto rect = *r.begin();

				x = rect.x;
				y = rect.y;
				w = rect.w;
				h = rect.h;
			}
		}

		BasicRect(T x_ = 0, T y_ = 0, T w_ = 0, T h_ = 0) :
		x{x_},
		y{y_},
		w{w_},
		h{h_} {}

		bool operator==(BasicRect<T> const & r) {
			return x == r.x && y == r.y && w == r.w && h == r.h;
		}

		SDL_Rect toSDLRect() {
			SDL_Rect result;
			result.x = (int) x;
			result.y = (int) y;
			result.w = (int) w;
			result.h = (int) h;

			return result;
		}

		bool isEmpty() {
			return !(w > 0 && h > 0);
		}

		BasicRect<T> intersect(BasicRect<T> other) {
			// First make sure there is at least overlap
			if (other.x + other.w <= x) return {};
			if (other.y + other.h <= y) return {};
			if (other.x >= x + w) return {};
			if (other.y >= y + h) return {};

			BasicRect<T> r;

			if (x > other.x) {
				r.x = x;

				r.w = std::min(other.x + other.w - x, w);
			} else { // other.x > x
				r.x = other.x;

				r.w = std::min(x + w - other.x, other.w);
			}

			if (y > other.y) {
				r.y = y;

				r.h = std::min(other.y + other.h - y, h);
			} else {
				r.y = other.y;

				r.h = std::min(y + h - other.y, other.h);
			}

			return r;
		}

		std::string toString() const {
			std::string result = "Rect{";
			result += nnb::tos(x) + " ";
			result += nnb::tos(y) + " ";
			result += nnb::tos(w) + " ";
			result += nnb::tos(h) + "}";
			
			return result;
		}

		friend std::ostream& operator<< (std::ostream& os, const BasicRect<T> &r) {
			os << r.toString(); 
			return os;
		}

		// Members
		T x, y, w, h;
	} ;

	using Rect = BasicRect<int>;
	using FloatRect = BasicRect<double>;

}

#endif // NNB_RECT_HPP

