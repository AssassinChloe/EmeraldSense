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
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position += velocity * speed;
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

	//SIZE HANDLING
	int getScale()
	{
		return scale;
	}

	void setScale(int newScale)
	{
		scale = newScale;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	void setWidth(int w)
	{
		width = w;
	}

	void setHeight(int h)
	{
		height = h;
	}
};