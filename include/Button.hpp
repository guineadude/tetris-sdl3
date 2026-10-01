#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL3/SDL.h>
#include <array>

class Button {
private:
  float m_width{};
  float m_height{};
  float m_x{};
  float m_y{};
  SDL_FRect m_bounds{};

  enum class State { Idle, Hovered, Clicked, Released };
  State m_state{State::Idle};

public:
  Button() = default;

  Button(float x, float y, float width, float height)
      : m_width(width), m_height(height), m_x(x), m_y(y) {
    m_bounds = SDL_FRect{x, y, width, height};
  }

  auto getBounds() const -> const SDL_FRect & { return m_bounds; }

  auto containsPoint(SDL_FPoint point) const -> bool {
    return SDL_PointInRectFloat(&point, &m_bounds);
  }

  auto onHover() -> bool;
  auto onClick() -> bool;
  auto onRelease() -> bool;
};

#endif // BUTTON_HPP