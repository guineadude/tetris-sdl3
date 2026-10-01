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
  texture.repositionClip(Texture::Clip::First);
  m_button1.setColorMod();
  texture.render(m_renderer, m_button1.getBounds());
  texture.repositionClip(Texture::Clip::Second);
  m_button2.setColorMod();
  texture.render(m_renderer, m_button2.getBounds());
  texture.repositionClip(Texture::Clip::Third);
  m_button3.setColorMod();
  texture.render(m_renderer, m_button3.getBounds());
  texture.repositionClip(Texture::Clip::Fourth);
  m_button4.setColorMod();
  texture.render(m_renderer, m_button4.getBounds());

  // m_textTexture.render(m_renderer, k_destRect);

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
  TextureAsset imgToRender{Texture{}, "assets\\button.png"};

  const float kButtonWidth{300.0f};
  const float kButtonHeight{200.0f};

  imgToRender.texture.populateClips(
      {SDL_FRect{0.0f, 0.0f, kButtonWidth, kButtonHeight},
       SDL_FRect{0.0f, kButtonHeight, kButtonWidth, kButtonHeight},
       SDL_FRect{0.0f, kButtonHeight * 2.0f, kButtonWidth, kButtonHeight},
       SDL_FRect{0.0f, kButtonHeight * 3.0f, kButtonWidth, kButtonHeight}});

  constexpr float kClipSize{static_cast<float>(k_defaultWidth) * .5f};
  m_button1 = Button{0.0f, 0.0f, kClipSize, kClipSize};
  m_button2 = Button{kClipSize, 0.0f, kClipSize, kClipSize};
  m_button3 = Button{0.0f, kClipSize, kClipSize, kClipSize};
  m_button4 = Button{kClipSize, kClipSize, kClipSize, kClipSize};

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

  SDL_Texture *buttonTexture{m_textureArray[0].texture.getTexture()};
  m_button1.setTexture(buttonTexture);
  m_button2.setTexture(buttonTexture);
  m_button3.setTexture(buttonTexture);
  m_button4.setTexture(buttonTexture);

  // if (!m_textTexture.loadFromRenderedText("Score: 100", k_defaultFontColor,
  // m_font, m_renderer))
  // {
  //     SDL_Log("Failed to create text texture");
  //     return false;
  // }

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
