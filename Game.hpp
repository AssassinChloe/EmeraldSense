#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Entity.hpp"
#include <iostream>

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

private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Entity player;
	int _up, _down, _left, _right;
};