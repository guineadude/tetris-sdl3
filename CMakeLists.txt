cmake_minimum_required(VERSION 3.21)

project(tetris_sdl3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL3_ROOT "" CACHE PATH "Root of the SDL3 mingw devel package (contains include/ and lib/)")
set(SDL3_IMAGE_ROOT "" CACHE PATH "Root of the SDL3_image mingw devel package (contains include/ and lib/)")
set(SDL3_TTF_ROOT "" CACHE PATH "Root of the SDL3_ttf mingw devel package (contains include/ and lib/)")

if(NOT SDL3_ROOT)
    message(FATAL_ERROR "SDL3_ROOT is not set. Provide it via CMakeUserPresets.json or -DSDL3_ROOT=... (see README.md).")
endif()
if(NOT SDL3_IMAGE_ROOT)
    message(FATAL_ERROR "SDL3_IMAGE_ROOT is not set. Provide it via CMakeUserPresets.json or -DSDL3_IMAGE_ROOT=... (see README.md).")
endif()
if(NOT SDL3_TTF_ROOT)
    message(FATAL_ERROR "SDL3_TTF_ROOT is not set. Provide it via CMakeUserPresets.json or -DSDL3_TTF_ROOT=... (see README.md).")
endif()

add_executable(tetris
    src/01-hello-sdl3.cpp
    src/Button.cpp
    src/Texture.cpp
)

target_include_directories(tetris PRIVATE
    "${SDL3_ROOT}/include"
    "${SDL3_IMAGE_ROOT}/include"
    "${SDL3_TTF_ROOT}/include"
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_directories(tetris PRIVATE
    "${SDL3_ROOT}/lib"
    "${SDL3_IMAGE_ROOT}/lib"
    "${SDL3_TTF_ROOT}/lib"
)

target_link_libraries(tetris PRIVATE
    SDL3
    SDL3_image
    SDL3_ttf
)

add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/bin/SDL3.dll"
        "${SDL3_IMAGE_ROOT}/bin/SDL3_image.dll"
        "${SDL3_TTF_ROOT}/bin/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:tetris>"
    COMMENT "Copying SDL3 runtime DLLs next to the built executable"
)

add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:tetris>/assets"
    COMMENT "Copying assets/ next to the built executable"
)
