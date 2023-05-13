#pragma once
#include <string>
#include "Game.hpp"
#include <fstream>
class Map
{
public:
	Map();
	~Map();

	static void loadMap(std::string path, int sizeX, int sizeY);

private:

};

