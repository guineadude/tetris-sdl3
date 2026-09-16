#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>

#include "Texture.h"

class Button
{
public:
    // Button dimensions
    static constexpr int kButtonWidth = 300;
    static constexpr int kButtonHeight = 200;

    // Initializes internal variables
    Button(Texture &spriteTexture);

    // Sets top left position
    void setPosition(float x, float y);

    // Handles mouse event
    void handleEvent(SDL_Event *e);

    // Shows button sprite
    void render();

private:
    enum class eButtonSprite
    {
        MouseOut = 0,
        MouseOverMotion = 1,
        MouseDown = 2,
        MouseUp = 3
    };

    // Top left position
    SDL_FPoint mPosition;

    // Currently used global sprite
    eButtonSprite mCurrentSprite;

    Texture &mSpriteTexture;
};

#endif // BUTTON_H