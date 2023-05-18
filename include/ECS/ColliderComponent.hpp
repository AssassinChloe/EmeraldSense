#pragma once

#include <string>
#include "Components.hpp"

class TransformComponent;

class ColliderComponent : public Component
{
private:
	SDL_Rect collider;
	int tag;
	TransformComponent* transform;

public:
	ColliderComponent() : collider({0,0,0,0}), tag(-1), transform(NULL){}

	ColliderComponent(int t) : collider({0,0,0,0}), tag(t), transform(NULL){}

	void init() override
	{
		if (!this->entity->hasComponent<TransformComponent>())
		{
			this->entity->addComponent<TransformComponent>();
		}
		this->transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		this->collider.x = static_cast<int>(this->transform->getPosX());
		this->collider.y = static_cast<int>(this->transform->getPosY());
		this->collider.w = this->transform->getWidth() * this->transform->getScale();
		this->collider.h = this->transform->getHeight() * this->transform->getScale();
	}

	SDL_Rect getCollider() const
	{
		return this->collider;
	}

	int getTag() const
	{
		return this->tag;
	}
};