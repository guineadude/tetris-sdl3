#include "DemoScene.hpp"

auto DemoScene::loadAssets(SDL_Renderer *renderer, TTF_Font *font,
                           int windowWidth, int windowHeight) -> bool
{
  m_windowWidth = windowWidth;
  m_windowHeight = windowHeight;
  m_redDot.setScreenSize(windowWidth, windowHeight);
  m_blueDot.setScreenSize(windowWidth, windowHeight);

  // if (!m_backgroundTexture.loadFromFile(k_backgroundPath.data(), renderer))
  // {
  //   SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", SDL_GetError());
  //   return false;
  // }

  if (!m_textTexture.loadFromRenderedText(m_text, k_defaultFontColor, font,
                                          renderer))
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to create text texture: %s", SDL_GetError());
    return false;
  }

  if (!m_redDot.loadAssets(renderer))
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to load red dot texture: %s", SDL_GetError());
    return false;
  }

  if (!m_blueDot.loadAssets(renderer))
  {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to load blue dot texture: %s", SDL_GetError());
    return false;
  }

  m_dots.push_back(&m_redDot);
  m_dots.push_back(&m_blueDot);

  return true;
}

auto DemoScene::handleEvent(const SDL_Event &event, int &exitCode) -> void
{
  (void)exitCode;

  auto inputType{getInputType(event)};

  switch (inputType)
  {
  case InputType::Player:
    m_redDot.handleEvent(event);
    m_blueDot.handleEvent(event);
    break;
  case InputType::System:
    m_toggleDebugOverlay_Callback ? m_toggleDebugOverlay_Callback() : SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Debug overlay callback nullptr");
    break;
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

  forEachObj([renderer](Dot &dot) {
    dot.run(renderer);
  });

  checkCollisions();
}

