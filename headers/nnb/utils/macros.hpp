// File: macros.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_MACROS_HPP
#define NNB_MACROS_HPP

#define NNB_STRINGIFY(x) #x
#define NNB_STRINGIFY_(x) NNB_STRINGIFY(x)
#define NNB__LINE__S NNB_STRINGIFY_(__LINE__)

//http://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
// Scary macros!
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define DEFVARS(src, ...) GET_MACRO(__VA_ARGS__, DEFVARS_8, DEFVARS_7, DEFVARS_6, DEFVARS_5, DEFVARS_4, DEFVARS_3, DEFVARS_2, DEFVARS_1)(src, __VA_ARGS__)

#define DGV(src, a, n) std::remove_reference<decltype(std::get<n>(src))>::type a;

#define DEFVARS_1(src, a) DGV(src, a, 0)
#define DEFVARS_2(src, a, b) DEFVARS_1(src, a) DGV(src, b, 1) 
#define DEFVARS_3(src, a, b, c) DEFVARS_2(src, a, b) DGV(src, c, 2) 
#define DEFVARS_4(src, a, b, c, d) DEFVARS_3(src, a, b, c) DGV(src, d, 3) 
#define DEFVARS_5(src, a, b, c, d, e) DEFVARS_4(src, a, b, c, d) DGV(src, e, 4) 
#define DEFVARS_6(src, a, b, c, d, e, f) DEFVARS_5(src, a, b, c, d, e) DGV(src, f, 5) 
#define DEFVARS_7(src, a, b, c, d, e, f, g) DEFVARS_6(src, a, b, c, d, e, f) DGV(src, g, 6) 
#define DEFVARS_8(src, a, b, c, d, e, f, g, h) DEFVARS_7(src, a, b, c, d, e, f, g) DGV(src, h, 7) 

#define NNB_UNPACK(src, ...) \
	DEFVARS(src, __VA_ARGS__) \
	std::tie(__VA_ARGS__) = src

#endif
