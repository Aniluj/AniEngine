#pragma once

#include "Exports.h"
#include <iostream>
#include <list>
#include "Shape.h"
#include "Sprite.h"
#include "glm\glm.hpp"

using namespace std;

class ENGINEDLL_API Animation
{
private:
	Shape* receivedShape;
	list<Sprite*>* frameList;
	int currentColumn;
	int currentRow;
public:
	Animation(Shape* shape);
	~Animation();
	void Update(double deltaTime);
	void AddFrame(int frameRow, int frameColumn);
};

