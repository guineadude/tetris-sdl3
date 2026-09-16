#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string_view>
#include <SDL3/SDL.h>

class Texture
{
private:
    SDL_Surface *m_texture{};
    int m_width{};
    int m_height{};

public:
    Texture();
    ~Texture();

    void destroy();

    bool loadFromFile(std::string_view path, SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, float xPos, float yPos);
    void render(SDL_Renderer *renderer,
                const SDL_FRect &source,
                const SDL_FRect &destination);
};

#endif // TEXTURE_HPP