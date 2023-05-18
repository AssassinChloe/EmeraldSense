#include "Map.hpp"

Map::Map() {
	this->tiles_sheet = TextureManager::loadTexture(TILES_PATH);
}

Map::~Map() {
	if (this->tiles_sheet)
		SDL_DestroyTexture(this->tiles_sheet);
}

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
			Game::addTile(tile_int,  x * TILES_W, y * TILES_H, this->tiles_sheet);
			this->map.push_back(tile_int);
			//mapFile.ignore();
		}
		mapFile.ignore();
	}
	mapFile.close();
	std::cout << "Map Loaded" << std::endl;
}

SDL_Texture* Map::getTex() const
{
	return (this->tiles_sheet);
}

std::vector<int>& Map::getMap()
{
	return (this->map);
}
