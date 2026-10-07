#ifndef DOT_HPP
#define DOT_HPP

#include <SDL3/SDL.h>
#include "Texture.hpp"

#include <algorithm>
#include <string_view>

class Dot
{
public:
    static constexpr int kDotWidth{64};
    static constexpr int kDotHeight{205};
    static constexpr int kDotVelocity{10};
    static constexpr int kAnimationClipCount{4};
    static constexpr int kAnimationClipWidth{64};
    static constexpr int kAnimationClipHeight{205};
    static constexpr Uint64 kAnimationFrameDuration{100'000'000}; // 100 ms
    Dot(int w, int h) : mScreenWidth{w}, mScreenHeight{h}
    {
        mPosX = mScreenWidth / 2;
        mPosY = mScreenHeight / 2;
    }

    auto handleEvent(const SDL_Event &event) -> void;
    auto setScreenSize(int w, int h) -> void
    {
        mScreenWidth = w;
        mScreenHeight = h;
    }
    auto move() -> void;
    auto animate() -> void;
    auto loadAssets(SDL_Renderer *renderer) -> bool;
    auto render(SDL_Renderer *renderer) -> void;

private:
    Texture mDotTexture{};
    std::string_view mDotTexturePath{"assets\\foo-sprites.png"};
    int mPosX{}, mPosY{};
    int mVelX{}, mVelY{};
    int mScreenWidth{}, mScreenHeight{};
    bool mMovingUp{}, mMovingDown{}, mMovingLeft{}, mMovingRight{};
    Texture::Clip mCurrentClip{Texture::Clip::None};
    Uint64 mLastAnimationUpdate{};
};

#endif // DOT_HPP