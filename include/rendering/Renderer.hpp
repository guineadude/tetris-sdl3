#pragma once

#include <SDL3/SDL.h>
#include <cstddef>

#include "Constants.hpp"

class Renderer
{
    public:
        Renderer() = default;
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(Renderer&&) = delete;
        
        auto initialize(SDL_Renderer *renderer) -> bool;
        auto update() -> void;
        auto shutdown() -> void;
    private:
        SDL_Renderer *m_renderer {nullptr};

        auto drawGrid() -> void;
};