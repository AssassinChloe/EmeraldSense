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
		transform = NULL;
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_z:
				transform->setVelY(-1);
				break;
			case SDLK_s:
				transform->setVelY(1);
				break;
			case SDLK_q:
				transform->setVelX(-1);
				break;
			case SDLK_d:
				transform->setVelX(1);
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
				transform->setVelY(0);
				break;
			case SDLK_s:
				transform->setVelY(0);
				break;
			case SDLK_q:
				transform->setVelX(0);
				break;
			case SDLK_d:
				transform->setVelX(0);
				break;
			default:
				break;
			}
		}

	}
			
};

