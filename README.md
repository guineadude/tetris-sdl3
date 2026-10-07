# Tetris with SDL3

This repository is my learning project while following the **Lazy Foo' Productions SDL3 tutorial**.

## Goal
Build a "Nasty Tetris" style game while learning SDL3 fundamentals, including:

- SDL3 project setup
- Rendering and textures
- Input handling
- Game loop structure
- Basic game state management

## Project Structure

- `src/` — source files
- `assets/` — images, fonts, sounds, and other game assets
- `CMakeLists.txt` — CMake build configuration

## Build

The project uses MinGW development packages for SDL3, SDL3_image, SDL3_ttf, and
SDL3_mixer. Set `SDL3_ROOT`, `SDL3_IMAGE_ROOT`, `SDL3_TTF_ROOT`, and
`SDL3_MIXER_ROOT` to each package's architecture-specific directory (the one
containing `include/`, `lib/`, and `bin/`). These paths can be set in the
untracked `CMakeUserPresets.json` file or passed as CMake cache variables.

Configure and build with the `desktop` preset:

```sh
cmake --preset desktop
cmake --build build
```

The build copies the SDL runtime DLLs and game assets beside the executable.
