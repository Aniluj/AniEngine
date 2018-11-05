#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Texture.h"
#include "CollisionManager.h"
#include <iostream>

using namespace std;

class Game : public GameBase
{
private:
	int i;
public:
	Game();
	~Game();
	Triangle* triangle;
	Rectangle* rectangle;
	Texture* texture;
	CollisionManager* collManager;
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

