#include "Button.hpp"

auto Button::onHover() -> void { m_state = State::Hovered; }
auto Button::onClick() -> void { m_state = State::Clicked; }
auto Button::onRelease() -> void { m_state = State::Released; }

auto Button::getState() const -> State { return m_state; }
auto Button::setState(State state) -> void { m_state = state; }

auto Button::render(SDL_Renderer *renderer) const -> void
{
  switch (m_state)
  {
  case State::Idle:
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    break;
  case State::Hovered:
    // SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
    break;
  case State::Clicked:
    SDL_SetRenderDrawColor(renderer, 150, 150, 255, 255);
    break;
  case State::Released:
    // SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
    break;
  }

  SDL_RenderFillRect(renderer, &m_bounds);
}