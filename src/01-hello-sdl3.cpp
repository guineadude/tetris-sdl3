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
bool loadMedia(Texture &texture, std::string_view path);

// handle input
void handleInput(SDL_KeyboardEvent &key, double &degrees, SDL_FlipMode &flipMode, std::size_t *colorChannelsIndices);

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
        Texture colorsTexture{*gRenderer};
        // Load media
        if (!loadMedia(colorsTexture, "assets\\colors.png"))
        {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        // The quit flag
        bool quit{false};

        // The event data
        SDL_Event e;
        SDL_zero(e);

        double degrees{};
        SDL_FlipMode flipMode{SDL_FLIP_NONE};
        SDL_FPoint center{colorsTexture.getWidth() / 2.f, colorsTexture.getHeight() / 2.f};

        // Init sprite clip
        // constexpr float kSpriteSize = 100.f;
        // SDL_FRect spriteClip{0.f, 0.f, kSpriteSize, kSpriteSize};

        // Init sprite size
        SDL_FRect spriteSize{0.f, 0.f, 0.f, 0.f};

        spriteSize.w = static_cast<float>(kScreenWidth) * 0.5f;
        spriteSize.h = static_cast<float>(kScreenHeight) * 0.5f;

        spriteSize.x =
            (static_cast<float>(kScreenWidth) - spriteSize.w) / 2.f;

        spriteSize.y =
            (static_cast<float>(kScreenHeight) - spriteSize.h) / 2.f;

        // Initialize colors
        std::size_t colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::MaxPlaceholder)];
        colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureRed)] = 2;
        colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureGreen)] = 2;
        colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureBlue)] = 2;
        colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureAlpha)] = 2;

        colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundRed)] = 2;
        colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundGreen)] = 2;
        colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundBlue)] = 2;

        // Initialize blending
        colorsTexture.setBlending(SDL_BLENDMODE_BLEND);

        // The main loop
        while (!quit)
        {
            // Get event data
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_EVENT_QUIT)
                    quit = true;

                if (e.type == SDL_EVENT_KEY_DOWN)
                    handleInput(e.key, degrees, flipMode, colorChannelsIndices);
            }

            // Fill the background
            SDL_SetRenderDrawColor(gRenderer,
                                   Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundRed)]],
                                   Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundGreen)]],
                                   Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundBlue)]],
                                   0xFF);

            // Clear screen
            SDL_RenderClear(gRenderer);

            // Set texture color and render
            colorsTexture.setColor(
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureRed)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureGreen)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureBlue)]]);
            colorsTexture.setAlpha(Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureAlpha)]]);

            colorsTexture.render(spriteSize.x, spriteSize.y, nullptr, spriteSize.w, spriteSize.h, degrees, &center, flipMode);
            // Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    // Clean up
    close();

    return exitCode;
}

void handleInput(SDL_KeyboardEvent &key, double &degrees, SDL_FlipMode &flipMode, std::size_t *colorChannelsIndices)
{
    // Sentinel: no color channel key was pressed this call
    Texture::eColorChannel channelToUpdate{Texture::eColorChannel::MaxPlaceholder};

    switch (key.key)
    {
    case SDLK_LEFT:
        degrees -= kRotationStep;
        break;
    case SDLK_RIGHT:
        degrees += kRotationStep;
        break; // Set flip mode based on 1/2/3 key press
    case SDLK_1:
        flipMode = SDL_FLIP_HORIZONTAL;
        break;
    case SDLK_2:
        flipMode = SDL_FLIP_NONE;
        break;
    case SDLK_3:
        flipMode = SDL_FLIP_VERTICAL;
        break; // Update texture color
    case SDLK_A:
        channelToUpdate = Texture::eColorChannel::TextureRed;
        break;
    case SDLK_S:
        channelToUpdate = Texture::eColorChannel::TextureGreen;
        break;
    case SDLK_D:
        channelToUpdate = Texture::eColorChannel::TextureBlue;
        break;
    case SDLK_F:
        channelToUpdate = Texture::eColorChannel::TextureAlpha;
        break;

    // Update background color
    case SDLK_Q:
        channelToUpdate = Texture::eColorChannel::BackgroundRed;
        break;
    case SDLK_W:
        channelToUpdate = Texture::eColorChannel::BackgroundGreen;
        break;
    case SDLK_E:
        channelToUpdate = Texture::eColorChannel::BackgroundBlue;
        break;
    default:
        break;
    }

    // Keep degrees within [0, 360)
    degrees = std::fmod(degrees, 360.0);
    if (degrees < 0.0)
        degrees += 360.0;

    // If a channel key was pressed, cycle its magnitude and log all values
    if (channelToUpdate != Texture::eColorChannel::MaxPlaceholder)
    {
        std::size_t &index{colorChannelsIndices[static_cast<std::size_t>(channelToUpdate)]};
        index = (index + 1) % Texture::kColorMagnitudeCount;

        SDL_Log("Texture - R:%d G:%d B:%d A:%d | Background - R:%d G:%d B:%d",
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureRed)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureGreen)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureBlue)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::TextureAlpha)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundRed)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundGreen)]],
                Texture::kColorMagnitudes[colorChannelsIndices[static_cast<std::size_t>(Texture::eColorChannel::BackgroundBlue)]]);
    }
}
