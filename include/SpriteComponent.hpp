
#pragma once

#include "Components.hpp"

class PositionComponent;
class DirectionComponent;

class SpriteComponent : public Component
{
private:
	PositionComponent *position;
	DirectionComponent *direction;
	SDL_Texture* texture;
	SDL_Rect src, dst;
	TextureManager texMan;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	void init()
	{
		position = &entity->getComponent<PositionComponent>();
		direction = &entity->getComponent<DirectionComponent>();
		src.x = src.y = 0;
		src.w = 102;
		src.h = 85;
		dst = src;
	}

	void setTexture(const char* path)
	{
		texture = texMan.loadTexture(path);
	}

	void update() override
	{
		position->setPos(position->x() + direction->x(), position->y() + direction->y());
		dst.x = position->x();
		dst.y = position->y();

	}
	void draw() override
	{
		//std::cout << "src :" << src.x << "," << src.y << "," << src.w << "," << src.h << std::endl;
		//std::cout << "dst :" << dst.x << "," << dst.y << "," << dst.w << "," << dst.h << std::endl;
		texMan.Draw(texture, src, dst);
	}

	~SpriteComponent()
	{
		if (texture)
			SDL_DestroyTexture(texture);
	}
};