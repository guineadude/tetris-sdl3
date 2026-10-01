#include "Button.hpp"

auto Button::onHover() -> void { m_state = State::Hovered; }
auto Button::onClick() -> void { m_state = State::Clicked; }
auto Button::onRelease() -> void { m_state = State::Released; }

auto Button::getState() const -> State { return m_state; }
auto Button::setState(State state) -> void { m_state = state; }

auto Button::setColorMod() -> void {

  switch (m_state) {
  case State::Idle:
    SDL_SetTextureColorMod(m_texture, 255, 255, 255);
    break;
  case State::Hovered:
    SDL_SetTextureColorMod(m_texture, 200, 200, 255);
    break;
  case State::Clicked:
    SDL_SetTextureColorMod(m_texture, 150, 150, 255);
    break;
  case State::Released:
    SDL_SetTextureColorMod(m_texture, 255, 255, 200);
    break;

  default:
    break;
  }
}