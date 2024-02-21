cmake_minimum_required(VERSION 3.28)
project(CppSDL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR}/cmake-modules)

set(SDL2_PATH "D:\\SDL2\\SDL2-devel-2.30.0-mingw\\SDL2-2.30.0\\x86_64-w64-mingw32")
set(SDL2_TTF_PATH "D:\\SDL2\\sdl2_ttf-devel-2.22.0-mingw\\SDL2_ttf-2.22.0\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_executable(CppSDL
        src/Engine/TinyEngine.h
        src/Engine/TinyEngine.cpp
        src/Engine/Input.h
        src/main.cpp
        src/Game.cpp
        src/Game.h
)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})