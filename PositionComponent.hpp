#pragma once
#include "ECS.hpp"
class PositionComponent : public Component
{
private:
	int xpos, ypos;

public:
	void init() override
	{
		xpos = 0;
		ypos = 0;
	}

	int x() { return xpos; }
	int y() { return ypos; }

	
	void setPos(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

};