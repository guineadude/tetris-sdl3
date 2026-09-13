cmake_minimum_required(VERSION 3.16)

project(tetris_sdl3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL3_ROOT "C:/Users/linda/Documents/Libraries/SDL3-devel-3.4.16-mingw/SDL3-3.4.16/x86_64-w64-mingw32")
set(SDL3_IMAGE_ROOT "C:/Users/linda/Documents/Libraries/SDL3_image-3.4.6/x86_64-w64-mingw32")

add_executable(tetris
    src/01-hello-sdl3.cpp
    src/Texture.cpp
)

target_include_directories(tetris PRIVATE
    "${SDL3_ROOT}/include"
    "${SDL3_IMAGE_ROOT}/include"
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_directories(tetris PRIVATE
    "${SDL3_ROOT}/lib"
    "${SDL3_IMAGE_ROOT}/lib"
)

target_link_libraries(tetris PRIVATE
    SDL3
    SDL3_image
)