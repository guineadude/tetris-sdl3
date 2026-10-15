#pragma once

#include <SDL3/SDL.h>
#include <array>
#include <cstdint>

#include "Constants.hpp"

enum class Shape
{
    I,
    O,
    T,
    S,
    Z,
    J,
    L,
    None
};

enum class Color : std::uint32_t
{
    Red     = 0xFF0000,
    Green   = 0x00FF00,
    Blue    = 0x0000FF,
    Yellow  = 0xFFFF00,
    Cyan    = 0x00FFFF,
    Magenta = 0xFF00FF,
    White   = 0xFFFFFF,
    Black   = 0x000000,
    None    = 0x000000
};

struct Cell
{
  enum class State { Empty, Occupied };

  State state{State::Empty};
  Color color{};

    [[nodiscard]] auto isOccupied() const -> bool
    {
        return this->state == State::Occupied;
    }
    [[nodiscard]] auto getColor() const -> Color
    {
        return this->color;
    }
};

class Board
{  
  private:
    std::array<std::array<Cell, tetris::constants::boardColumns>, tetris::constants::boardRows> m_cells{};
  public:
    Board() = default;
    ~Board() = default;
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=(Board&&) = delete;

    [[nodiscard]] auto getCell(std::size_t row, std::size_t col) -> Cell&
    {
        return m_cells.at(row).at(col);
    }
    [[nodiscard]] auto getCell(std::size_t row, std::size_t col) const -> const Cell&
    {
        return m_cells.at(row).at(col);
    }
    auto setCell(std::size_t row, std::size_t col, const Cell& cell) -> void
    {
        m_cells.at(row).at(col) = cell;
    }
};
