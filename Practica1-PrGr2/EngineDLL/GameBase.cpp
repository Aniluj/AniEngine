#include "GameBase.h"


GameBase::GameBase()
{
}


GameBase::~GameBase()
{
}

bool GameBase::Start() 
{
	cout << "GameBase::Start()" << endl;

	window = new Window();
	renderer = new Renderer();

	if (!renderer->Start())
	{
		return false;
	}
	if (!window->Start(960,640,"gameWindow"))
	{
		return false;
	}

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
		res = OnUpdate();
		window->PollEvents();
	}
}