#include "Game.hpp"
#include "ECS/Components.hpp"
#include "Collision.hpp"

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;
Manager manager;
Entity& player(manager.addEntity());
std::vector<Entity*> tilesV;
SDL_Rect Game::camera = {0,0,WIN_W,WIN_H};

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupColliders
};

Game::Game()
{
	this->isRunning = false;
	this->window = NULL; 
	this->map = NULL;
	this->up = this->left = this->down = this->right = 0;
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
			this->map->loadMap(MAP_PATH, MAP_WIDTH);
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
		case SDL_KEYDOWN:
			if (event.key.repeat == 0)
			{
				if (event.key.keysym.sym == SDLK_z)
				{
					if (this->timer == 0)
					{
						this->timer = 60;
						this->up = 1;
					}
					else
						this->up = 0;
				}
				else if (event.key.keysym.sym == SDLK_s)
					this->down = 1;
				else if (event.key.keysym.sym == SDLK_q)
					this->left = 1;
				else if (event.key.keysym.sym == SDLK_d)
					this->right = 1;
				else if (event.key.keysym.sym == SDLK_m)
					this->dig = 1;
				else if (event.key.keysym.sym == SDLK_ESCAPE)
					this->isRunning = false;
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_z)
			{
				this->up = 0;
				this->timer = 0;
			}
			else if (event.key.keysym.sym == SDLK_s)
				this->down = 0;
			else if (event.key.keysym.sym == SDLK_q)
				this->left = 0;
			else if (event.key.keysym.sym == SDLK_d)
				this->right = 0;
			else if (event.key.keysym.sym == SDLK_m)
				this->dig = 0;
			break;
		default:
			break;
	}

}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& colliders(manager.getGroup(groupColliders));

void Game::checkNear(Vector2D playerPos)
{
	int x = (playerPos.x + PLAYER_W / 2) / TILES_W;
	int y = (playerPos.y + PLAYER_H / 2) / TILES_H;
	Vector2D dir(static_cast<float>(this->right - this->left), static_cast<float>(this->down - this->up));
	if (x >= 2 && y >= 2 && x < MAP_WIDTH - 2 && y < MAP_HEIGHT - 2)
	{
		// GRAVITY !!
		if (this->timer == 0 && tilesV[(y + 1) * MAP_WIDTH + x]->getComponent<TileComponent>().isRigid() == false)
		{
			player.getComponent<TransformComponent>().setVelY(1);
		}
		else 
		{
			//DIGGING
			if (this->dig == 1)
			{
				if ((tilesV[(y + dir.y)*MAP_WIDTH + (x + dir.x)]->getComponent<TileComponent>().getId() == DIRT
					|| tilesV[(y + dir.y)*MAP_WIDTH + (x + dir.x)]->getComponent<TileComponent>().getId() == WORM))
				{
					tilesV[(y + dir.y) * MAP_WIDTH + (x + dir.x)]->destroy();
					this->addTile(DIG, ((x + dir.x) * TILES_W), ((y + dir.y) * TILES_H), map->getTex());
				}
				if ((tilesV[(y - 1 + dir.y) * MAP_WIDTH + (x + dir.x)]->getComponent<TileComponent>().getId() == DIRT
					|| tilesV[(y - 1 + dir.y) * MAP_WIDTH + (x + dir.x)]->getComponent<TileComponent>().getId() == WORM))
				{
					tilesV[(y - 1 + dir.y) * MAP_WIDTH + (x + dir.x)]->destroy();
					this->addTile(DIG, ((x + dir.x) * TILES_W), ((y - 1 + dir.y) * TILES_H), map->getTex());
				}

			}
			//COLLISION
			if ((dir.x < 0 && tilesV[(y)*MAP_WIDTH + x - 1]->hasComponent<ColliderComponent>()) || (dir.x > 0 && tilesV[(y)*MAP_WIDTH + x + 1]->hasComponent<ColliderComponent>()))
				dir.x = 0;
			if ((dir.y < 0 && tilesV[(y - 1) * MAP_WIDTH + x]->hasComponent<ColliderComponent>()) || (dir.y > 0 && tilesV[(y + 1) * MAP_WIDTH + x]->hasComponent<ColliderComponent>()))
				dir.y = 0;
			player.getComponent<TransformComponent>().setVelocity(dir);
		}
	}
	if (timer > 0)
		timer--;
}

