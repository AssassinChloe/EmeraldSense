#ifndef MAP_HPP
#define MAP_HPP
#include <string>
#include "Game.hpp"
#include <fstream>
#include "Const.hpp"
#include "TextureManager.hpp"
#include <vector>

class Map
{
public:
	Map();
	~Map();

	void loadMap(std::string path, int sizeX);
	SDL_Texture* getTex() const;
	std::vector<int>& getMap();

private:
	SDL_Texture* tiles_sheet;
	std::vector<int> map;
};
#endif

