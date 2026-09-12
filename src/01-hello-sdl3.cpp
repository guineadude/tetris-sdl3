/*This source code copyrighted by Lazy Foo' Productions 2004-2026
and may not be redistributed without written permission.*/

/* Headers */
// Using SDL and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

/* Constants */
// Screen dimension constants
constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

/* Global Variables */
// The window we'll be rendering to
SDL_Window *gWindow{};

// The surface contained by the window
SDL_Surface *gScreenSurface{};

// The image we will load and show on the screen
SDL_Surface *gHelloWorld{};

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
        // Create window
        if (gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0); !gWindow)
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return true;
}

bool loadMedia()
{

    // Load splash image
    std::string imagePath{"assets\\hello-sdl3.bmp"};
    if (gHelloWorld = SDL_LoadBMP(imagePath.c_str()); !gHelloWorld)
    {
        SDL_Log("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError());
        return false;
    }

    return true;
}

void close()
{
    // Clean up surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = nullptr;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

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
        // Load media
        if (!loadMedia())
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

                // Fill the surface white
                SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

                // Render image on screen
                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

                // Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    // Clean up
    close();

    return exitCode;
}
