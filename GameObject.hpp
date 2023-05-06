#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "SDL_image.h"
#include "Game.hpp"
#include<iostream>


class GameObject
{
public:
    GameObject();
    GameObject(int posx, int posy, const char *fileName);

    SDL_Texture* getTex() const ;
    int getSpritesNb() const;

    void updatePos(int dirx, int diry, int speed);
    void render();
    int animateSprite();
    ~GameObject();

private:
    SDL_Rect _currentFrame, _dst;
    SDL_Texture* _tex;
    int _spritesNb;
};
#endif