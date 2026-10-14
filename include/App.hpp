#pragma once

#include <SDL3/SDL.h>

#include "scenes/TetrisScene.hpp"

class App
{
  public:
    App() = default;
    ~App();
    App(const App &) = delete;
    App &operator=(const App &) = delete;
    App(App &&) = delete;
    App &operator=(App &&) = delete;

    auto initialize() -> bool;
    auto run() -> void;
    auto shutdown() -> int;

    auto getRenderer() -> SDL_Renderer * { return m_renderer; }
    
  private:
    SDL_Window   *m_window         {nullptr};
    SDL_Renderer *m_renderer       {nullptr};
    TetrisScene   m_tetrisScene    {};
    int           m_exitCode       {};
    bool          m_sdlInitialized {false};
};