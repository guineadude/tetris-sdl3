#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

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
    TTF_Font *m_font{nullptr};
    bool m_sdlInitialized{false};
    bool m_ttfInitialized{false};
};