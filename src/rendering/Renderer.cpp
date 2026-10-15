#include "rendering/Renderer.hpp"

namespace 
{
    constexpr SDL_Color k_bgColor   {0x30, 0x0A, 0x24, 0xFF};
    constexpr SDL_Color k_lineColor {0xFF, 0xFF, 0xFF, 0xFF};
}

constexpr SDL_Color toSDLColor(Color color);


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
    
auto Renderer::update(const Board &board) -> void
{
    drawBackground();
    drawGrid(board);
    drawCells(board);

    SDL_RenderPresent(m_renderer);
}

auto Renderer::drawBackground() -> void
{
    SDL_SetRenderDrawColor(m_renderer, k_bgColor.r, k_bgColor.g, k_bgColor.b, k_bgColor.a);
    SDL_RenderClear(m_renderer);
}

auto Renderer::drawCells(const Board &board) -> void
{
    constexpr int gridLeft {tetris::constants::boardMargin};
    constexpr int gridTop  {tetris::constants::boardMargin};

    for (std::size_t row {0}; row < tetris::constants::boardRows; ++row)
    {
        for (std::size_t col {0}; col < tetris::constants::boardColumns; ++col)
        {
            const auto &cell = board.getCell(row, col);
            if (cell.isOccupied())
            {
                const auto color = toSDLColor(cell.getColor());
                SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
                
                const SDL_FRect cellRect{
                    static_cast<float>(gridLeft + col * tetris::constants::cellSize),
                    static_cast<float>(gridTop + row * tetris::constants::cellSize),
                    static_cast<float>(tetris::constants::cellSize),
                    static_cast<float>(tetris::constants::cellSize)
                };

                SDL_RenderFillRect(m_renderer, &cellRect);
            }
        }
    }
}
auto Renderer::drawGrid(const Board &board) -> void
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

constexpr auto toSDLColor(Color color) -> SDL_Color
{
    const auto rgb = static_cast<std::uint32_t>(color);
    return {
        static_cast<std::uint8_t>((rgb >> 16) & 0xFF),
        static_cast<std::uint8_t>((rgb >> 8) & 0xFF),
        static_cast<std::uint8_t>(rgb & 0xFF),
        0xFF
    };
}