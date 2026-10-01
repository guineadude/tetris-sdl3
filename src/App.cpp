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

  if (!m_scene.loadAssets(m_renderer, m_font, k_defaultWidth,
                          k_defaultHeight)) {
    SDL_Log("Failed to load scene assets: %s", SDL_GetError());
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

  m_scene.render(m_renderer);

  SDL_RenderPresent(m_renderer);
}

void App::handleEvents(SDL_Event *event, int &exitCode) {
  while (SDL_PollEvent(event) == true && exitCode == 0) {
    if (event->type == SDL_EVENT_QUIT) {
      exitCode = -1;
    }
    if (event->type == SDL_EVENT_KEY_DOWN) {
      switch (event->key.key) {
      case SDLK_ESCAPE:
        exitCode = -1;
        break;
      }
    }

    m_scene.handleEvent(*event, exitCode);
  }
}
