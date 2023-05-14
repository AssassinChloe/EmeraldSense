#include "Map.hpp"
#include "Const.hpp"

Map::Map() {}

Map::~Map() {}

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::ifstream mapFile;
	mapFile.open(path);
	
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			int tile_int = atoi(&tile);
			Game::addTile(tile_int,  x * TILES_W, y * TILES_H);
			mapFile.ignore();
		}
		//mapFile.ignore();
	}
	mapFile.close();
}