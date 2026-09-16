/*This source code copyrighted by Lazy Foo' Productions 2004-2026
and may not be redistributed without written permission.*/

#include "01-hello-sdl3.h"

bool loadMedia(Texture &textTexture, std::string_view path, Application &app)
{

    if (!(app.font = TTF_OpenFont(path.data(), 28)))
    {
        SDL_Log("Unable to load font %.*s! SDL_ttf Error: %s\n", static_cast<int>(path.size()), path.data(), SDL_GetError());
        return false;
    }
    else
    {
        SDL_Color textColor{0xFF, 0xFF, 0xFF, 0xFF};
        if (!textTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, *app.font))
        {
            SDL_Log("Unable to render text texture! SDL_ttf Error: %s\n", SDL_GetError());
            return false;
        }
        return true;
    }
}

int main(int argc, char *args[])
{
    Application app;

    // Initialize
    if (!app.init())
    {
        app.close();
        return 1;
    }

    TexturesForUpdateLoop textures{{*app.renderer}};

    if (!loadMedia(textures.textTexture, "assets\\lazy.ttf", app))
    {
        SDL_Log("Unable to load media!\n");
        app.close();
        return 2;
    }

    int ec = updateLoop(textures, app);

    // Clean up
    app.close();
    return ec;
}

auto updateLoop(TexturesForUpdateLoop &textures, Application &app) -> int
{
    bool quit{false};
    SDL_Event e;
    SDL_zero(e);
    SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0xFF);

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

        SDL_RenderClear(app.renderer);

        textures.textTexture.render((Application::kScreenWidth - textures.textTexture.getWidth()) * .5f, (Application::kScreenHeight - textures.textTexture.getHeight()) * .5f);

        // Update screen
        SDL_RenderPresent(app.renderer);
    }
    return 0;
}

void handleInput(SDL_KeyboardEvent &key)
{
    switch (key.key)
    {

    default:
        break;
    }
}
