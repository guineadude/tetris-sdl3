#ifndef DOT_HPP
#define DOT_HPP

#include <SDL3/SDL.h>

class Dot
{
public:
    static constexpr int kDotWidth{20};
    static constexpr int kDotHeight{20};
    static constexpr int kDotVelocity{10};

    Dot();

    auto handleEvent(SDL_Event &event) -> void;
    auto move() -> void;
    auto render(SDL_Renderer *renderer) -> void;

private:
    int mPosX{}, mPosY{};
    int mVelX{}, mVelY{};
};

#endif // DOT_HPP