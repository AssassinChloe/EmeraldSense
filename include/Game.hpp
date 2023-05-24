#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.hpp"
#include "TextureManager.hpp"
#include <vector>
#include "Const.hpp"
#include "Vector2D.hpp"

class ColliderComponent;
class Map;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();

	void update();
	void render();
	void clean();

	bool running();

	static void addTile(int id, int x, int y, SDL_Texture *tex);
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;

private:
	bool isRunning;
	SDL_Window* window;
	Map *map;
	int left, right, up, down, dig;
	int timer = 0;
	void buildPlayer();
	void checkNear(Vector2D playerPos);
};