#pragma once

#include "Components.hpp"

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
		case 0:
			this->path = "assets/water.png";
			break;
		case 1:
			this->path = "assets/grass.png";
			break;
		case 2:
			this->path = "assets/dirt.png";
			break;
		case 3:
			this->path = "assets/wall.png";
			break;
		default:
			this->path = "asset/nean.png";
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
};