#ifndef FRAME_TIMER_HPP
#define FRAME_TIMER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
class FrameTimer {
private:
  Uint64 m_startTick{};

public:
  auto toggleOnOff() -> void;
  auto reset() -> void;
  auto tick() -> void;
};

#endif // FRAME_TIMER_HPP