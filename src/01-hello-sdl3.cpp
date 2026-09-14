/*This source code copyrighted by Lazy Foo' Productions 2004-2026
and may not be redistributed without written permission.*/

/* Headers */
// Using SDL and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include "Texture.h"
/* Constants */
// Screen dimension constants
constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia(Texture &texture);

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

bool loadMedia(Texture &texture)
{

    // Load splash image
    if (!texture.loadFromFile("assets\\hello-sdl3.bmp"))
    {
        SDL_Log("Unable to load image %s! SDL Error: %s\n", "assets\\hello-sdl3.bmp", SDL_GetError());
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
        Texture pngTexture{*gRenderer};
        // Load media
        if (!loadMedia(pngTexture))
        {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        else
        {
            // The quit flag
            bool quit{false};

            // The event data
            SDL_Event e;
            SDL_zero(e);

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
                }

                // Fill the background white
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // Render image on screen
                pngTexture.render(0.f, 0.f);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Clean up
    close();

    return exitCode;
}
