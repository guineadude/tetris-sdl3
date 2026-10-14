cmake_minimum_required(VERSION 3.21)

project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL3_ROOT "" CACHE PATH "Root of the SDL3 development package")
set(SDL3_TTF_ROOT "" CACHE PATH "Root of the SDL3_ttf development package")

foreach(dependency SDL3 SDL3_TTF)
    if(NOT ${dependency}_ROOT)
        message(FATAL_ERROR
            "${dependency}_ROOT is not set. Configure it in CMakeUserPresets.json "
            "or pass it as a CMake cache variable.")
    endif()
endforeach()

add_executable(tetris
    src/main.cpp
    src/App.cpp
    src/game/Board.cpp
    src/game/Piece.cpp
    src/game/Game.cpp
    src/scenes/TetrisScene.cpp
    src/rendering/GameRenderer.cpp
)

target_include_directories(tetris PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${SDL3_ROOT}/include"
    "${SDL3_TTF_ROOT}/include"
)

target_link_directories(tetris PRIVATE
    "${SDL3_ROOT}/lib"
    "${SDL3_TTF_ROOT}/lib"
)

target_link_libraries(tetris PRIVATE SDL3 SDL3_ttf)

add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/bin/SDL3.dll"
        "${SDL3_TTF_ROOT}/bin/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:tetris>"
    VERBATIM
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(TARGET tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:tetris>/assets"
        VERBATIM
    )
endif()
