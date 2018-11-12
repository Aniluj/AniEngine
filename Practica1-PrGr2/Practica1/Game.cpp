
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
	texture = new Texture(renderer, 
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/uvtemplate.bmp",
		100);
	texture->material = Material::CreateMaterial(
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/TextureTransformVertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/TextureFragmentShader.txt");
	triangle = new Triangle(renderer);
	triangle->material = Material::CreateMaterial(
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/VertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/FragmentShader.txt");
	rectangle = new Rectangle(renderer, 10);
	rectangle->material = Material::CreateMaterial(
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/TransformVertexShader.txt",
		"C:/Users/Administrador/Desktop/GameEngine-PrGr/Practica1-PrGr2/Shaders/ColorFragmentShader.txt"
		);

	collManager->RegisterBoundingBox(texture->bbox);
	collManager->RegisterBoundingBox(rectangle->bbox);

	collManager->RegisterBoundingCircle(texture->bcircle);
	collManager->RegisterBoundingCircle(rectangle->bcircle);

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
	i++;
	rectangle->Translate(2.5 - i / 26, -2.5, 0.0);
	triangle->RotateZ(45-i);

	//rectangle->RotateZ(56+i);

	cout << rectangle->vectorPosition.y << endl;
	cout << rectangle->bbox->vectorPosition.y << endl;
	cout << texture->vectorPosition.y << endl;
	cout << texture->bbox->vectorPosition.y << endl;

	//cout << rectangle->vectorPosition.y << endl;
	//cout << rectangle->bcircle->vectorPosition.y << endl;
	//cout << texture->vectorPosition.y << endl;
	//cout << texture->bcircle->vectorPosition.y << endl;
	texture->Translate(-2.5 + i / 15, -2.5, 0.0);

	//texture->RotateZ(56 + i);

	collManager->CheckForBoundingBoxCollisions();
	//collManager->CheckForBoundingCircleCollisions();

	cout <<"Game::OnUpdate(): " << i << endl;
	return true;
}

void Game::OnDraw()
{
	texture->Draw();
	triangle->Draw();
	rectangle->Draw();
}