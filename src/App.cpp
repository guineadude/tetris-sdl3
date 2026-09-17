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

    addTexturesToArray(m_textureArray);

    if (!initializeTextures(m_textureArray))
    {
        SDL_Log("Failed to initialize textures: %s", SDL_GetError());
        return 2;
    }

    while (exitCode == 0)
    {
        handleEvents(&event, exitCode);
        render(m_textureArray);
    }

    return exitCode;
}

void App::render(std::array<TextureAsset, k_numTextures> &textures) const
{
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer);

    for (auto &textureAsset : textures)
    {
        textureAsset.texture.render(m_renderer);
    }

    SDL_RenderPresent(m_renderer);
}

void App::handleEvents(SDL_Event *event, int &exitCode) const
{
    while (SDL_PollEvent(event) == true && exitCode == 0)
    {
        if (event->type == SDL_EVENT_QUIT)
        {
            exitCode = -1;
        }
    }
}

void App::addTexturesToArray(std::array<TextureAsset, k_numTextures> &textures)
{
    TextureAsset imgToRender{
        Texture{SDL_Color{0x00, 0x00, 0xFF, 0xFF}},
        "assets\\button.png"};

    textures[0] = std::move(imgToRender);
    // return true;
}

bool App::initializeTextures(std::array<TextureAsset, k_numTextures> &textures) const
{
    for (auto &textureAsset : textures)
    {
        if (!textureAsset.texture.loadFromFile(textureAsset.path.data(), m_renderer))
        {
            SDL_Log("Failed to load image: %s", SDL_GetError());
            return false;
        }
    }
    return true;
}
