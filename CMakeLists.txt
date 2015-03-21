cmake_minimum_required(VERSION 3.2)
project(nutsnbolts)

add_definitions(-std=c++11 -g)
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
