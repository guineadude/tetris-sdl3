#ifndef HELLO_SDL3_H
#define HELLO_SDL3_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <string_view>

#include "Texture.h"
#include "Application.h"

struct TexturesForUpdateLoop
{
    Texture textTexture;
};

auto loadMedia(Texture &textTexture, std::string_view path, Application &app) -> bool; // Loads media

auto handleInput(SDL_KeyboardEvent &key) -> void; // handle input

auto updateLoop(TexturesForUpdateLoop &textures, Application &app) -> int; // Updates the main loop

#endif // HELLO_SDL3_H