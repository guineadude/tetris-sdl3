#ifndef APP_HPP
#define APP_HPP

#include <string_view>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "DemoScene.hpp"

class App
{
public:
  static constexpr int k_defaultWidth{500};
  static constexpr int k_defaultHeight{500};

  // font
  static constexpr std::string_view k_fontPath{"assets/lazy.ttf"};
  static constexpr int k_fontSize{30};

  App() = default;
  ~App();

  App(const App &) = delete;
  App &operator=(const App &) = delete;
  App(App &&) = delete;
  App &operator=(App &&) = delete;

  bool init();
  int run();

private:
  SDL_Window *m_window{};
  SDL_Renderer *m_renderer{};
  TTF_Font *m_font{};
  DemoScene m_scene{k_defaultWidth, k_defaultHeight, [this]()
                    { toggleSettings(); }};

  // framerate and vsync settings
  int m_maxFPS{60};
  bool m_vsyncEnabled{true};
  bool m_capFramerate{true};
  Uint64 m_tickCount{};
  Uint64 m_lastTickCount{};

  auto handleEvents(SDL_Event *event, int &exitCode) -> void;
  auto tick() -> void;
  auto render() -> void;

  auto toggleSettings() -> void
  {
    toggleVsync();
    toggleFramerateCap();
    SDL_Log("Toggling settings: VSync is now %s, Framerate cap is now %s",
            m_vsyncEnabled ? "enabled" : "disabled",
            m_capFramerate ? "capped" : "uncapped");
  }
  auto toggleVsync() -> void
  {
    m_vsyncEnabled = !m_vsyncEnabled;
    SDL_SetRenderVSync(m_renderer, m_vsyncEnabled ? true : false);
  }
  auto toggleFramerateCap() -> void
  {
    m_capFramerate = !m_capFramerate;
  };
  auto initializeWindow(std::string_view name, int width = k_defaultWidth,
                        int height = k_defaultHeight) -> bool
  {
    if (m_window = SDL_CreateWindow(name.data(), width, height, 0); !m_window)
    {
      SDL_Log("Window initialization failed: %s", SDL_GetError());
      return false;
    }
    return true;
  }
  auto initializeRenderer() -> bool
  {
    if (m_renderer = SDL_CreateRenderer(m_window, nullptr); !m_renderer)
    {
      SDL_Log("Renderer initialization failed: %s", SDL_GetError());
      return false;
    }
    return true;
  }
  auto initializeFont(std::string_view path = k_fontPath,
                      int fontSize = k_fontSize) -> bool
  {
    if (m_font = TTF_OpenFont(path.data(), fontSize); !m_font)
    {
      SDL_Log("Font initialization failed: %s", SDL_GetError());
      return false;
    }
    return true;
  }
};

#endif // APP_HPP