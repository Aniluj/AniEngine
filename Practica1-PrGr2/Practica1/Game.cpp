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

	triangle = new Triangle;
	i = 0;
	triangle->SetVertexArrayObject();
	triangle->SetBuffer();

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
	triangle->Draw();
	cout <<"Game::OnUpdate(): " << i << endl;

	return true;
}