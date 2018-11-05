#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::OnStart()
{
	//string shaderPathMyPC = "C:/Image Campus/Segundo año/Programacion de Graficos 2/GameEngine-PrGr/Practica1-PrGr2/Shaders";
	//string shaderPathIC = "C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders";

	collManager = new CollisionManager();

	cout << "Game::OnStart() " << endl;
	texture = new Texture(renderer, "C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/uvtemplate.bmp");
	texture->material = Material::CreateMaterial("C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/TextureTransformVertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/TextureFragmentShader.txt");
	triangle = new Triangle(renderer);
	triangle->material = Material::CreateMaterial("C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/VertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/FragmentShader.txt");
	rectangle = new Rectangle(renderer);
	rectangle->material = Material::CreateMaterial("C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/TransformVertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/ColorFragmentShader.txt");

	collManager->RegisterBoundingBox(texture->bbox);
	collManager->RegisterBoundingBox(rectangle->bbox);

	i = 0;

	return true;
}

bool Game::OnStop() 
{
	cout << "Game::OnStop()" << endl;

	delete texture;
	delete triangle;
	delete rectangle;
	delete collManager;

	return true;
}

bool Game::OnUpdate() 
{
	rectangle->Translate(2.5, 2.5 + i/8, 0.0);
	triangle->RotateZ(45-i);
	//rectangle->RotateZ(56+i);
	//cout << rectangle-> << endl;
	cout << rectangle->vectorPosition.x << endl;
	cout << rectangle->bbox->vectorPosition.x << endl;
	texture->Translate(2.5, -2.0 + i/8, 0.0);
	//texture->RotateZ(56 + i);
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