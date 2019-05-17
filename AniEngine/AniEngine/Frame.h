#pragma once

#include "Exports.h"
#include <iostream>
#include "glm\glm.hpp"

class ENGINEDLL_API Frame
{
public:
	Frame(int frameRow, int frameColumn);
	~Frame();

	float minU;
	float maxU;
	float minV;
	float maxV;

	int rowPositionOfFrame;
	int columPositionOfFrame;
};

