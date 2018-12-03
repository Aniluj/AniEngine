
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::OnStart()
{

	collManager = new CollisionManager();

	//bmp base = uvtemplate.bmp
	//bmp test spritesheet = Test-Spritesheet1.bmp

	cout << "Game::OnStart() " << endl;
	texture = new Texture(
		renderer, 
		"Test-Spritesheet.bmp",
		100.0f,
		32,
		32,
		1,
		1);
	texture->material = Material::CreateMaterial(
		"Shaders/TextureTransformVertexShader.txt",
		"Shaders/TextureFragmentShader.txt");
	triangle = new Triangle(renderer);
	triangle->material = Material::CreateMaterial(
		"Shaders/VertexShader.txt",
		"Shaders/FragmentShader.txt");
	rectangle = new Rectangle(renderer, 10);
	rectangle->material = Material::CreateMaterial(
		"Shaders/TransformVertexShader.txt",
		"Shaders/ColorFragmentShader.txt");

	collManager->RegisterBoundingBox(texture->bbox);
	collManager->RegisterBoundingBox(rectangle->bbox);

	collManager->RegisterBoundingCircle(texture->bcircle);
	collManager->RegisterBoundingCircle(rectangle->bcircle);

	//rectangle->Translate(600, 320, 0.0);
	//texture->Translate(480, 320, 0.0);

	rectangle->Translate(320, 300, 0.0);
	texture->Translate(320, 150, 0.0);

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
	//i++;
	
	//rectangle->Translate(rectangle->vectorPosition.x - 2, 320, 0.0);
	rectangle->Translate(320, rectangle->vectorPosition.y - 2, 0.0);

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

	//texture->Translate(texture->vectorPosition.x + 2, 320, 0.0);
	texture->Translate(320, texture->vectorPosition.y, 0.0);
	texture->UpdateDT(deltaTime);

	//texture->RotateZ(56 + i);

	collManager->CheckForBoundingBoxCollisions();
	//collManager->CheckForBoundingCircleCollisions();

	return true;
}

void Game::OnDraw()
{
	texture->Draw();
	triangle->Draw();
	rectangle->Draw();
}