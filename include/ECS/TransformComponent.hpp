#pragma once
#include "Components.hpp"
#include "Vector2D.hpp"

class TransformComponent : public Component
{
private:
	Vector2D position;
	Vector2D velocity;
	int speed = 1;

public:

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}


	//POSITION HANDLING 

	float getPosX()
	{
		return position.x;
	}
	float getPosY()
	{
		return position.y;
	}

	Vector2D getPosition()
	{
		return(position);
	}

	void setPosition(Vector2D& vec)
	{
		position = vec;
	}

	// VELOCITY HANDLING

	float getDirX()
	{
		return position.x;
	}
	float getDirY()
	{
		return position.y;
	}

	Vector2D getVelocity()
	{
		return velocity;
	}

	void setVelocity(Vector2D& vec)
	{
		velocity = vec;
	}

	void setVelX(float newX)
	{
		velocity.x = newX;
	}

	void setVelY(float newY)
	{
		velocity.y = newY;
	}

	//SPEED HANDLING 
	void setSpeed(int newSpeed)
	{
		speed = newSpeed;
	}
};