#include "Game.hpp"
#include "ECS/Components.hpp"
#include "Collision.hpp"
#include "Const.hpp"

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;
Manager manager;
Entity& player(manager.addEntity());
std::vector<Entity*> tilesV;

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

Game::Game()
{
	this->isRunning = false;
	this->window = NULL; 
	this->map = NULL;
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
			Map::loadMap(MAP_PATH, MAP_WIDTH, MAP_HEIGHT);
			buildPlayer();
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

	for (auto cc : colliders)
	{
		if (cc != &player.getComponent<ColliderComponent>() && Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
		{
			if (cc->getTag() == DIRT)
			{
				this->addTile(DIG, cc->getCollider().x, cc->getCollider().y);
				cc->entity->destroy();
			}
		}
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
//auto& enemies(manager.getGroup(groupEnemies));

void Game::render()
{
	SDL_RenderClear(this->renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	//for (auto& e : enemies)
	//{
	//	e->draw();
	//}
	SDL_RenderPresent(this->renderer);
}
void Game::clean()
{
	player.destroy();
	for (Entity* t : tilesV)
	{
		t->destroy();
	}
	manager.refresh();
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

void Game::addTile(int id, int x, int y)
{
	Entity& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, TILES_H, TILES_W, id);
	tile.addGroup(groupMap);
	if (id == DIRT || id == WORM || id == ROCK)
	{
		tile.addComponent<ColliderComponent>(id);
	}
	tilesV.push_back(&tile);
}

void Game::buildPlayer()
{
	player.addComponent<TransformComponent>(static_cast<float>(PLAYER_X), static_cast<float>(PLAYER_Y), PLAYER_W, PLAYER_H, 1);
	player.addComponent<SpriteComponent>(PLAYER_PATH, PLAYER_TEX_SIZE, PLAYER_ANIMATED);
	player.getComponent<SpriteComponent>().addAnimation(IDLE, PLAYER_IDLE_FRAMES, PLAYER_ANIM_SPEED);
	player.getComponent<SpriteComponent>().addAnimation(WALK, PLAYER_WALK_FRAMES, PLAYER_ANIM_SPEED);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>(PLAYER_ID);
	player.addGroup(groupPlayers);
}