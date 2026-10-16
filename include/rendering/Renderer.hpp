#pragma once

#include <SDL3/SDL.h>
#include <cstddef>
#include <optional>

#include "Constants.hpp"
#include "game/Board.hpp"
#include "game/Piece.hpp"

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
        auto update(const Board& board, const std::optional<Piece>& activePiece) -> void;
        auto shutdown() -> void;

    private:
        SDL_Renderer *m_renderer {nullptr};

        auto drawBackground() -> void;
        auto drawGrid() -> void;
        auto drawCells(const Board &board) -> void;
        auto drawActivePiece(const std::optional<Piece>& activePiece) -> void;

};