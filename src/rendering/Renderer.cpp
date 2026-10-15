#include "rendering/Renderer.hpp"

namespace 
{
    constexpr SDL_Color k_bgColor   {0x30, 0x0A, 0x24, 0xFF};
    constexpr SDL_Color k_lineColor {0xFF, 0xFF, 0xFF, 0xFF};
    constexpr int gridLeft {tetris::constants::boardMargin};
    constexpr int gridTop  {tetris::constants::boardMargin};
    constexpr int gridWidth {
        static_cast<int>(tetris::constants::boardColumns) * tetris::constants::cellSize
    };
    constexpr int gridHeight {
        static_cast<int>(tetris::constants::boardRows) * tetris::constants::cellSize
    };
}

constexpr SDL_Color toSDLColor(Color color);

template <typename Callback>
auto forEachCell(const Board& board, Callback&& callback) -> void
{
    for (auto row {0uz}; row < tetris::constants::boardRows; ++row)
    {
        for (auto col {0uz}; col < tetris::constants::boardColumns; ++col)
        {
            callback(row, col, board.getCell(row, col));
        }
    }
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
    
auto Renderer::update(const Board &board) -> void
{
    drawBackground();
    drawCells(board);
    drawGrid();

    SDL_RenderPresent(m_renderer);
}

auto Renderer::drawBackground() -> void
{
    SDL_SetRenderDrawColor(m_renderer, k_bgColor.r, k_bgColor.g, k_bgColor.b, k_bgColor.a);
    SDL_RenderClear(m_renderer);
}

auto Renderer::drawCells(const Board &board) -> void
{
    auto fillCells = [&](std::size_t row, std::size_t col, const Cell &cell)
    {
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
    };

    forEachCell(board, fillCells);
}

auto Renderer::drawGrid() -> void
{   
    auto drawGridLine = [&](int startX, int startY, int endX, int endY)
    {
        SDL_RenderLine(m_renderer, startX, startY, endX, endY);
    };

    SDL_SetRenderDrawColor(m_renderer, k_lineColor.r, k_lineColor.g,
        k_lineColor.b, k_lineColor.a);

    for (auto row {0uz}; row <= tetris::constants::boardRows; ++row)
    {
        drawGridLine(
            gridLeft, (gridTop + (row * tetris::constants::cellSize)),
            gridLeft + gridWidth, (gridTop + (row * tetris::constants::cellSize))
        );
    }
    
    for (auto col {0uz}; col <= tetris::constants::boardColumns; ++col)
    {
        drawGridLine(
            (gridLeft + (col * tetris::constants::cellSize)), gridTop,
            (gridLeft + (col * tetris::constants::cellSize)), gridTop + gridHeight
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