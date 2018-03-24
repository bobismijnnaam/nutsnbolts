cmake_minimum_required(VERSION 3.0)
project(nutsnbolts)

# Makes sure all executables are put in root
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

 add_definitions(-DNNB_LOGLVL_VERBOSE)

if (WIN32)
	add_definitions(-DNNB_WIN)
elseif (UNIX)
	add_definitions(-DNNB_UNIX)
endif()

include_directories("${PROJECT_SOURCE_DIR}/headers")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("/usr/include")

add_subdirectory(sources)

add_library(nutsnbolts STATIC
	${SOURCES}
)

if (WIN32)
    if (NOT ZLIB_INCLUDE)
        MESSAGE(FATAL_ERROR "No zlib include!")
    endif()
    if (NOT ZLIB_STATIC_LIBRARY)
        MESSAGE(FATAL_ERROR "No zlib static library!")
    endif()
    if (NOT LIBPNG_INCLUDE)
        MESSAGE(FATAL_ERROR "No libpng include!")
    endif()
    if (NOT LIBPNG_STATIC_LIBRARY)
        MESSAGE(FATAL_ERROR "No libpng static library")
    endif()

    # The weird structure here is because I used to write my code with SDL2/ in front
    # of the includes. Sorry about that, but I'm too lazy to change it heh.
	include_directories(
        "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.8"
        "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.8/include"
        "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.3"
        "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.3/include"
        "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.2"
        "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.2/include"
        "${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.14"
        "${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.14/include"
        "${PROJECT_SOURCE_DIR}/lib/jpeg-6b/include"
        "${PROJECT_SOURCE_DIR}/tools"
        ${LIBPNG_INCLUDE}
        ${ZLIB_INCLUDE}
        )

    link_directories(
        "${PROJECT_SOURCE_DIR}/lib/jpeg-6b/lib"
        )

    MESSAGE("${PROJECT_SOURCE_DIR}/tools")

    add_definitions(-D__BASE_FILE__="lol_windows")

    target_link_libraries( nutsnbolts
        SDL2main
        SDL2
        jpeg
        ${ZLIB_STATIC_LIBRARY}
        ${LIBPNG_STATIC_LIBRARY}
        )

elseif (UNIX)
    add_definitions(-std=c++11 -g)
    link_directories("/usr/lib/x86_64-linux-gnu")

    target_link_libraries( nutsnbolts
        SDL2main
        SDL2
        png
        jpeg
        z
        )
endif()


add_executable(nutsnbolts_test
	${TESTSOURCES}
)
target_link_libraries(nutsnbolts_test nutsnbolts)
