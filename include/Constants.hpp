#pragma once

#include <cstddef>

namespace tetris::constants
{
    inline constexpr int windowWidth  {420};
    inline constexpr int windowHeight {820};
    inline constexpr char windowTitle[] {"Tetris"};

    inline constexpr std::size_t boardColumns {10};
    inline constexpr std::size_t boardRows    {20};

    inline constexpr int cellSize {40};
    inline constexpr int boardMargin {10};
}
