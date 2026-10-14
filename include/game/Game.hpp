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

        auto initialize() -> bool;
        auto update() -> void;
        auto shutdown() -> void;

        auto board() noexcept -> Board& { return m_board; }
        auto board() const noexcept -> const Board& { return m_board; }
    private:
        Board m_board {};
};
