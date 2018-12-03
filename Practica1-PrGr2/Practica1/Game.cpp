
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
	character = new Texture(
		renderer, 
		"Test-Spritesheet.bmp",
		20.0f,
		32,
		32,
		1,
		1);
	character->material = Material::CreateMaterial(
		"Shaders/TextureTransformVertexShader.txt",
		"Shaders/TextureFragmentShader.txt");

	character->testAnimation->AddFrame(2, 1);
	character->testAnimation->AddFrame(3, 1);
	character->testAnimation->AddFrame(4, 1);
	character->testAnimation->AddFrame(5, 1);
	character->testAnimation->AddFrame(6, 1);
	character->testAnimation->AddFrame(7, 1);
	character->testAnimation->AddFrame(8, 1);


	enemy = new Texture(
		renderer,
		"uvtemplate.bmp",
		100.0f,
		51.2f,
		51.2f,
		1,
		1
	);
	enemy->material = Material::CreateMaterial(
		"Shaders/TextureTransformVertexShader.txt",
		"Shaders/TextureFragmentShader.txt");

	enemy->testAnimation->AddFrame(2, 1);
	enemy->testAnimation->AddFrame(3, 1);
	enemy->testAnimation->AddFrame(4, 1);
	enemy->testAnimation->AddFrame(5, 1);
	enemy->testAnimation->AddFrame(6, 1);
	enemy->testAnimation->AddFrame(7, 1);
	enemy->testAnimation->AddFrame(8, 1);

	triangle = new Triangle(renderer);
	triangle->material = Material::CreateMaterial(
		"Shaders/VertexShader.txt",
		"Shaders/FragmentShader.txt");
	rectangle = new Rectangle(renderer, 10.0f);
	rectangle->material = Material::CreateMaterial(
		"Shaders/TransformVertexShader.txt",
		"Shaders/ColorFragmentShader.txt");

	collManager->RegisterBoundingBox(character->bbox);
	collManager->RegisterBoundingBox(rectangle->bbox);
	collManager->RegisterBoundingBox(enemy->bbox);

	/*collManager->RegisterBoundingCircle(character->bcircle);
	collManager->RegisterBoundingCircle(rectangle->bcircle);

	rectangle->Translate(600, 320, 0.0);
	texture->Translate(480, 320, 0.0);*/

	triangle->Translate(750, 400, 0);
	rectangle->Translate(320, 300, 0.0);
	character->Translate(320, 150, 0.0);
	enemy->Translate(600, 250, 0);

	i = 0;

	return true;
}

bool Game::OnStop() 
{
	cout << "Game::OnStop()" << endl;

	delete character;
	delete triangle;
	delete rectangle;
	delete collManager;

	return true;
}

bool Game::OnUpdate() 
{
	i++;
	
	//rectangle->Translate(rectangle->vectorPosition.x - 2, 320, 0.0);
	rectangle->Translate(rectangle->vectorPosition.x, rectangle->vectorPosition.y - (100 * deltaTime), 0.0);

	triangle->RotateZ(45-i);

	//rectangle->RotateZ(56+i);

	cout << rectangle->vectorPosition.y << endl;
	cout << rectangle->bbox->vectorPosition.y << endl;
	cout << character->vectorPosition.y << endl;
	cout << character->bbox->vectorPosition.y << endl;

	//cout << rectangle->vectorPosition.y << endl;
	//cout << rectangle->bcircle->vectorPosition.y << endl;
	//cout << texture->vectorPosition.y << endl;
	//cout << texture->bcircle->vectorPosition.y << endl;

	//texture->Translate(texture->vectorPosition.x + 2, 320, 0.0);
	character->Translate(character->vectorPosition.x, character->vectorPosition.y + (100 * deltaTime), 0.0);
	character->UpdateDT(deltaTime);

	enemy->Translate(enemy->vectorPosition.x - (150 * deltaTime), 350, 0.0);
	enemy->UpdateDT(deltaTime);

	//texture->RotateZ(56 + i);

	collManager->CheckForBoundingBoxCollisions();
	//collManager->CheckForBoundingCircleCollisions();

	return true;
}

void Game::OnDraw()
{
	character->Draw();
	enemy->Draw();
	triangle->Draw();
	rectangle->Draw();
}