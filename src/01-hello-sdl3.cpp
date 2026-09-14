/*This source code copyrighted by Lazy Foo' Productions 2004-2026
and may not be redistributed without written permission.*/

/* Headers */
// Using SDL and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <string_view>
#include "Texture.h"
/* Constants */
// Screen dimension constants
constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia(Texture &texture, std::string_view path);

// Frees media and shuts down SDL
void close();

/* Global Variables */
// The window we'll be rendering to
SDL_Window *gWindow{};

// The renderer used to draw to the window
SDL_Renderer *gRenderer{};

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
    }

    return true;
}

bool loadMedia(Texture &texture, std::string_view path)
{

    // Load splash image
    if (!texture.loadFromFile(path))
    {
        SDL_Log("Unable to load image %.*s! SDL Error: %s\n", static_cast<int>(path.size()), path.data(), SDL_GetError());
        return false;
    }

    return true;
}

void close()
{
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
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
        Texture background{*gRenderer};
        Texture colourKeyedCharacter{*gRenderer};
        // Load media
        if (!loadMedia(background, "assets\\background.png") || !loadMedia(colourKeyedCharacter, "assets\\foo.png"))
        {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        // The quit flag
        bool quit{false};

        // The event data
        SDL_Event e;
        SDL_zero(e);

        SDL_Color bgColor{0xFF, 0xFF, 0xFF, 0xFF};

        // Fill the background white
        SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);

        // The main loop
        while (!quit)
        {
            // Get event data
            while (SDL_PollEvent(&e))
            {
                // If event is quit type
                if (e.type == SDL_EVENT_QUIT)
                {
                    // End the main loop
                    quit = true;
                }

                if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
            SDL_RenderClear(gRenderer);

            background.render(0.0f, 0.0f);
            colourKeyedCharacter.render(240.0f, 190.0f);

            // Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    // Clean up
    close();

    return exitCode;
}
