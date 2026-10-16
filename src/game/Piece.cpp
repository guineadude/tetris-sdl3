#include "game/Piece.hpp"

#include <stdexcept>

namespace
{
    constexpr auto rotateClockwise(CellOffset cell) -> CellOffset
    {
        return {cell.col, -cell.row};
    }

    constexpr auto rotateClockwise(Orientation orientation) -> Orientation
    {
        for (auto& cell : orientation)
            cell = rotateClockwise(cell);

        return orientation;
    }

    constexpr auto makeRotations(Orientation initial, bool symmetric = false) -> Rotations
    {
        Rotations rotations {};
        rotations[0] = initial;

        for (std::size_t index {1}; index < rotations.size(); ++index)
            rotations[index] = symmetric ? initial : rotateClockwise(rotations[index - 1]);

        return rotations;
    }

    constexpr auto kIRotations = makeRotations(
        Orientation {{{0, -1}, {0, 0}, {0, 1}, {0, 2}}});
    constexpr auto kORotations = makeRotations(
        Orientation {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}, true);
    constexpr auto kTRotations = makeRotations(
        Orientation {{{-1, 0}, {0, -1}, {0, 0}, {0, 1}}});
    constexpr auto kSRotations = makeRotations(
        Orientation {{{-1, 0}, {-1, 1}, {0, -1}, {0, 0}}});
    constexpr auto kZRotations = makeRotations(
        Orientation {{{-1, -1}, {-1, 0}, {0, 0}, {0, 1}}});
    constexpr auto kJRotations = makeRotations(
        Orientation {{{-1, -1}, {0, -1}, {0, 0}, {0, 1}}});
    constexpr auto kLRotations = makeRotations(
        Orientation {{{-1, 1}, {0, -1}, {0, 0}, {0, 1}}});
}

auto rotationsFor(Shape shape) -> const Rotations&
{
    switch (shape)
    {
        case Shape::I:
            return kIRotations;
        case Shape::O:
            return kORotations;
        case Shape::T:
            return kTRotations;
        case Shape::S:
            return kSRotations;
        case Shape::Z:
            return kZRotations;
        case Shape::J:
            return kJRotations;
        case Shape::L:
            return kLRotations;
        default:
            throw std::invalid_argument("Rotations are not defined for this shape");
    }
}

auto occupiedCells(const Piece& piece) -> Orientation
{
    auto cells = rotationsFor(piece.shape).at(piece.rotation);
    for (auto& cell : cells)
    {
        cell.row += piece.row;
        cell.col += piece.col;
    }

    return cells;
}
