#include "DemoScene.hpp"

auto DemoScene::loadAssets(SDL_Renderer *renderer, TTF_Font *font,
                           int windowWidth, int windowHeight) -> bool
{
  m_windowWidth = windowWidth;
  m_windowHeight = windowHeight;

  if (!m_backgroundTexture.loadFromFile(k_backgroundPath.data(), renderer))
  {
    SDL_Log("Failed to load image: %s", SDL_GetError());
    return false;
  }

  if (!m_textTexture.loadFromRenderedText(m_text, k_defaultFontColor, font,
                                          renderer))
  {
    SDL_Log("Failed to create text texture: %s", SDL_GetError());
    return false;
  }

  layoutButtons();

  return true;
}

auto DemoScene::layoutButtons() -> void
{
  const float kClipSize{static_cast<float>(m_windowWidth) * 0.5f};
  const float kButtonX{static_cast<float>(m_windowWidth) * 0.25f};
  const float kButtonY{static_cast<float>(m_windowHeight) * 0.5f};
  m_buttons[0] = Button{kButtonX, kButtonY, kClipSize, kClipSize * 0.5f};
}

auto DemoScene::findButtonAt(SDL_FPoint point) -> Button *
{
  for (auto &button : m_buttons)
  {
    if (button.containsPoint(point))
    {
      return &button;
    }
  }
  return nullptr;
}

auto DemoScene::handleEvent(const SDL_Event &event, int &exitCode) -> void
{
  (void)exitCode;

  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
  {
    if (auto *button = findButtonAt({event.button.x, event.button.y}))
    {
      button->onClick();
    }
  }
  if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
  {
    if (auto *button = findButtonAt({event.button.x, event.button.y}))
    {
      button->onRelease();
    }
  }
  if (event.type == SDL_EVENT_MOUSE_MOTION)
  {
    if (auto *button = findButtonAt({event.motion.x, event.motion.y}))
    {
      button->onHover();
    }
  }
  if (event.type == SDL_EVENT_KEY_DOWN)
  {
    switch (event.key.key)
    {
    case SDLK_GRAVE:
      if (m_toggleDebugOverlay_Callback)
        m_toggleDebugOverlay_Callback();
      break;
    }
  }
}

auto DemoScene::render(SDL_Renderer *renderer) -> void
{
  const SDL_FRect backgroundRect{0.0f, 0.0f, static_cast<float>(m_windowWidth),
                                 static_cast<float>(m_windowHeight)};
  m_backgroundTexture.render(renderer, backgroundRect);

  const SDL_FRect textRect{(m_windowWidth - m_textTexture.getWidth()) * 0.5f,
                           (m_windowHeight - m_textTexture.getHeight()) * 0.25f,
                           static_cast<float>(m_textTexture.getWidth()),
                           static_cast<float>(m_textTexture.getHeight())};
  m_textTexture.render(renderer, textRect);

  for (auto &button : m_buttons)
  {
    button.render(renderer);
  }
}
