#ifndef GAME_HPP
#define GAME_HPP

#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.hpp"
#include <iostream>
#include "Map.hpp"
#include "ECS.hpp"
#include "PositionComponent.hpp"

class GameObject;
class Map;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void doKeyDown(SDL_KeyboardEvent* event);
	void doKeyUp(SDL_KeyboardEvent* event);

	void update();
	void render();
	void clean();

	bool running();
	static SDL_Renderer *renderer;

private:
	bool isRunning;
	SDL_Window* window;
	GameObject *player;
	int _up, _down, _left, _right;
	Map *map;
};
#endif