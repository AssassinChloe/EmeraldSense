#include "Map.hpp"

Map::Map() {
	this->tiles_sheet = TextureManager::loadTexture(TILES_PATH);
}

Map::~Map() {
	if (this->tiles_sheet)
		SDL_DestroyTexture(this->tiles_sheet);
}

void Map::loadMap(std::string path, int sizeX)
{
	std::string tiles_str = "";
	std::string tmp = "";
	std::ifstream mapFile;
	mapFile.open(path);
	if (!mapFile.is_open())
	{
		std::cout << "Error opening Map" << std::endl;
	}
	while (getline(mapFile, tmp))
	{
		if (!tmp.empty() && static_cast<int>(tmp.size()) > sizeX)
			tmp.resize(sizeX);
		tiles_str += tmp;

	}
	mapFile.close();
	int i = 0;

	for (char c : tiles_str)
	{
			Game::addTile((c - '0'),  i % sizeX * TILES_W, i / sizeX * TILES_H, this->tiles_sheet);		
			i++;
	}
	std::cout << std::endl;
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
