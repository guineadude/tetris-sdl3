#pragma once

#include <SDL3/SDL.h>

class Renderer
{
    public:
        auto initialize(SDL_Renderer *renderer) -> bool;
        auto update() -> void;
        auto shutdown() -> void;
    private:
        SDL_Renderer *m_renderer {nullptr};
};