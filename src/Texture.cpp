#include "Texture.h"

Texture::Texture()
    : mTexture{}, mWidth{}, mHeight{}
{
}

Texture::~Texture()
{
    destroy();
}

auto Texture::destroy() -> void
{
}

auto Texture::loadFromFile(std::string path) -> bool
{
    destroy();

    if (SDL_Surface *loadedSurface = IMG_Load(path.c_str()); !loadedSurface)
    {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    return true;
}