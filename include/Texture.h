#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <unordered_map>
#include <string_view>
class Texture
{
public:
    static constexpr int kColorMagnitudeCount = 3;
    static constexpr Uint8 kColorMagnitudes[kColorMagnitudeCount] = {0x00, 0x7F, 0xFF};

    enum class eColorChannel
    {
        TextureRed = 0,
        TextureGreen = 1,
        TextureBlue = 2,
        TextureAlpha = 3,

        BackgroundRed = 4,
        BackgroundGreen = 5,
        BackgroundBlue = 6,

        MaxPlaceholder = 7,
    };

    static constexpr float kOriginalSize{-1.f};

    // special functions
    Texture(SDL_Renderer &renderer);

    ~Texture();

    Texture(const Texture &) = delete;

    Texture &operator=(const Texture &) = delete;

    Texture(Texture &&) = delete;

    Texture &operator=(Texture &&) = delete;

    // Loads texture from disk
    auto loadFromFile(std::string_view path) -> bool;

    // Cleans up texture
    auto destroy() -> void;

    // Draws texture
    void render(float x, float y, SDL_FRect *clip = nullptr, float width = kOriginalSize, float height = kOriginalSize, double degrees = 0.0, SDL_FPoint *center = nullptr, SDL_FlipMode flipMode = SDL_FLIP_NONE);

    // Sets color modulation
    void setColor(Uint8 r, Uint8 g, Uint8 b);

    // Sets opacity
    void setAlpha(Uint8 alpha);

    // Sets blend mode
    void setBlending(SDL_BlendMode blendMode);

    // Gets texture attributes
    auto getWidth() const -> int { return mWidth; }
    auto getHeight() const -> int { return mHeight; }
    auto isLoaded() const -> bool { return mTexture != nullptr; }

private:
    // Contains texture data
    SDL_Texture *mTexture{};

    SDL_Renderer &mRenderer;

    // Texture dimensions
    int mWidth{};
    int mHeight{};
};

#endif // TEXTURE_H