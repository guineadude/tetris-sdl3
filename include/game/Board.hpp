#pragma once

#include <SDL3/SDL.h>
#include <array>
#include <cstdint>

#include "Constants.hpp"

enum class State
{
    Empty,
    Occupied
};

struct Cell
{
  State state{State::Empty};
  SDL_Color color{};

    [[nodiscard]] auto isOccupied() const -> bool
    {
        return this->state == State::Occupied;
    }
    [[nodiscard]] auto getColor() const -> SDL_Color
    {
        return this->color;
    }
};

class Board
{
  public:
    Board() = default;
    ~Board() = default;
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=(Board&&) = delete;

    [[nodiscard]] auto getCell(std::size_t row, std::size_t col) const -> const Cell&
    {
        return m_cells[row][col];
    }

  private:
    std::array<std::array<Cell, tetris::constants::boardColumns>, tetris::constants::boardRows> m_cells{};
};
