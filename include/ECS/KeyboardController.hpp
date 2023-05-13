#pragma once
#include "Game.hpp"
#include "Components.hpp"

class KeyboardController : public Component
{

private:
	TransformComponent* transform;

	public:
	KeyboardController()
	{
		this->transform = NULL;
	}
	void init() override
	{
		this->transform = &this->entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_z:
				this->transform->setVelY(-1);
				break;
			case SDLK_s:
				this->transform->setVelY(1);
				break;
			case SDLK_q:
				this->transform->setVelX(-1);
				break;
			case SDLK_d:
				this->transform->setVelX(1);
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_z:
				this->transform->setVelY(0);
				break;
			case SDLK_s:
				this->transform->setVelY(0);
				break;
			case SDLK_q:
				this->transform->setVelX(0);
				break;
			case SDLK_d:
				this->transform->setVelX(0);
				break;
			default:
				break;
			}
		}

	}
			
};

