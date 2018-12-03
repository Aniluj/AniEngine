#pragma once

#include "Exports.h"
#include <iostream>
#include "glm\glm.hpp"

class ENGINEDLL_API Sprite
{
public:
	Sprite(int frameRow, int frameColumn);
	~Sprite();

	float minU;
	float maxU;
	float minV;
	float maxV;

	int rowPositionOfFrame;
	int columPositionOfFrame;
};

