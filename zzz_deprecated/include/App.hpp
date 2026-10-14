#ifndef APP_HPP
#define APP_HPP

#include <string_view>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "DemoScene.hpp"

class App
{
public:
  static constexpr int k_defaultWidth{1000};
  static constexpr int k_defaultHeight{1000};

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

  // framerate and vsync settings
  int m_maxFPS{60};
  bool m_vsyncEnabled{true};
  bool m_capFramerate{true};
  Uint64 m_lastTickCount{};
  DemoScene m_scene{k_defaultWidth, k_defaultHeight,
                    [this]() { toggleSettings(); }};

  auto handleEvents(SDL_Event *event, int &exitCode) -> void;
  auto tick() -> void;
  auto render() -> void;

  auto toggleSettings() -> void;
  auto toggleVsync() -> void;
  auto toggleFramerateCap() -> void;
  auto initializeWindow(std::string_view name, int width = k_defaultWidth,
                        int height = k_defaultHeight) -> bool;
  auto initializeRenderer() -> bool;
  auto initializeFont(std::string_view path = k_fontPath,
                      int fontSize = k_fontSize) -> bool;
};

#endif // APP_HPP