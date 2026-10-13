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

auto DemoScene::getInputAction(const SDL_Event &event) const -> InputAction
{
  if (event.type == SDL_EVENT_TEXT_INPUT)
  {
    return m_renderUserInput ? InputAction::TextInput : InputAction::Unmapped;
  }

  if (event.type != SDL_EVENT_KEY_DOWN && event.type != SDL_EVENT_KEY_UP)
  {
    return InputAction::Unmapped;
  }

  InputAction inputAction{InputAction::Unmapped};
  switch (event.key.key)
  {
  case SDLK_GRAVE:
    inputAction = InputAction::ToggleDebugOverlay;
    break;
  case SDLK_RETURN:
    inputAction = InputAction::ToggleTextEntry;
    break;
  case SDLK_UP:
  case SDLK_DOWN:
  case SDLK_LEFT:
  case SDLK_RIGHT:
    inputAction = InputAction::Player;
    break;
  default:
    return InputAction::Unmapped;
  }

  const KeyEventMode eventMode{inputAction == InputAction::Player
                                   ? m_playerKeyEvents
                                   : m_systemKeyEvents};

  if (event.type == SDL_EVENT_KEY_UP && eventMode == KeyEventMode::KeyDownOnly)
  {
    return InputAction::Unmapped;
  }

  return inputAction;
}

auto DemoScene::handleEvent(const SDL_Event &event, int &exitCode) -> void
{
  (void)exitCode;

  const InputAction inputAction{getInputAction(event)};

  switch (inputAction)
  {
  case InputAction::Player:
    break;
  case InputAction::ToggleDebugOverlay:
    m_toggleDebugOverlay_Callback ? m_toggleDebugOverlay_Callback() : SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Debug overlay callback nullptr");
    break;
  case InputAction::ToggleTextEntry:
    m_renderUserInput = !m_renderUserInput;
    break;
  case InputAction::TextInput:
    break;
  case InputAction::Unmapped:
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

  if(m_renderUserInput)
  {
    
  }
}
