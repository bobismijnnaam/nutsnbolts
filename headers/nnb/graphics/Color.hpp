// File: Color.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-05-29
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_COLOR_HPP
#define NNB_COLOR_HPP

// Public
#include <initializer_list>
#include <cassert>
#include <algorithm>

// Private
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/utils/macros.hpp"

namespace nnb {
	template<
		class T,
		long minval,
		long maxval
	>
	struct BasicColor {
		// Methods
		BasicColor(std::initializer_list<T> const c) {
			assert(c.size() == 3 || c.size() == 4);

			auto it = c.begin();
			r = *it++;
			g = *it++;
			b = *it++;

			if (it != c.end()) {
				a = *it++;
			} else {
				a = maxval;
			}
		}

		BasicColor(std::initializer_list<BasicColor<T, minval, maxval>> const c) {
			assert(c.size() <= 1);

			if (c.size() == 0) {
				r = minval;
				g = minval;
				b = minval;
				a = maxval;
			} else {
				auto clr = *c.begin();

				r = clr.r;
				g = clr.g;
				b = clr.b;
				a = clr.a;
			}
		}

		BasicColor(T r_ = minval, T g_ = minval, T b_ = minval, T a_ = maxval) :
		r{r_},
		g{g_},
		b{b_},
		a{a_} {}

		void clamp() {
			r = std::max(std::min((T) maxval, r), (T) minval);
			g = std::max(std::min((T) maxval, g), (T) minval);
			b = std::max(std::min((T) maxval, b), (T) minval);
			a = std::max(std::min((T) maxval, a), (T) minval);
		}

		BasicColor<T, minval, maxval> getClamped() {
			BasicColor<T, minval, maxval> result{*this};
			result.clamp();
			return result;
		}

		bool operator==(BasicColor<T, minval, maxval> const & c) {
			return r == c.r && g == c.g && b == c.b && a == c.a;
		}

		std::string toString() const {
			std::string result = "Color{";
			result += nnb::tos(r) + " ";
			result += nnb::tos(g) + " ";
			result += nnb::tos(b) + " ";
			result += nnb::tos(a) + "}";
			
			return result;
		}

		friend std::ostream& operator<< (std::ostream& os, const BasicColor<T, minval, maxval> &c) {
			os << c.toString(); 
			return os;
		}

		// Members
		T r, g, b, a;
		
	} ;

	using Color = BasicColor<unsigned char, 0, 255>;
	using Tint = BasicColor<double, 0, 1>;

	Color toColor(Tint t);
	Tint toTint(Color c);

}

#endif // NNB_COLOR_HPP
