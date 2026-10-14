#include "rendering/Renderer.hpp"

namespace 
{
    constexpr SDL_Color k_bgColor   {0x30, 0x0A, 0x24, 0xFF};
    constexpr SDL_Color k_lineColor {0xFF, 0xFF, 0xFF, 0xFF};
}

Renderer::~Renderer()
{
    shutdown();
}

auto Renderer::initialize(SDL_Renderer *renderer) -> bool
{
    if(!renderer)
        return false;

    m_renderer = renderer;

    SDL_SetRenderDrawColor(m_renderer, k_bgColor.r, k_bgColor.g, k_bgColor.b, k_bgColor.a);
    return true;
}
    
auto Renderer::update() -> void
{
    drawBackground();
    drawGrid();

    SDL_RenderPresent(m_renderer);
}

auto Renderer::drawBackground() -> void
{
    SDL_SetRenderDrawColor(m_renderer, k_bgColor.r, k_bgColor.g, k_bgColor.b, k_bgColor.a);
    SDL_RenderClear(m_renderer);
}


auto Renderer::drawGrid() -> void
{
    constexpr int gridWidth {
        static_cast<int>(tetris::constants::boardColumns) * tetris::constants::cellSize
    };
    constexpr int gridHeight {
        static_cast<int>(tetris::constants::boardRows) * tetris::constants::cellSize
    };
    constexpr int gridLeft {tetris::constants::boardMargin};
    constexpr int gridTop  {tetris::constants::boardMargin};

    SDL_SetRenderDrawColor(m_renderer, k_lineColor.r, k_lineColor.g,
        k_lineColor.b, k_lineColor.a);
        
    for (auto index {0uz}; index <= tetris::constants::boardRows; ++index)
    {
        SDL_RenderLine(m_renderer,
            gridLeft, (gridTop + (index * tetris::constants::cellSize)),
            gridLeft + gridWidth, (gridTop + (index * tetris::constants::cellSize))
        );
    }
    
    for (auto index {0uz}; index <= tetris::constants::boardColumns; ++index)
    {
        SDL_RenderLine(m_renderer,
            (gridLeft + (index * tetris::constants::cellSize)), gridTop,
            (gridLeft + (index * tetris::constants::cellSize)), gridTop + gridHeight
        );
    }
}

auto Renderer::shutdown() -> void {}
