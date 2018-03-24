cmake_minimum_required(VERSION 3.0)
project(nutsnbolts)

# Makes sure all executables are put in root
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_definitions(-std=c++11 -g -DNNB_LOGLVL_VERBOSE)

if (WIN32)
	add_definitions(-mwindows -DNNB_WIN)
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

target_link_libraries( nutsnbolts
    SDL2main
    SDL2
    png
    jpeg
    z
    )

if (WIN32)
	target_link_libraries(mingw32)
elseif (UNIX)
    link_directories("/usr/lib/x86_64-linux-gnu")
endif()


add_executable(nutsnbolts_test
	${TESTSOURCES}
)
target_link_libraries(nutsnbolts_test nutsnbolts)
