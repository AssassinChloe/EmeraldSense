#pragma once

#include "Game.hpp"

class TextureManager
{
public:
	TextureManager();
	static SDL_Texture* loadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip);

};