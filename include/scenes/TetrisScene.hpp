#pragma once

#include <SDL3/SDL.h>

#include "game/Game.hpp"
#include "rendering/Renderer.hpp"

namespace
{
    struct RendererData
    {
    };
}

class TetrisScene 
{
    public:
        auto initialize(SDL_Renderer *renderer) -> bool;
        auto run() { update(); }
        auto update() -> void;
        auto shutdown() -> void;
    private:
        Game     m_game     {};
        Renderer m_renderer {};
};