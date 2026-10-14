#include "rendering/Renderer.hpp"

auto Renderer::initialize(SDL_Renderer *renderer) -> bool
{
    if(!renderer)
        return false;

    m_renderer = renderer;
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    return true;
}
    
auto Renderer::update() -> void
{
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

auto Renderer::shutdown() -> void
{
}