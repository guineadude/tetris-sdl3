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

auto TetrisScene::update() -> void
{
    SDL_Event event {};
    bool running {true};

    while(running)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
                running = false;
        }
        if(event.type == SDL_EVENT_KEY_DOWN)
        {

        }

        m_game.update();
        m_renderer.update(m_game.board());
    }


}

auto TetrisScene::shutdown() -> void
{
    m_renderer.shutdown();
    m_game.shutdown();
}