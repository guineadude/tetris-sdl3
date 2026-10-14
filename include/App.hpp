#pragma once

#include <SDL3/SDL.h>

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

  private:
    SDL_Window *m_window{nullptr};
    SDL_Renderer *m_renderer{nullptr};
    bool m_sdlInitialized{false};
};