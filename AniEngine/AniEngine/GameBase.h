#pragma once

#include <iostream>
#include "Exports.h"
#include "Renderer.h"
#include "TypeDef.h"
#include "Window.h"
#include "Node.h"
#include "Timer.h"

using namespace std;

class ENGINEDLL_API GameBase
{
private:
	Node* nScene;
public:
	GameBase();
	~GameBase();
	bool Start();
	bool Stop();
	void Loop();
	Node* GetActualScene();
	void SetScene(Node* scene);
	Renderer* renderer;
	Window* window;
	static double deltaTime;
protected:
	bool virtual OnStart()= 0;
	bool virtual OnStop()= 0;
	bool virtual OnUpdate() = 0;
	void virtual OnDraw() = 0;
};

