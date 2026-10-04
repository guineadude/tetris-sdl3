#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL3/SDL.h>

#include <functional>

class Button {
private:
  SDL_FRect m_bounds{};
  std::function<void()> m_onClick{};

  enum class State { Idle, Hovered, Clicked, Released };
  State m_state{State::Idle};

public:
  Button() = default;

  Button(float x, float y, float width, float height)
      : m_bounds{x, y, width, height} {}

  auto containsPoint(SDL_FPoint point) const -> bool {
    return SDL_PointInRectFloat(&point, &m_bounds);
  }

  auto onHover() -> void;
  auto onClick() -> void;
  auto onRelease() -> void;

  auto getState() const -> State;
  auto getBounds() const -> const SDL_FRect & { return m_bounds; }

  auto setState(State state) -> void;
  auto setOnClick(std::function<void()> callback) -> void {
    m_onClick = std::move(callback);
  }

  // Draws the button as a solid rect tinted by its current state.
  auto render(SDL_Renderer *renderer) const -> void;
};

#endif // BUTTON_HPP