#include "Game.hpp"
#include "Components.hpp"

SDL_Renderer* Game::renderer = NULL;

Manager manager;
auto& player(manager.addEntity());

Game::Game()
{
	this->isRunning = false;
	this->window = NULL; 
	this->map = NULL;
	_up = 0;
	_down = 0;
	_left = 0;
	_right = 0;
}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = SDL_WINDOW_ALLOW_HIGHDPI;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised!" << std::endl;
		this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (this->window)
		{
			std::cout << "Window Created!" << std::endl;
			this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (this->renderer)
			{
				std::cout << "Renderer Created!" << std::endl;
				SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
			}
		}
		this->isRunning = true;
		if (!IMG_Init(IMG_INIT_PNG))
		{
			std::cout << "IMG init failed: " << SDL_GetError() << std::endl;
		}
		else
		{
			this->map = new Map();
			player.addComponent<PositionComponent>();
			player.addComponent<DirectionComponent>();
			player.addComponent<SpriteComponent>("assets/renard.png");

		}
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			this->isRunning = false;
			break;
		case SDL_KEYDOWN:
			this->doKeyDown(&event.key);
			break;
		case SDL_KEYUP:
			this->doKeyUp(&event.key);
			break;
		default:
			break;
	}
}

void Game::doKeyDown(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP
			|| event->keysym.scancode == SDL_SCANCODE_Z
			|| event->keysym.scancode == SDL_SCANCODE_W)
		{
			_up = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN
			|| event->keysym.scancode == SDL_SCANCODE_S)
		{
			_down = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT
			|| event->keysym.scancode == SDL_SCANCODE_Q
			|| event->keysym.scancode == SDL_SCANCODE_A)
		{
			_left = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT
			|| event->keysym.scancode == SDL_SCANCODE_D)
		{
			_right = 1;
		}
	}
}

void Game::doKeyUp(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP
			|| event->keysym.scancode == SDL_SCANCODE_Z
			|| event->keysym.scancode == SDL_SCANCODE_W)
		{
			_up = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN
			|| event->keysym.scancode == SDL_SCANCODE_S)
		{
			_down = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT
			|| event->keysym.scancode == SDL_SCANCODE_Q
			|| event->keysym.scancode == SDL_SCANCODE_A)
		{
			_left = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT
			|| event->keysym.scancode == SDL_SCANCODE_D)
		{
			_right = 0;
		}
	}
}

void Game::update()
{
	manager.refresh();
	player.getComponent<DirectionComponent>().setDir(_right - _left, _down - _up);
	manager.update();
}
void Game::render()
{
	SDL_RenderClear(this->renderer);
	this->map->drawMap();
	manager.draw();
	SDL_RenderPresent(this->renderer);
}
void Game::clean()
{	
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	delete(this->map);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

bool Game::running()
{
	return (this->isRunning);
}