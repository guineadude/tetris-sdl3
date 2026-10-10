#ifndef COLLISION_HANDLER_HPP
#define COLLISION_HANDLER_HPP

#include <array>

#include <SDL3/SDL.h>

namespace CollisionHandler {

    [[nodiscard]] inline auto checkAABB(const SDL_FRect& a, const SDL_FRect& b) -> bool
    {
        return (a.x < b.x + b.w &&
                a.x + a.w > b.x &&
                a.y < b.y + b.h &&
                a.y + a.h > b.y);
    }  
}

#endif // COLLISION_HANDLER_HPP