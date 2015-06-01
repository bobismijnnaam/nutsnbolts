// File: unique_ptr.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-08-13
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef NNB_UNIQUE_PTR_HPP
#define NNB_UNIQUE_PTR_HPP

// Public
#include <memory>

// Private

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif // NNB_UNIQUE_PTR_HPP
