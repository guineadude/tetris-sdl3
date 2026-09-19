#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <optional>
#include <string_view>
#include <array>
#include <initializer_list>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

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

public:
    // constructor, destructor and move semantics
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

    // clip management
    auto repositionClip(Clip clip) -> void;
    auto populateClips(std::initializer_list<SDL_FRect> clips) -> void;

    // getters
    auto getFilePath() const -> std::string_view;
    auto getTexture() const -> SDL_Texture *;

    // setters
    auto setFilePath(std::string_view filePath) -> void;
};

#endif // TEXTURE_HPP