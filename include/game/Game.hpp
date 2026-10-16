#pragma once

#include "game/Board.hpp"
#include "game/Piece.hpp"
#include <optional>

class Game
{
    public:
        Game() = default;
        ~Game();
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game(Game&&) = delete;
        Game& operator=(Game&&) = delete;

        [[nodiscard]] auto initialize() -> bool;
        auto update() -> void;
        auto rotateActivePiece(bool clockwise) -> void;
        auto shutdown() -> void;

        [[nodiscard]] auto board() noexcept -> Board& { return m_board; }
        [[nodiscard]] auto board() const noexcept -> const Board& { return m_board; }
        [[nodiscard]] auto activePiece() noexcept -> std::optional<Piece>& { return m_activePiece; }
        [[nodiscard]] auto activePiece() const noexcept -> const std::optional<Piece>& { return m_activePiece; }
    private:
        Board m_board {};
        double m_dropElapsedSeconds {};    
        std::optional<Piece> m_activePiece {};

        [[nodiscard]] auto canPlace(const Piece& piece) const -> bool;
        auto dropTiles() -> void;
        auto spawnTiles() -> void;
};
