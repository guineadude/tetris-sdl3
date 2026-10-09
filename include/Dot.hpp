#ifndef DOT_HPP
#define DOT_HPP

#include <SDL3/SDL.h>
#include "Texture.hpp"

#include <algorithm>
#include <string_view>

class Dot
{
public:
    const int kDotWidth{100};
    const int kDotHeight{100};
    const int kDotVelocity{10};
    const int kAnimationClipCount{4};
    const int kAnimationClipWidth{64};
    const int kAnimationClipHeight{200};
    static constexpr Uint64 kAnimationFrameDuration{100'000'000}; // 100 ms

    explicit Dot(int w, int h, int startX, int startY, bool canMove, std::string_view texturePath) : mScreenWidth{w}, mScreenHeight{h}, mDotTexturePath{texturePath}, mCanMove{canMove}
    {
        mPosX = startX;
        mPosY = startY;
        mHasTexture = true;
    }
    explicit Dot(int w, int h, int startX, int startY, bool canMove, SDL_Color color) : mScreenWidth{w}, mScreenHeight{h}, mDotColor{color}, mCanMove{canMove}
    {
        mPosX = startX;
        mPosY = startY;
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

private:
    int mScreenWidth{}, mScreenHeight{};

    Texture mDotTexture{};
    SDL_Color mDotColor{};
    std::string_view mDotTexturePath{"assets\\foo-sprites.png"};
    bool mHasTexture{false};
    bool mCanMove{true};

    int mPosX{}, mPosY{};
    int mVelX{}, mVelY{};

    bool mMovingUp{}, mMovingDown{}, mMovingLeft{}, mMovingRight{};
    Texture::Clip mCurrentClip{Texture::Clip::None};
    Uint64 mLastAnimationUpdate{};

    auto move() -> void;
    auto animate() -> void;
    auto render(SDL_Renderer *renderer) -> void;
};

#endif // DOT_HPP