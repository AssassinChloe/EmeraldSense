#pragma once
#include "SDL_image.h"
#include<iostream>

class Entity
{
public:
    Entity();
    Entity(int posx, int posy, const char *fileName, SDL_Renderer *ren);

    Entity& operator()(int posx, int posy, const char* fileName, SDL_Renderer* ren);
    SDL_Texture* getTex() const ;
    int getSpritesNb() const;

    void updatePos(int dirx, int diry, int speed);
    void render();
    int animateSprite();
    ~Entity();

private:
    SDL_Rect _currentFrame, _dst;
    SDL_Texture* _tex;
    SDL_Renderer *_renderer;
    int _spritesNb;
};