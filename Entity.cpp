#include "Entity.hpp"

Entity::Entity() : _tex(NULL), _currentFrame({0, 0, 0, 0}), _dst({0,0,0,0}), _spritesNb(1), _renderer(NULL) {}

Entity::Entity(int posx, int posy, const char *fileName, SDL_Renderer *ren) :
 _renderer(ren)
{
    _currentFrame.x = 0;
    _currentFrame.y = 0;
    _currentFrame.w = 102;
    _currentFrame.h = 85;
    _dst = _currentFrame;
    _dst.x = posx;
    _dst.y = posy;
    _spritesNb = 8;
    this->_tex = IMG_LoadTexture(ren, fileName);
    if (!this->_tex)
    {
        std::cout << "Failed texture load" << std::endl;
    }
}

Entity& Entity::operator()(int posx, int posy, const char* fileName, SDL_Renderer* ren)
{
    this->_renderer = ren;
    this->_tex = IMG_LoadTexture(ren, fileName);
    if (!this->_tex)
    {
        std::cout << "Failed texture load" << std::endl;
    }
    this->_currentFrame.x = 0;
    this->_currentFrame.y = 0;
    this->_currentFrame.w = 102;
    this->_currentFrame.h = 85;
    this->_dst = this->_currentFrame;
    _dst.x = posx;
    _dst.y = posy;
    this->_spritesNb = 8;
    return (*this);
}

SDL_Texture* Entity::getTex() const
{
    return _tex;
}

int Entity::getSpritesNb() const
{
    return _spritesNb;
}
void Entity::updatePos(int dirx, int diry, int speed)
{
   _dst.x = _dst.x + (speed * dirx);
   _dst.y = _dst.y + (speed * diry);
}

int Entity::animateSprite()
{
    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / 1000;
    Uint32 sprite = seconds % _spritesNb;
    return (sprite);
}

void Entity::render()
{
    SDL_Rect src;
    src = this->_currentFrame;
    src.x += (this->_currentFrame.w * this->animateSprite());
    SDL_RenderCopy(this->_renderer, this->_tex, &src, &this->_dst);
}

Entity::~Entity()
{
    if (_tex)
        SDL_DestroyTexture(_tex);
}
