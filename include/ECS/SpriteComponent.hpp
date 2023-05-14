
#pragma once

#include "Components.hpp"
#include "AnimatedSpriteComponent.hpp"
#include "TextureManager.hpp"


class TransformComponent;
class AnimatedSpriteComponent;

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect src, dst;
	bool animated = false;

public:
	SpriteComponent(): transform(NULL), texture(NULL), src({0,0,0,0}), dst({0,0,0,0}) {}

	SpriteComponent(const char* path, bool animation) : transform(NULL), texture(NULL), src({ 0,0,0,0 }), dst({ 0,0,0,0 }), animated(animation)
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
		this->texture = TextureManager::loadTexture(path);
	}

	void update() override
	{
		this->dst.x = static_cast<int>(this->transform->getPosX());
		this->dst.y = static_cast<int>(this->transform->getPosY());
		this->dst.w = this->transform->getWidth() * this->transform->getScale();
		this->dst.h = this->transform->getHeight() * this->transform->getScale();
		if (entity->hasComponent<AnimatedSpriteComponent>() == true && this->animated == true)
		{
			this->src.x = this->src.w * this->entity->getComponent<AnimatedSpriteComponent>().getFrame();
		}
		else if (entity->hasComponent<AnimatedSpriteComponent>() == true && this->animated == false)
		{
			if (transform->getDirX() < 0)
				this->src.x = this->src.w * 0;
			else if (transform->getDirX() > 0)
				this->src.x = this->src.w * 1;
			else if (transform->getDirY() > 0)
				this->src.x = this->src.w * 2;
			else if (transform->getDirY() < 0)
				this->src.x = this->src.w * 3;
		}

	}
	void draw() override
	{
		/*std::cout << "src :" << src.x << "," << src.y << "," << src.w << "," << src.h << std::endl;
		std::cout << "dst :" << dst.x << "," << dst.y << "," << dst.w << "," << dst.h << std::endl;*/
		TextureManager::Draw(this->texture, this->src, this->dst);
	}

	~SpriteComponent()
	{
		//if (this->texture)
		//{
		//	SDL_DestroyTexture(this->texture);
		//}
	}
};