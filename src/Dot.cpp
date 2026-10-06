#include "Dot.hpp"

auto Dot::handleEvent(const SDL_Event &event) -> void
{
    const bool isKeyDown{event.type == SDL_EVENT_KEY_DOWN};
    if (!isKeyDown && event.type != SDL_EVENT_KEY_UP) // if the event is neither a key down nor a key up event
    {
        return;
    }

    switch (event.key.key)
    {
    case SDLK_UP:
        mMovingUp = isKeyDown;
        break;
    case SDLK_DOWN:
        mMovingDown = isKeyDown;
        break;
    case SDLK_LEFT:
        mMovingLeft = isKeyDown;
        break;
    case SDLK_RIGHT:
        mMovingRight = isKeyDown;
        break;
    }

    mVelX = (static_cast<int>(mMovingRight) - static_cast<int>(mMovingLeft)) *
            kDotVelocity;
    mVelY = (static_cast<int>(mMovingDown) - static_cast<int>(mMovingUp)) *
            kDotVelocity;
}

auto Dot::move() -> void
{
    mPosX += mVelX;
    mPosY += mVelY;

    mPosX = std::clamp(mPosX, 0, mScreenWidth - kDotWidth);
    mPosY = std::clamp(mPosY, 0, mScreenHeight - kDotHeight);
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