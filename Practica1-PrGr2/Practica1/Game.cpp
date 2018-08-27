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

	i = 0;

	return true;
}

bool Game::OnStop() 
{
	cout << "Game::OnStop()" << endl;

	return true;
}

bool Game::OnUpdate() 
{
	i++;

	cout <<"Game::OnUpdate(): " <<i << endl;

	//if (i > 5)
	//{
	//	return false;
	//}

	return true;
}