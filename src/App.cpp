#include "App.hpp"

App::App() {}

App::~App() {
  if (m_font) {
    TTF_CloseFont(m_font);
  }
  TTF_Quit();
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

bool App::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return false;
  }
  if (!TTF_Init()) {
    SDL_Log("TTF_Init failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeWindow("Tetris")) {
    SDL_Log("Window initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeRenderer()) {
    SDL_Log("Renderer initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeFont()) {
    SDL_Log("Font initialization failed: %s", SDL_GetError());
    return false;
  }

  return true;
}

int App::run() {
  int exitCode{};

  SDL_Event event;
  SDL_zero(event);

  addTexturesToArray();

  if (!initializeTextures()) {
    SDL_Log("Failed to initialize textures: %s", SDL_GetError());
    return 2;
  }

  while (exitCode == 0) {
    handleEvents(&event, exitCode);
    render();
  }

  return exitCode;
}

void App::render() {
  SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(m_renderer);

  auto &texture{m_textureArray[0].texture};
  const auto destRect{SDL_FRect{
      (k_defaultWidth - m_textTexture.getWidth()) * 0.5f,
      (k_defaultHeight - m_textTexture.getHeight()) * 0.5f,
      static_cast<float>(m_textTexture.getWidth()),
      static_cast<float>(m_textTexture.getHeight())}};
  m_textTexture.render(m_renderer, destRect);

  SDL_RenderPresent(m_renderer);
}

void App::handleEvents(SDL_Event *event, int &exitCode) {
  while (SDL_PollEvent(event) == true && exitCode == 0) {
    if (event->type == SDL_EVENT_QUIT) {
      exitCode = -1;
    }
    if (event->type == SDL_EVENT_KEY_DOWN) {
      switch (event->key.key) {}
    }
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      if (auto *button = checkButtonBounds()) {
        button->onClick();
      }
    }
    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
      if (auto *button = checkButtonBounds()) {
        button->onRelease();
      }
    }
    if (event->type == SDL_EVENT_MOUSE_MOTION) {
      if (auto *button = checkButtonBounds()) {
        button->onHover();
      }
    }
  }
}

void App::addTexturesToArray() {
  TextureAsset imgToRender{Texture{}, "assets\\kappn.png"};

  m_textureArray[0] = std::move(imgToRender);
}

bool App::initializeTextures() {
  for (auto &textureAsset : m_textureArray) {
    if (!textureAsset.texture.loadFromFile(textureAsset.path.data(),
                                           m_renderer)) {
      SDL_Log("Failed to load image: %s", SDL_GetError());
      return false;
    }
  }

  if (!m_textTexture.loadFromRenderedText("Text Timing", k_defaultFontColor,
                                          m_font, m_renderer)) {
    SDL_Log("Failed to create text texture: %s", SDL_GetError());
    return false;
  }

  return true;
}

auto App::checkButtonBounds() -> Button * {
  float x = -1.f, y = -1.f;
  SDL_GetMouseState(&x, &y);
  const SDL_FPoint mousePos{x, y};

  if (m_button1.containsPoint(mousePos)) {
    return &m_button1;
  }
  if (m_button2.containsPoint(mousePos)) {
    return &m_button2;
  }
  if (m_button3.containsPoint(mousePos)) {
    return &m_button3;
  }
  if (m_button4.containsPoint(mousePos)) {
    return &m_button4;
  }

  return nullptr;
}
