#include "scenes/TetrisScene.hpp"

TetrisScene::~TetrisScene()
{
    shutdown();
}

auto TetrisScene::initialize(SDL_Renderer *renderer) -> bool
{
    if(!m_game.initialize())
        return false;
    if(!m_renderer.initialize(renderer))
        return false;

    return true;
}

auto TetrisScene::processEvents() -> bool
{
    SDL_Event event {};
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            m_running = false;
    }

    return m_running;
}

auto TetrisScene::update() -> void
{
    m_game.update();
}

auto TetrisScene::render() -> void
{
    m_renderer.update(m_game.board());
}

auto TetrisScene::shutdown() -> void
{
    m_renderer.shutdown();
    m_game.shutdown();
}