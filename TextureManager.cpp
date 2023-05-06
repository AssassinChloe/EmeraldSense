#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	SDL_Texture *tex = IMG_LoadTexture(Game::renderer, fileName);
	return (tex);
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}