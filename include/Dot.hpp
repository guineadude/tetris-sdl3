#ifndef DOT_HPP
#define DOT_HPP

#include <SDL3/SDL.h>
#include "Texture.hpp"

#include <algorithm>
#include <string_view>

class Dot
{
public:
    const float kDotWidth{100};
    const float kDotHeight{100};
    const float kDotVelocity{10};
    const float kAnimationClipWidth{64};
    const float kAnimationClipHeight{200};
    const int kAnimationClipCount{4};
    static constexpr Uint64 kAnimationFrameDuration{100'000'000}; // 100 ms

    explicit Dot(int w, int h, int startX, int startY, bool canMove, std::string_view texturePath) : mScreenWidth{w}, mScreenHeight{h}, mDotTexturePath{texturePath}, mCanMove{canMove}
    {
        mPosX = startX;
        mPosY = startY;
        mCollider = SDL_FRect{
            static_cast<float>(mPosX),
            static_cast<float>(mPosY),
            kDotWidth,
            kDotHeight};
        mHasTexture = true;
    }
    explicit Dot(int w, int h, int startX, int startY, bool canMove, SDL_Color color) : mScreenWidth{w}, mScreenHeight{h}, mDotColor{color}, mCanMove{canMove}
    {
        mPosX = startX;
        mPosY = startY;
        mCollider = SDL_FRect{
            static_cast<float>(mPosX),
            static_cast<float>(mPosY),
            kDotWidth,
            kDotHeight};
        mHasTexture = false;
    }

    auto handleEvent(const SDL_Event &event) -> void;
    auto setScreenSize(int w, int h) -> void
    {
        mScreenWidth = w;
        mScreenHeight = h;
    }

    auto loadAssets(SDL_Renderer *renderer) -> bool;
    auto run(SDL_Renderer *renderer) -> void;
    auto getBounds() const -> SDL_FRect { return mCollider; }

private:
    int mScreenWidth{}, mScreenHeight{};

    Texture mDotTexture{};
    SDL_Color mDotColor{};
    std::string_view mDotTexturePath{"assets\\foo-sprites.png"};
    bool mHasTexture{false};
    bool mCanMove{true};

    int mPosX{}, mPosY{};
    int mVelX{}, mVelY{};
    SDL_FRect mCollider{};

    bool mMovingUp{}, mMovingDown{}, mMovingLeft{}, mMovingRight{};
    Texture::Clip mCurrentClip{Texture::Clip::None};
    Uint64 mLastAnimationUpdate{};

    auto move() -> void;
    auto animate() -> void;
    auto render(SDL_Renderer *renderer) -> void;
};

#endif // DOT_HPP