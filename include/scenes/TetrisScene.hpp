#pragma once

#include <SDL3/SDL.h>

#include "game/Game.hpp"
#include "rendering/Renderer.hpp"

class TetrisScene 
{
    public:
        TetrisScene() = default;
        ~TetrisScene();
        TetrisScene(const TetrisScene&) = delete;
        TetrisScene& operator=(const TetrisScene&) = delete;
        TetrisScene(TetrisScene&&) = delete;
        TetrisScene& operator=(TetrisScene&&) = delete;

        [[nodiscard]] auto initialize(SDL_Renderer *renderer) -> bool;
        auto run() { update(); }
        auto update() -> void;
        auto shutdown() -> void;
    private:
        Game     m_game     {};
        Renderer m_renderer {};
};