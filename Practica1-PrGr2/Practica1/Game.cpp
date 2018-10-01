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
	rectangle = new Rectangle(renderer);
	rectangle->material = Material::CreateMaterial("C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/VertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/FragmentShader.txt");
	triangle = new Triangle(renderer);
	triangle->material = Material::CreateMaterial("C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/TransformVertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/ColorFragmentShader.txt");
	i = 0;

	return true;
}

bool Game::OnStop() 
{
	cout << "Game::OnStop()" << endl;

	delete triangle;
	delete rectangle;

	return true;
}

bool Game::OnUpdate() 
{
	rectangle->Translate(2.5, 2.5, 0.0);
	//triangle->Translate(2.5, 2.5, 0.0);
	triangle->RotateZ(45);
	i++;
	cout <<"Game::OnUpdate(): " << i << endl;
	return true;
}

void Game::OnDraw()
{
	triangle->Draw();
	rectangle->Draw();
}