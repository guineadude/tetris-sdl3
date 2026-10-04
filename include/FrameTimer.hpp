#ifndef FRAME_TIMER_HPP
#define FRAME_TIMER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Texture.hpp"

class FrameTimer {
private:
  Texture m_statsTexture{};
  Uint64 m_startTick{};
  Uint64 m_tickCount{};
  bool m_isRunning{false};
  bool m_isVSYNC{false};

public:
  FrameTimer() = default;

  auto updateStatsTexture(SDL_Renderer *renderer, TTF_Font *font) -> void;
  auto renderStatsTexture(SDL_Renderer *renderer, SDL_FPoint position) -> void;
  auto toggleOnOff() -> void;
  auto reset() -> void;
  auto tick(SDL_Renderer *renderer, TTF_Font *font) -> void;

  auto isRunning() const -> bool { return m_isRunning; }
};

#endif // FRAME_TIMER_HPP