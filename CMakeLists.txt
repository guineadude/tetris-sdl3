cmake_minimum_required(VERSION 3.16)
project(tetris_sdl3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO: find_package(SDL3 REQUIRED)
# target_link_libraries(tetris PRIVATE SDL3::SDL3)

add_executable(tetris
    src/main.cpp
)

target_include_directories(tetris PRIVATE include)
