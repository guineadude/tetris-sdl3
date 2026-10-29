#pragma once

#include <cstddef>
#include <cstdint>

namespace tetris::constants
{
    inline constexpr int windowWidth  {420};
    inline constexpr int windowHeight {820};
    inline constexpr char windowTitle[] {"Tetris"};
    inline constexpr double gameUpdateDeltaSeconds {1.0 / 60.0};
    inline constexpr double gameUpdateIntervalMs {gameUpdateDeltaSeconds * 1000.0};
    inline constexpr double gameDropIntervalSeconds {1.0};

    inline constexpr std::size_t boardColumns {10};
    inline constexpr std::size_t boardRows    {20};

    inline constexpr int cellSize {40};
    inline constexpr int boardMargin {10};
}
