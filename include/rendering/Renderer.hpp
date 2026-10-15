#pragma once

#include <SDL3/SDL.h>
#include <cstddef>

#include "Constants.hpp"
#include "game/Board.hpp"

class Board;

class Renderer
{
    public:
        Renderer() = default;
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(Renderer&&) = delete;
        
        [[nodiscard]] auto initialize(SDL_Renderer *renderer) -> bool;
        auto update(const Board &board) -> void;
        auto shutdown() -> void;

    private:
        SDL_Renderer *m_renderer {nullptr};

        auto drawBackground() -> void;
        auto drawGrid(const Board &board) -> void;
        auto drawCells(const Board &board) -> void;

};