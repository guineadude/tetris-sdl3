#ifndef DEMO_SCENE_HPP
#define DEMO_SCENE_HPP

#include <string>
#include <string_view>
#include <functional>
#include <utility>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Texture.hpp"
#include "Dot.hpp"

// Throwaway SDL learning scaffolding; to be replaced by real Tetris scene
// logic.
class DemoScene
{
public:
  DemoScene() = default;
  explicit DemoScene(int windowWidth, int windowHeight, std::function<void()> debug_Callback)
      : m_windowWidth{windowWidth}, m_windowHeight{windowHeight}, m_toggleDebugOverlay_Callback{std::move(debug_Callback)} {}

  auto loadAssets(SDL_Renderer *renderer, TTF_Font *font, int windowWidth,
                  int windowHeight) -> bool;
  auto handleEvent(const SDL_Event &event, int &exitCode) -> void;
  auto render(SDL_Renderer *renderer) -> void;

private:
  // static constexpr std::string_view k_backgroundPath{"assets\\kappn.png"};
  static constexpr SDL_Color k_defaultFontColor{0x00, 0x00, 0xFF, 0xFF};

  Texture m_backgroundTexture{};
  Texture m_textTexture{};
  std::string m_text{"Press ~ to print debug stats"};
  int m_windowWidth{};
  int m_windowHeight{};
  Dot m_dot{m_windowWidth, m_windowHeight};
  std::function<void()> m_toggleDebugOverlay_Callback{};

  enum class InputType
  {
    Unmapped,
    Player,
    System
  };
  auto getInputType(const SDL_Event &event) const -> InputType
  {
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
      switch (event.key.key)
      {
      case SDLK_GRAVE:
        return InputType::System;
        break;
      case SDLK_UP:
      case SDLK_DOWN:
      case SDLK_LEFT:
      case SDLK_RIGHT:
        return InputType::Player;
        break;
      }
    }
    return InputType::Unmapped; // Default to Unmapped if no relevant key is pressed
  }
};

#endif // DEMO_SCENE_HPP
