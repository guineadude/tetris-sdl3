#ifndef HELLO_SDL3_H
#define HELLO_SDL3_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <string_view>
#include <array>
#include "Texture.h"
#include "Application.h"
#include "Button.h"

auto loadMedia(Texture &text, std::string_view path, Application &app) -> bool; // Loads media

auto handleInput(SDL_KeyboardEvent &key) -> void; // handle input

auto updateLoop(/*TexturesForUpdateLoop &textures,*/ Application &app, int buttonCount, Button buttons[]) -> int; // Updates the main loop

#endif // HELLO_SDL3_H