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
		this->tag = "notag";
	}

	ColliderComponent(std::string t)
	{
		this->tag = t;
	}
	void init() override
	{
		if (!this->entity->hasComponent<TransformComponent>())
		{
			this->entity->addComponent<TransformComponent>();
		}
		this->transform = &entity->getComponent<TransformComponent>();
		Game::colliders.push_back(this);
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

	std::string getTag() const
	{
		return this->tag;
	}
};