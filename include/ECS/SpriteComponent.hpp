
#pragma once

#include "Components.hpp"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <map>


class TransformComponent;
class Vector2D;

class SpriteComponent : public Component
{
private:
	TransformComponent *transform = NULL;
	SDL_Texture* texture = NULL;
	int textureSize = 32;
	SDL_Rect src, dst;

	bool animated = false;
	Animation animation = {0, 1, 100};
	std::map<int, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	double angle = 0;

public:

	SpriteComponent(): src({0,0,0,0}), dst({0,0,0,0}) {}

	SpriteComponent(const char* path) : src({ 0,0,0,0 }), dst({ 0,0,0,0 })
	{
		setTexture(path);
	}
	SpriteComponent(SDL_Texture * tex) : src({ 0,0,0,0 }), dst({ 0,0,0,0 }), texture(tex)
	{}
	SpriteComponent(const char* path, int size, bool animation)
	: transform(NULL), texture(NULL), src({ 0,0,0,0 }), dst({ 0,0,0,0 }), animated(animation), textureSize(size)
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
		this->src.w = this->textureSize;
		this->src.h = this->textureSize;
		this->dst = this->src;
	}

	void setTexture(const char* path)
	{
		this->texture = TextureManager::loadTexture(path);
	}



	void angleCalc()
	{
		//taupe
		if (transform->getDirX() == 1)
			this->spriteFlip = SDL_FLIP_VERTICAL;
		else if (transform->getDirX() == -1)
			this->spriteFlip = SDL_FLIP_NONE;
		//else if (transform->getDirY() == 1)
		//	this->angle = 0;
		
		//lutin
		//if (transform->getDirX() == 1)
		//	play(WALK_R);
		//else if (transform->getDirY() == -1)
		//	play(WALK_B);
		//else if (transform->getDirX() == -1)
		//	play(WALK_L);
		//else
		//	play(WALK);
	}

	void update() override
	{
		if (animated == true && animations.size() > IDLE && transform->getVelocity() == Vector2D(0.0f, 0.0f))
		{
			play(IDLE);
			
			//taupe
			this->angle = 90;
			//lutin
			//this->angle = 0;

		}
		else if (animated == true && animations.size() > WALK && transform->getVelocity() != Vector2D(0.0f, 0.0f))
		{
			//taupe
			play(WALK);
			this->angle = 90;

			angleCalc();
		}
		this->dst.x = static_cast<int>(this->transform->getPosX()) - Game::camera.x;
		this->dst.y = static_cast<int>(this->transform->getPosY()) - Game::camera.y;
		this->dst.w = this->transform->getWidth() * this->transform->getScale();
		this->dst.h = this->transform->getHeight() * this->transform->getScale();
		if (this->animated == true)
		{
			this->src.x = this->src.w * static_cast<int>((SDL_GetTicks() / this->animation.speed) % this->animation.frames);
		}
		this->src.y = this->animation.index * this->src.h;
	}

	void draw() override
	{
		TextureManager::Draw(this->texture, this->src, this->dst, this->angle, this->spriteFlip);
	}

	void play(int animName)
	{
		this->animation = animations[animName];
	}

	void addAnimation(int index, int f, int s)
	{
		animations.emplace(index, Animation(index, f, s));
	}

	~SpriteComponent()
	{
		if (this->texture != NULL) 
		{
			SDL_DestroyTexture(this->texture);
			this->texture = NULL;
		}
	}
};