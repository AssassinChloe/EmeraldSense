#pragma once
#include "Components.hpp"

class DirectionComponent : public Component
{
private:
	int xdir, ydir;

public:
	DirectionComponent()
	{
		xdir = 0;
		ydir = 0;
	}
	DirectionComponent(int x, int y)
	{
		xdir = x;
		ydir = y;
	}

	int x() { return xdir; }
	int y() { return ydir; }


	void setDir(int x, int y)
	{
		xdir = x;
		ydir = y;
	}

};