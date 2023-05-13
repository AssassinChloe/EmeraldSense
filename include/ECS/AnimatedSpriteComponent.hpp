#pragma once
#include "Components.hpp"

class AnimatedSpriteComponent : public Component
{
private:
    int spriteNbW;
    int spriteNbH;

public :
    AnimatedSpriteComponent() : spriteNbW(1), spriteNbH(1){}
    AnimatedSpriteComponent(int spritesW, int spritesH) : spriteNbW(spritesW), spriteNbH(spritesH) {}

    int getFrame()
    {
        Uint32 ticks = SDL_GetTicks();
        Uint32 seconds = ticks / 1000;
        Uint32 xpos = seconds % (this->spriteNbW * this->spriteNbH);
        return (xpos);
    }

    int getSpriteNbW()
    {
        return (this->spriteNbW);
    }

    int getSpriteNbH()
    {
        return (this->spriteNbH);
    }

};


