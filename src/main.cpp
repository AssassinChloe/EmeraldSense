#include <SDL.h>
#include "Game.hpp"
#include "Const.hpp"

int main(int argc, char* argv[])
{
	Game* game = nullptr;
	game = new Game();
	game->init("Emerald Sense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, false);
	std::cout << "init complete" << std::endl;

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();

	}
	game->clean();
	delete(game);
	return 0;
}