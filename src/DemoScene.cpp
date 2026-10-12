#include "DemoScene.hpp"

#include <utility>

DemoScene::DemoScene(int windowWidth, int windowHeight,
                     std::function<void()> debugCallback,
                     KeyEventMode playerKeyEvents,
                     KeyEventMode systemKeyEvents)
    : m_windowWidth{windowWidth}, m_windowHeight{windowHeight},
      m_playerKeyEvents{playerKeyEvents}, m_systemKeyEvents{systemKeyEvents},
      m_toggleDebugOverlay_Callback{std::move(debugCallback)}
{
}

auto DemoScene::loadAssets(SDL_Renderer *renderer, TTF_Font *font,
                           int windowWidth, int windowHeight) -> bool
{
  m_windowWidth = windowWidth;
  m_windowHeight = windowHeight;

  if (!m_textTexture.loadFromRenderedText(m_text, k_defaultFontColor, font,
                                          renderer))
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to create text texture: %s", SDL_GetError());
    return false;
  }

  return true;
}

auto DemoScene::getInputType(const SDL_Event &event) const -> InputType
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

auto DemoScene::handleEvent(const SDL_Event &event, int &exitCode) -> void
{
  (void)exitCode;

  auto inputType{getInputType(event)};

  switch (inputType)
  {
  case InputType::Player:
    break;
  case InputType::System:
    m_toggleDebugOverlay_Callback ? m_toggleDebugOverlay_Callback() : SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Debug overlay callback nullptr");
    break;
  case InputType::Unmapped:
    break;
  }
}

auto DemoScene::render(SDL_Renderer *renderer) -> void
{
  const SDL_FRect textRect{(m_windowWidth - m_textTexture.getWidth()) * 0.5f,
                           (m_windowHeight - m_textTexture.getHeight()) * 0.25f,
                           static_cast<float>(m_textTexture.getWidth()),
                           static_cast<float>(m_textTexture.getHeight())};
  m_textTexture.render(renderer, textRect);
}
