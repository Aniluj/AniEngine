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
	triangle->material = Material::CreateMaterial("C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/VertexShader.txt", "C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/FragmentShader.txt");
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
	triangle->Translate(2.0,1.5,0.5);
	i++;
	cout <<"Game::OnUpdate(): " << i << endl;
	return true;
}

void Game::OnDraw()
{
	triangle->Draw();
}