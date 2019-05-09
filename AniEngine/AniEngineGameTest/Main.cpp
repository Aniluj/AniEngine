#include "Game.h"

using namespace std;

int main()
{
	Game* game = new Game();

	//TODO: startup

	if (game->Start())
	{
		game->Loop();
	}

	game->Stop();

	system("PAUSE");

	delete game;

	return 0;
}