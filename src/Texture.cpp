#include "Texture.h"

Texture::Texture()
    : mTexture{}, mWidth{}, mHeight{}
{
}

Texture::~Texture()
{
    destroy();
}
