#pragma once

#include "Components.hpp"
#include "Const.hpp"

class TileComponent : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Rect tile;
	int id;
	std::string path;

public:
	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id) : tile({x,y,w,h}), id(id) 
	{
		switch (this->id)
		{
		case WATER:
			this->path = WATER_PATH;
			break;
		case DIRT:
			this->path = DIRT_PATH;
			break;
		case DIG:
			this->path = DIG_PATH;
			break;
		case WORM:
			this->path = WORM_PATH;
			break;
		case ROCK:
			this->path = ROCK_PATH;
			break;
		default:
			this->path = DEFAULT_PATH;
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tile.x, (float)tile.y, tile.w, tile.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path.c_str());
		sprite = &entity->getComponent<SpriteComponent>();
	}

	SDL_Rect getTile()
	{
		return this->tile;
	}
};