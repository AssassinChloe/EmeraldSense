#pragma once
#include "Game.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"

class KeyboardController : public Component
{

private:
	TransformComponent* transform;
	int up, left, right, down;

	public:
	KeyboardController()
	{
		this->transform = NULL;
		this->up = this->down = this->left = this->right = 0;
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
				this->up = 1;
				break;
			case SDLK_s:
				this->down = 1;
				break;
			case SDLK_q:
				this->left = 1;
				break;
			case SDLK_d:
				this->right = 1;
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
				this->up = 0;
				break;
			case SDLK_s:
				this->down = 0;
				break;
			case SDLK_q:
				this->left = 0;
				break;
			case SDLK_d:
				this->right = 0;
				break;
			default:
				break;
			}
		}
		Vector2D dir(static_cast<float>(this->right - this->left), static_cast<float>(this->down - this->up));
		this->transform->setVelocity(dir);
	}
			
};

