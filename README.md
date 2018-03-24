#Nuts 'n Bolts
A game library built on top of various libraries like GLM, SDL2, and dirent.h.

## Building
- Add SDL2 header path (/usr/include)
- Install libsdl2-ttf-dev
- Install libsdl2-mixer-dev
- Remove all the default parameters in context.cpp
- Rename the initWindow variable in Context class to something sane (windowIsInitialised?)
- Add to cmakelists 
```
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
```
- Install libsdl2-image-2.0-0
- Install libsdl2-image-dev
- Set directories where all the libs are stored: `link_directories("/usr/lib/x86_64-linux-gnu")`