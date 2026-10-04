#include "FrameTimer.hpp"

#include <string>

void FrameTimer::toggleOnOff() { m_isRunning = !m_isRunning; }

void FrameTimer::reset() {
  m_startTick = 0;
  m_tickCount = 0;
  m_isRunning = false;
}

void FrameTimer::tick(SDL_Renderer *renderer, TTF_Font *font) {
  if (m_isRunning) {
    m_startTick = SDL_GetTicks();
    ++m_tickCount;
    updateStatsTexture(renderer, font);
  }
}

void FrameTimer::updateStatsTexture(SDL_Renderer *renderer, TTF_Font *font) {
  static constexpr SDL_Color kStatsColor{0xFF, 0x00, 0x00, 0xFF};

  const std::string stats{
      "VSync: " + std::string(m_isVSYNC ? "ON" : "OFF") +
      "\nTimer: " + std::string(m_isRunning ? "Running" : "Stopped") +
      "\nTicks: " + std::to_string(m_tickCount)};

  m_statsTexture.loadFromRenderedText(stats, kStatsColor, font, renderer);
}

void FrameTimer::renderStatsTexture(SDL_Renderer *renderer,
                                    SDL_FPoint position) {
  const SDL_FRect destination{position.x, position.y,
                              static_cast<float>(m_statsTexture.getWidth()),
                              static_cast<float>(m_statsTexture.getHeight())};
  m_statsTexture.render(renderer, destination);
}