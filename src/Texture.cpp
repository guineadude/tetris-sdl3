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

auto Texture::render(float xPos, float yPos, SDL_FRect *clip, float clipSizeX, float clipSizeY) -> void
{
    SDL_FRect dstRect{xPos, yPos, clip ? clip->w : static_cast<float>(mWidth), clip ? clip->h : static_cast<float>(mHeight)};

    if (clipSizeX > 0.0f)
    {
        dstRect.w = clipSizeX;
    }

    if (clipSizeY > 0.0f)
    {
        dstRect.h = clipSizeY;
    }

    SDL_RenderTexture(&mRenderer, mTexture, clip, &dstRect);
}

auto Texture::setColor(Uint8 r, Uint8 g, Uint8 b) -> void
{
    SDL_SetTextureColorMod(mTexture, r, g, b);
}

auto Texture::setAlpha(Uint8 alpha) -> void
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

auto Texture::setBlending(SDL_BlendMode blendMode) -> void
{
    SDL_SetTextureBlendMode(mTexture, blendMode);
}

#if defined(SDL_TTF_MAJOR_VERSION)
auto Texture::loadFromRenderedText(std::string_view textureText, SDL_Color textColor, TTF_Font &font) -> bool
{
    destroy();

    if (SDL_Surface *textSurface = TTF_RenderText_Blended(&font, textureText.data(), 0, textColor); !textSurface)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
        SDL_DestroySurface(textSurface);
        return false;
    }
    else
    {
        if (mTexture = SDL_CreateTextureFromSurface(&mRenderer, textSurface); !mTexture)
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            SDL_DestroySurface(textSurface);
            return false;
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_DestroySurface(textSurface);
    }

    return true;
}
#endif
