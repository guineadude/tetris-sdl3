/*This source code copyrighted by Lazy Foo' Productions 2004-2026
and may not be redistributed without written permission.*/

#include "01-hello-sdl3.h"

int main(int argc, char *args[])
{
    Application app;

    // Initialize
    if (!app.init())
    {
        app.close();
        return 1;
    }

    Texture buttonTexture{*app.renderer};
    if (!loadMedia(buttonTexture, "assets\\button.png", app))
    {
        app.close();
        return 2;
    }

    // Place buttons
    constexpr int kButtonCount = 4;
    Button buttons[kButtonCount]{{buttonTexture}, {buttonTexture}, {buttonTexture}, {buttonTexture}};
    buttons[0].setPosition(0, 0);
    buttons[1].setPosition(Application::kScreenWidth - Button::kButtonWidth, 0);
    buttons[2].setPosition(0, Application::kScreenHeight - Button::kButtonHeight);
    buttons[3].setPosition(Application::kScreenWidth - Button::kButtonWidth, Application::kScreenHeight - Button::kButtonHeight);

    int ec = updateLoop(/*buttons,*/ app, kButtonCount, buttons);

    // Clean up
    app.close();
    return ec;
}

auto updateLoop(/*TexturesForUpdateLoop &textures,*/ Application &app, int buttonCount, Button buttons[]) -> int
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

            // Handle button events
            for (int i = 0; i < buttonCount; ++i)
            {
                buttons[i].handleEvent(&e);
            }
        }

        SDL_RenderClear(app.renderer);

        // Render buttons
        for (int i = 0; i < buttonCount; i++)
        {
            buttons[i].render();
        }

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
bool loadMedia(Texture &text, std::string_view path, Application &app)
{
    if (!text.loadFromFile(path))
    {
        SDL_Log("Unable to load texture %.*s! SDL Error: %s\n", static_cast<int>(path.size()), path.data(), SDL_GetError());
        return false;
    }

    return true;
}
