#include "Game.hpp"
#include "ECS/Components.hpp"
#include "Collision.hpp"

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;
Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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
			player.addComponent<TransformComponent>(2);
			player.addComponent<AnimatedSpriteComponent>(2, 1);
			player.addComponent<SpriteComponent>("assets/marchetest.png");
			player.addComponent<KeyboardController>();
			player.addComponent<ColliderComponent>("player");

			wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
			wall.addComponent<SpriteComponent>("assets/wall.png");
			wall.addComponent<ColliderComponent>("wall");

		}
	}
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			this->isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().getCollider(), wall.getComponent<ColliderComponent>().getCollider()))
	{
		player.getComponent<TransformComponent>().setVelocity(player.getComponent<TransformComponent>().getVelocity() * -1);
	}
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