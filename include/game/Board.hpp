#pragma once

#include <SDL3/SDL.h>
#include <array>
#include <bitset>

#include "Constants.hpp"

class Board
{
  public:

  private:
    struct Cell 
    {
      bool occupied {false};
      std::optional<SDL_Color> value {std::nullopt};
    };

    std::array<std::array<Cell, tetris::constants::boardColumns>, tetris::constants::boardRows> m_cells{};
};
