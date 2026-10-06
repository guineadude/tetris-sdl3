#include "Dot.hpp"

auto Dot::handleEvent(const SDL_Event &event) -> void
{
    switch (event.key.key)
    {
    case SDLK_UP:
        mVelY -= kDotVelocity;
        break;
    case SDLK_DOWN:
        mVelY += kDotVelocity;
        break;
    case SDLK_LEFT:
        mVelX -= kDotVelocity;
        break;
    case SDLK_RIGHT:
        mVelX += kDotVelocity;
        break;
    }
}

auto Dot::move() -> void
{
    mPosX += mVelX;
    mPosY += mVelY;

    mPosX = std::clamp(mPosX, 0, mScreenWidth - kDotWidth);
    mPosY = std::clamp(mPosY, 0, mScreenHeight - kDotHeight);

    SDL_Log("Dot position: (%d, %d)", mPosX, mPosY);
}

auto Dot::render(SDL_Renderer *renderer) -> void
{
    mDotTexture.render(renderer, SDL_FRect{
                                     static_cast<float>(mPosX),
                                     static_cast<float>(mPosY),
                                     static_cast<float>(kDotWidth),
                                     static_cast<float>(kDotHeight)});
}

auto Dot::loadTexture(SDL_Renderer *renderer) -> bool
{
    return mDotTexture.loadFromFile(mDotTexturePath.data(), renderer);
}