#include "TextureManager.hpp"

TextureManager::TextureManager()
{}

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	SDL_Texture* tex = IMG_LoadTexture(Game::renderer, fileName);
	return (tex);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip)
{
	if (tex)
		SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, NULL, flip);
	else
		std::cout << "your tex is null" << std::endl;
}