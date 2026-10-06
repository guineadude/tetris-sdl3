#include "DemoScene.hpp"

auto DemoScene::loadAssets(SDL_Renderer *renderer, TTF_Font *font,
                           int windowWidth, int windowHeight) -> bool
{
  m_windowWidth = windowWidth;
  m_windowHeight = windowHeight;

  // if (!m_backgroundTexture.loadFromFile(k_backgroundPath.data(), renderer))
  // {
  //   SDL_Log("Failed to load image: %s", SDL_GetError());
  //   return false;
  // }

  if (!m_textTexture.loadFromRenderedText(m_text, k_defaultFontColor, font,
                                          renderer))
  {
    SDL_Log("Failed to create text texture: %s", SDL_GetError());
    return false;
  }

  return true;
}

auto DemoScene::handleEvent(const SDL_Event &event, int &exitCode) -> void
{
  (void)exitCode;

  if (event.type == SDL_EVENT_KEY_DOWN)
  {
    switch (event.key.key)
    {
    case SDLK_GRAVE:
      m_toggleDebugOverlay_Callback ? m_toggleDebugOverlay_Callback() : SDL_Log("Debug overlay callback nullptr");
      break;
    }
  }
}

auto DemoScene::render(SDL_Renderer *renderer) -> void
{
  // const SDL_FRect backgroundRect{0.0f, 0.0f, static_cast<float>(m_windowWidth),
  //                                static_cast<float>(m_windowHeight)};
  // m_backgroundTexture.render(renderer, backgroundRect);

  const SDL_FRect textRect{(m_windowWidth - m_textTexture.getWidth()) * 0.5f,
                           (m_windowHeight - m_textTexture.getHeight()) * 0.25f,
                           static_cast<float>(m_textTexture.getWidth()),
                           static_cast<float>(m_textTexture.getHeight())};
  m_textTexture.render(renderer, textRect);
}
