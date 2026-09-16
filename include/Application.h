#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

class Application
{
public:
    static constexpr int kScreenWidth{640};
    static constexpr int kScreenHeight{480};

    SDL_Window *window{};
    SDL_Renderer *renderer{};
    TTF_Font *font{};

    Application() = default;

    ~Application()
    {
        close();
    }

    auto init() -> bool
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
            if (SDL_CreateWindowAndRenderer("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0, &window, &renderer); !window || !renderer)
            {
                SDL_Log("Window / Renderer could not be created! SDL error: %s\n", SDL_GetError());
                close();
                return false;
            }
            else
            {
                if (!TTF_Init())
                {
                    SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
                    close();
                    return false;
                }
            }
        }

        return true;
    }

    auto close() -> void
    {
        // Free font
        TTF_CloseFont(font);
        font = nullptr;

        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        SDL_DestroyWindow(window);
        window = nullptr;

        // Quit SDL subsystems
        SDL_Quit();
        TTF_Quit();
    }
};

#endif // APPLICATION_H