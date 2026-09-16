#ifndef APP_HPP
#define APP_HPP

#include <SDL3/SDL.h>

#include <string_view>

class App
{
public:
    App();
    ~App();

    bool init();
    int run();

private:
    static constexpr int k_defaultWidth = 800;
    static constexpr int k_defaultHeight = 600;

    SDL_Window *m_window{};
    SDL_Renderer *m_renderer{};

    void handleEvents(SDL_Event *event, int &exitCode);
    void render();

    bool initializeWindow(std::string_view name, int width = k_defaultWidth, int height = k_defaultHeight)
    {
        if (m_window = SDL_CreateWindow(name.data(), width, height, 0); !m_window)
        {
            SDL_Log("Window initialization failed: %s", SDL_GetError());
            return false;
        }
        return true;
    }
    bool initializeRenderer()
    {
        if (m_renderer = SDL_CreateRenderer(m_window, nullptr); !m_renderer)
        {
            SDL_Log("Renderer initialization failed: %s", SDL_GetError());
            return false;
        }
        return true;
    }

    SDL_Window *getWindow() const { return m_window; }
    SDL_Renderer *getRenderer() const { return m_renderer; }
};

#endif // APP_HPP