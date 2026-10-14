#include "Game.hpp"

auto Game::initialize() -> bool
{
    if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
    return false;
  }
  if (!TTF_Init())
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeWindow("Tetris"))
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Window initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeRenderer())
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Renderer initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeFont())
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Font initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!SDL_SetRenderVSync(m_renderer, 1))
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to set VSync: %s", SDL_GetError());
    return false;
  }
  SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
  return true;
}

auto Game::run() -> void
{
    // Game loop code here
}

auto Game::shutdown() -> int
{
    // Shutdown code here
    return 0;
}