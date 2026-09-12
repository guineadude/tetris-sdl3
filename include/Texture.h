#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

    // Loads texture from disk
    auto loadFromFile(std::string path) const -> bool;

    // Cleans up texture
    auto destroy() -> void;

    // Draws texture
    auto render(float x, float y) const -> void;

    // Gets texture attributes
    auto getWidth() const -> int;
    auto getHeight() const -> int;
    auto isLoaded() const -> bool;

private:
    // Contains texture data
    SDL_Texture *mTexture{};

    // Texture dimensions
    int mWidth{};
    int mHeight{};
};

#endif // TEXTURE_H