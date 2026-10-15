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


}

auto Game::shutdown() -> void
{
}
