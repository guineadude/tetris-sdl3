#ifndef DOT_HPP
#define DOT_HPP

#include <SDL3/SDL.h>
#include "Texture.hpp"

#include <algorithm>
#include <string_view>

class Dot
{
public:
    static constexpr int kDotWidth{20};
    static constexpr int kDotHeight{20};
    static constexpr int kDotVelocity{10};
    static constexpr int kAnimationClipCount{4};
    static constexpr int kAnimationClipWidth{64};
    static constexpr int kAnimationClipHeight{205};

    Dot(int w, int h, int maxFPS) : mScreenWidth{w}, mScreenHeight{h}, m_maxFPS{maxFPS}
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
    auto loadAssets(SDL_Renderer *renderer) -> bool;
    auto render(SDL_Renderer *renderer) -> void;

private:
    Texture mDotTexture{};
    std::string_view mDotTexturePath{"assets\\foo-sprites.png"};
    int mPosX{}, mPosY{};
    int mVelX{}, mVelY{};
    int mScreenWidth{}, mScreenHeight{};
    bool mMovingUp{}, mMovingDown{}, mMovingLeft{}, mMovingRight{};
    const int m_maxFPS{};

    auto animate() -> void;
};

#endif // DOT_HPP