void Game::update()
{
	//SDL_Rect playerCol = player.getComponent<ColliderComponent>().getCollider();
	Vector2D playerPos = player.getComponent<TransformComponent>().getPosition();


	manager.refresh();
	manager.update();

	camera.x = static_cast<int>(player.getComponent<TransformComponent>().getPosX() - (WIN_W / 2));
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().getPosY() - (WIN_H / 2));
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > ((MAP_WIDTH * TILES_W) - WIN_W))
		camera.x = (MAP_WIDTH * TILES_W) - WIN_W;
	if (camera.y > ((MAP_HEIGHT * TILES_H) - WIN_H))
		camera.y = (MAP_HEIGHT * TILES_H) - WIN_H;
	checkNear(playerPos);
}


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
	delete(this->map);
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

bool Game::running()
{
	return (this->isRunning);
}

void Game::addTile(int id, int x, int y, SDL_Texture *tex)
{
	Entity& tile(manager.addEntity());
	if (id == DIRT || id == WORM || id == ROCK)
	{
		tile.addComponent<TileComponent>(x, y, TILES_H, TILES_W, id, tex, true);
		tile.addComponent<ColliderComponent>(id);
		tile.addGroup(groupColliders);
	}
	else
	{
		tile.addComponent<TileComponent>(x, y, TILES_H, TILES_W, id, tex, false);
	}
	tile.addGroup(groupMap);
	if (tilesV.size() < (MAP_WIDTH * MAP_HEIGHT))
	{
		tilesV.push_back(&tile);
	}
	else
	{
		tilesV[(x / TILES_W) + (y / TILES_H * MAP_WIDTH)] = &tile;
	}
}

void Game::buildPlayer()
{
	player.addComponent<TransformComponent>(static_cast<float>(PLAYER_X), static_cast<float>(PLAYER_Y), PLAYER_W, PLAYER_H, 1);
	player.addComponent<SpriteComponent>(PLAYER_PATH, PLAYER_TEX_SIZE, PLAYER_ANIMATED);
	player.getComponent<SpriteComponent>().addAnimation(IDLE, PLAYER_IDLE_FRAMES, PLAYER_ANIM_SPEED);
	player.getComponent<SpriteComponent>().addAnimation(WALK, PLAYER_WALK_FRAMES, PLAYER_ANIM_SPEED);
	//player.getComponent<SpriteComponent>().addAnimation(WALK_L, PLAYER_WALK_LEFT_FRAMES, PLAYER_ANIM_SPEED);
	//player.getComponent<SpriteComponent>().addAnimation(WALK_R, PLAYER_WALK_RIGHT_FRAMES, PLAYER_ANIM_SPEED);
	//player.getComponent<SpriteComponent>().addAnimation(WALK_B, PLAYER_WALK_BACK_FRAMES, PLAYER_ANIM_SPEED);
	player.addComponent<ColliderComponent>(PLAYER_ID);
	player.addGroup(groupPlayers);

	//POUR TRANSFORMER L'ENVIRONNEMENT AUTOUR DU JOUEUR EN VIDE
	int x = (PLAYER_X + PLAYER_W / 2) / TILES_W;
	int y = (PLAYER_Y + PLAYER_H / 2) / TILES_H;

	for (int h = y - 3; h < y + 3; h++)
	{
		for (int w = x - 3; w < x + 3; w++)
		{
			tilesV[h * MAP_WIDTH + w]->destroy();
			this->addTile(DIG, (w * TILES_W), (h * TILES_H), map->getTex());
		}
	}

}