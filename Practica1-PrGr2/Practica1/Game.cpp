#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::OnStart()
{
	cout << "Game::OnStart() " << endl;
	triangle = new Triangle(renderer);
	i = 0;

	return true;
}

bool Game::OnStop() 
{
	cout << "Game::OnStop()" << endl;

	delete triangle;

	return true;
}

bool Game::OnUpdate() 
{
	i++;
	cout <<"Game::OnUpdate(): " << i << endl;

	return true;
}

void Game::OnDraw()
{
	triangle->Draw();
}