/*This source code copyrighted by Lazy Foo' Productions 2004-2026
and may not be redistributed without written permission.*/

/* Headers */
// Using SDL and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>
#include <string>
#include <string_view>
#include "Texture.h"
/* Constants */
// Screen dimension constants
constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

// Degrees added/removed per rotation key press
constexpr double kRotationStep{5.0};

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia(Texture &textTexture, std::string_view path);

// handle input
void handleInput(SDL_KeyboardEvent &key);

// Frees media and shuts down SDL
void close();

/* Global Variables */
// The window we'll be rendering to
SDL_Window *gWindow{};

// The renderer used to draw to the window
SDL_Renderer *gRenderer{};
// Global font
TTF_Font *gFont{nullptr};

/* Function Implementations */
bool init()
{

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        // Create window and renderer
        if (SDL_CreateWindowAndRenderer("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer); !gWindow || !gRenderer)
        {
            SDL_Log("Window / Renderercould not be created! SDL error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            if (!TTF_Init())
            {
                SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
                return false;
            }
        }
    }

    return true;
}

bool loadMedia(Texture &textTexture, std::string_view path)
{

    if (!(gFont = TTF_OpenFont("assets\\lazy.ttf", 28)))
    {
        SDL_Log("Unable to load font %.*s! SDL_ttf Error: %s\n", static_cast<int>(path.size()), path.data(), SDL_GetError());
        return false;
    }
    else
    {
        SDL_Color textColor{0xFF, 0xFF, 0xFF, 0xFF};
        if (!textTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, *gFont))
        {
            SDL_Log("Unable to render text texture! SDL_ttf Error: %s\n", SDL_GetError());
            return false;
        }
        return true;
    }
}

void close()
{
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Free font
    TTF_CloseFont(gFont);
    gFont = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
    TTF_Quit();
}

int main(int argc, char *args[])
{
    // Final exit code
    int exitCode{0};

    // Initialize
    if (!init())
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        Texture textTexture{*gRenderer};
        // Load media
        if (!loadMedia(textTexture, "assets\\lazy.ttf"))
        {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        // The quit flag
        bool quit{false};

        // The event data
        SDL_Event e;
        SDL_zero(e);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

        // The main loop
        while (!quit)
        {
            // Get event data
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_EVENT_QUIT)
                    quit = true;

                if (e.type == SDL_EVENT_KEY_DOWN)
                    handleInput(e.key);
            }

            SDL_RenderClear(gRenderer);

            textTexture.render((kScreenWidth - textTexture.getWidth()) * .5f, (kScreenHeight - textTexture.getHeight()) * .5f);

            // Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    // Clean up
    close();

    return exitCode;
}

void handleInput(SDL_KeyboardEvent &key)
{
    // Sentinel: no color channel key was pressed this call
    Texture::eColorChannel channelToUpdate{Texture::eColorChannel::MaxPlaceholder};

    switch (key.key)
    {

    default:
        break;
    }
}
