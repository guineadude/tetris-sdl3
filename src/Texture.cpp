#include "Texture.hpp"

Texture::Texture(std::optional<SDL_Color> colorKey)
    : m_texture{}, m_colorKey{colorKey}, m_width{}, m_height{}
{
}

Texture::~Texture()
{
    destroy();
}

bool Texture::loadFromFile(std::string_view path, SDL_Renderer *renderer)
{
    SDL_Surface *surface{IMG_Load(path.data())};
    if (!surface)
    {
        SDL_Log("Failed to load texture from file: %s", SDL_GetError());
        return false;
    }

    if (m_colorKey)
    {
        if (!SDL_SetSurfaceColorKey(surface, true, SDL_MapSurfaceRGB(surface, m_colorKey->r, m_colorKey->g, m_colorKey->b)))
        {
            SDL_Log("Failed to set color key: %s", SDL_GetError());
        }
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    m_width = surface->w;
    m_height = surface->h;
    SDL_DestroySurface(surface);
    return m_texture != nullptr;
}

void Texture::render(SDL_Renderer *renderer, float xPos, float yPos)
{
    SDL_FRect destination{xPos, yPos, static_cast<float>(m_width), static_cast<float>(m_height)};
    SDL_RenderTexture(renderer, m_texture, nullptr, &destination);
}

void Texture::render(SDL_Renderer *renderer,
                     const SDL_FRect &source,
                     const SDL_FRect &destination)
{
    SDL_RenderTexture(renderer, m_texture, &source, &destination);
}

void Texture::destroy()
{
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}