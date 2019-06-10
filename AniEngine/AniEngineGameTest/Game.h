#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Mesh.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "Tilemap.h"
#include "Camera.h"
#include "Input.h"
#include "ScGraphObject.h"
#include <iostream>
#include <time.h>

using namespace std;

class Game : public GameBase
{
private:
	int i;
	float timeLim = 4.0f;
	float timer;
public:
	Game();
	~Game();
	Camera* camera;
	Triangle* triangle;
	Rectangle* rectangle;
	Mesh* M4Fusil;
	Mesh* Spider;
	Sprite* character;
	Sprite* enemy;
	Input* input;
	CollisionManager* collManager;
	Tilemap* tilemap;
	ScGraphObject* exampleObject;
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

