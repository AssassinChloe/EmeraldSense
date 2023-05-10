#include "TextureManager.hpp"

TextureManager::TextureManager()
{}

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	SDL_Texture* tex = IMG_LoadTexture(Game::renderer, fileName);
	return (tex);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	if (tex)
		SDL_RenderCopy(Game::renderer, tex, &src, &dest);
	else
		std::cout << "your tex is null" << std::endl;
}