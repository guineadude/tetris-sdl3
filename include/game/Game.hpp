#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
class Game 
{
    public:
    Game() = default;
    ~Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    auto initialize() -> bool;
    auto run() -> void;
    auto shutdown() -> int;
    private:
};