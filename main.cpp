#include <SDL2/SDL.h>
#include "Game.hpp"
#include "Const.hpp"

int main()
{
	Game* game = nullptr;
	game = new Game();
	game->init("Emerald Sense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, false);
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