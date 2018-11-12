#pragma once

#include "Exports.h"
#include "Shape.h"
#include <iostream>
#include "glm\glm.hpp"

using namespace std;


class ENGINEDLL_API BoundingCircle
{
public:
	BoundingCircle(const char * tag);
	~BoundingCircle();

	bool isStatic;

	float mass;

	float radius;
	glm::vec3 vectorPosition;
	string bcircleTag;
	void UpdateBoundingCircleModel(float radiusParam, glm::vec3 entityVectorPosition, float &massToSet);
};

