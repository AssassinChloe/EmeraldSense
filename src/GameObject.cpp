#include "GameObject.hpp"

GameObject::GameObject() : _tex(NULL), _currentFrame({0, 0, 0, 0}), _dst({0,0,0,0}), _spritesNb(1) {}

GameObject::GameObject(int posx, int posy, const char *fileName)
{
    _currentFrame.x = 0;
    _currentFrame.y = 0;
    _currentFrame.w = 102;
    _currentFrame.h = 85;
    _dst = _currentFrame;
    _dst.x = posx;
    _dst.y = posy;
    _spritesNb = 8;
    this->_tex = IMG_LoadTexture(Game::renderer, fileName);
    if (!this->_tex)
    {
        std::cout << "Failed texture load" << std::endl;
    }
}

SDL_Texture* GameObject::getTex() const
{
    return _tex;
}

int GameObject::getSpritesNb() const
{
    return _spritesNb;
}
void GameObject::updatePos(int dirx, int diry, int speed)
{
   _dst.x = _dst.x + (speed * dirx);
   _dst.y = _dst.y + (speed * diry);
}

int GameObject::animateSprite()
{
    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / 100;
    Uint32 sprite = seconds % _spritesNb;
    return (sprite);
}

void GameObject::render()
{
    SDL_Rect src;
    src = this->_currentFrame;
    src.x += (this->_currentFrame.w * this->animateSprite());
    SDL_RenderCopy(Game::renderer, this->_tex, &src, &this->_dst);

}

GameObject::~GameObject()
{
    if (_tex)
        SDL_DestroyTexture(_tex);
}
