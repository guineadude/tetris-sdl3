#include "game/Game.hpp"

Game::~Game()
{
    shutdown();
}

auto Game::initialize() -> bool
{
    return true;
}

auto Game::update() -> void
{
    board().setCell(0, 0, Cell{State::Occupied, Color::Cyan});
}

auto Game::shutdown() -> void
{
}
