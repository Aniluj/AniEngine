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

	renderer->ClearColor(0, 0, 0.4, 0);

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
		clock_t begin = clock();
		res = OnUpdate();
		renderer->ClearScreen();
		OnDraw();
		renderer->SwapBuffer();
		window->PollEvents();
		clock_t end = clock();

		deltaTime = double(end -begin) / CLOCKS_PER_SEC;
	}
}

double & GameBase::GetDeltaTime()
{
	return deltaTime;
}