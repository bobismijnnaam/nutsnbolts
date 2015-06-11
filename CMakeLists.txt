cmake_minimum_required(VERSION 3.2)
project(nutsnbolts)

# Makes sure all executables are put in root
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_definitions(-std=c++11 -g -mwindows -DNNB_LOGLVL_VERBOSE)
include_directories(SYSTEM "c:/mingw/mingw32/include")
include_directories("${PROJECT_SOURCE_DIR}/headers")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(sources)

add_library(nutsnbolts STATIC
	${SOURCES}
)
target_link_libraries(nutsnbolts mingw32 SDL2_image SDL2_mixer SDL2_ttf SDL2main SDL2 png jpeg z)

add_executable(nutsnbolts_test
	${TESTSOURCES}
)
target_link_libraries(nutsnbolts_test nutsnbolts)
