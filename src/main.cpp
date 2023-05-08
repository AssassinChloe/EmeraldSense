#include <SDL.h>
#include "Game.hpp"

int main(int argc, char* argv[])
{

	Game* game = nullptr;
	game = new Game();
	game->init("Emerald Sense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	std::cout << "init complete" << std::endl;

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();

	}
	game->clean();
	



	return 0;
}