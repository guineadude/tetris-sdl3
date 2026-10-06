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

    Dot(int w, int h) : mScreenWidth{w}, mScreenHeight{h} {}

    auto handleEvent(const SDL_Event &event) -> void;
    auto move() -> void;
    auto loadTexture(SDL_Renderer *renderer) -> bool;
    auto render(SDL_Renderer *renderer) -> void;

private:
    Texture mDotTexture{};
    std::string_view mDotTexturePath{"assets\\kappn.png"};
    int mPosX{250}, mPosY{250};
    int mVelX{}, mVelY{};
    int mScreenWidth{}, mScreenHeight{};
};

#endif // DOT_HPP