#pragma once

#include <array>
#include <cstddef>

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

struct CellOffset
{
    int row;
    int col;
};

using Orientation = std::array<CellOffset, 4>;
using Rotations = std::array<Orientation, 4>;

struct Piece
{
    Shape shape {Shape::T};
    int row {}; // Pivot position on the board.
    int col {};
    std::size_t rotation {}; // 0–3.
};

[[nodiscard]] auto rotationsFor(Shape shape) -> const Rotations&;
[[nodiscard]] auto occupiedCells(const Piece& piece) -> Orientation;
