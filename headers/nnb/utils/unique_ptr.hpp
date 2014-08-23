// File: unique_ptr.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 13-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <memory>

// Private


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
