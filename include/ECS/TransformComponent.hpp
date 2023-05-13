#pragma once
#include "Components.hpp"
#include "Vector2D.hpp"

class TransformComponent : public Component
{
private:
	Vector2D position;
	Vector2D velocity;
	int height = 32;
	int width = 32;
	int scale = 1;
	int speed = 1;

public:

	TransformComponent()
	{
		this->position.Zero();
	}

	TransformComponent(int sc)
	{
		this->position.Zero();
		this->scale = sc;
	}
	TransformComponent(float x, float y)
	{
		this->position.x = x;
		this->position.y = y;
	}
	TransformComponent(float x, float y, int w, int h, int sc)
	{
		this->position.x = x;
		this->position.y = y;
		this->width = w;
		this->height = h;
		this->scale = sc;
	}

	void init() override
	{
		this->velocity.Zero();
	}

	void update() override
	{
		this->position += this->velocity * this->speed;
	}


	//POSITION HANDLING 

	float getPosX()
	{
		return this->position.x;
	}
	float getPosY()
	{
		return this->position.y;
	}

	Vector2D getPosition()
	{
		return(this->position);
	}

	void setPosition(Vector2D& vec)
	{
		this->position = vec;
	}

	// VELOCITY HANDLING

	float getDirX()
	{
		return this->position.x;
	}
	float getDirY()
	{
		return this->position.y;
	}

	Vector2D getVelocity()
	{
		return this->velocity;
	}

	void setVelocity(Vector2D& vec)
	{
		this->velocity = vec;
	}

	void setVelX(float newX)
	{
		this->velocity.x = newX;
	}

	void setVelY(float newY)
	{
		this->velocity.y = newY;
	}

	//SPEED HANDLING 
	void setSpeed(int newSpeed)
	{
		this->speed = newSpeed;
	}

	//SIZE HANDLING
	int getScale()
	{
		return this->scale;
	}

	void setScale(int newScale)
	{
		this->scale = newScale;
	}

	int getWidth()
	{
		return this->width;
	}

	int getHeight()
	{
		return this->height;
	}

	void setWidth(int w)
	{
		this->width = w;
	}

	void setHeight(int h)
	{
		this->height = h;
	}
};