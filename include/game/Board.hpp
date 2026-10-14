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

struct Color
{
  std::uint8_t r;
  std::uint8_t g;
  std::uint8_t b;
};

struct Cell
{
  State state{State::Empty};
  Color color{};
};

class Board
{
  public:
    auto getCell(std::size_t row, std::size_t col) const -> const Cell&
    {
        return m_cells[row][col];
    }
    auto getCellOccupied(const Cell& cell) const -> bool
    {
        return cell.state == State::Occupied;
    }
    auto getCellColor(const Cell& cell) const -> Color
    {
        return cell.color;
    }
  private:
    

    std::array<std::array<Cell, tetris::constants::boardColumns>, tetris::constants::boardRows> m_cells{};
};
