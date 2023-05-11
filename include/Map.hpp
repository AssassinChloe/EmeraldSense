#pragma once

#include "Game.hpp"

class Map
{
public:
	Map();
	~Map();

	void loadMap(int arr[20][25]);
	void drawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture *dirt, *grass, *water, *wall;

	int map[20][25];
};

