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
  auto handleEvent(const SDL_Event &event, int &exitCode, TTF_Font *font, SDL_Renderer *renderer,
                   SDL_Window *window) -> void;
  auto render(SDL_Renderer *renderer) -> void;

  auto getIsEnteringText() const -> bool { return m_renderUserInput; }
  auto setIsEnteringText(bool isEnteringText, SDL_Window *window) -> void;

private:
  static constexpr SDL_Color k_defaultFontColor{0x00, 0x00, 0xFF, 0xFF};
  static constexpr int k_inputWidth{400};
  static constexpr int k_inputHeight{50};

  Texture m_textTexture{};
  Texture m_userInputTexture{};

  int m_windowWidth{};
  int m_windowHeight{};

  KeyEventMode m_playerKeyEvents{KeyEventMode::KeyDownAndUp};
  KeyEventMode m_systemKeyEvents{KeyEventMode::KeyDownOnly};

  std::function<void()> m_toggleDebugOverlay_Callback{};
  const std::string m_text{"Enter text:"};
  std::string m_inputText{"Placeholder"};

  bool m_renderUserInput{false};

  enum class InputAction
  {
    Unmapped,
    Player,
    ToggleDebugOverlay,
    ToggleTextEntry,
    Backspace,
    TextInput
  };
  auto getInputAction(const SDL_Event &event) const -> InputAction;

  //input handling functions
  auto handlePlayerInput(const SDL_Event &event) -> void;
  auto handleDebugOverlayToggle(const SDL_Event &event) -> void;
  auto handleTextInput(const SDL_Event &event, TTF_Font *font, SDL_Renderer *renderer, bool isBackspace = false) -> void;
};

#endif // DEMO_SCENE_HPP
