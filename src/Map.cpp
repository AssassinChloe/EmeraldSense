#include "Map.hpp"

int lvl1[20][25] = {
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
	{3,1,1,2,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,3},
	{3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3},
	{3,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
	{3,2,2,0,2,0,2,2,0,2,0,0,2,2,2,2,2,2,0,0,0,0,0,0,3},
	{3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};

Map::Map()
{
	this->dirt = TextureManager::loadTexture("assets/dirt.png");
	this->water = TextureManager::loadTexture("assets/water.png");
	this->grass = TextureManager::loadTexture("assets/grass.png");
	this->wall = TextureManager::loadTexture("assets/wall.png");
	if (!dirt || !water || !grass || !wall)
		std::cout << "pb during loading map's tiles" << std::endl;

	loadMap(lvl1);
	src.x = src.y = dest.x = dest.y = 0;
	src.w = src.h = dest.w = dest.h = 32;

}
Map::~Map()
{
	if (dirt)
		SDL_DestroyTexture(dirt);
	if (water)
		SDL_DestroyTexture(water);
	if (grass)
		SDL_DestroyTexture(grass);
	if (wall)
		SDL_DestroyTexture(wall);

}

void Map::loadMap(int arr[20][25])
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}
void Map::drawMap()
{
	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column];
			dest.x = column * 32;
			dest.y = row * 32;

			switch (type)
			{
			case 0:
				TextureManager::Draw(water, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;
			case 3:
				TextureManager::Draw(wall, src, dest);
			}
		}
	}
}