#include "game/Game.hpp"

Game::~Game()
{
    shutdown();
}

auto Game::initialize() -> bool
{
    spawnTiles();
    SDL_Log("Game start");
    return true;
}

auto Game::update() -> void
{
    m_dropElapsedSeconds += tetris::constants::gameUpdateDeltaSeconds;
    if (m_dropElapsedSeconds >= tetris::constants::gameDropIntervalSeconds)
    {
        m_dropElapsedSeconds = 0.0;
        dropTiles();
    }
    
}

auto Game::rotateActivePiece(bool clockwise) -> void
{
    if (!m_activePiece)
        return;

    auto rotated = *m_activePiece;
    rotated.rotation = clockwise
        ? (rotated.rotation + 1) % 4
        : (rotated.rotation + 3) % 4;

    if (canPlace(rotated))
        m_activePiece = rotated;
}

auto Game::shutdown() -> void
{
}

auto Game::canPlace(const Piece& piece) const -> bool
{
    for (const auto& cell : occupiedCells(piece))
    {
        if (cell.row < 0 ||
            cell.row >= static_cast<int>(tetris::constants::boardRows) ||
            cell.col < 0 ||
            cell.col >= static_cast<int>(tetris::constants::boardColumns))
            return false;

        if (m_board.getCell(
                static_cast<std::size_t>(cell.row),
                static_cast<std::size_t>(cell.col)).isOccupied())
            return false;
    }

    return true;
}

auto Game::dropTiles() -> void
{
}

auto Game::spawnTiles() -> void
{
    Piece candidate {Shape::T, 1, 4, 0};
    if (!canPlace(candidate))
        return;
    m_activePiece = candidate;
}
