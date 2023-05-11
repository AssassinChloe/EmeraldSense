
#pragma once

#include "Components.hpp"
#include "AnimatedSpriteComponent.hpp"


class TransformComponent;
class AnimatedSpriteComponent;

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
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
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		src.x = src.y = 0;
		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		if (entity->hasComponent<AnimatedSpriteComponent>() == true)
		{
			src.w = w / entity->getComponent<AnimatedSpriteComponent>().getSpriteNbW();
			src.h = h / entity->getComponent<AnimatedSpriteComponent>().getSpriteNbH();
		}
		else
		{
			src.w = w;
			src.h = h;
		}
		dst = src;
	}

	void setTexture(const char* path)
	{
		texture = texMan.loadTexture(path);
	}

	void update() override
	{
		dst.x = static_cast<int>(transform->getPosX());
		dst.y = static_cast<int>(transform->getPosY());
		dst.w = transform->getWidth() * transform->getScale();
		dst.h = transform->getHeight() * transform->getScale();
		if (entity->hasComponent<AnimatedSpriteComponent>() == true)
		{
			src.x = src.w * entity->getComponent<AnimatedSpriteComponent>().getFrame();
		}

	}
	void draw() override
	{
		/*std::cout << "src :" << src.x << "," << src.y << "," << src.w << "," << src.h << std::endl;
		std::cout << "dst :" << dst.x << "," << dst.y << "," << dst.w << "," << dst.h << std::endl;*/
		texMan.Draw(texture, src, dst);
	}

	~SpriteComponent()
	{
		if (texture)
			SDL_DestroyTexture(texture);
	}
};