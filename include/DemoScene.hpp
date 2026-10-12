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
                     KeyEventMode systemKeyEvents = KeyEventMode::KeyDownOnly,
                     KeyEventMode textInputKeyEvents = KeyEventMode::KeyDownOnly);

  auto loadAssets(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight) -> bool;
  auto handleEvent(const SDL_Event &event, int &exitCode) -> void;
  auto render(SDL_Renderer *renderer) -> void;

  auto getIsEnteringText() const -> bool { return m_renderUserInput; }
  auto setIsEnteringText(bool renderUserInput) -> void { m_renderUserInput = renderUserInput; }
  
private:
  static constexpr SDL_Color k_defaultFontColor{0x00, 0x00, 0xFF, 0xFF};

  Texture m_textTexture{};

  int m_windowWidth{};
  int m_windowHeight{};

  KeyEventMode m_playerKeyEvents{KeyEventMode::KeyDownAndUp};
  KeyEventMode m_systemKeyEvents{KeyEventMode::KeyDownOnly};
  KeyEventMode m_textInputKeyEvents{KeyEventMode::KeyDownOnly};

  std::function<void()> m_toggleDebugOverlay_Callback{};
  const std::string m_text{"Enter text:"};
  std::string m_inputText{};

  bool m_renderUserInput{false};

  enum class InputType
  {
    Unmapped,
    Player,
    TextInput,
    System
  };
  auto getInputType(const SDL_Event &event) const -> InputType;
};

#endif // DEMO_SCENE_HPP
