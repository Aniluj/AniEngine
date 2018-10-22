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
	texture = new Texture(renderer, "C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/uvtemplate.bmp");
	texture->material = Material::CreateMaterial("C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/TextureTransformVertexShader.txt",
		"C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/TextureFragmentShader.txt");
	triangle = new Triangle(renderer);
	triangle->material = Material::CreateMaterial("C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/VertexShader.txt",
		"C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/FragmentShader.txt");
	rectangle = new Rectangle(renderer);
	rectangle->material = Material::CreateMaterial("C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/TransformVertexShader.txt",
		"C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders/ColorFragmentShader.txt");
	i = 0;

	return true;
}

bool Game::OnStop() 
{
	cout << "Game::OnStop()" << endl;

	delete texture;
	delete triangle;
	delete rectangle;

	return true;
}

bool Game::OnUpdate() 
{
	rectangle->Translate(2.5, 2.5, 0.0);
	triangle->RotateZ(45-i);
	rectangle->RotateZ(56+i);
	texture->Translate(-2.0, -2.0, 0.0);
	i++;
	cout <<"Game::OnUpdate(): " << i << endl;
	return true;
}

void Game::OnDraw()
{
	texture->Draw();
	triangle->Draw();
	rectangle->Draw();
}