#include "App.hpp"

App::~App()
{
  MIX_DestroyTrack(m_track);
  MIX_DestroyAudio(m_audio);
  MIX_DestroyMixer(m_mixer);
  if (m_mixerInitialized)
  {
    MIX_Quit();
  }
  if (m_font)
  {
    TTF_CloseFont(m_font);
  }
  TTF_Quit();
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

bool App::init()
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
  {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return false;
  }
  if (!TTF_Init())
  {
    SDL_Log("TTF_Init failed: %s", SDL_GetError());
    return false;
  }
  if (!MIX_Init())
  {
    SDL_Log("MIX_Init failed: %s", SDL_GetError());
    return false;
  }
  m_mixerInitialized = true;
  if (!initializeMixer())
  {
    return false;
  }
  if (!initializeWindow("Tetris"))
  {
    SDL_Log("Window initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeRenderer())
  {
    SDL_Log("Renderer initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!initializeFont())
  {
    SDL_Log("Font initialization failed: %s", SDL_GetError());
    return false;
  }
  if (!SDL_SetRenderVSync(m_renderer, 1))
  {
    SDL_Log("Failed to set VSync: %s", SDL_GetError());
    return false;
  }

  return true;
}

int App::run()
{
  int exitCode{};

  SDL_Event event;
  SDL_zero(event);

  if (!m_scene.loadAssets(m_renderer, m_font, k_defaultWidth,
                          k_defaultHeight))
  {
    SDL_Log("Failed to load scene assets: %s", SDL_GetError());
    return 2;
  }

  if (m_audio = MIX_LoadAudio(m_mixer, "assets/low.wav", true); !m_audio)
  {
    SDL_Log("Failed to load audio: %s", SDL_GetError());
    return 3;
  }
  if (m_track = MIX_CreateTrack(m_mixer); !m_track)
  {
    SDL_Log("Failed to create track: %s", SDL_GetError());
    return 4;
  }
  SDL_PropertiesID propID = SDL_CreateProperties();
  SDL_SetNumberProperty(propID, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
  MIX_SetTrackAudio(m_track, m_audio);
  MIX_PlayTrack(m_track, propID);
  SDL_DestroyProperties(propID);

  while (exitCode == 0)
  {
    handleEvents(&event, exitCode);
    render();
  }

  return exitCode;
}

void App::render()
{
  // updating settings
  tick();

  // rendering
  SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(m_renderer);
  m_scene.render(m_renderer);
  SDL_RenderPresent(m_renderer);
}

void App::handleEvents(SDL_Event *event, int &exitCode)
{
  while (SDL_PollEvent(event) == true && exitCode == 0)
  {
    if (event->type == SDL_EVENT_QUIT)
    {
      exitCode = -1;
    }
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
      switch (event->key.key)
      {
      case SDLK_ESCAPE:
        exitCode = -1;
        break;
      }
    }

    m_scene.handleEvent(*event, exitCode);
  }
}

void App::tick()
{
  if (!m_capFramerate)
  {
    return;
  }

  const Uint64 targetFrameNs{1'000'000'000ull / static_cast<Uint64>(m_maxFPS)};
  const Uint64 currentTicks{SDL_GetTicksNS()};
  const Uint64 elapsedTicks{currentTicks - m_lastTickCount};

  if (elapsedTicks < targetFrameNs) // if time since last tick is less than target frame time
  {
    SDL_DelayNS(targetFrameNs - elapsedTicks); // delay to maintain target frame rate
  }

  m_lastTickCount = currentTicks;
}