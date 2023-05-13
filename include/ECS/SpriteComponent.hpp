
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
		if (!this->entity->hasComponent<TransformComponent>())
		{
			this->entity->addComponent<TransformComponent>();
		}
		this->transform = &this->entity->getComponent<TransformComponent>();
		this->src.x = this->src.y = 0;
		int w, h;
		SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
		if (entity->hasComponent<AnimatedSpriteComponent>() == true)
		{
			this->src.w = w / this->entity->getComponent<AnimatedSpriteComponent>().getSpriteNbW();
			this->src.h = h / this->entity->getComponent<AnimatedSpriteComponent>().getSpriteNbH();
		}
		else
		{
			this->src.w = w;
			this->src.h = h;
		}
		this->dst = this->src;
	}

	void setTexture(const char* path)
	{
		this->texture = this->texMan.loadTexture(path);
	}

	void update() override
	{
		this->dst.x = static_cast<int>(this->transform->getPosX());
		this->dst.y = static_cast<int>(this->transform->getPosY());
		this->dst.w = this->transform->getWidth() * this->transform->getScale();
		this->dst.h = this->transform->getHeight() * this->transform->getScale();
		if (this->entity->hasComponent<AnimatedSpriteComponent>() == true)
		{
			this->src.x = this->src.w * this->entity->getComponent<AnimatedSpriteComponent>().getFrame();
		}

	}
	void draw() override
	{
		/*std::cout << "src :" << src.x << "," << src.y << "," << src.w << "," << src.h << std::endl;
		std::cout << "dst :" << dst.x << "," << dst.y << "," << dst.w << "," << dst.h << std::endl;*/
		this->texMan.Draw(this->texture, this->src, this->dst);
	}

	~SpriteComponent()
	{
		if (this->texture)
			SDL_DestroyTexture(this->texture);
	}
};