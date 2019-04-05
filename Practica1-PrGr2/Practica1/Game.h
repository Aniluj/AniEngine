#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "Tilemap.h"
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
	Triangle* triangle;
	Rectangle* rectangle;
	Texture* character;
	Texture* enemy;
	CollisionManager* collManager;
	Tilemap* tilemap;
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

