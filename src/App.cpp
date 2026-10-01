#include "App.hpp"

App::App()
{
}

App::~App()
{
    if (m_font)
    {
        TTF_CloseFont(m_font);
    }
    TTF_Quit();
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
    if (!TTF_Init())
    {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
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
    if (!initializeFont())
    {
        SDL_Log("Font initialization failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

int App::run()
{
    int exitCode{};

    SDL_Event event;
    SDL_zero(event);

    addTexturesToArray();

    if (!initializeTextures())
    {
        SDL_Log("Failed to initialize textures: %s", SDL_GetError());
        return 2;
    }

    while (exitCode == 0)
    {
        handleEvents(&event, exitCode);
        render();
    }

    return exitCode;
}

void App::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer);

    auto &button{m_textureArray[0].texture};
    constexpr float kClipSize{static_cast<float>(k_defaultWidth) * .5f};
    button.repositionClip(Texture::Clip::First);
    button.render(m_renderer, SDL_FRect{0.0f, 0.0f, kClipSize, kClipSize});
    button.repositionClip(Texture::Clip::Second);
    button.render(m_renderer, SDL_FRect{kClipSize, 0.0f, kClipSize, kClipSize});
    button.repositionClip(Texture::Clip::Third);
    button.render(m_renderer, SDL_FRect{0.0f, kClipSize, kClipSize, kClipSize});
    button.repositionClip(Texture::Clip::Fourth);
    button.render(m_renderer, SDL_FRect{kClipSize, kClipSize, kClipSize, kClipSize});

    // m_textTexture.render(m_renderer, k_destRect);

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
        if (event->type == SDL_EVENT_KEY_DOWN)
        {
            switch (event->key.key)
            {
            case (SDLK_LEFT):
                m_textureArray[0].texture.setAlpha(128);
                m_textureArray[0].texture.setBlendMode(SDL_BLENDMODE_BLEND);
                break;
            case (SDLK_RIGHT):
                m_textureArray[0].texture.setColorMod(255, 0, 0);
                break;
            }
        }
    }
}

void App::addTexturesToArray()
{
    TextureAsset imgToRender{
        Texture{},
        "assets\\button.png"};

    constexpr float kButtonWidth{300.0f};
    constexpr float kButtonHeight{200.0f};

    imgToRender.texture.populateClips({SDL_FRect{0.0f, 0.0f, kButtonWidth, kButtonHeight},
                                       SDL_FRect{0.0f, kButtonHeight, kButtonWidth, kButtonHeight},
                                       SDL_FRect{0.0f, kButtonHeight * 2.0f, kButtonWidth, kButtonHeight},
                                       SDL_FRect{0.0f, kButtonHeight * 3.0f, kButtonWidth, kButtonHeight}});

    m_textureArray[0] = std::move(imgToRender);
}
bool App::initializeTextures()
{
    for (auto &textureAsset : m_textureArray)
    {
        if (!textureAsset.texture.loadFromFile(textureAsset.path.data(), m_renderer))
        {
            SDL_Log("Failed to load image: %s", SDL_GetError());
            return false;
        }
    }

    // if (!m_textTexture.loadFromRenderedText("Score: 100", k_defaultFontColor, m_font, m_renderer))
    // {
    //     SDL_Log("Failed to create text texture");
    //     return false;
    // }

    return true;
}
