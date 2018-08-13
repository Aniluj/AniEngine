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

	renderer = new Renderer();

	if (!renderer->Start())
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

	delete renderer;
	return true;
}

void GameBase::Loop() 
{
	cout << "GameBase::Loop()" << endl;

	bool res = true;

	while (res) 
	{
		res = OnUpdate();
	}
}