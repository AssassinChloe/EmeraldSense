#pragma once

#include <string>
#include "Components.hpp"

class TransformComponent;

class ColliderComponent : public Component
{
private:
	SDL_Rect collider;
	std::string tag;
	TransformComponent* transform;

public:
	ColliderComponent()
	{
		tag = "notag";
	}

	ColliderComponent(std::string t)
	{
		tag = t;
	}
	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->getPosX());
		collider.y = static_cast<int>(transform->getPosY());
		collider.w = transform->getWidth() * transform->getScale();
		collider.h = transform->getHeight() * transform->getScale();
	}

	SDL_Rect& getCollider()
	{
		return collider;
	}
};