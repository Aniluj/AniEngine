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

	sceneBSPTest = new Node("Scene", renderer);
	SetScene(sceneBSPTest);

	sceneObjects = new Node("Objects", renderer);
	sceneBSPTest->AddChild(sceneObjects);

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
	//shapeExampleObject = new ScGraphShapeObject("shapeExampleObject", renderer);

	//M4Fusil = new Mesh("M4A1/M4A1.FBX", renderer, "M4A1/M4A1Tex.bmp");
	//Spider = new Mesh("Spider/spider.obj", renderer, "Spider/SpiderTex.bmp");

	/*tilemap->material = Material::CreateMaterial(
	"Shaders/TextureTransformVertexShader.txt",
	"Shaders/TextureFragmentShader.txt");*/

	Weapon1Root = new Node("Weapon1Root", renderer);
	Weapon1Root->transform->Translate(0.0f, 0.0f, 5.0f);
	sceneObjects->AddChild(Weapon1Root);

	Weapon1 = new Node("Weapon1", renderer);
	Weapon1Root->AddChild(Weapon1);
	Weapon1Mesh = new MeshComponentLoader();
	Weapon1Mesh->Start("M4_1 Mesh", Weapon1, "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", renderer);
	Weapon1->AddComponent(Weapon1Mesh);

	Weapon2Root = new Node("Weapon2Root", renderer);
	Weapon2Root->transform->Translate(-90.0f, 0.0f, 5.0f);
	sceneObjects->AddChild(Weapon2Root);

	Weapon2 = new Node("Weapon2", renderer);
	Weapon2Root->AddChild(Weapon2);
	Weapon2Mesh = new MeshComponentLoader();
	Weapon2Mesh->Start("M4_2 Mesh", Weapon2, "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", renderer);
	Weapon2->AddComponent(Weapon2Mesh);

	Weapon3Root = new Node("Weapon3Root", renderer);
	Weapon3Root->transform->Translate(90.0f, 0.0f, 5.0f);
	sceneObjects->AddChild(Weapon3Root);

	Weapon3 = new Node("Weapon3", renderer);
	Weapon3Root->AddChild(Weapon3);
	Weapon3Mesh = new MeshComponentLoader();
	Weapon3Mesh->Start("M4_3 Mesh", Weapon3, "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", renderer);
	Weapon3->AddComponent(Weapon3Mesh);

	Weapon4Root = new Node("Weapon4Root", renderer);
	Weapon4Root->transform->Translate(-15.0f, 0.0f, 90.0f);
	sceneObjects->AddChild(Weapon4Root);

	Weapon4 = new Node("Weapon4", renderer);
	Weapon4Root->AddChild(Weapon4);
	Weapon4Mesh = new MeshComponentLoader();
	Weapon4Mesh->Start("M4_4 Mesh", Weapon4, "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", renderer);
	Weapon4->AddComponent(Weapon4Mesh);

	Weapon5Root = new Node("Weapon5Root", renderer);
	Weapon5Root->transform->Translate(-30.0f, 0.0f, 90.0f);
	sceneObjects->AddChild(Weapon5Root);

	Weapon5 = new Node("Weapon5", renderer);
	Weapon5Root->AddChild(Weapon5);
	Weapon5Mesh = new MeshComponentLoader();
	Weapon5Mesh->Start("M4_5 Mesh", Weapon5, "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", renderer);
	Weapon5->AddComponent(Weapon5Mesh);

	nBSP1 = new Node("BSP1", renderer);
	sceneBSPTest->AddChild(nBSP1);

	nBSP1->transform->Translate(40.0f, 0.0f, 15.0f);
	nBSP1->transform->RotateY(90.0f);
	BSPComponent1 = new BSP();
	BSPComponent1->Start("BSP 1", renderer, camera, nBSP1->transform);
	nBSP1->AddComponent(BSPComponent1);

	nBSP2 = new Node("BSP2", renderer);
	sceneBSPTest->AddChild(nBSP2);

	nBSP2->transform->Translate(-40.0f, 0.0f, 15.0f);
	nBSP2->transform->RotateY(90.0f);
	BSPComponent2 = new BSP();
	BSPComponent2->Start("BSP 2", renderer, camera, nBSP2->transform);
	nBSP2->AddComponent(BSPComponent2);

	nBSP3 = new Node("BSP3", renderer);
	sceneBSPTest->AddChild(nBSP3);

	nBSP3->transform->Translate(0.0f, 0.0f, 65.0f);
	nBSP3->transform->RotateY(180.0f);
	BSPComponent3 = new BSP();
	BSPComponent3->Start("BSP 3", renderer, camera, nBSP3->transform);
	nBSP3->AddComponent(BSPComponent3);


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

	//triangle->Translate(750, 400, 0.0);
	//rectangle->Translate(320, 300, 1000);
	//character->Translate(320, 150, 0.0);
	//enemy->Translate(600, 250, 0.0);
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
		camera->Walk(cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_S))
	{
		camera->Walk(-cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_A))
	{
		camera->Strafe(cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_D))
	{
		camera->Strafe(-cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_F))
	{
		camera->Yaw(cameraSpeed * deltaTime);

		/*shapeExampleObject->transform->Translate(shapeExampleObject->transform->localPosition.x,
												 shapeExampleObject->transform->localPosition.y - (100 * deltaTime),
												 shapeExampleObject->transform->localPosition.z
												);*/


												//exampleObject->M4->transform->Translate(exampleObject->M4->transform->localPosition.x,
												//	exampleObject->M4->transform->localPosition.y - (100 * deltaTime),
												//	exampleObject->M4->transform->localPosition.z
												//);
												//exampleObject->M4->transform->Translate(exampleObject->M4->transform->localPosition.x - (100 * deltaTime),
												//	exampleObject->M4->transform->localPosition.y,
												//	exampleObject->M4->transform->localPosition.z
												//);
	}
	if (input->isInput(GLFW_KEY_G))
	{
		camera->Yaw(-cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_Q))
	{
		camera->Roll(-cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_E))
	{
		camera->Roll(cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_C))
	{
		camera->Pitch(cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_Z))
	{
		camera->Pitch(-cameraSpeed * deltaTime);
	}
	if (input->isInput(GLFW_KEY_LEFT_ALT))
	{
		Weapon1Root->transform->Translate(
			Weapon1Root->transform->localPosition.x - (100 * deltaTime),
			Weapon1Root->transform->localPosition.y,
			Weapon1Root->transform->localPosition.z
		);
	}
	if (input->isInput(GLFW_KEY_LEFT_CONTROL))
	{
		Weapon1Root->transform->Translate(
			Weapon1Root->transform->localPosition.x + (100 * deltaTime),
			Weapon1Root->transform->localPosition.y,
			Weapon1Root->transform->localPosition.z
		);
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

	//character->Translate(character->vectorPosition.x, character->vectorPosition.y + (100 * deltaTime), 0.0);
	//character->UpdateDT(deltaTime);

	//enemy->Translate(enemy->vectorPosition.x - (150 * deltaTime), 350, 0.0);
	//enemy->UpdateDT(deltaTime);

	//shapeExampleObject->Update();

	//texture->RotateZ(56 + i);
	//M4Fusil->RotateZ(-i);
	//Spider->RotateY(-i);
	//collManager->CheckForBoundingBoxCollisions();
	//collManager->CheckForBoundingCircleCollisions();

	return true;
}

void Game::OnDraw()
{
	//character->Draw();
	//enemy->Draw();

	//M4Fusil->Draw();
	//Spider->Draw();
	//exampleObject->Draw();

	//shapeExampleObject->Draw();
	//triangle->Draw();
	//rectangle->Draw();
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
	delete shapeExampleObject;

	delete Weapon1Root;
	delete Weapon1;
	delete Weapon1Mesh;

	delete Weapon2Root;
	delete Weapon2;
	delete Weapon2Mesh;

	delete Weapon3Root;
	delete Weapon3;
	delete Weapon3Mesh;

	delete Weapon4Root;
	delete Weapon4;
	delete Weapon4Mesh;

	delete Weapon5Root;
	delete Weapon5;
	delete Weapon5Mesh;

	delete sceneBSPTest;
	delete nBSP1;
	delete BSPComponent1;
	delete nBSP2;
	delete BSPComponent2;
	delete nBSP3;
	delete BSPComponent3;

	return true;
}