#include "Texture.hpp"

Texture::Texture(std::optional<SDL_Color> colorKey)
    : m_texture{}, m_colorKey{colorKey}, m_width{}, m_height{}
{
}

Texture::~Texture()
{
    destroy();
}

Texture::Texture(Texture &&other) noexcept
    : m_texture{other.m_texture},
      m_filePath{other.m_filePath},
      m_colorKey{other.m_colorKey},
      m_currentClip{other.m_currentClip},
      m_clipData{other.m_clipData},
      m_width{other.m_width},
      m_height{other.m_height}
{
    other.m_texture = nullptr;
    other.m_width = 0;
    other.m_height = 0;
}

Texture &Texture::operator=(Texture &&other) noexcept
{
    if (this != &other)
    {
        destroy();
        m_texture = other.m_texture;
        m_filePath = other.m_filePath;
        m_colorKey = other.m_colorKey;
        m_currentClip = other.m_currentClip;
        m_clipData = other.m_clipData;
        m_width = other.m_width;
        m_height = other.m_height;

        other.m_texture = nullptr;
        other.m_width = 0;
        other.m_height = 0;
    }
    return *this;
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

void Texture::render(SDL_Renderer *renderer, const SDL_FRect &destination)
{
    const SDL_FRect *sourceRect{m_currentClip != Clip::None ? &m_clipData[static_cast<std::size_t>(m_currentClip)] : nullptr};
    SDL_RenderTexture(renderer, m_texture, sourceRect, &destination);
}

void Texture::destroy()
{
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}

void Texture::repositionClip(Clip clip)
{
    m_currentClip = clip;
}

void Texture::populateClips(std::initializer_list<SDL_FRect> clips)
{
    std::copy(clips.begin(), clips.end(), m_clipData.begin() + 1); // skip unused Clip::None slot
    m_currentClip = Clip::None;
}
