#ifndef DEMO_SCENE_HPP
#define DEMO_SCENE_HPP

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <functional>
#include <utility>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Button.hpp"
#include "Texture.hpp"

// Throwaway SDL learning scaffolding; to be replaced by real Tetris scene
// logic.
class DemoScene
{
public:
  static constexpr std::size_t k_buttonCount{1};

  DemoScene() = default;
  DemoScene(std::function<void()> debug_Callback,
            std::function<void()> toggleFrameTimer_Callback)
      : m_toggleDebugOverlay_Callback(std::move(debug_Callback)),
        m_toggleFrameTimer_Callback(std::move(toggleFrameTimer_Callback)) {}

  auto loadAssets(SDL_Renderer *renderer, TTF_Font *font, int windowWidth,
                  int windowHeight) -> bool;
  auto handleEvent(const SDL_Event &event, int &exitCode) -> void;
  auto render(SDL_Renderer *renderer) -> void;

private:
  static constexpr std::string_view k_backgroundPath{"assets\\kappn.png"};
  static constexpr SDL_Color k_defaultFontColor{0x00, 0x00, 0xFF, 0xFF};

  Texture m_backgroundTexture{};
  Texture m_textTexture{};
  std::string m_text{"Click to start timer:"};
  std::array<Button, k_buttonCount> m_buttons{};
  int m_windowWidth{};
  int m_windowHeight{};
  std::function<void()> m_toggleDebugOverlay_Callback{};
  std::function<void()> m_toggleFrameTimer_Callback{};
  auto layoutButtons() -> void;
  auto findButtonAt(SDL_FPoint point) -> Button *;
};

#endif // DEMO_SCENE_HPP
