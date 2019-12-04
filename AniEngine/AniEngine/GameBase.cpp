#include "GameBase.h"

double GameBase::deltaTime;

GameBase::GameBase()
{
}


GameBase::~GameBase()
{
}

bool GameBase::Start() 
{
	cout << "GameBase::Start()" << endl;

	deltaTime = 0;

	window = new Window();
	renderer = new Renderer();

	if (!window->Start(960,640,"gameWindow"))
	{
		return false;
	}
	if (!renderer->Start(window))
	{
		return false;
	}

	renderer->ClearColor(0.3f, 0.3f, 0.3f, 0.0);

	return OnStart();
}

bool GameBase::Stop() 
{

	cout << "GameBase::Stop()" << endl;

	if (!OnStop())
	{
		// log error
	}

	if (!renderer->Stop())
	{

	}

	if (!window->Stop())
	{

	}

	nScene = NULL;
	delete renderer;
	delete window;
	return true;
}

void GameBase::Loop() 
{
	cout << "GameBase::Loop()" << endl;

	bool res = true;

	while (res && !window->ShouldClose()) 
	{
		Timer::BeginClock();

		res = OnUpdate();

		renderer->ClearScreen();

		if (nScene)
		{
			nScene->Update();
		}

		renderer->entitiesCounter = 0;

		OnDraw();

		if (nScene)
		{
			renderer->MakeBSPClean(nScene);
			nScene->Draw();
		}

		cout << "Entities being drawn: " << renderer->entitiesCounter << endl;

		renderer->SwapBuffer();

		window->PollEvents();

		Timer::EndClock();

		deltaTime = Timer::GetDeltaTime();
	}
}

Node* GameBase::GetActualScene()
{
	return nScene;
}

void GameBase::SetScene(Node* scene)
{
	nScene = scene;
}