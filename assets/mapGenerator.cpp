#include <fstream>
#include <iostream>
#include <vector>
#define DEAD 0
#define ALIVE 1
#define FOOD 2
#define MAP_W 100
#define MAP_H 100
#define APROB 60
#define FPROB 3
#define GENERATION 6
#define PLAYER_X 10
#define PLAYER_Y 10
#define DIGGED 3
#define ROCK 4

void displayCave(std::vector<int> map)
{
	for (int h = 0; h < MAP_H; h++)
	{
		for (int w = 0; w < MAP_W; w++)
		{
			std::cout << map[h * MAP_W + w];
		}
		std::cout << std::endl;
	}
}

void saveCave(std::vector<int> map, int seed)
{
    std::ofstream file;

    file.open("map.txt", std::ios::trunc);
    for (int h = 0; h < MAP_H; h++)
	{
		for (int w = 0; w < MAP_W; w++)
		{
            file << map[h * MAP_W + w];
		}
		file << std::endl;
	}
    file.close();
}

int near(int x, int y, std::vector<int>map)
{
	int count = 0;
	for (int h =  y - 1; h < y + 2; h++)
	{
		for (int w = x - 1; w < x + 2; w++)
		{
			if (!(w == x && h == y))
				count += map[h * MAP_W + w];
		}
	}
	return count;
}


void genCave(int seed)
{
	srand(seed);
	std::vector<int> map;
	for (int h = 0; h < MAP_H; h++)
	{
		for (int w = 0; w < MAP_W; w++)
		{
			if (rand() % 100 > APROB)
				map.push_back(DEAD);
			else
				map.push_back(ALIVE);
		}
	}
	for (int gen = 0; gen < GENERATION; gen++)
	{
		for (int h = 1; h < MAP_H - 1; h++)
		{
			for (int w = 1; w < MAP_W - 1; w++)
			{
				int count = near(w, h, map);
				if (map[h * MAP_W + w] == DEAD && count >= 6)
				{
					map[h * MAP_W + w] = ALIVE;	
				}
				if (map[h * MAP_W + w] == ALIVE && count <= 3)
					map[h * MAP_W + w] = DEAD;
				if (gen == GENERATION - 1 && map[h * MAP_W + w] == ALIVE && rand() % 100 < FPROB)
					map[h * MAP_W + w] = FOOD;
			}
		}
	}
	for (int h = 0; h < MAP_H; h++)
	{
		for (int w = 0; w < MAP_W; w++)
		{
			if (h == 0 || h == MAP_H - 1|| w == 0 || w == MAP_W - 1)
				map[h * MAP_W + w] = ROCK;
			if (h <= PLAYER_Y + 1 && h > PLAYER_Y - 2 && w >= PLAYER_X - 2 && w <= PLAYER_X + 2)
				map[h * MAP_W + w] = ALIVE;
			if (h <= PLAYER_Y && h > PLAYER_Y - 1 && w >= PLAYER_X - 1 && w <= PLAYER_X + 1)
				map[h * MAP_W + w] = DIGGED;
		}
	}

	displayCave(map);
    saveCave(map, seed);
}

int main(int argc, char* argv[])
{
	int seed = time(NULL);
	genCave(seed);
}