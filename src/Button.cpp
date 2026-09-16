#include "Button.h"

// LButton Implementation
Button::Button(Texture &spriteTexture) : mPosition{0.f, 0.f},
                                         mCurrentSprite{eButtonSprite::MouseOut},
                                         mSpriteTexture{spriteTexture}
{
}

void Button::setPosition(float x, float y)
{
    mPosition.x = x;
    mPosition.y = y;
}
void Button::handleEvent(SDL_Event *e)
{
    // If mouse event happened
    if (e->type == SDL_EVENT_MOUSE_MOTION || e->type == SDL_EVENT_MOUSE_BUTTON_DOWN || e->type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        // Get mouse position
        float x = -1.f, y = -1.f;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > mPosition.x + kButtonWidth)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > mPosition.y + kButtonHeight)
        {
            inside = false;
        }

        if (!inside)
        {
            mCurrentSprite = eButtonSprite::MouseOut;
        }
        // Mouse is inside button
        else
        {
            // Set mouse over sprite
            switch (e->type)
            {
            case SDL_EVENT_MOUSE_MOTION:
                mCurrentSprite = eButtonSprite::MouseOverMotion;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                mCurrentSprite = eButtonSprite::MouseDown;
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                mCurrentSprite = eButtonSprite::MouseUp;
                break;
            }
        }
    }
}
void Button::render()
{
    // Define sprites
    SDL_FRect spriteClips[] = {
        {0.f, 0 * kButtonHeight, kButtonWidth, kButtonHeight},
        {0.f, 1 * kButtonHeight, kButtonWidth, kButtonHeight},
        {0.f, 2 * kButtonHeight, kButtonWidth, kButtonHeight},
        {0.f, 3 * kButtonHeight, kButtonWidth, kButtonHeight},
    };

    // Show current button sprite
    mSpriteTexture.render(mPosition.x, mPosition.y, &spriteClips[static_cast<int>(mCurrentSprite)], kButtonWidth, kButtonHeight);
}