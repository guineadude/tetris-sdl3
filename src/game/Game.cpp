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

auto Game::shutdown() -> void
{
}

auto Game::dropTiles() -> void
{
}

auto Game::spawnTiles() -> void
{
}
