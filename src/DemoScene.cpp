#include "DemoScene.hpp"

auto DemoScene::loadAssets(SDL_Renderer *renderer, TTF_Font *font,
                           int windowWidth, int windowHeight) -> bool {
  m_windowWidth = windowWidth;
  m_windowHeight = windowHeight;

  if (!m_backgroundTexture.loadFromFile(k_backgroundPath.data(), renderer)) {
    SDL_Log("Failed to load image: %s", SDL_GetError());
    return false;
  }

  if (!m_textTexture.loadFromRenderedText(m_text, k_defaultFontColor, font,
                                          renderer)) {
    SDL_Log("Failed to create text texture: %s", SDL_GetError());
    return false;
  }

  // layoutButtons();

  return true;
}

auto DemoScene::layoutButtons() -> void {
  const float kClipSize{static_cast<float>(m_windowWidth) * 0.5f};
  m_buttons[0] = Button{0.0f, 0.0f, kClipSize, kClipSize};
  m_buttons[1] = Button{kClipSize, 0.0f, kClipSize, kClipSize};
  m_buttons[2] = Button{0.0f, kClipSize, kClipSize, kClipSize};
  m_buttons[3] = Button{kClipSize, kClipSize, kClipSize, kClipSize};
}

auto DemoScene::findButtonAt(SDL_FPoint point) -> Button * {
  for (auto &button : m_buttons) {
    if (button.containsPoint(point)) {
      return &button;
    }
  }
  return nullptr;
}

auto DemoScene::handleEvent(const SDL_Event &event, int &exitCode) -> void {
  (void)exitCode;

  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (auto *button = findButtonAt({event.button.x, event.button.y})) {
      button->onClick();
    }
  }
  if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
    if (auto *button = findButtonAt({event.button.x, event.button.y})) {
      button->onRelease();
    }
  }
  if (event.type == SDL_EVENT_MOUSE_MOTION) {
    if (auto *button = findButtonAt({event.motion.x, event.motion.y})) {
      button->onHover();
    }
  }
}

auto DemoScene::render(SDL_Renderer *renderer) -> void {
  const SDL_FRect backgroundRect{0.0f, 0.0f, static_cast<float>(m_windowWidth),
                                 static_cast<float>(m_windowHeight)};
  m_backgroundTexture.render(renderer, backgroundRect);

  const SDL_FRect textRect{(m_windowWidth - m_textTexture.getWidth()) * 0.5f,
                           (m_windowHeight - m_textTexture.getHeight()) * 0.5f,
                           static_cast<float>(m_textTexture.getWidth()),
                           static_cast<float>(m_textTexture.getHeight())};
  m_textTexture.render(renderer, textRect);

  for (auto &button : m_buttons) {
    button.render(renderer);
  }
}
