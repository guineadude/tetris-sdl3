#include "App.hpp"

App::App()
{
}

App::~App()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool App::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if (!initializeWindow("Tetris"))
    {
        SDL_Log("Window initialization failed: %s", SDL_GetError());
        return false;
    }

    if (!initializeRenderer())
    {
        SDL_Log("Renderer initialization failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

int App::run()
{
    int exitCode{};
    SDL_Event event;
    SDL_zero(event);
    Texture imgToRender{};

    if (!imgToRender.loadFromFile("assets\\button.png", m_renderer))
    {
        SDL_Log("Failed to load image: %s", SDL_GetError());
        exitCode = 2;
    }

    while (exitCode == 0)
    {
        handleEvents(&event, exitCode);
        render(imgToRender);
    }

    return exitCode;
}

void App::render(Texture &texture)
{
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer);

    texture.render(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void App::handleEvents(SDL_Event *event, int &exitCode)
{
    while (SDL_PollEvent(event) == true && exitCode == 0)
    {
        if (event->type == SDL_EVENT_QUIT)
        {
            exitCode = -1;
        }
    }
}
