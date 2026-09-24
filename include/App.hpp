#ifndef APP_HPP
#define APP_HPP

#include <SDL3/SDL.h>
#include <array>
#include <string_view>

#include "Texture.hpp"

class App
{
public:
    struct TextureAsset
    {
        Texture texture;
        std::string_view path;
    };

    static constexpr int k_defaultWidth{640};
    static constexpr int k_defaultHeight{240};

    App();
    ~App();

    App(const App &) = delete;
    App &operator=(const App &) = delete;
    App(App &&) = delete;
    App &operator=(App &&) = delete;

    bool init();
    int run();

private:
    static constexpr std::size_t k_numTextures{1};
    SDL_Window *m_window{};
    SDL_Renderer *m_renderer{};
    std::array<TextureAsset, k_numTextures> m_textureArray{};

    // Aliases
    using TextureArray = std::array<TextureAsset, k_numTextures>;

    auto handleEvents(SDL_Event *event, int &exitCode) -> void;
    auto render() -> void;
    auto addTexturesToArray() -> void;
    auto initializeTextures() -> bool;
    auto initializeWindow(std::string_view name, int width = k_defaultWidth, int height = k_defaultHeight) -> bool
    {
        if (m_window = SDL_CreateWindow(name.data(), width, height, 0); !m_window)
        {
            SDL_Log("Window initialization failed: %s", SDL_GetError());
            return false;
        }
        return true;
    }
    auto initializeRenderer() -> bool
    {
        if (m_renderer = SDL_CreateRenderer(m_window, nullptr); !m_renderer)
        {
            SDL_Log("Renderer initialization failed: %s", SDL_GetError());
            return false;
        }
        return true;
    }

    auto getWindow() const -> SDL_Window * { return m_window; }
    auto getRenderer() const -> SDL_Renderer * { return m_renderer; }
};

#endif // APP_HPP