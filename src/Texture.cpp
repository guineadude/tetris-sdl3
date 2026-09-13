#include "Texture.h"

Texture::Texture(SDL_Renderer &renderer)
    : mTexture{}, mRenderer{renderer}, mWidth{}, mHeight{}
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

    // Destroy any existing texture
    destroy();

    // Load surface
    if (SDL_Surface *loadedSurface = IMG_Load(path.c_str()); !loadedSurface)
    {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    else
    {
        // Create texture from surface
        if (mTexture = SDL_CreateTextureFromSurface(&mRenderer, loadedSurface); !mTexture)
        {
            SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Clean up loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    // Return success if texture loaded
    return mTexture != nullptr;
}