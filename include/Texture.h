#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class Texture
{
public:
    // special functions
    Texture(SDL_Renderer &renderer);
    ~Texture();
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;
    Texture(Texture &&) = delete;
    Texture &operator=(Texture &&) = delete;

    // Loads texture from disk
    auto loadFromFile(std::string path) -> bool;

    // Cleans up texture
    auto destroy() -> void;

    // Draws texture
    auto render(float x, float y) const -> void;

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