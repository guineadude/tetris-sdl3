#include "App.hpp"

#include "Constants.hpp"

App::~App()
{
    shutdown();
}

auto App::initialize() -> bool
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return false;
    }
    m_sdlInitialized = true;

    if (m_window = SDL_CreateWindow(tetris::constants::windowTitle,
                                    tetris::constants::windowWidth,
                                    tetris::constants::windowHeight, 0); !m_window)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Window initialization failed: %s", SDL_GetError());
        return false;
    }

    if (m_renderer = SDL_CreateRenderer(m_window, nullptr); !m_renderer)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Renderer initialization failed: %s", SDL_GetError());
        return false;
    }

    if (!SDL_SetRenderVSync(m_renderer, 1))
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to set VSync: %s", SDL_GetError());
        return false;
    }

    if(!m_tetrisScene.initialize(getRenderer()))
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "TetrisScene initialization failed");
        return false;
    }

    SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
    return true;
}

auto App::run() -> void
{
    m_tetrisScene.run();
}

auto App::shutdown() -> int
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    if (m_sdlInitialized)
    {
        SDL_Quit();
        m_sdlInitialized = false;
    }
  return m_exitCode;
}