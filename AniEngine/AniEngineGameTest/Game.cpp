#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

bool Game::OnStart()
{
	//renderer->SetProjectionMatrixToPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	//renderer->SetViewMatrix(glm::vec3(window->GetWidth()/2, window->GetHeight()/2, window->GetWidth()), glm::vec3(window->GetWidth()/2, window->GetHeight()/2, 0), glm::vec3(0, 1, 0));
	
	camera = new Camera(renderer);
	collManager = new CollisionManager();
	input = Input::getInstance();
	input->SetWindowContext(window);

	//bmp base = uvtemplate.bmp
	//bmp test spritesheet = Test-Spritesheet1.bmp

	cout << "Game::OnStart() " << endl;
	character = new Sprite(
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


	enemy = new Sprite(
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
	
	exampleObject = new ScGraphObject(renderer);
	//M4Fusil = new Mesh("M4A1/M4A1.FBX", renderer, "M4A1/M4A1Tex.bmp");
	//Spider = new Mesh("Spider/spider.obj", renderer, "Spider/SpiderTex.bmp");

	/*tilemap->material = Material::CreateMaterial(
	"Shaders/TextureTransformVertexShader.txt",
	"Shaders/TextureFragmentShader.txt");*/

	tilemap = new Tilemap(
		renderer,
		1,
		2,
		960,
		640,
		"BattleCityCloneTiles.bmp",
		"BattleCityCloneTiledMap.csv");

	collManager->RegisterBoundingBox(character->bbox);
	collManager->RegisterBoundingBox(rectangle->bbox);
	collManager->RegisterBoundingBox(enemy->bbox);

	/*collManager->RegisterBoundingCircle(character->bcircle);
	collManager->RegisterBoundingCircle(rectangle->bcircle);

	rectangle->Translate(600, 320, 0.0);
	texture->Translate(480, 320, 0.0);*/

	triangle->Translate(750, 400, 0.0);
	rectangle->Translate(320, 300, 0.0);
	character->Translate(320, 150, 0.0);
	enemy->Translate(600, 250, 0.0);
	//M4Fusil->Translate(480, 370, 1200);
	//M4Fusil->RotateZ(90);
	//M4Fusil->RotateX(-90);
	//Spider->Translate(480, 305, 1200);
	//mesh->Translate(480, 312, 1475);

	i = 0;

	return true;
}


bool Game::OnUpdate() 
{
	i++;
	timer += deltaTime;
	
	if (input->isInput(GLFW_KEY_W))
	{
		camera->Walk(-30 * deltaTime);
	}
	if (input->isInput(GLFW_KEY_S))
	{
		camera->Walk(30 * deltaTime);
	}
	if (input->isInput(GLFW_KEY_A))
	{
		camera->Strafe(-75 * deltaTime);
	}
	if (input->isInput(GLFW_KEY_D))
	{
		camera->Strafe(75 * deltaTime);
	}
	if (input->isInput(GLFW_KEY_F))
	{
		camera->Yaw(0.5f);
	}
	if (input->isInput(GLFW_KEY_G))
	{
		camera->Yaw(-0.5f);
	}
	if (input->isInput(GLFW_KEY_Q))
	{
		camera->Roll(0.5);
	}
	if (input->isInput(GLFW_KEY_E))
	{
		camera->Roll(-0.5);
	}
	if (input->isInput(GLFW_KEY_C))
	{
		camera->Pitch(0.5f);
	}
	if (input->isInput(GLFW_KEY_Z))
	{
		camera->Pitch(-0.5f);
	}
	//camera->Pitch(-0.7f);
	//camera->Roll(0.3);
	

	/*if (timer >= timeLim)
	{
		cout << "SALIO" << endl;
		renderer->SetProjectionMatrixToOrtho(0.0f, 450.0f, 0.0f, 500.0f, 0.0f, 100.0f);
	}*/

	//rectangle->Translate(rectangle->vectorPosition.x - 2, 320, 0.0);

	//rectangle->Translate(rectangle->vectorPosition.x, rectangle->vectorPosition.y - (100 * deltaTime), 0.0);

	//triangle->RotateZ(-i);

	//rectangle->RotateZ(56+i);

	//cout << rectangle->vectorPosition.y << endl;
	//cout << rectangle->bbox->vectorPosition.y << endl;
	//cout << character->vectorPosition.y << endl;
	//cout << character->bbox->vectorPosition.y << endl;

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
	//M4Fusil->RotateZ(-i);
	//Spider->RotateY(-i);
	//collManager->CheckForBoundingBoxCollisions();
	//collManager->CheckForBoundingCircleCollisions();

	return true;
}

void Game::OnDraw()
{
	character->Draw();
	enemy->Draw();
	exampleObject->Draw();
	//triangle->Draw();
	//rectangle->Draw();
	//M4Fusil->Draw();
	//Spider->Draw();
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;

	delete character;
	delete triangle;
	delete rectangle;
	//delete M4Fusil;
	//delete Spider;
	delete collManager;
	delete camera;
	delete exampleObject;

	return true;
}