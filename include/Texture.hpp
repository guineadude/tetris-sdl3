#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <optional>
#include <string_view>
#include <array>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Texture
{

public:
    enum class Clip : std::size_t
    {
        None,
        First,
        Second,
        Third,
        Fourth,
        Max
    };

private:
    SDL_Texture *m_texture{};
    std::string_view m_filePath{};
    std::optional<SDL_Color> m_colorKey{};
    std::optional<SDL_FRect> m_currentClip{};
    std::array<SDL_FRect, static_cast<std::size_t>(Clip::Max)> m_clips{};
    int m_width{};
    int m_height{};

public:
    Texture(std::optional<SDL_Color> colorKey = std::nullopt);
    ~Texture();
    Texture(Texture &&other) noexcept;
    Texture &operator=(Texture &&other) noexcept;

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    auto destroy() -> void;
    auto getFilePath() const -> std::string_view;
    auto setFilePath(std::string_view filePath) -> void;
    auto getTexture() const -> SDL_Texture *;
    auto populateClips(std::initializer_list<SDL_FRect> clips) -> void;

    auto loadFromFile(std::string_view path, SDL_Renderer *renderer) -> bool;
    auto render(SDL_Renderer *renderer, float xPos = 0.0F, float yPos = 0.0F) -> void;
    auto render(SDL_Renderer *renderer, const SDL_FRect &destination) -> void;
    auto repositionClip(Clip clip) -> void;
};

#endif // TEXTURE_HPP