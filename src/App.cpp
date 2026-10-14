#include "App.hpp"

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

    m_window = SDL_CreateWindow("Tetris", 800, 600, 0);
    if (!m_window)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Window initialization failed: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Renderer initialization failed: %s", SDL_GetError());
        return false;
    }

    if (!SDL_SetRenderVSync(m_renderer, 1))
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Failed to set VSync: %s", SDL_GetError());
        return false;
    }

    SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
    return true;
}

auto App::run() -> void
{
    bool isRunning{true};
    SDL_Event event;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                isRunning = false;
            }
        }

        if (!isRunning)
        {
            break;
        }

        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }
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
    return 0;
}