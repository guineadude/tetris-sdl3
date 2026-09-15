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
    // Clean up texture
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

auto Texture::loadFromFile(std::string_view path) -> bool
{

    // Destroy any existing texture
    destroy();

    // Load surface
    if (SDL_Surface *loadedSurface = IMG_Load(path.data()); !loadedSurface)
    {
        SDL_Log("Unable to load image %.*s! SDL_image error: %s\n", static_cast<int>(path.size()), path.data(), SDL_GetError());
        return false;
    }
    else
    {
        if (!SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0x00, 0xFF, 0xFF)))
        {
            SDL_Log("Unable to set color key for image %.*s! SDL error: %s\n", static_cast<int>(path.size()), path.data(), SDL_GetError());
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
        }

        // Clean up loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    // Return success if texture loaded
    return mTexture != nullptr;
}

auto Texture::render(float x, float y, SDL_FRect *clip, float width, float height, double degrees, SDL_FPoint *center, SDL_FlipMode flipMode) -> void
{
    // Set texture pos
    SDL_FRect dstRect{x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

    if (clip)
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    // Resize if new dimensions are given
    if (width > 0)
    {
        dstRect.w = width;
    }
    if (height > 0)
    {
        dstRect.h = height;
    }

    // Render texture
    SDL_RenderTextureRotated(&mRenderer, mTexture, clip, &dstRect, degrees, center, flipMode);
}