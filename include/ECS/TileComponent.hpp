#ifndef TILECOMPONENT_HPP
#define TILECOMPONENT_HPP

#include "Components.hpp"
#include "Const.hpp"

class TileComponent : public Component
{
private:
	TransformComponent *transform = NULL;
	SDL_Rect tile;
	Vector2D initial_position;
	int id;
	bool rigid = false;
	SDL_Texture* tilesSheet = NULL;

public:
	TileComponent() : tile({ 0,0,0,0 }), id(7), tilesSheet(NULL) 
	{}

	TileComponent(int x, int y, int w, int h, int id, SDL_Texture *tex, bool rigidity) : tile({x,y,w,h}), id(id), tilesSheet(tex), rigid(rigidity) {}

	void init() override
	{
		initial_position.x = tile.x;
		initial_position.y = tile.y;
		entity->addComponent<TransformComponent>((float)tile.x, (float)tile.y, tile.w, tile.h, 1);
		transform = &entity->getComponent<TransformComponent>();
	}

	void draw() override
	{
		SDL_Rect src = {id * TILES_W, (id / TEX_BY_ROW) * TILES_H, TILES_W, TILES_H};
		TextureManager::Draw(this->tilesSheet, src, this->tile, 0, SDL_FLIP_NONE);
	}

	void update() override
	{
		tile.x = initial_position.x - Game::camera.x;
		tile.y = initial_position.y - Game::camera.y;
	}
	SDL_Rect getTile()
	{
		return this->tile;
	}

	SDL_Texture* getTex() const
	{
		return (this->tilesSheet);
	}

	bool isRigid()
	{
		return rigid;
	}

	int getId() const
	{
		return this->id;
	}
};
#endif