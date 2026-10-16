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
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            switch (event.key.key)
            {
                case SDLK_UP:
                case SDLK_X:
                    m_game.rotateActivePiece(true);
                    break;
                case SDLK_Z:
                    m_game.rotateActivePiece(false);
                    break;
                default:
                    break;
            }
        }
    }

    return m_running;
}

auto TetrisScene::update() -> void
{
    m_game.update();
}

auto TetrisScene::render() -> void
{
    m_renderer.update(m_game.board(), m_game.activePiece());
}

auto TetrisScene::shutdown() -> void
{
    m_renderer.shutdown();
    m_game.shutdown();
}