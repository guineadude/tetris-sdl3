#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <optional>
#include <string_view>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Texture
{
private:
    SDL_Texture *m_texture{};
    std::optional<SDL_Color> m_colorKey{};
    int m_width{};
    int m_height{};

public:
    Texture(std::optional<SDL_Color> colorKey = std::nullopt);
    ~Texture();

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;
    Texture(Texture &&) = delete;
    Texture &operator=(Texture &&) = delete;

    void destroy();

    bool loadFromFile(std::string_view path, SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, float xPos = 0.0F, float yPos = 0.0F);
    void render(SDL_Renderer *renderer,
                const SDL_FRect &source,
                const SDL_FRect &destination);
};

#endif // TEXTURE_HPP