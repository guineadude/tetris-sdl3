#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <optional>
#include <string_view>
#include <array>
#include <initializer_list>
#include <algorithm>
#include <cstddef>
#include <cmath>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class Texture
{

public:
    enum class Clip : std::size_t
    {
        None,
        Default,
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
    Clip m_currentClip{Clip::None};
    std::array<SDL_FRect, static_cast<std::size_t>(Clip::Max)> m_clipData{};
    int m_width{};
    int m_height{};
    double m_rotationAngle{};
    SDL_FlipMode m_flipMode{};
    SDL_FPoint textureCenter{0.F, 0.F};

public:
    // constructor, destructor and move semantics.
    Texture(std::optional<SDL_Color> colorKey = std::nullopt);
    ~Texture();
    Texture(Texture &&other) noexcept;
    Texture &operator=(Texture &&other) noexcept;

    // non-copyable semantics (deleted copy constructor and copy assignment operator)
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    // destruction of the texture resource
    auto destroy() -> void;

    // resource management
    auto loadFromFile(std::string_view path, SDL_Renderer *renderer) -> bool;

    auto render(SDL_Renderer *renderer, const SDL_FRect &destination = {0.F, 0.F, 0.F, 0.F}) -> void;

    // rendering management
    auto setAlpha(uint8_t alpha) -> void;
    auto setBlendMode(SDL_BlendMode blendMode) -> void;
    auto setColorMod(uint8_t red, uint8_t green, uint8_t blue) -> void;

    // rotating, flipping
    auto rotateTexture(double angle) -> void;
    auto flipTexture(SDL_FlipMode flipMode) -> void;

    // clip management
    auto repositionClip(Clip clip) -> void { m_currentClip = clip; }
    auto populateClips(std::initializer_list<SDL_FRect> clips) -> void;

    // fonts
#if defined(SDL_TTF_MAJOR_VERSION)
    auto loadFromRenderedText(
        std::string_view text,
        SDL_Color color,
        TTF_Font *font,
        SDL_Renderer *renderer) -> bool;
#endif

    // getters
    auto getFilePath() const -> std::string_view;
    auto getTexture() const -> SDL_Texture *;
    auto getAlpha() const -> uint8_t;

    // setters
    auto setFilePath(std::string_view filePath) -> void;
};

#endif // TEXTURE_HPP