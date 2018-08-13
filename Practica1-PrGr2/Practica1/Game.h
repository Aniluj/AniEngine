#pragma once

#include "GameBase.h"
#include <iostream>

using namespace std;

class Game : public GameBase
{
private:
	int i;
public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
};

