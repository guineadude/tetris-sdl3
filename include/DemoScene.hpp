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
  enum class KeyEventMode
  {
    KeyDownOnly,
    KeyDownAndUp
  };

  DemoScene() = default;
  explicit DemoScene(int windowWidth, int windowHeight, int maxFPS,
                     std::function<void()> debug_Callback,
                     KeyEventMode playerKeyEvents = KeyEventMode::KeyDownAndUp,
                     KeyEventMode systemKeyEvents = KeyEventMode::KeyDownOnly)
      : m_windowWidth{windowWidth}, m_windowHeight{windowHeight},
        m_maxFPS{maxFPS},
        m_toggleDebugOverlay_Callback{std::move(debug_Callback)},
        m_playerKeyEvents{playerKeyEvents}, m_systemKeyEvents{systemKeyEvents} {}

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
  Dot m_redDot{m_windowWidth, m_windowHeight, 0, 0, true, std::string_view{"assets\\foo-sprites.png"}};
  Dot m_blueDot{m_windowWidth, m_windowHeight, 250, 250, false, SDL_Color{0x00, 0x00, 0xFF, 0xFF}};
  std::function<void()> m_toggleDebugOverlay_Callback{};
  KeyEventMode m_playerKeyEvents{KeyEventMode::KeyDownAndUp};
  KeyEventMode m_systemKeyEvents{KeyEventMode::KeyDownOnly};
  const int m_maxFPS{};

  enum class InputType
  {
    Unmapped,
    Player,
    System
  };
  auto getInputType(const SDL_Event &event) const -> InputType
  {
    if (event.type != SDL_EVENT_KEY_DOWN && event.type != SDL_EVENT_KEY_UP)
    {
      return InputType::Unmapped;
    }

    InputType inputType{InputType::Unmapped};
    switch (event.key.key)
    {
    case SDLK_GRAVE:
      inputType = InputType::System;
      break;
    case SDLK_UP:
    case SDLK_DOWN:
    case SDLK_LEFT:
    case SDLK_RIGHT:
      inputType = InputType::Player;
      break;
    default:
      return InputType::Unmapped;
    }

    const KeyEventMode eventMode{inputType == InputType::Player
                                     ? m_playerKeyEvents
                                     : m_systemKeyEvents};
    if (event.type == SDL_EVENT_KEY_UP &&
        eventMode == KeyEventMode::KeyDownOnly)
    {
      return InputType::Unmapped;
    }

    return inputType;
  }
};

#endif // DEMO_SCENE_HPP
