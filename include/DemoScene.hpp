#ifndef DEMO_SCENE_HPP
#define DEMO_SCENE_HPP

#include <functional>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Texture.hpp"

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
  explicit DemoScene(int windowWidth, int windowHeight,
                     std::function<void()> debug_Callback,
                     KeyEventMode playerKeyEvents = KeyEventMode::KeyDownAndUp,
                     KeyEventMode systemKeyEvents = KeyEventMode::KeyDownOnly);

  auto loadAssets(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight) -> bool;
  auto handleEvent(const SDL_Event &event, int &exitCode) -> void;
  auto render(SDL_Renderer *renderer) -> void;

private:
  static constexpr SDL_Color k_defaultFontColor{0x00, 0x00, 0xFF, 0xFF};

  Texture m_textTexture{};

  int m_windowWidth{};
  int m_windowHeight{};

  KeyEventMode m_playerKeyEvents{KeyEventMode::KeyDownAndUp};
  KeyEventMode m_systemKeyEvents{KeyEventMode::KeyDownOnly};

  std::function<void()> m_toggleDebugOverlay_Callback{};
  std::string m_text{"Press ~ to print debug stats"};

  enum class InputType
  {
    Unmapped,
    Player,
    System
  };
  auto getInputType(const SDL_Event &event) const -> InputType;
};

#endif // DEMO_SCENE_HPP
