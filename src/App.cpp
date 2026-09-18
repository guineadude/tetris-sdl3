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
        handleEvents(&event, m_textureArray, exitCode);
        render(m_textureArray);
    }

    return exitCode;
}

void App::render(std::array<TextureAsset, k_numTextures> &textures) const
{
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer);

    const static SDL_FRect k_destRect{
        0.0f,
        0.0f,
        static_cast<float>(k_defaultWidth),
        static_cast<float>(k_defaultHeight)};

    textures[0].texture.render(m_renderer, k_destRect);

    SDL_RenderPresent(m_renderer);
}

void App::handleEvents(SDL_Event *event, std::array<TextureAsset, k_numTextures> &textures, int &exitCode) const
{
    while (SDL_PollEvent(event) == true && exitCode == 0)
    {
        if (event->type == SDL_EVENT_QUIT)
        {
            exitCode = -1;
        }
        if (event->type == SDL_EVENT_KEY_DOWN)
        {
            switch (event->key.key)
            {
            case (SDLK_1):
                textures[0].texture.repositionClip(Texture::Clip::First);
                break;
            case (SDLK_2):
                textures[0].texture.repositionClip(Texture::Clip::Second);
                break;
            case (SDLK_3):
                textures[0].texture.repositionClip(Texture::Clip::Third);
                break;
            case (SDLK_4):
                textures[0].texture.repositionClip(Texture::Clip::Fourth);
                break;
            case (SDLK_0):
                textures[0].texture.repositionClip(Texture::Clip::Default);
                break;
            }
        }
    }
}

void App::addTexturesToArray(std::array<TextureAsset, k_numTextures> &textures)
{
    TextureAsset imgToRender{
        Texture{SDL_Color{0x00, 0x00, 0xFF, 0xFF}},
        "assets\\button.png"};

    imgToRender.texture.populateClips({
        SDL_FRect{0, 0, App::k_defaultWidth, App::k_defaultHeight},       // Default
        SDL_FRect{0, 0, App::k_defaultWidth, App::k_defaultHeight / 4},   // First
        SDL_FRect{0, 200, App::k_defaultWidth, App::k_defaultHeight / 4}, // Second
        SDL_FRect{0, 400, App::k_defaultWidth, App::k_defaultHeight / 4}, // Third
        SDL_FRect{0, 600, App::k_defaultWidth, App::k_defaultHeight / 4}  // Fourth
    });

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
