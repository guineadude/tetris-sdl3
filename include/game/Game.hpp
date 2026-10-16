#pragma once

#include "game/Board.hpp"

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
        auto shutdown() -> void;

        [[nodiscard]] auto board() noexcept -> Board& { return m_board; }
        [[nodiscard]] auto board() const noexcept -> const Board& { return m_board; }
    private:
        Board m_board {};
        double m_dropElapsedSeconds {};    

        auto dropTiles() -> void;
        auto spawnTiles() -> void;
};
